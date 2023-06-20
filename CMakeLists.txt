cmake_minimum_required(VERSION 3.16)
project(Saper)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(Saper main.cpp Grid.cpp Grid.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories(C:/SFML-2.5.1/include)
target_link_libraries(Saper sfml-system sfml-window sfml-graphics sfml-network sfml-audio)