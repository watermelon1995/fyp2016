#define M1_FULL_FORWARD 127
#define M1_HALF_FORWARD 96
#define M1_FULL_REVERSE 1

#define M2_FULL_FORWARD 255
#define M2_HALF_FORWARD 224
#define M2_FULL_REVERSE 128

#define ALL_STOP 0

#include <Wire.h>
#include <TimerOne.h>
#include <L3G4200D.h>
#include <HMC5883L.h>
#include <SoftwareSerial.h>

#define d_rx 6
#define d_tx 7

#define b_rx 8
#define b_tx 9

//SoftwareSerial bt( b_rx, b_tx);
#define  CTRL_REG1  0x20
#define  CTRL_REG2  0x21
#define  CTRL_REG3  0x22
#define  CTRL_REG4  0x23
#define  CTRL_REG5  0x24
#define  CTRL_REG6  0x25

#define Register_ID 0
#define Register_2D 0x2D
#define Register_X0 0x32
#define Register_X1 0x33
#define Register_Y0 0x34
#define Register_Y1 0x35
#define Register_Z0 0x36
#define Register_Z1 0x37


int accI2CAddr=0xA7 >>1;
int gyroI2CAddr=105;

int X0,X1,X_out;
int Y0,Y1,Y_out;
int Z0,Z1,Z_out;

float pose_x = 0.0;
float pose_y = 0.0;

double accRaw[3];

int gyroRaw[3];                         // raw sensor data, each axis, pretty useless really but here it is.
double gyroDPS[3];                      // gyro degrees per second, each axis

float heading[3]={0.0f};                // heading[x], heading[y], heading [z]

int gyroZeroRate[3];                    // Calibration data.  Needed because the sensor does center at zero, but rather always reports a small amount of rotation on each axis.
int gyroThreshold[3];                   // Raw rate change data less than the statistically derived threshold is discarded.

#define  NUM_GYRO_SAMPLES  50           // As recommended in STMicro doc
#define  GYRO_SIGMA_MULTIPLE  3         // As recommended

float dpsPerDigit=.00875f;              // for conversion to degrees per second

unsigned long lastMilli;
unsigned long interval;


//Connection interface with the motor driver
SoftwareSerial driver(d_rx , d_tx);

HMC5883L compass;


struct MOVEMENT {
  byte m1_command;
  byte m2_command;
  unsigned int duration;
};

MOVEMENT m, last_m;

boolean new_move = false;

byte movement_buffer[6];

void setup() {
  driver.begin(9600);
  Serial.begin(115200);
  pinMode(13, OUTPUT);

  Wire.begin();
  Wire.beginTransmission(accI2CAddr);
  Wire.write(Register_2D);
  Wire.write(8);                //measuring enable
  Wire.endTransmission();     // stop transmitting

//
//  //Initalize Timer interrupt
//  Timer1.initialize(5000);
//  Timer1.attachInterrupt(timerIsr);

  //enable Gyro
  Wire.begin();
  setupGyro();
  calibrateGyro();

//  delay(2000);
//  motor_stop();
 compass = HMC5883L(); // Construct a new HMC5883 compass.
 compass.SetMeasurementMode(Measurement_Continuous);

}




void read_acc() {
  //--------------X
  int i;

  X_out=0;
  for(i=0;i<10;i++) {
    Wire.beginTransmission(accI2CAddr); // transmit to device
    Wire.write(Register_X0);
    Wire.write(Register_X1);
    Wire.endTransmission();
    Wire.requestFrom(accI2CAddr,2);
    if(Wire.available()<=2)
    {
      X0 = Wire.read();
      X1 = Wire.read();
      X1=X1<<8;
      X_out+=(X0+X1);
    }
  }
  X_out/=10;

  //------------------Y
  Wire.beginTransmission(accI2CAddr); // transmit to device
  Wire.write(Register_Y0);
  Wire.write(Register_Y1);
  Wire.endTransmission();
  Wire.requestFrom(accI2CAddr,2);
  if(Wire.available()<=2)
  {
    Y0 = Wire.read();
    Y1 = Wire.read();
    Y1=Y1<<8;
    Y_out=Y0+Y1;
  }
  //------------------Z
  Wire.beginTransmission(accI2CAddr); // transmit to device
  Wire.write(Register_Z0);
  Wire.write(Register_Z1);
  Wire.endTransmission();
  Wire.requestFrom(accI2CAddr,2);
  if(Wire.available()<=2)
  {
    Z0 = Wire.read();
    Z1 = Wire.read();
    Z1=Z1<<8;
    Z_out=Z0+Z1;
  }
  accRaw[0]=X_out/256.0;
  accRaw[1]=Y_out/256.0;
  accRaw[2]=Z_out/256.0;
  pose_x+=accRaw[0];
  pose_y+=accRaw[1];
}



