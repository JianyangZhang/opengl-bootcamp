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
include opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/depend.make

# Include the progress variables for this target.
include opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/progress.make

# Include the compile flags for this target's objects.
include opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/flags.make

opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/heightmap.c.obj: opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/flags.make
opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/heightmap.c.obj: opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/includes_C.rsp
opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/heightmap.c.obj: ../opengl-lib/glfw-3.1.2/examples/heightmap.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/heightmap.c.obj"
	cd /d D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\examples && C:\GCC\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\heightmap.dir\heightmap.c.obj   -c D:\CLionWorkSpace\opengl-bootcamp\opengl-lib\glfw-3.1.2\examples\heightmap.c

opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/heightmap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/heightmap.dir/heightmap.c.i"
	cd /d D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\examples && C:\GCC\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\CLionWorkSpace\opengl-bootcamp\opengl-lib\glfw-3.1.2\examples\heightmap.c > CMakeFiles\heightmap.dir\heightmap.c.i

opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/heightmap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/heightmap.dir/heightmap.c.s"
	cd /d D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\examples && C:\GCC\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\CLionWorkSpace\opengl-bootcamp\opengl-lib\glfw-3.1.2\examples\heightmap.c -o CMakeFiles\heightmap.dir\heightmap.c.s

opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/heightmap.c.obj.requires:

.PHONY : opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/heightmap.c.obj.requires

opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/heightmap.c.obj.provides: opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/heightmap.c.obj.requires
	$(MAKE) -f opengl-lib\glfw-3.1.2\examples\CMakeFiles\heightmap.dir\build.make opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/heightmap.c.obj.provides.build
.PHONY : opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/heightmap.c.obj.provides

opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/heightmap.c.obj.provides.build: opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/heightmap.c.obj


opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj: opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/flags.make
opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj: opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/includes_C.rsp
opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj: ../opengl-lib/glfw-3.1.2/deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj"
	cd /d D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\examples && C:\GCC\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\heightmap.dir\__\deps\glad.c.obj   -c D:\CLionWorkSpace\opengl-bootcamp\opengl-lib\glfw-3.1.2\deps\glad.c

opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/heightmap.dir/__/deps/glad.c.i"
	cd /d D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\examples && C:\GCC\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\CLionWorkSpace\opengl-bootcamp\opengl-lib\glfw-3.1.2\deps\glad.c > CMakeFiles\heightmap.dir\__\deps\glad.c.i

opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/heightmap.dir/__/deps/glad.c.s"
	cd /d D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\examples && C:\GCC\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\CLionWorkSpace\opengl-bootcamp\opengl-lib\glfw-3.1.2\deps\glad.c -o CMakeFiles\heightmap.dir\__\deps\glad.c.s

opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj.requires:

.PHONY : opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj.requires

opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj.provides: opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj.requires
	$(MAKE) -f opengl-lib\glfw-3.1.2\examples\CMakeFiles\heightmap.dir\build.make opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj.provides.build
.PHONY : opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj.provides

opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj.provides.build: opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj


# Object files for target heightmap
heightmap_OBJECTS = \
"CMakeFiles/heightmap.dir/heightmap.c.obj" \
"CMakeFiles/heightmap.dir/__/deps/glad.c.obj"

# External object files for target heightmap
heightmap_EXTERNAL_OBJECTS =

opengl-lib/glfw-3.1.2/examples/heightmap.exe: opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/heightmap.c.obj
opengl-lib/glfw-3.1.2/examples/heightmap.exe: opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj
opengl-lib/glfw-3.1.2/examples/heightmap.exe: opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/build.make
opengl-lib/glfw-3.1.2/examples/heightmap.exe: opengl-lib/glfw-3.1.2/src/libglfw3.a
opengl-lib/glfw-3.1.2/examples/heightmap.exe: opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/linklibs.rsp
opengl-lib/glfw-3.1.2/examples/heightmap.exe: opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/objects1.rsp
opengl-lib/glfw-3.1.2/examples/heightmap.exe: opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable heightmap.exe"
	cd /d D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\heightmap.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/build: opengl-lib/glfw-3.1.2/examples/heightmap.exe

.PHONY : opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/build

opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/requires: opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/heightmap.c.obj.requires
opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/requires: opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/__/deps/glad.c.obj.requires

.PHONY : opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/requires

opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/clean:
	cd /d D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\examples && $(CMAKE_COMMAND) -P CMakeFiles\heightmap.dir\cmake_clean.cmake
.PHONY : opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/clean

opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\CLionWorkSpace\opengl-bootcamp D:\CLionWorkSpace\opengl-bootcamp\opengl-lib\glfw-3.1.2\examples D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\examples D:\CLionWorkSpace\opengl-bootcamp\cmake-build-debug\opengl-lib\glfw-3.1.2\examples\CMakeFiles\heightmap.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : opengl-lib/glfw-3.1.2/examples/CMakeFiles/heightmap.dir/depend

