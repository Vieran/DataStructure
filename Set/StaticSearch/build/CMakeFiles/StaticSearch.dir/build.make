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
CMAKE_SOURCE_DIR = D:\AllOfProgram\Code\Data_Structures\Set\StaticSearch

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\AllOfProgram\Code\Data_Structures\Set\StaticSearch\build

# Include any dependencies generated for this target.
include CMakeFiles/StaticSearch.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/StaticSearch.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/StaticSearch.dir/flags.make

CMakeFiles/StaticSearch.dir/StaticSearch.cpp.obj: CMakeFiles/StaticSearch.dir/flags.make
CMakeFiles/StaticSearch.dir/StaticSearch.cpp.obj: CMakeFiles/StaticSearch.dir/includes_CXX.rsp
CMakeFiles/StaticSearch.dir/StaticSearch.cpp.obj: ../StaticSearch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\AllOfProgram\Code\Data_Structures\Set\StaticSearch\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/StaticSearch.dir/StaticSearch.cpp.obj"
	D:\AllOfProgram\Auxiliary\MinGW-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\StaticSearch.dir\StaticSearch.cpp.obj -c D:\AllOfProgram\Code\Data_Structures\Set\StaticSearch\StaticSearch.cpp

CMakeFiles/StaticSearch.dir/StaticSearch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StaticSearch.dir/StaticSearch.cpp.i"
	D:\AllOfProgram\Auxiliary\MinGW-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\AllOfProgram\Code\Data_Structures\Set\StaticSearch\StaticSearch.cpp > CMakeFiles\StaticSearch.dir\StaticSearch.cpp.i

CMakeFiles/StaticSearch.dir/StaticSearch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StaticSearch.dir/StaticSearch.cpp.s"
	D:\AllOfProgram\Auxiliary\MinGW-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\AllOfProgram\Code\Data_Structures\Set\StaticSearch\StaticSearch.cpp -o CMakeFiles\StaticSearch.dir\StaticSearch.cpp.s

# Object files for target StaticSearch
StaticSearch_OBJECTS = \
"CMakeFiles/StaticSearch.dir/StaticSearch.cpp.obj"

# External object files for target StaticSearch
StaticSearch_EXTERNAL_OBJECTS =

StaticSearch.exe: CMakeFiles/StaticSearch.dir/StaticSearch.cpp.obj
StaticSearch.exe: CMakeFiles/StaticSearch.dir/build.make
StaticSearch.exe: CMakeFiles/StaticSearch.dir/linklibs.rsp
StaticSearch.exe: CMakeFiles/StaticSearch.dir/objects1.rsp
StaticSearch.exe: CMakeFiles/StaticSearch.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\AllOfProgram\Code\Data_Structures\Set\StaticSearch\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable StaticSearch.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\StaticSearch.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/StaticSearch.dir/build: StaticSearch.exe

.PHONY : CMakeFiles/StaticSearch.dir/build

CMakeFiles/StaticSearch.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\StaticSearch.dir\cmake_clean.cmake
.PHONY : CMakeFiles/StaticSearch.dir/clean

CMakeFiles/StaticSearch.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\AllOfProgram\Code\Data_Structures\Set\StaticSearch D:\AllOfProgram\Code\Data_Structures\Set\StaticSearch D:\AllOfProgram\Code\Data_Structures\Set\StaticSearch\build D:\AllOfProgram\Code\Data_Structures\Set\StaticSearch\build D:\AllOfProgram\Code\Data_Structures\Set\StaticSearch\build\CMakeFiles\StaticSearch.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/StaticSearch.dir/depend
