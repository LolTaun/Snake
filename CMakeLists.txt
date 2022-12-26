cmake_minimum_required(VERSION 3.23)
project(snake)
set(CMAKE_CXX_STANDARD 20)

set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

SET(CMAKE_CXX_FLAGS -pthread)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})



add_executable(snake main.cpp Game.h Game.cpp snake_context.h snake_context.cpp  )
target_link_libraries(snake ${SDL2_LIBRARIES} -lSDL2_ttf -lSDL2)