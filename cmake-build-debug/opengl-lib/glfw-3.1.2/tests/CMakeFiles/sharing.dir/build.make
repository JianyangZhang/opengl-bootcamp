# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\CLionWorkSpace\opengl-bootcamp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug

# Include any dependencies generated for this target.
include opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/depend.make

# Include the progress variables for this target.
include opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/progress.make

# Include the compile flags for this target's objects.
include opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/flags.make

opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj: opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/flags.make
opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj: opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/includes_C.rsp
opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj: ../opengl-lib/glfw-3.1.2/tests/sharing.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj"
	cd /d D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\tests && C:\GCC\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\sharing.dir\sharing.c.obj   -c D:\CLionWorkSpace\opengl-bootcamp\opengl-lib\glfw-3.1.2\tests\sharing.c

opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sharing.dir/sharing.c.i"
	cd /d D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\tests && C:\GCC\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\CLionWorkSpace\opengl-bootcamp\opengl-lib\glfw-3.1.2\tests\sharing.c > CMakeFiles\sharing.dir\sharing.c.i

opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sharing.dir/sharing.c.s"
	cd /d D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\tests && C:\GCC\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\CLionWorkSpace\opengl-bootcamp\opengl-lib\glfw-3.1.2\tests\sharing.c -o CMakeFiles\sharing.dir\sharing.c.s

opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj.requires:

.PHONY : opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj.requires

opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj.provides: opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj.requires
	$(MAKE) -f opengl-lib\glfw-3.1.2\tests\CMakeFiles\sharing.dir\build.make opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj.provides.build
.PHONY : opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj.provides

opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj.provides.build: opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj


# Object files for target sharing
sharing_OBJECTS = \
"CMakeFiles/sharing.dir/sharing.c.obj"

# External object files for target sharing
sharing_EXTERNAL_OBJECTS =

opengl-lib/glfw-3.1.2/tests/sharing.exe: opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj
opengl-lib/glfw-3.1.2/tests/sharing.exe: opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/build.make
opengl-lib/glfw-3.1.2/tests/sharing.exe: opengl-lib/glfw-3.1.2/src/libglfw3.a
opengl-lib/glfw-3.1.2/tests/sharing.exe: opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/linklibs.rsp
opengl-lib/glfw-3.1.2/tests/sharing.exe: opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/objects1.rsp
opengl-lib/glfw-3.1.2/tests/sharing.exe: opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable sharing.exe"
	cd /d D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\sharing.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/build: opengl-lib/glfw-3.1.2/tests/sharing.exe

.PHONY : opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/build

opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/requires: opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj.requires

.PHONY : opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/requires

opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/clean:
	cd /d D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\tests && $(CMAKE_COMMAND) -P CMakeFiles\sharing.dir\cmake_clean.cmake
.PHONY : opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/clean

opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\CLionWorkSpace\opengl-bootcamp D:\CLionWorkSpace\opengl-bootcamp\opengl-lib\glfw-3.1.2\tests D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\tests D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\tests\CMakeFiles\sharing.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : opengl-lib/glfw-3.1.2/tests/CMakeFiles/sharing.dir/depend

