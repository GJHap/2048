cmake_minimum_required(VERSION 3.10)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(2048 VERSION 1.0)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Curses REQUIRED)
set(SOURCE_LIST
  "src/2048.cpp"
  "src/2048.hpp"
  "src/Main.cpp"
  "CMakeLists.txt"
  "LICENSE"
  "README.md"
  ".gitignore"
  )

add_executable(${PROJECT_NAME} ${SOURCE_LIST})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
target_include_directories(${PROJECT_NAME} PRIVATE ${CURSES_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
