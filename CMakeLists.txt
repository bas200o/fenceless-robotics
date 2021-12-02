cmake_minimum_required(VERSION 3.14.0)
project(fenceless-robot VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(realsense2 REQUIRED)
find_package( PCL 1.2 REQUIRED )
find_package (Python2 COMPONENTS Interpreter Development)
find_package (Threads)

# [C/C++]>[General]>[Additional Include Directories]
include_directories( ${PCL_INCLUDE_DIRS} )

# [C/C++]>[Preprocessor]>[Preprocessor Definitions]
add_definitions( ${PCL_DEFINITIONS} )
  
# For Use Not PreCompiled Features 
add_definitions( -DPCL_NO_PRECOMPILE )

  # [Linker]>[General]>[Additional Library Directories]
link_directories( ${PCL_LIBRARY_DIRS} )

# Enable C++11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(fenceless-robot src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${realsense2_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
