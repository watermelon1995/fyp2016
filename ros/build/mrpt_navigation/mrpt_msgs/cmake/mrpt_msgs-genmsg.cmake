# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "mrpt_msgs: 4 messages, 0 services")

set(MSG_I_FLAGS "-Imrpt_msgs:/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(mrpt_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBearingObservation.msg" NAME_WE)
add_custom_target(_mrpt_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "mrpt_msgs" "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBearingObservation.msg" ""
)

get_filename_component(_filename "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/ObservationRangeBeacon.msg" NAME_WE)
add_custom_target(_mrpt_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "mrpt_msgs" "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/ObservationRangeBeacon.msg" "geometry_msgs/Point:mrpt_msgs/SingleRangeBeaconObservation:geometry_msgs/Quaternion:std_msgs/Header:geometry_msgs/Pose"
)

get_filename_component(_filename "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/ObservationRangeBearing.msg" NAME_WE)
add_custom_target(_mrpt_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "mrpt_msgs" "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/ObservationRangeBearing.msg" "geometry_msgs/Point:mrpt_msgs/SingleRangeBearingObservation:geometry_msgs/Quaternion:std_msgs/Header:geometry_msgs/Pose"
)

get_filename_component(_filename "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBeaconObservation.msg" NAME_WE)
add_custom_target(_mrpt_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "mrpt_msgs" "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBeaconObservation.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(mrpt_msgs
  "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBearingObservation.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/mrpt_msgs
)
_generate_msg_cpp(mrpt_msgs
  "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/ObservationRangeBeacon.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBeaconObservation.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/mrpt_msgs
)
_generate_msg_cpp(mrpt_msgs
  "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/ObservationRangeBearing.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBearingObservation.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/mrpt_msgs
)
_generate_msg_cpp(mrpt_msgs
  "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBeaconObservation.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/mrpt_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(mrpt_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/mrpt_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(mrpt_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(mrpt_msgs_generate_messages mrpt_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBearingObservation.msg" NAME_WE)
add_dependencies(mrpt_msgs_generate_messages_cpp _mrpt_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/ObservationRangeBeacon.msg" NAME_WE)
add_dependencies(mrpt_msgs_generate_messages_cpp _mrpt_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/ObservationRangeBearing.msg" NAME_WE)
add_dependencies(mrpt_msgs_generate_messages_cpp _mrpt_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBeaconObservation.msg" NAME_WE)
add_dependencies(mrpt_msgs_generate_messages_cpp _mrpt_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(mrpt_msgs_gencpp)
add_dependencies(mrpt_msgs_gencpp mrpt_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS mrpt_msgs_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(mrpt_msgs
  "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBearingObservation.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/mrpt_msgs
)
_generate_msg_lisp(mrpt_msgs
  "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/ObservationRangeBeacon.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBeaconObservation.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/mrpt_msgs
)
_generate_msg_lisp(mrpt_msgs
  "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/ObservationRangeBearing.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBearingObservation.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/mrpt_msgs
)
_generate_msg_lisp(mrpt_msgs
  "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBeaconObservation.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/mrpt_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(mrpt_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/mrpt_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(mrpt_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(mrpt_msgs_generate_messages mrpt_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBearingObservation.msg" NAME_WE)
add_dependencies(mrpt_msgs_generate_messages_lisp _mrpt_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/ObservationRangeBeacon.msg" NAME_WE)
add_dependencies(mrpt_msgs_generate_messages_lisp _mrpt_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/ObservationRangeBearing.msg" NAME_WE)
add_dependencies(mrpt_msgs_generate_messages_lisp _mrpt_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBeaconObservation.msg" NAME_WE)
add_dependencies(mrpt_msgs_generate_messages_lisp _mrpt_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(mrpt_msgs_genlisp)
add_dependencies(mrpt_msgs_genlisp mrpt_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS mrpt_msgs_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(mrpt_msgs
  "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBearingObservation.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mrpt_msgs
)
_generate_msg_py(mrpt_msgs
  "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/ObservationRangeBeacon.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBeaconObservation.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mrpt_msgs
)
_generate_msg_py(mrpt_msgs
  "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/ObservationRangeBearing.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBearingObservation.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mrpt_msgs
)
_generate_msg_py(mrpt_msgs
  "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBeaconObservation.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mrpt_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(mrpt_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mrpt_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(mrpt_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(mrpt_msgs_generate_messages mrpt_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBearingObservation.msg" NAME_WE)
add_dependencies(mrpt_msgs_generate_messages_py _mrpt_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/ObservationRangeBeacon.msg" NAME_WE)
add_dependencies(mrpt_msgs_generate_messages_py _mrpt_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/ObservationRangeBearing.msg" NAME_WE)
add_dependencies(mrpt_msgs_generate_messages_py _mrpt_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/kin/fyp2016/ros/src/mrpt_navigation/mrpt_msgs/msg/SingleRangeBeaconObservation.msg" NAME_WE)
add_dependencies(mrpt_msgs_generate_messages_py _mrpt_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(mrpt_msgs_genpy)
add_dependencies(mrpt_msgs_genpy mrpt_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS mrpt_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/mrpt_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/mrpt_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(mrpt_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)
add_dependencies(mrpt_msgs_generate_messages_cpp geometry_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/mrpt_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/mrpt_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(mrpt_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)
add_dependencies(mrpt_msgs_generate_messages_lisp geometry_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mrpt_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mrpt_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mrpt_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(mrpt_msgs_generate_messages_py std_msgs_generate_messages_py)
add_dependencies(mrpt_msgs_generate_messages_py geometry_msgs_generate_messages_py)
