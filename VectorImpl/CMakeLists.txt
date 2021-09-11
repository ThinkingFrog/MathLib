cmake_minimum_required(VERSION 3.0)
project(VectorImpl)
set(CMAKE_CXX_STANDARD 11)

add_definitions(-DBUILD_INTERFACES)

include_directories(include)
set(SRC_VECTOR src/VectorImpl.cpp src/LoggerImpl.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC_VECTOR})
