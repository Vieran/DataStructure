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
CMAKE_SOURCE_DIR = D:\AllOfProgram\Code\Data_Structures\Algorithm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\AllOfProgram\Code\Data_Structures\Algorithm\build

# Include any dependencies generated for this target.
include CMakeFiles/Algorithm.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Algorithm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Algorithm.dir/flags.make

CMakeFiles/Algorithm.dir/Algorithm.cpp.obj: CMakeFiles/Algorithm.dir/flags.make
CMakeFiles/Algorithm.dir/Algorithm.cpp.obj: CMakeFiles/Algorithm.dir/includes_CXX.rsp
CMakeFiles/Algorithm.dir/Algorithm.cpp.obj: ../Algorithm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\AllOfProgram\Code\Data_Structures\Algorithm\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Algorithm.dir/Algorithm.cpp.obj"
	D:\AllOfProgram\Auxiliary\MinGW-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Algorithm.dir\Algorithm.cpp.obj -c D:\AllOfProgram\Code\Data_Structures\Algorithm\Algorithm.cpp

CMakeFiles/Algorithm.dir/Algorithm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Algorithm.dir/Algorithm.cpp.i"
	D:\AllOfProgram\Auxiliary\MinGW-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\AllOfProgram\Code\Data_Structures\Algorithm\Algorithm.cpp > CMakeFiles\Algorithm.dir\Algorithm.cpp.i

CMakeFiles/Algorithm.dir/Algorithm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Algorithm.dir/Algorithm.cpp.s"
	D:\AllOfProgram\Auxiliary\MinGW-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\AllOfProgram\Code\Data_Structures\Algorithm\Algorithm.cpp -o CMakeFiles\Algorithm.dir\Algorithm.cpp.s

CMakeFiles/Algorithm.dir/Lib/Small_Tricks.cpp.obj: CMakeFiles/Algorithm.dir/flags.make
CMakeFiles/Algorithm.dir/Lib/Small_Tricks.cpp.obj: CMakeFiles/Algorithm.dir/includes_CXX.rsp
CMakeFiles/Algorithm.dir/Lib/Small_Tricks.cpp.obj: ../Lib/Small_Tricks.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\AllOfProgram\Code\Data_Structures\Algorithm\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Algorithm.dir/Lib/Small_Tricks.cpp.obj"
	D:\AllOfProgram\Auxiliary\MinGW-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Algorithm.dir\Lib\Small_Tricks.cpp.obj -c D:\AllOfProgram\Code\Data_Structures\Algorithm\Lib\Small_Tricks.cpp

CMakeFiles/Algorithm.dir/Lib/Small_Tricks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Algorithm.dir/Lib/Small_Tricks.cpp.i"
	D:\AllOfProgram\Auxiliary\MinGW-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\AllOfProgram\Code\Data_Structures\Algorithm\Lib\Small_Tricks.cpp > CMakeFiles\Algorithm.dir\Lib\Small_Tricks.cpp.i

CMakeFiles/Algorithm.dir/Lib/Small_Tricks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Algorithm.dir/Lib/Small_Tricks.cpp.s"
	D:\AllOfProgram\Auxiliary\MinGW-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\AllOfProgram\Code\Data_Structures\Algorithm\Lib\Small_Tricks.cpp -o CMakeFiles\Algorithm.dir\Lib\Small_Tricks.cpp.s

# Object files for target Algorithm
Algorithm_OBJECTS = \
"CMakeFiles/Algorithm.dir/Algorithm.cpp.obj" \
"CMakeFiles/Algorithm.dir/Lib/Small_Tricks.cpp.obj"

# External object files for target Algorithm
Algorithm_EXTERNAL_OBJECTS =

Algorithm.exe: CMakeFiles/Algorithm.dir/Algorithm.cpp.obj
Algorithm.exe: CMakeFiles/Algorithm.dir/Lib/Small_Tricks.cpp.obj
Algorithm.exe: CMakeFiles/Algorithm.dir/build.make
Algorithm.exe: CMakeFiles/Algorithm.dir/linklibs.rsp
Algorithm.exe: CMakeFiles/Algorithm.dir/objects1.rsp
Algorithm.exe: CMakeFiles/Algorithm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\AllOfProgram\Code\Data_Structures\Algorithm\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Algorithm.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Algorithm.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Algorithm.dir/build: Algorithm.exe

.PHONY : CMakeFiles/Algorithm.dir/build

CMakeFiles/Algorithm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Algorithm.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Algorithm.dir/clean

CMakeFiles/Algorithm.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\AllOfProgram\Code\Data_Structures\Algorithm D:\AllOfProgram\Code\Data_Structures\Algorithm D:\AllOfProgram\Code\Data_Structures\Algorithm\build D:\AllOfProgram\Code\Data_Structures\Algorithm\build D:\AllOfProgram\Code\Data_Structures\Algorithm\build\CMakeFiles\Algorithm.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Algorithm.dir/depend

