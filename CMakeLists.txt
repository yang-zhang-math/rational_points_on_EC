cmake_minimum_required(VERSION 3.0.0)
project(EConQ VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(EConQ main.cpp)

add_subdirectory(libs)

target_link_libraries(EConQ libs)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
