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
include stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/depend.make

# Include the progress variables for this target.
include stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/progress.make

# Include the compile flags for this target's objects.
include stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/flags.make

stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.o: stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/flags.make
stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.o: /home/kin/fyp2016/ros/src/stdr_simulator/stdr_server/src/stdr_server_node.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kin/fyp2016/ros/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.o"
	cd /home/kin/fyp2016/ros/build/stdr_simulator/stdr_server && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.o -c /home/kin/fyp2016/ros/src/stdr_simulator/stdr_server/src/stdr_server_node.cpp

stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.i"
	cd /home/kin/fyp2016/ros/build/stdr_simulator/stdr_server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kin/fyp2016/ros/src/stdr_simulator/stdr_server/src/stdr_server_node.cpp > CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.i

stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.s"
	cd /home/kin/fyp2016/ros/build/stdr_simulator/stdr_server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kin/fyp2016/ros/src/stdr_simulator/stdr_server/src/stdr_server_node.cpp -o CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.s

stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.o.requires:
.PHONY : stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.o.requires

stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.o.provides: stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.o.requires
	$(MAKE) -f stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/build.make stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.o.provides.build
.PHONY : stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.o.provides

stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.o.provides.build: stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.o

# Object files for target stdr_server_node
stdr_server_node_OBJECTS = \
"CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.o"

# External object files for target stdr_server_node
stdr_server_node_EXTERNAL_OBJECTS =

/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.o
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/build.make
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /home/kin/fyp2016/ros/devel/lib/libstdr_server.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libnodeletlib.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libbondcpp.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libuuid.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libtinyxml.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libclass_loader.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/libPocoFoundation.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libdl.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libroslib.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libimage_loader.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libtf.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libtf2_ros.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libactionlib.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libmessage_filters.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libroscpp.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libxmlrpcpp.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libtf2.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/librosconsole.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/librosconsole_log4cxx.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/librosconsole_backend_interface.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/liblog4cxx.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libroscpp_serialization.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/librostime.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libcpp_common.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /home/kin/fyp2016/ros/devel/lib/libstdr_map_server.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /home/kin/fyp2016/ros/devel/lib/libstdr_map_loader.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libnodeletlib.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libbondcpp.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libuuid.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libtinyxml.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libclass_loader.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/libPocoFoundation.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libdl.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libroslib.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libimage_loader.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libtf.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libtf2_ros.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libactionlib.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libmessage_filters.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libroscpp.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libxmlrpcpp.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libtf2.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/librosconsole.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/librosconsole_log4cxx.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/librosconsole_backend_interface.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/liblog4cxx.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libroscpp_serialization.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/librostime.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /opt/ros/indigo/lib/libcpp_common.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node: stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node"
	cd /home/kin/fyp2016/ros/build/stdr_simulator/stdr_server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stdr_server_node.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/build: /home/kin/fyp2016/ros/devel/lib/stdr_server/stdr_server_node
.PHONY : stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/build

stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/requires: stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/src/stdr_server_node.cpp.o.requires
.PHONY : stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/requires

stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/clean:
	cd /home/kin/fyp2016/ros/build/stdr_simulator/stdr_server && $(CMAKE_COMMAND) -P CMakeFiles/stdr_server_node.dir/cmake_clean.cmake
.PHONY : stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/clean

stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/depend:
	cd /home/kin/fyp2016/ros/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kin/fyp2016/ros/src /home/kin/fyp2016/ros/src/stdr_simulator/stdr_server /home/kin/fyp2016/ros/build /home/kin/fyp2016/ros/build/stdr_simulator/stdr_server /home/kin/fyp2016/ros/build/stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : stdr_simulator/stdr_server/CMakeFiles/stdr_server_node.dir/depend

