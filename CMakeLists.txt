cmake_minimum_required(VERSION 3.14)
project(Project_3_Final)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp square.cpp square.h maze.cpp maze.h TextureManager.cpp TextureManager.h Random.cpp Random.h HomeScreen.cpp HomeScreen.h MazeAnalysis.cpp MazeAnalysis.h Game.cpp Game.h)
add_executable(Project_3_Final ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Project_3_Final sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
