cmake_minimum_required(VERSION 3.5)
project(solucion)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-g -O3 -pthread")

include_directories(tests/google-test)
add_subdirectory(tests/google-test)

file(GLOB SOURCE_FILES src/code/*.cpp src/code/tools/*.cpp)
file(GLOB TEST_SOURCES tests/*.cpp)

add_executable(tp3 src/main.cpp ${SOURCE_FILES})
add_executable(compare src/comparador.cpp ${SOURCE_FILES})

# Creamos el ejecutable para correr los tests
add_executable(correrTests ${TEST_SOURCES} ${SOURCE_FILES})

# Necesitamos asociar los archivos del framework de testing
target_link_libraries(correrTests gtest gtest_main)

add_test(correrTests correrTests)
