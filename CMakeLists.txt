cmake_minimum_required(VERSION 3.14.0)
project(fenceless-robot VERSION 0.1.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# set(CMAKE_PREFIX_PATH "/opt/intel/oneapi/tbb/latest")

include(CTest)
enable_testing()

find_package(realsense2 REQUIRED)
find_package( PCL 1.2 REQUIRED )
find_package (Python2 COMPONENTS Interpreter Development)
find_package (Threads)
find_package(OpenCV REQUIRED)
find_package ( Qt5 COMPONENTS Widgets REQUIRED )
find_package ( TBB REQUIRED tbb)

qt5_wrap_cpp(gui_SRC GUIApplication.hpp GUIApplication.cpp GUIData.hpp GUIData.cpp)

# [C/C++]>[General]>[Additional Include Directories]
include_directories( ${PCL_INCLUDE_DIRS} )
include_directories( &{OpenCV_INCLUDE_DIRS})
# [C/C++]>[Preprocessor]>[Preprocessor Definitions]
add_definitions( ${PCL_DEFINITIONS} )

# For Use Not PreCompiled Features 
add_definitions( -DPCL_NO_PRECOMPILE )

# No keywords in Qt (clashing with TBB)
add_definitions( -DQT_NO_KEYWORDS )

  # [Linker]>[General]>[Additional Library Directories]
link_directories( ${PCL_LIBRARY_DIRS} )

# Enable C++11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(fenceless-robot ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} ${realsense2_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} )
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} TBB::tbb)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)