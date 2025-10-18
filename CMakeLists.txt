cmake_minimum_required(VERSION 4.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")

project(game1 VERSION 0.0.0 LANGUAGES CXX)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(game1 ${SOURCES})

target_compile_options(game1 PRIVATE /utf-8)

target_include_directories(game1 PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/box2d/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SFML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML/lib/cmake/SFML)
find_package(SFML REQUIRED COMPONENTS Graphics Window System)

target_link_libraries(game1 PRIVATE
  SFML::Graphics
  SFML::Window
  SFML::System
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/box2d/build/src/Release/box2d.lib
)
