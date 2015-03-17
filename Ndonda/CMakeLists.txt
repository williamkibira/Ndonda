cmake_minimum_required(VERSION 2.6)
project(ndonda)

add_executable(ndonda main.cpp)

install(TARGETS ndonda RUNTIME DESTINATION bin)
