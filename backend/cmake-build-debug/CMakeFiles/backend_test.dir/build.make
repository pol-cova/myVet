# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/paulcontreras/Documents/GitHub/myVet/backend

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/paulcontreras/Documents/GitHub/myVet/backend/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/backend_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/backend_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/backend_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/backend_test.dir/flags.make

CMakeFiles/backend_test.dir/test.cpp.o: CMakeFiles/backend_test.dir/flags.make
CMakeFiles/backend_test.dir/test.cpp.o: ../test.cpp
CMakeFiles/backend_test.dir/test.cpp.o: CMakeFiles/backend_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/paulcontreras/Documents/GitHub/myVet/backend/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/backend_test.dir/test.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/backend_test.dir/test.cpp.o -MF CMakeFiles/backend_test.dir/test.cpp.o.d -o CMakeFiles/backend_test.dir/test.cpp.o -c /Users/paulcontreras/Documents/GitHub/myVet/backend/test.cpp

CMakeFiles/backend_test.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/backend_test.dir/test.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/paulcontreras/Documents/GitHub/myVet/backend/test.cpp > CMakeFiles/backend_test.dir/test.cpp.i

CMakeFiles/backend_test.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/backend_test.dir/test.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/paulcontreras/Documents/GitHub/myVet/backend/test.cpp -o CMakeFiles/backend_test.dir/test.cpp.s

# Object files for target backend_test
backend_test_OBJECTS = \
"CMakeFiles/backend_test.dir/test.cpp.o"

# External object files for target backend_test
backend_test_EXTERNAL_OBJECTS =

backend_test: CMakeFiles/backend_test.dir/test.cpp.o
backend_test: CMakeFiles/backend_test.dir/build.make
backend_test: CMakeFiles/backend_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/paulcontreras/Documents/GitHub/myVet/backend/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable backend_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/backend_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/backend_test.dir/build: backend_test
.PHONY : CMakeFiles/backend_test.dir/build

CMakeFiles/backend_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/backend_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/backend_test.dir/clean

CMakeFiles/backend_test.dir/depend:
	cd /Users/paulcontreras/Documents/GitHub/myVet/backend/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/paulcontreras/Documents/GitHub/myVet/backend /Users/paulcontreras/Documents/GitHub/myVet/backend /Users/paulcontreras/Documents/GitHub/myVet/backend/cmake-build-debug /Users/paulcontreras/Documents/GitHub/myVet/backend/cmake-build-debug /Users/paulcontreras/Documents/GitHub/myVet/backend/cmake-build-debug/CMakeFiles/backend_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/backend_test.dir/depend

