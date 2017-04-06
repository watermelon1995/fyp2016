#include <iostream>
#include <fstream>
#include "Motor.cpp"


int main(int argc, char **argv){
  Motor *m = new Motor();

  m->print_debug();
  m->save_file();

  return 0;
}
