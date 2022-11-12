cmake_minimum_required(VERSION 3.23)
project(CafeteriaSimulation)

set(CMAKE_CXX_STANDARD 23)

add_executable(CafeteriaSimulation main.cpp Scheduler.cpp Scheduler.h Event.cpp Event.h)
