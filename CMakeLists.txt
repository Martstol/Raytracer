project(raytracer)
cmake_minimum_required(VERSION 2.8)

add_definitions(-DGLM_FORCE_RADIANS)

find_package(PNG REQUIRED)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wpedantic -Wfatal-errors -g3 -Og -march=native")

set(libs
	${PNG_LIBRARIES}
)

set(incs
	include/
)

set(srcs
	src/main.cpp
	src/raytracer.cpp
)

set(exec raytracer)

include_directories(${incs})

add_executable(${exec} ${srcs})
target_link_libraries(${exec} ${libs})

