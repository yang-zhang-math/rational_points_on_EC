cmake_minimum_required(VERSION 3.0.0)
project(libs VERSION 0.1.0)

include(CTest)
enable_testing()


add_library(libs STATIC rational.cpp test.cpp ECcurve.cpp)

target_include_directories(libs PUBLIC ./)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
