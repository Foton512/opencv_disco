cmake_minimum_required(VERSION 3.3)
project(opencv_disco)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(opencv_disco ${SOURCE_FILES})
target_link_libraries(opencv_disco ${OpenCV_LIBS} )