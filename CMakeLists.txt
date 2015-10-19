project(raytracer)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

add_definitions(-DGLM_FORCE_RADIANS)

find_package(PNG REQUIRED)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -Weverything -Wno-c++98-compat -Wno-shadow -pedantic -march=native")

set(libs
	${PNG_LIBRARIES}
)

set(incs
	include/
	${PNG_INCLUDES}
)

set(srcs
	src/main.cpp
	src/raytracer.cpp
	src/light.cpp
	src/model.cpp
	src/sphere.cpp
)

set(exec raytracer)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include_directories(${incs})

add_executable(${exec} ${srcs})
target_link_libraries(${exec} ${libs})

