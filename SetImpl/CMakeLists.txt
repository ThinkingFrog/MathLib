cmake_minimum_required(VERSION 3.0)
project(SetImpl)
set(CMAKE_CXX_STANDARD 11)

add_definitions(-DBUILD_INTERFACES)

include_directories(include)
set(SRC_SET src/SetImpl.h src/SetImplControlBlock.h
    src/LoggerImpl.cpp src/SetImpl.cpp src/SetImplIterator.cpp src/SetImplControlBlock.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC_SET})
# What's for? target_link_directories(${PROJECT_NAME} PUBLIC lib)
# find_library ???
find_library(VECTOR_LIB NAMES libVectorImpl VectorImpl lVectorImpl HINTS "lib/")
target_link_libraries(${PROJECT_NAME} ${VECTOR_LIB})