// Kalman filter module
 //
 // float Q_angle  =  0.001;
 // float Q_gyro   =  0.003;
 // float R_angle  =  0.03;
 //
 // float x_angle = 0;
 // float x_bias = 0;
 // float P_00 = 0, P_01 = 0, P_10 = 0, P_11 = 0;
 // float dt, y, S;
 // float K_0, K_1;
 //
 //
 //  float kalmanCalculate(float newAngle, float newRate,int looptime) {
 //    dt = float(looptime)/1000;
 //    x_angle += dt * (newRate - x_bias);
 //    P_00 +=  - dt * (P_10 + P_01) + Q_angle * dt;
 //    P_01 +=  - dt * P_11;
 //    P_10 +=  - dt * P_11;
 //    P_11 +=  + Q_gyro * dt;
 //
 //    y = newAngle - x_angle;
 //    S = P_00 + R_angle;
 //    K_0 = P_00 / S;
 //    K_1 = P_10 / S;
 //
 //    x_angle +=  K_0 * y;
 //    x_bias  +=  K_1 * y;
 //    P_00 -= K_0 * P_00;
 //    P_01 -= K_0 * P_01;
 //    P_10 -= K_1 * P_00;
 //    P_11 -= K_1 * P_01;
 //
 //    return x_angle;
 //  }

void motor_stop(){
  driver.write((byte)ALL_STOP);
//  Serial.println("S");
//  bt.println("S");
}

void motor_fast_forward(){
  driver.write((byte)M1_FULL_FORWARD);
  driver.write((byte)M2_FULL_FORWARD);
//  Serial.println("F");
//  bt.println("F");
}


void motor_fast_backward(){
  driver.write((byte)M1_FULL_REVERSE);
  driver.write((byte)M2_FULL_REVERSE);
//  Serial.println("B");
//  bt.println("B");
}

char cmd;
String read_data = "";

void read_movement_command(){
  Serial.readBytes(movement_buffer, 6);

//  for(int i = 0;i<6;i++){
////    Serial.println(movement_buffer[i]);
//      if(movement_buffer[i] == 127){
//        digitalWrite(13, HIGH);
//      }
//  }

  m.m1_command = movement_buffer[0];
  m.m2_command = movement_buffer[1];
  Serial.flush();
  m.duration = (movement_buffer[5] << 24) | (movement_buffer[4] << 16) | (movement_buffer[3] << 8) | movement_buffer[2];

  if(m.duration == 1000){
    digitalWrite(13, HIGH);
  }
}

void reset(){
  for(int i = 0;i<6;i++){
    movement_buffer[i] = 0;
  }
  last_m.m1_command = m.m1_command;
  last_m.m2_command = m.m2_command;
  last_m.duration = m.duration;

  m.m1_command = 0;
  m.m2_command = 0;
  m.duration = 0;
}

void serialEvent() {
  while (Serial.available()) {
  Serial.readBytes(movement_buffer, 6);

    m.m1_command = movement_buffer[0];
    m.m2_command = movement_buffer[1];
    Serial.flush();
    m.duration = (movement_buffer[5] << 24) | (movement_buffer[4] << 16) | (movement_buffer[3] << 8) | movement_buffer[2];

    if(m.duration == 1000){
      digitalWrite(13, HIGH);
    }

      driver.write((byte)m.m1_command);
      driver.write((byte)m.m2_command);
      delay(m.duration);
      motor_stop();
      digitalWrite(13, LOW);
      new_move = true;
      reset();
  }
}

void comand_mode(){
  read_movement_command();
  driver.write((byte)m.m1_command);
  driver.write((byte)m.m2_command);
  delay(m.duration);
  motor_stop();
  digitalWrite(13, LOW);
  reset();
}

void auto_mode(){
  motor_fast_forward();
  delay(1000);
  motor_stop();
  delay(1000);
}

//void read_gyro(){
//  gyro.read();
//  RawGyro[0] = gyro.g.x/256.0;
//  RawGyro[1] = gyro.g.y/256.0;
//  RawGyro[2] = gyro.g.z/256.0;
//}

//Timer Routine
void timerIsr(){
//  static unsigned long newMilli;
//
//  newMilli = millis();
//
//  read_gyro();
//
//  delta = newMilli - lastMilli;
//
//  if(delta < 0.0){
//    delta = newMilli+(4294967295-lastMilli);
//  }
//
//  headings -= (RawGyro[2]*delta)/1000000.0f;
//
//
////  Serial.println(headings);
//
//  lastMilli = newMilli;

}


void updateHeadings()
{

  float deltaT=getDeltaTMicros();

  for (int j=0;j<3;j++)
    heading[j] -= (gyroDPS[j]*deltaT)/1000000.0f;
}

// this simply returns the elapsed time since the last call.
unsigned long getDeltaTMicros()
{
  static unsigned long lastTime=0;

  unsigned long currentTime=micros();

  unsigned long deltaT=currentTime-lastTime;
  if (deltaT < 0.0)
     deltaT=currentTime+(4294967295-lastTime);

  lastTime=currentTime;

  return deltaT;
}

// I called this from the loop function to see what the right values were for the calibration constants.
// If you are trying to reduce the amount of time needed for calibration just try not to go so low that consecutive
// calibration calls give you completely unrelated data.  Some sensors are probably better than others.
void testCalibration()
{
  calibrateGyro();
  for (int j=0;j<3;j++)
  {
    Serial.print(gyroZeroRate[j]);
    Serial.print("  ");
    Serial.print(gyroThreshold[j]);
    Serial.print("  ");
  }
  Serial.println();
  return;
}

