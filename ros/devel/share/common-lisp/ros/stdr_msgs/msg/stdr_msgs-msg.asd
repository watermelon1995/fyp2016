
(cl:in-package :asdf)

(defsystem "stdr_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :actionlib_msgs-msg
               :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "FootprintMsg" :depends-on ("_package_FootprintMsg"))
    (:file "_package_FootprintMsg" :depends-on ("_package"))
    (:file "KinematicMsg" :depends-on ("_package_KinematicMsg"))
    (:file "_package_KinematicMsg" :depends-on ("_package"))
    (:file "Noise" :depends-on ("_package_Noise"))
    (:file "_package_Noise" :depends-on ("_package"))
    (:file "CO2SensorMsg" :depends-on ("_package_CO2SensorMsg"))
    (:file "_package_CO2SensorMsg" :depends-on ("_package"))
    (:file "SonarSensorMsg" :depends-on ("_package_SonarSensorMsg"))
    (:file "_package_SonarSensorMsg" :depends-on ("_package"))
    (:file "SoundSensorMsg" :depends-on ("_package_SoundSensorMsg"))
    (:file "_package_SoundSensorMsg" :depends-on ("_package"))
    (:file "RfidSensorMeasurementMsg" :depends-on ("_package_RfidSensorMeasurementMsg"))
    (:file "_package_RfidSensorMeasurementMsg" :depends-on ("_package"))
    (:file "CO2SensorMeasurementMsg" :depends-on ("_package_CO2SensorMeasurementMsg"))
    (:file "_package_CO2SensorMeasurementMsg" :depends-on ("_package"))
    (:file "CO2SourceVector" :depends-on ("_package_CO2SourceVector"))
    (:file "_package_CO2SourceVector" :depends-on ("_package"))
    (:file "RfidSensorMsg" :depends-on ("_package_RfidSensorMsg"))
    (:file "_package_RfidSensorMsg" :depends-on ("_package"))
    (:file "ThermalSourceVector" :depends-on ("_package_ThermalSourceVector"))
    (:file "_package_ThermalSourceVector" :depends-on ("_package"))
    (:file "RfidTag" :depends-on ("_package_RfidTag"))
    (:file "_package_RfidTag" :depends-on ("_package"))
    (:file "RobotIndexedVectorMsg" :depends-on ("_package_RobotIndexedVectorMsg"))
    (:file "_package_RobotIndexedVectorMsg" :depends-on ("_package"))
    (:file "SoundSourceVector" :depends-on ("_package_SoundSourceVector"))
    (:file "_package_SoundSourceVector" :depends-on ("_package"))
    (:file "RobotMsg" :depends-on ("_package_RobotMsg"))
    (:file "_package_RobotMsg" :depends-on ("_package"))
    (:file "RfidTagVector" :depends-on ("_package_RfidTagVector"))
    (:file "_package_RfidTagVector" :depends-on ("_package"))
    (:file "CO2Source" :depends-on ("_package_CO2Source"))
    (:file "_package_CO2Source" :depends-on ("_package"))
    (:file "SoundSensorMeasurementMsg" :depends-on ("_package_SoundSensorMeasurementMsg"))
    (:file "_package_SoundSensorMeasurementMsg" :depends-on ("_package"))
    (:file "LaserSensorMsg" :depends-on ("_package_LaserSensorMsg"))
    (:file "_package_LaserSensorMsg" :depends-on ("_package"))
    (:file "ThermalSource" :depends-on ("_package_ThermalSource"))
    (:file "_package_ThermalSource" :depends-on ("_package"))
    (:file "ThermalSensorMeasurementMsg" :depends-on ("_package_ThermalSensorMeasurementMsg"))
    (:file "_package_ThermalSensorMeasurementMsg" :depends-on ("_package"))
    (:file "ThermalSensorMsg" :depends-on ("_package_ThermalSensorMsg"))
    (:file "_package_ThermalSensorMsg" :depends-on ("_package"))
    (:file "RobotIndexedMsg" :depends-on ("_package_RobotIndexedMsg"))
    (:file "_package_RobotIndexedMsg" :depends-on ("_package"))
    (:file "SoundSource" :depends-on ("_package_SoundSource"))
    (:file "_package_SoundSource" :depends-on ("_package"))
    (:file "DeleteRobotActionResult" :depends-on ("_package_DeleteRobotActionResult"))
    (:file "_package_DeleteRobotActionResult" :depends-on ("_package"))
    (:file "SpawnRobotFeedback" :depends-on ("_package_SpawnRobotFeedback"))
    (:file "_package_SpawnRobotFeedback" :depends-on ("_package"))
    (:file "DeleteRobotGoal" :depends-on ("_package_DeleteRobotGoal"))
    (:file "_package_DeleteRobotGoal" :depends-on ("_package"))
    (:file "SpawnRobotAction" :depends-on ("_package_SpawnRobotAction"))
    (:file "_package_SpawnRobotAction" :depends-on ("_package"))
    (:file "RegisterRobotActionGoal" :depends-on ("_package_RegisterRobotActionGoal"))
    (:file "_package_RegisterRobotActionGoal" :depends-on ("_package"))
    (:file "SpawnRobotGoal" :depends-on ("_package_SpawnRobotGoal"))
    (:file "_package_SpawnRobotGoal" :depends-on ("_package"))
    (:file "DeleteRobotAction" :depends-on ("_package_DeleteRobotAction"))
    (:file "_package_DeleteRobotAction" :depends-on ("_package"))
    (:file "SpawnRobotResult" :depends-on ("_package_SpawnRobotResult"))
    (:file "_package_SpawnRobotResult" :depends-on ("_package"))
    (:file "SpawnRobotActionGoal" :depends-on ("_package_SpawnRobotActionGoal"))
    (:file "_package_SpawnRobotActionGoal" :depends-on ("_package"))
    (:file "SpawnRobotActionResult" :depends-on ("_package_SpawnRobotActionResult"))
    (:file "_package_SpawnRobotActionResult" :depends-on ("_package"))
    (:file "DeleteRobotActionGoal" :depends-on ("_package_DeleteRobotActionGoal"))
    (:file "_package_DeleteRobotActionGoal" :depends-on ("_package"))
    (:file "DeleteRobotActionFeedback" :depends-on ("_package_DeleteRobotActionFeedback"))
    (:file "_package_DeleteRobotActionFeedback" :depends-on ("_package"))
    (:file "RegisterRobotActionFeedback" :depends-on ("_package_RegisterRobotActionFeedback"))
    (:file "_package_RegisterRobotActionFeedback" :depends-on ("_package"))
    (:file "DeleteRobotFeedback" :depends-on ("_package_DeleteRobotFeedback"))
    (:file "_package_DeleteRobotFeedback" :depends-on ("_package"))
    (:file "RegisterRobotResult" :depends-on ("_package_RegisterRobotResult"))
    (:file "_package_RegisterRobotResult" :depends-on ("_package"))
    (:file "RegisterRobotAction" :depends-on ("_package_RegisterRobotAction"))
    (:file "_package_RegisterRobotAction" :depends-on ("_package"))
    (:file "RegisterRobotGoal" :depends-on ("_package_RegisterRobotGoal"))
    (:file "_package_RegisterRobotGoal" :depends-on ("_package"))
    (:file "DeleteRobotResult" :depends-on ("_package_DeleteRobotResult"))
    (:file "_package_DeleteRobotResult" :depends-on ("_package"))
    (:file "SpawnRobotActionFeedback" :depends-on ("_package_SpawnRobotActionFeedback"))
    (:file "_package_SpawnRobotActionFeedback" :depends-on ("_package"))
    (:file "RegisterRobotActionResult" :depends-on ("_package_RegisterRobotActionResult"))
    (:file "_package_RegisterRobotActionResult" :depends-on ("_package"))
    (:file "RegisterRobotFeedback" :depends-on ("_package_RegisterRobotFeedback"))
    (:file "_package_RegisterRobotFeedback" :depends-on ("_package"))
  ))