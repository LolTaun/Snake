cmake_minimum_required(VERSION 3.23)
project(snake)
set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(snake ${SDL2_INCLUDE_DIR})
#message(${SDL2_INCLUDE_DIRS})

add_executable(snake main.cpp snake+direction.h snake_context.h)
target_link_libraries(snake ${SDL2_LIBRARIES})