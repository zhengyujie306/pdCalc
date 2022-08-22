cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

project(pdCalc-cli)

add_definitions(-std=c++14)

set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(src)
add_executable(pdCalc-cli pdCalc-simple-cli.cpp)
target_link_libraries(pdCalc-cli src)

project(pdCalc-gui)

add_definitions(-std=c++14)

set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_executable(pdCalc-gui pdCalc-simple-gui.cpp)
target_link_libraries(pdCalc-gui src sfml-graphics sfml-window sfml-system)

