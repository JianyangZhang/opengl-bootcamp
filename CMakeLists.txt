# CMake is a generator of buildsystems. It can produce Makefiles
cmake_minimum_required(VERSION 3.8)
project(opengl_bootcamp)
find_package(OpenGL REQUIRED) # cannot compile without this line, figure it out later
set(CMAKE_CXX_STANDARD 11)

# generate opengl_bootcamp.exe after compile
set(SOURCE_FILES main.cpp)
add_executable(opengl_bootcamp ${SOURCE_FILES})

# figure it out later
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/opengl-lib/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP
if (INCLUDE_DISTRIB)
    add_subdirectory(distrib)
endif (INCLUDE_DISTRIB)

# import all opengl libraries
add_subdirectory(opengl-lib)
include_directories(
        opengl-lib/AntTweakBar-1.16/include/
        opengl-lib/glfw-3.1.2/include/GLFW/
        opengl-lib/glm-0.9.7.1/
        opengl-lib/glew-1.13.0/include/
        opengl-lib/assimp-3.0.1270/include/
        opengl-lib/bullet-2.81-rev2613/src/
        .
)

# figure it out later, maybe define some constants
add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
)

# define ALL_LIBS
set(ALL_LIBS
        ${OPENGL_LIBRARY}
        glfw
        GLEW_1130
        )

# link opengl_bootcamp.exe to all ALL_LIBS
target_link_libraries(opengl_bootcamp
        ${ALL_LIBS}
        )