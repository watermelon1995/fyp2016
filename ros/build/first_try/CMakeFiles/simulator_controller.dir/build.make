# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kin/fyp2016/ros/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kin/fyp2016/ros/build

# Include any dependencies generated for this target.
include first_try/CMakeFiles/simulator_controller.dir/depend.make

# Include the progress variables for this target.
include first_try/CMakeFiles/simulator_controller.dir/progress.make

# Include the compile flags for this target's objects.
include first_try/CMakeFiles/simulator_controller.dir/flags.make

first_try/CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.o: first_try/CMakeFiles/simulator_controller.dir/flags.make
first_try/CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.o: /home/kin/fyp2016/ros/src/first_try/src/robot_movement_controller.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kin/fyp2016/ros/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object first_try/CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.o"
	cd /home/kin/fyp2016/ros/build/first_try && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.o -c /home/kin/fyp2016/ros/src/first_try/src/robot_movement_controller.cpp

first_try/CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.i"
	cd /home/kin/fyp2016/ros/build/first_try && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kin/fyp2016/ros/src/first_try/src/robot_movement_controller.cpp > CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.i

first_try/CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.s"
	cd /home/kin/fyp2016/ros/build/first_try && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kin/fyp2016/ros/src/first_try/src/robot_movement_controller.cpp -o CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.s

first_try/CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.o.requires:
.PHONY : first_try/CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.o.requires

first_try/CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.o.provides: first_try/CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.o.requires
	$(MAKE) -f first_try/CMakeFiles/simulator_controller.dir/build.make first_try/CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.o.provides.build
.PHONY : first_try/CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.o.provides

first_try/CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.o.provides.build: first_try/CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.o

# Object files for target simulator_controller
simulator_controller_OBJECTS = \
"CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.o"

# External object files for target simulator_controller
simulator_controller_EXTERNAL_OBJECTS =

/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: first_try/CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.o
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: first_try/CMakeFiles/simulator_controller.dir/build.make
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /opt/ros/indigo/lib/libmrpt_bridge.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /opt/ros/indigo/lib/libinteractive_markers.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /opt/ros/indigo/lib/libtf.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /opt/ros/indigo/lib/libtf2_ros.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /opt/ros/indigo/lib/libactionlib.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /opt/ros/indigo/lib/libmessage_filters.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /opt/ros/indigo/lib/libroscpp.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /opt/ros/indigo/lib/libxmlrpcpp.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /opt/ros/indigo/lib/libtf2.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /opt/ros/indigo/lib/librosconsole.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /opt/ros/indigo/lib/librosconsole_log4cxx.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /opt/ros/indigo/lib/librosconsole_backend_interface.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /usr/lib/liblog4cxx.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /opt/ros/indigo/lib/libroscpp_serialization.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /opt/ros/indigo/lib/librostime.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /opt/ros/indigo/lib/libcpp_common.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller: first_try/CMakeFiles/simulator_controller.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller"
	cd /home/kin/fyp2016/ros/build/first_try && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simulator_controller.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
first_try/CMakeFiles/simulator_controller.dir/build: /home/kin/fyp2016/ros/devel/lib/first_try/simulator_controller
.PHONY : first_try/CMakeFiles/simulator_controller.dir/build

first_try/CMakeFiles/simulator_controller.dir/requires: first_try/CMakeFiles/simulator_controller.dir/src/robot_movement_controller.cpp.o.requires
.PHONY : first_try/CMakeFiles/simulator_controller.dir/requires

first_try/CMakeFiles/simulator_controller.dir/clean:
	cd /home/kin/fyp2016/ros/build/first_try && $(CMAKE_COMMAND) -P CMakeFiles/simulator_controller.dir/cmake_clean.cmake
.PHONY : first_try/CMakeFiles/simulator_controller.dir/clean

first_try/CMakeFiles/simulator_controller.dir/depend:
	cd /home/kin/fyp2016/ros/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kin/fyp2016/ros/src /home/kin/fyp2016/ros/src/first_try /home/kin/fyp2016/ros/build /home/kin/fyp2016/ros/build/first_try /home/kin/fyp2016/ros/build/first_try/CMakeFiles/simulator_controller.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : first_try/CMakeFiles/simulator_controller.dir/depend

