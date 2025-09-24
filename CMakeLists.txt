cmake_minimum_required(VERSION 4.0.1)

project(game1 VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(game1 ${SOURCES})

target_compile_options(game1 PRIVATE /utf-8)

target_include_directories(game1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SFML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML/lib/cmake/SFML)
find_package(SFML REQUIRED COMPONENTS Graphics Window System)

target_link_libraries(game1 PRIVATE
  SFML::Graphics
  SFML::Window
  SFML::System
)

