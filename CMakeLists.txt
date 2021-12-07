cmake_minimum_required(VERSION 3.15)
project(ParaRacu_3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(ParaRacu_3 main.cpp sinhroniziranaVrsta.h)
