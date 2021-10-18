cmake_minimum_required(VERSION 3.0)
project(CompactImpl)
set(CMAKE_CXX_STANDARD 11)

add_definitions(-DBUILD_INTERFACES)

include_directories(include)
set(SRC_COMPACT src/CompactImpl.h src/CompactImplControlBlock.h src/MultiIndexImpl.h
    src/LoggerImpl.cpp src/CompactImpl.cpp src/CompactImplIterator.cpp
    src/CompactImplControlBlock.cpp src/MultiIndexImpl.cpp src/CompactImplIterator.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC_COMPACT})
# What's for? target_link_directories(${PROJECT_NAME} PUBLIC lib)
# find_library ???
find_library(VECTOR_LIB NAMES libVectorImpl VectorImpl lVectorImpl HINTS "lib/")
target_link_libraries(${PROJECT_NAME} ${VECTOR_LIB})
