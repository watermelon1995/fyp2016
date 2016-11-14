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
CMAKE_BINARY_DIR = /home/kin/fyp2016/ros/build-src-Desktop_Qt_5_7_0_GCC_64bit-Default

# Include any dependencies generated for this target.
include stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/depend.make

# Include the progress variables for this target.
include stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/progress.make

# Include the compile flags for this target's objects.
include stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/flags.make

stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.o: stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/flags.make
stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.o: /home/kin/fyp2016/ros/src/stdr_simulator/stdr_robot/src/sensors/rfid_reader.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kin/fyp2016/ros/build-src-Desktop_Qt_5_7_0_GCC_64bit-Default/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.o"
	cd /home/kin/fyp2016/ros/build-src-Desktop_Qt_5_7_0_GCC_64bit-Default/stdr_simulator/stdr_robot && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.o -c /home/kin/fyp2016/ros/src/stdr_simulator/stdr_robot/src/sensors/rfid_reader.cpp

stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.i"
	cd /home/kin/fyp2016/ros/build-src-Desktop_Qt_5_7_0_GCC_64bit-Default/stdr_simulator/stdr_robot && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kin/fyp2016/ros/src/stdr_simulator/stdr_robot/src/sensors/rfid_reader.cpp > CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.i

stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.s"
	cd /home/kin/fyp2016/ros/build-src-Desktop_Qt_5_7_0_GCC_64bit-Default/stdr_simulator/stdr_robot && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kin/fyp2016/ros/src/stdr_simulator/stdr_robot/src/sensors/rfid_reader.cpp -o CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.s

stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.o.requires:
.PHONY : stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.o.requires

stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.o.provides: stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.o.requires
	$(MAKE) -f stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/build.make stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.o.provides.build
.PHONY : stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.o.provides

stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.o.provides.build: stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.o

# Object files for target stdr_rfid_reader
stdr_rfid_reader_OBJECTS = \
"CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.o"

# External object files for target stdr_rfid_reader
stdr_rfid_reader_EXTERNAL_OBJECTS =

devel/lib/libstdr_rfid_reader.so: stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.o
devel/lib/libstdr_rfid_reader.so: stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/build.make
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libnodeletlib.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libbondcpp.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libuuid.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libclass_loader.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/libPocoFoundation.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libdl.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libtf.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libtf2_ros.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libactionlib.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libmessage_filters.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libtf2.so
devel/lib/libstdr_rfid_reader.so: devel/lib/libstdr_parser.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libtinyxml.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libroscpp.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libboost_signals.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/librosconsole.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/librosconsole_log4cxx.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/librosconsole_backend_interface.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/liblog4cxx.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libboost_regex.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libxmlrpcpp.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libroslib.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libroscpp_serialization.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/librostime.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libcpp_common.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libboost_system.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libboost_thread.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libpthread.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
devel/lib/libstdr_rfid_reader.so: devel/lib/libstdr_sensor_base.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libnodeletlib.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libbondcpp.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libuuid.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libclass_loader.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/libPocoFoundation.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libdl.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libtf.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libtf2_ros.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libactionlib.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libmessage_filters.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libtf2.so
devel/lib/libstdr_rfid_reader.so: devel/lib/libstdr_parser.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libtinyxml.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libroscpp.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libboost_signals.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/librosconsole.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/librosconsole_log4cxx.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/librosconsole_backend_interface.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/liblog4cxx.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libboost_regex.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libxmlrpcpp.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libroslib.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libroscpp_serialization.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/librostime.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
devel/lib/libstdr_rfid_reader.so: /opt/ros/indigo/lib/libcpp_common.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libboost_system.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libboost_thread.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libpthread.so
devel/lib/libstdr_rfid_reader.so: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
devel/lib/libstdr_rfid_reader.so: stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../../devel/lib/libstdr_rfid_reader.so"
	cd /home/kin/fyp2016/ros/build-src-Desktop_Qt_5_7_0_GCC_64bit-Default/stdr_simulator/stdr_robot && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stdr_rfid_reader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/build: devel/lib/libstdr_rfid_reader.so
.PHONY : stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/build

stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/requires: stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/src/sensors/rfid_reader.cpp.o.requires
.PHONY : stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/requires

stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/clean:
	cd /home/kin/fyp2016/ros/build-src-Desktop_Qt_5_7_0_GCC_64bit-Default/stdr_simulator/stdr_robot && $(CMAKE_COMMAND) -P CMakeFiles/stdr_rfid_reader.dir/cmake_clean.cmake
.PHONY : stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/clean

stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/depend:
	cd /home/kin/fyp2016/ros/build-src-Desktop_Qt_5_7_0_GCC_64bit-Default && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kin/fyp2016/ros/src /home/kin/fyp2016/ros/src/stdr_simulator/stdr_robot /home/kin/fyp2016/ros/build-src-Desktop_Qt_5_7_0_GCC_64bit-Default /home/kin/fyp2016/ros/build-src-Desktop_Qt_5_7_0_GCC_64bit-Default/stdr_simulator/stdr_robot /home/kin/fyp2016/ros/build-src-Desktop_Qt_5_7_0_GCC_64bit-Default/stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : stdr_simulator/stdr_robot/CMakeFiles/stdr_rfid_reader.dir/depend
