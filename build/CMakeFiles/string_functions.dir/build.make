# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.30.5/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/geoffreykoech/Desktop/Personal Projects/Libraries/C++/Networking/Requests"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/geoffreykoech/Desktop/Personal Projects/Libraries/C++/Networking/Requests/build"

# Include any dependencies generated for this target.
include CMakeFiles/string_functions.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/string_functions.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/string_functions.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/string_functions.dir/flags.make

CMakeFiles/string_functions.dir/libs/string_functions.c++.o: CMakeFiles/string_functions.dir/flags.make
CMakeFiles/string_functions.dir/libs/string_functions.c++.o: /Users/geoffreykoech/Desktop/Personal\ Projects/Libraries/C++/Networking/Requests/libs/string_functions.c++
CMakeFiles/string_functions.dir/libs/string_functions.c++.o: CMakeFiles/string_functions.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/geoffreykoech/Desktop/Personal Projects/Libraries/C++/Networking/Requests/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/string_functions.dir/libs/string_functions.c++.o"
	/usr/local/Cellar/llvm/19.1.1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/string_functions.dir/libs/string_functions.c++.o -MF CMakeFiles/string_functions.dir/libs/string_functions.c++.o.d -o CMakeFiles/string_functions.dir/libs/string_functions.c++.o -c "/Users/geoffreykoech/Desktop/Personal Projects/Libraries/C++/Networking/Requests/libs/string_functions.c++"

CMakeFiles/string_functions.dir/libs/string_functions.c++.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/string_functions.dir/libs/string_functions.c++.i"
	/usr/local/Cellar/llvm/19.1.1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/geoffreykoech/Desktop/Personal Projects/Libraries/C++/Networking/Requests/libs/string_functions.c++" > CMakeFiles/string_functions.dir/libs/string_functions.c++.i

CMakeFiles/string_functions.dir/libs/string_functions.c++.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/string_functions.dir/libs/string_functions.c++.s"
	/usr/local/Cellar/llvm/19.1.1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/geoffreykoech/Desktop/Personal Projects/Libraries/C++/Networking/Requests/libs/string_functions.c++" -o CMakeFiles/string_functions.dir/libs/string_functions.c++.s

# Object files for target string_functions
string_functions_OBJECTS = \
"CMakeFiles/string_functions.dir/libs/string_functions.c++.o"

# External object files for target string_functions
string_functions_EXTERNAL_OBJECTS =

libstring_functions.a: CMakeFiles/string_functions.dir/libs/string_functions.c++.o
libstring_functions.a: CMakeFiles/string_functions.dir/build.make
libstring_functions.a: CMakeFiles/string_functions.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/geoffreykoech/Desktop/Personal Projects/Libraries/C++/Networking/Requests/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libstring_functions.a"
	$(CMAKE_COMMAND) -P CMakeFiles/string_functions.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/string_functions.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/string_functions.dir/build: libstring_functions.a
.PHONY : CMakeFiles/string_functions.dir/build

CMakeFiles/string_functions.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/string_functions.dir/cmake_clean.cmake
.PHONY : CMakeFiles/string_functions.dir/clean

CMakeFiles/string_functions.dir/depend:
	cd "/Users/geoffreykoech/Desktop/Personal Projects/Libraries/C++/Networking/Requests/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/geoffreykoech/Desktop/Personal Projects/Libraries/C++/Networking/Requests" "/Users/geoffreykoech/Desktop/Personal Projects/Libraries/C++/Networking/Requests" "/Users/geoffreykoech/Desktop/Personal Projects/Libraries/C++/Networking/Requests/build" "/Users/geoffreykoech/Desktop/Personal Projects/Libraries/C++/Networking/Requests/build" "/Users/geoffreykoech/Desktop/Personal Projects/Libraries/C++/Networking/Requests/build/CMakeFiles/string_functions.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/string_functions.dir/depend

