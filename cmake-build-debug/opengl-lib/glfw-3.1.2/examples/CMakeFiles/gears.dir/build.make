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
include opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/depend.make

# Include the progress variables for this target.
include opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/progress.make

# Include the compile flags for this target's objects.
include opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/flags.make

opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.obj: opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/flags.make
opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.obj: opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/includes_C.rsp
opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.obj: ../opengl-lib/glfw-3.1.2/examples/gears.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.obj"
	cd /d D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\examples && C:\GCC\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\gears.dir\gears.c.obj   -c D:\CLionWorkSpace\opengl-bootcamp\opengl-lib\glfw-3.1.2\examples\gears.c

opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gears.dir/gears.c.i"
	cd /d D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\examples && C:\GCC\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\CLionWorkSpace\opengl-bootcamp\opengl-lib\glfw-3.1.2\examples\gears.c > CMakeFiles\gears.dir\gears.c.i

opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gears.dir/gears.c.s"
	cd /d D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\examples && C:\GCC\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\CLionWorkSpace\opengl-bootcamp\opengl-lib\glfw-3.1.2\examples\gears.c -o CMakeFiles\gears.dir\gears.c.s

opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.obj.requires:

.PHONY : opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.obj.requires

opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.obj.provides: opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.obj.requires
	$(MAKE) -f opengl-lib\glfw-3.1.2\examples\CMakeFiles\gears.dir\build.make opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.obj.provides.build
.PHONY : opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.obj.provides

opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.obj.provides.build: opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.obj


# Object files for target gears
gears_OBJECTS = \
"CMakeFiles/gears.dir/gears.c.obj"

# External object files for target gears
gears_EXTERNAL_OBJECTS =

opengl-lib/glfw-3.1.2/examples/gears.exe: opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.obj
opengl-lib/glfw-3.1.2/examples/gears.exe: opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/build.make
opengl-lib/glfw-3.1.2/examples/gears.exe: opengl-lib/glfw-3.1.2/src/libglfw3.a
opengl-lib/glfw-3.1.2/examples/gears.exe: opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/linklibs.rsp
opengl-lib/glfw-3.1.2/examples/gears.exe: opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/objects1.rsp
opengl-lib/glfw-3.1.2/examples/gears.exe: opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable gears.exe"
	cd /d D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\gears.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/build: opengl-lib/glfw-3.1.2/examples/gears.exe

.PHONY : opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/build

opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/requires: opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.obj.requires

.PHONY : opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/requires

opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/clean:
	cd /d D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\examples && $(CMAKE_COMMAND) -P CMakeFiles\gears.dir\cmake_clean.cmake
.PHONY : opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/clean

opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\CLionWorkSpace\opengl-bootcamp D:\CLionWorkSpace\opengl-bootcamp\opengl-lib\glfw-3.1.2\examples D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\examples D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\examples\CMakeFiles\gears.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : opengl-lib/glfw-3.1.2/examples/CMakeFiles/gears.dir/depend

