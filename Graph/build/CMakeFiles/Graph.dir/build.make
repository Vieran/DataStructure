# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\AllOfProgram\Auxiliary\cmake-3.16.2-win64-x64\bin\cmake.exe

# The command to remove a file.
RM = D:\AllOfProgram\Auxiliary\cmake-3.16.2-win64-x64\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\AllOfProgram\Code\Data_Structures\Graph

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\AllOfProgram\Code\Data_Structures\Graph\build

# Include any dependencies generated for this target.
include CMakeFiles/Graph.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Graph.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Graph.dir/flags.make

CMakeFiles/Graph.dir/Graph.cpp.obj: CMakeFiles/Graph.dir/flags.make
CMakeFiles/Graph.dir/Graph.cpp.obj: CMakeFiles/Graph.dir/includes_CXX.rsp
CMakeFiles/Graph.dir/Graph.cpp.obj: ../Graph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\AllOfProgram\Code\Data_Structures\Graph\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Graph.dir/Graph.cpp.obj"
	D:\AllOfProgram\Auxiliary\MinGW-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Graph.dir\Graph.cpp.obj -c D:\AllOfProgram\Code\Data_Structures\Graph\Graph.cpp

CMakeFiles/Graph.dir/Graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Graph.dir/Graph.cpp.i"
	D:\AllOfProgram\Auxiliary\MinGW-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\AllOfProgram\Code\Data_Structures\Graph\Graph.cpp > CMakeFiles\Graph.dir\Graph.cpp.i

CMakeFiles/Graph.dir/Graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Graph.dir/Graph.cpp.s"
	D:\AllOfProgram\Auxiliary\MinGW-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\AllOfProgram\Code\Data_Structures\Graph\Graph.cpp -o CMakeFiles\Graph.dir\Graph.cpp.s

# Object files for target Graph
Graph_OBJECTS = \
"CMakeFiles/Graph.dir/Graph.cpp.obj"

# External object files for target Graph
Graph_EXTERNAL_OBJECTS =

Graph.exe: CMakeFiles/Graph.dir/Graph.cpp.obj
Graph.exe: CMakeFiles/Graph.dir/build.make
Graph.exe: CMakeFiles/Graph.dir/linklibs.rsp
Graph.exe: CMakeFiles/Graph.dir/objects1.rsp
Graph.exe: CMakeFiles/Graph.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\AllOfProgram\Code\Data_Structures\Graph\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Graph.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Graph.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Graph.dir/build: Graph.exe

.PHONY : CMakeFiles/Graph.dir/build

CMakeFiles/Graph.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Graph.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Graph.dir/clean

CMakeFiles/Graph.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\AllOfProgram\Code\Data_Structures\Graph D:\AllOfProgram\Code\Data_Structures\Graph D:\AllOfProgram\Code\Data_Structures\Graph\build D:\AllOfProgram\Code\Data_Structures\Graph\build D:\AllOfProgram\Code\Data_Structures\Graph\build\CMakeFiles\Graph.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Graph.dir/depend
