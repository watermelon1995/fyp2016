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

# Utility rule file for _run_tests_stdr_server_rostest_test_functional_interfaces_test.launch.

# Include the progress variables for this target.
include stdr_simulator/stdr_server/test/CMakeFiles/_run_tests_stdr_server_rostest_test_functional_interfaces_test.launch.dir/progress.make

stdr_simulator/stdr_server/test/CMakeFiles/_run_tests_stdr_server_rostest_test_functional_interfaces_test.launch:
	cd /home/kin/fyp2016/ros/build/stdr_simulator/stdr_server/test && ../../../catkin_generated/env_cached.sh /usr/bin/python /opt/ros/indigo/share/catkin/cmake/test/run_tests.py /home/kin/fyp2016/ros/build/test_results/stdr_server/rostest-test_functional_interfaces_test.xml /opt/ros/indigo/share/rostest/cmake/../../../bin/rostest\ --pkgdir=/home/kin/fyp2016/ros/src/stdr_simulator/stdr_server\ --package=stdr_server\ --results-filename\ test_functional_interfaces_test.xml\ --results-base-dir\ "/home/kin/fyp2016/ros/build/test_results"\ /home/kin/fyp2016/ros/src/stdr_simulator/stdr_server/test/functional/interfaces_test.launch\ 

_run_tests_stdr_server_rostest_test_functional_interfaces_test.launch: stdr_simulator/stdr_server/test/CMakeFiles/_run_tests_stdr_server_rostest_test_functional_interfaces_test.launch
_run_tests_stdr_server_rostest_test_functional_interfaces_test.launch: stdr_simulator/stdr_server/test/CMakeFiles/_run_tests_stdr_server_rostest_test_functional_interfaces_test.launch.dir/build.make
.PHONY : _run_tests_stdr_server_rostest_test_functional_interfaces_test.launch

# Rule to build all files generated by this target.
stdr_simulator/stdr_server/test/CMakeFiles/_run_tests_stdr_server_rostest_test_functional_interfaces_test.launch.dir/build: _run_tests_stdr_server_rostest_test_functional_interfaces_test.launch
.PHONY : stdr_simulator/stdr_server/test/CMakeFiles/_run_tests_stdr_server_rostest_test_functional_interfaces_test.launch.dir/build

stdr_simulator/stdr_server/test/CMakeFiles/_run_tests_stdr_server_rostest_test_functional_interfaces_test.launch.dir/clean:
	cd /home/kin/fyp2016/ros/build/stdr_simulator/stdr_server/test && $(CMAKE_COMMAND) -P CMakeFiles/_run_tests_stdr_server_rostest_test_functional_interfaces_test.launch.dir/cmake_clean.cmake
.PHONY : stdr_simulator/stdr_server/test/CMakeFiles/_run_tests_stdr_server_rostest_test_functional_interfaces_test.launch.dir/clean

stdr_simulator/stdr_server/test/CMakeFiles/_run_tests_stdr_server_rostest_test_functional_interfaces_test.launch.dir/depend:
	cd /home/kin/fyp2016/ros/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kin/fyp2016/ros/src /home/kin/fyp2016/ros/src/stdr_simulator/stdr_server/test /home/kin/fyp2016/ros/build /home/kin/fyp2016/ros/build/stdr_simulator/stdr_server/test /home/kin/fyp2016/ros/build/stdr_simulator/stdr_server/test/CMakeFiles/_run_tests_stdr_server_rostest_test_functional_interfaces_test.launch.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : stdr_simulator/stdr_server/test/CMakeFiles/_run_tests_stdr_server_rostest_test_functional_interfaces_test.launch.dir/depend

