cmake_minimum_required(VERSION 2.8.3)
project(first_try)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  tf
  mrpt_bridge
  nav_msgs
  visualization_msgs
  interactive_markers
)

MESSAGE( STATUS "catkin_LIBRARIES_DIRS: " ${catkin_LIBRARIES})


find_package(MRPT REQUIRED base maps gui opengl slam)

find_package(mrpt_bridge REQUIRED map time pose)

# find_package(wxWidgets COMPONENTS core base REQUIRED)
# include(${wxWidgets_USE_FILE})

# MESSAGE( STATUS "MRPT_LIBRARY_DIRS: " ${MRPT_LIBRARIES})

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS thread)

set(MYSQLCONNECTORCPP_ROOT_DIR
        "${MYSQLCONNECTORCPP_ROOT_DIR}"
        CACHE
        PATH
        "/home/kin/Desktop/mysql-connector-c++-1.1.8-linux-glibc2.5-x86-64bit")

if(WIN32)
    find_path(MYSQLCONNECTORCPP_INCLUDE_DIR
            NAMES
            mysql_connection.h
            PATHS
            "C:\\Program Files"
            HINTS
            ${MYSQLCONNECTORCPP_ROOT_DIR}
            PATH_SUFFIXES
            include)

    find_library(MYSQLCONNECTORCPP_LIBRARY
            NAMES
            mysqlcppconn
            mysqlcppconn-static
            HINTS
            ${MYSQLCONNECTORCPP_ROOT_DIR}
            PATH_SUFFIXES
            lib)

else()
    find_path(MYSQLCONNECTORCPP_INCLUDE_DIR
            mysql_connection.h
            HINTS
            ${MYSQLCONNECTORCPP_ROOT_DIR}
            PATH_SUFFIXES
            include)

    find_library(MYSQLCONNECTORCPP_LIBRARY
            NAMES
            mysqlcppconn
            mysqlcppconn-static
            HINTS
            ${MYSQLCONNECTORCPP_ROOT_DIR}
            PATH_SUFFIXES
            lib64
            lib)
endif()

mark_as_advanced(MYSQLCONNECTORCPP_INCLUDE_DIR MYSQLCONNECTORCPP_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MysqlConnectorCpp
        DEFAULT_MSG
        MYSQLCONNECTORCPP_INCLUDE_DIR
        MYSQLCONNECTORCPP_LIBRARY)

if(MYSQLCONNECTORCPP_FOUND)
    set(MYSQLCONNECTORCPP_INCLUDE_DIRS "${MYSQLCONNECTORCPP_INCLUDE_DIR}") # Add any dependencies here
    set(MYSQLCONNECTORCPP_LIBRARIES "${MYSQLCONNECTORCPP_LIBRARY}") # Add any dependencies here
    mark_as_advanced(MYSQLCONNECTORCPP_ROOT_DIR)
endif()

## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs
# )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES first_try
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
# add_library(first_try
#   src/${PROJECT_NAME}/first_try.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(first_try ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
# add_executable(first_try_node src/first_try_node.cpp)

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(first_try_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
# target_link_libraries(first_try_node
#   ${catkin_LIBRARIES}
# )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS first_try first_try_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_first_try.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)


include_directories(include ${catkin_INCLUDE_DIRS} "/home/kin/fyp2016/ros/src/first_try")


# add_executable(talker src/helloworld.cpp)
# target_link_libraries(talker ${catkin_LIBRARIES})
# add_dependencies(talker first_try_generate_messages_cpp)

# add_executable(listener src/helloworld_listener.cpp)
# target_link_libraries(listener ${catkin_LIBRARIES})
# add_dependencies(listener first_try_generate_messages_cpp)

add_executable(kinMap src/kinMap.cpp)
target_link_libraries(kinMap ${catkin_LIBRARIES})
add_dependencies(kinMap first_try_generate_messages_cpp)

add_executable(new_kinMap src/new_kinMap.cpp)
target_link_libraries(new_kinMap ${catkin_LIBRARIES} ${MRPT_LIBRARIES})
add_dependencies(new_kinMap first_try_generate_messages_cpp)

add_executable(simulator_controller src/robot_movement_controller.cpp)
target_link_libraries(simulator_controller ${catkin_LIBRARIES} ${MRPT_LIBRARIES})
add_dependencies(simulator_controller first_try_generate_messages_cpp)

add_executable(dynamic_obstacle src/fake_laser.cpp)
target_link_libraries(dynamic_obstacle ${catkin_LIBRARIES} ${MRPT_LIBRARIES})
add_dependencies(dynamic_obstacle first_try_generate_messages_cpp)

add_executable(command_prepare src/prepare_table.cpp)
target_link_libraries(command_prepare ${catkin_LIBRARIES} ${MRPT_LIBRARIES} mysqlcppconn)
add_dependencies(command_prepare first_try_generate_messages_cpp)

add_executable(mysql_test src/mysql_test.cpp)
target_link_libraries(mysql_test ${catkin_LIBRARIES} ${MRPT_LIBRARIES} mysqlcppconn)
add_dependencies(mysql_test first_try_generate_messages_cpp)

add_executable(new_arduino_driver src/motor_arduino_ros.cpp)
target_link_libraries(new_arduino_driver ${catkin_LIBRARIES} ${MRPT_LIBRARIES} )
add_dependencies(new_arduino_driver first_try_generate_messages_cpp)


# add_executable(controller src/controller_gui.cpp)
# target_link_libraries(controller ${catkin_LIBRARIES} ${MRPT_LIBRARIES} ${wxWidgets_LIBRARIES})
# add_dependencies(controller first_try_generate_messages_cpp)
