cmake_minimum_required(VERSION 3.0)
project(Interface)
set(CMAKE_CXX_STANDARD 11)

include_directories(include)
include_directories(test)

file(GLOB SRC_VECTOR src/VectorImpl.cpp src/LoggerImpl.cpp)
file(GLOB SRC_SET src/SetImpl.cpp src/LoggerImpl.cpp)

file(GLOB TEST test/*.cpp)

add_library(Vector SHARED ${SRC_VECTOR})
add_library(Set SHARED ${SRC_SET})

add_executable(${PROJECT_NAME}-test ${TEST})
target_link_libraries(${PROJECT_NAME}-test Vector Set)
