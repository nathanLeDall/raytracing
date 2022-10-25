cmake_minimum_required(VERSION 3.21)
project(untitled2)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled2 main.cpp vec3.h Colour.h Ray.h hittable.h sphere.h hittableList.h rtconstants.h Camera.h Material.h randoms.h)