// The settings here will suffice unless you want to use the interrupt feature.
void setupGyro()
{
  gyroWriteI2C(CTRL_REG1, 0x1F);        // Turn on all axes, disable power down
  gyroWriteI2C(CTRL_REG3, 0x08);        // Enable control ready signal
  setGyroSensitivity500();

  delay(100);
}

// Call this at start up.  It's critical that your device is completely stationary during calibration.
// The sensor needs recalibration after lots of movement, lots of idle time, temperature changes, etc, so try to work that in to your design.
void calibrateGyro()
{
  long int gyroSums[3]={0};
  long int gyroSigma[3]={0};

  for (int i=0;i<NUM_GYRO_SAMPLES;i++)
  {
    updateGyroValues();
    for (int j=0;j<3;j++)
    {
      gyroSums[j]+=gyroRaw[j];
      gyroSigma[j]+=gyroRaw[j]*gyroRaw[j];
    }
  }
  for (int j=0;j<3;j++)
  {
    int averageRate=gyroSums[j]/NUM_GYRO_SAMPLES;

    // Per STM docs, we store the average of the samples for each axis and subtract them when we use the data.
    gyroZeroRate[j]=averageRate;

    // Per STM docs, we create a threshold for each axis based on the standard deviation of the samples times 3.
    gyroThreshold[j]=sqrt((double(gyroSigma[j]) / NUM_GYRO_SAMPLES) - (averageRate * averageRate)) * GYRO_SIGMA_MULTIPLE;
  }
}

void updateGyroValues() {

  while (!(gyroReadI2C(0x27) & B00001000)){}      // Without this line you will get bad data occasionally

  //if (gyroReadI2C(0x27) & B01000000)
  //  Serial.println("Data missed!  Co#include <HMC5883L.h>nsider using an interrupt");

  int reg=0x28;
  for (int j=0;j<3;j++)
  {
    gyroRaw[j]=(gyroReadI2C(reg) | (gyroReadI2C(reg+1)<<8));
    reg+=2;
  }

  int deltaGyro[3];
  for (int j=0;j<3;j++)
  {
    deltaGyro[j]=gyroRaw[j]-gyroZeroRate[j];      // Use the calibration data to modify the sensor value.
    if (abs(deltaGyro[j]) < gyroThreshold[j])
      deltaGyro[j]=0;
    gyroDPS[j]= dpsPerDigit * deltaGyro[j];      // Multiply the sensor value by the sensitivity factor to get degrees per second.
  }
}

void setGyroSensitivity250(void)
{
  dpsPerDigit=.00875f;
  gyroWriteI2C(CTRL_REG4, 0x80);        // Set scale (250 deg/sec)
}

void setGyroSensitivity500(void)
{
  dpsPerDigit=.0175f;
  gyroWriteI2C(CTRL_REG4, 0x90);        // Set scale (500 deg/sec)
}

void setGyroSensitivity2000(void)
{
  dpsPerDigit=.07f;
  gyroWriteI2C(CTRL_REG4,0xA0);
}

int gyroReadI2C (byte regAddr) {
  Wire.beginTransmission(gyroI2CAddr);
  Wire.write(regAddr);
  Wire.endTransmission();
  Wire.requestFrom(gyroI2CAddr, 1);
  while(!Wire.available()) {};
  return (Wire.read());
}

int gyroWriteI2C( byte regAddr, byte val){
  Wire.beginTransmission(gyroI2CAddr);
  Wire.write(regAddr);
  Wire.write(val);
  Wire.endTransmission();
}


void read_compass(){
    // Retrive the raw values from the compass (not scaled).
  MagnetometerRaw raw = compass.ReadRawAxis();
  // Retrived the scaled values from the compass (scaled to the configured scale).
  MagnetometerScaled scaled = compass.ReadScaledAxis();

  // Values are accessed like so:
  int MilliGauss_OnThe_XAxis = scaled.XAxis;// (or YAxis, or ZAxis)

  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(scaled.YAxis, scaled.XAxis);

  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: 2� 37' W, which is 2.617 Degrees, or (which we need) 0.0456752665 radians, I will use 0.0457
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  float declinationAngle = 0.0457;
  heading += declinationAngle;

  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;

  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;

  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI;

  Serial.print("Compass: ");
  Serial.println(headingDegrees);
}

void loop() {
  updateGyroValues();
  updateHeadings();
  Serial.print("GYRO: ");
  Serial.println(heading[2]);
  read_compass();
  read_acc();
  Serial.print("X: ");
  Serial.println(pose_x);
  Serial.print("Y: ");
  Serial.println(pose_y);
  if(new_move == true){
    Serial.print("M: ");
    Serial.print(last_m.m1_command);
    Serial.print(",");
    Serial.print(last_m.m2_command);
    Serial.print(",");
    Serial.println(last_m.duration);
    new_move = false;
  }
//  Serial.print("M1: ");


//  digitalWrite(13, HIGH);
//  auto_mode();
//  comand_mode();
}
