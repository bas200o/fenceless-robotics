cmake_minimum_required(VERSION 3.0.0)
project(fenceless-robot VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(realsense2 REQUIRED)
# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(fenceless-robot src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${realsense2_LIBRARY})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
