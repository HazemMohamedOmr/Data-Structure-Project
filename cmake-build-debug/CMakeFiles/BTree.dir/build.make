# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Hazem\CLionProjects\BTree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Hazem\CLionProjects\BTree\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/BTree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/BTree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BTree.dir/flags.make

CMakeFiles/BTree.dir/main.c.obj: CMakeFiles/BTree.dir/flags.make
CMakeFiles/BTree.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Hazem\CLionProjects\BTree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/BTree.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\BTree.dir\main.c.obj -c C:\Users\Hazem\CLionProjects\BTree\main.c

CMakeFiles/BTree.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BTree.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Hazem\CLionProjects\BTree\main.c > CMakeFiles\BTree.dir\main.c.i

CMakeFiles/BTree.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BTree.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Hazem\CLionProjects\BTree\main.c -o CMakeFiles\BTree.dir\main.c.s

CMakeFiles/BTree.dir/BTree.c.obj: CMakeFiles/BTree.dir/flags.make
CMakeFiles/BTree.dir/BTree.c.obj: ../BTree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Hazem\CLionProjects\BTree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/BTree.dir/BTree.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\BTree.dir\BTree.c.obj -c C:\Users\Hazem\CLionProjects\BTree\BTree.c

CMakeFiles/BTree.dir/BTree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BTree.dir/BTree.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Hazem\CLionProjects\BTree\BTree.c > CMakeFiles\BTree.dir\BTree.c.i

CMakeFiles/BTree.dir/BTree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BTree.dir/BTree.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Hazem\CLionProjects\BTree\BTree.c -o CMakeFiles\BTree.dir\BTree.c.s

# Object files for target BTree
BTree_OBJECTS = \
"CMakeFiles/BTree.dir/main.c.obj" \
"CMakeFiles/BTree.dir/BTree.c.obj"

# External object files for target BTree
BTree_EXTERNAL_OBJECTS =

BTree.exe: CMakeFiles/BTree.dir/main.c.obj
BTree.exe: CMakeFiles/BTree.dir/BTree.c.obj
BTree.exe: CMakeFiles/BTree.dir/build.make
BTree.exe: CMakeFiles/BTree.dir/linklibs.rsp
BTree.exe: CMakeFiles/BTree.dir/objects1.rsp
BTree.exe: CMakeFiles/BTree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Hazem\CLionProjects\BTree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable BTree.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\BTree.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BTree.dir/build: BTree.exe

.PHONY : CMakeFiles/BTree.dir/build

CMakeFiles/BTree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\BTree.dir\cmake_clean.cmake
.PHONY : CMakeFiles/BTree.dir/clean

CMakeFiles/BTree.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Hazem\CLionProjects\BTree C:\Users\Hazem\CLionProjects\BTree C:\Users\Hazem\CLionProjects\BTree\cmake-build-debug C:\Users\Hazem\CLionProjects\BTree\cmake-build-debug C:\Users\Hazem\CLionProjects\BTree\cmake-build-debug\CMakeFiles\BTree.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BTree.dir/depend

