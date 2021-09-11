cmake_minimum_required(VERSION 3.0)
project(InterfaceTest)
set(CMAKE_CXX_STANDARD 11)

include_directories(include)
include_directories(test)

file(GLOB TEST test/*.cpp)

add_executable(${PROJECT_NAME} ${TEST})
target_link_libraries(${PROJECT_NAME} VectorImpl SetImpl CompactImpl)
