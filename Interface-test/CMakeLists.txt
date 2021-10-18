cmake_minimum_required(VERSION 3.0)
project(InterfaceTest)
set(CMAKE_CXX_STANDARD 11)

include_directories(include)
include_directories(test)

file(GLOB TEST test/*.cpp)

add_executable(${PROJECT_NAME} ${TEST})

# find_library ???
# target_link_directories(${PROJECT_NAME} PUBLIC lib)
# find_library ???
find_library(VECTOR_LIB NAMES libVectorImpl VectorImpl lVectorImpl HINTS "lib/")
find_library(SET_LIB NAMES libSetImpl SetImpl lSetImpl HINTS "lib/")
find_library(COMPACT_LIB NAMES libCompactImpl CompactImpl lCompactImpl HINTS "lib/")
target_link_libraries(${PROJECT_NAME} ${VECTOR_LIB} ${SET_LIB} ${COMPACT_LIB})
