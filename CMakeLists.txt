cmake_minimum_required( VERSION 3.1 )

project(SMABP)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall")

#package
find_package(Boost COMPONENTS program_options timer REQUIRED)
find_package(OpenMP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

include_directories(src ${Boost_INCLUDE_DIR})

file(GLOB SOURCES src/*.cpp)

add_executable(SMABP ${SOURCES})
target_link_libraries(SMABP ${Boost_LIBRARIES})
