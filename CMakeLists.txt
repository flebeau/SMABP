cmake_minimum_required( VERSION 3.1 )

project(SMABP)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall")

include_directories(src)
file(GLOB SOURCES src/*.cpp)

add_executable(SMABP ${SOURCES})
#target_link_libraries(raytracer m ${X11_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
