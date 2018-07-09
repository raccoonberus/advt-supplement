cmake_minimum_required(VERSION 3.10)
project(advt_supplement)

set(CMAKE_CXX_STANDARD 11)

add_executable(advt_supplement main.cpp)

find_package(OpenCV REQUIRED)
target_link_libraries(advt_supplement ${OpenCV_LIBS})