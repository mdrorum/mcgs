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
CMAKE_SOURCE_DIR = /home/pi/mcgs/practicas/practica01/fib_cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/mcgs/practicas/practica01/fib_cmake/build

# Utility rule file for apidoc.

# Include the progress variables for this target.
include CMakeFiles/apidoc.dir/progress.make

CMakeFiles/apidoc: .././doc

./doc: ../Doxyfile
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/mcgs/practicas/practica01/fib_cmake/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating ./doc"
	cd /home/pi/mcgs/practicas/practica01/fib_cmake && /usr/bin/cmake -E echo_append Building\ API\ Documentation...
	cd /home/pi/mcgs/practicas/practica01/fib_cmake && /usr/bin/doxygen Doxyfile
	cd /home/pi/mcgs/practicas/practica01/fib_cmake && /usr/bin/cmake -E echo Done.

apidoc: CMakeFiles/apidoc
apidoc: ./doc
apidoc: CMakeFiles/apidoc.dir/build.make
.PHONY : apidoc

# Rule to build all files generated by this target.
CMakeFiles/apidoc.dir/build: apidoc
.PHONY : CMakeFiles/apidoc.dir/build

CMakeFiles/apidoc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/apidoc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/apidoc.dir/clean

CMakeFiles/apidoc.dir/depend:
	cd /home/pi/mcgs/practicas/practica01/fib_cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/mcgs/practicas/practica01/fib_cmake /home/pi/mcgs/practicas/practica01/fib_cmake /home/pi/mcgs/practicas/practica01/fib_cmake/build /home/pi/mcgs/practicas/practica01/fib_cmake/build /home/pi/mcgs/practicas/practica01/fib_cmake/build/CMakeFiles/apidoc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/apidoc.dir/depend
