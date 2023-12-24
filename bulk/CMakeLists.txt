cmake_minimum_required(VERSION 3.0.0)
project(bulk CXX)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_BUILD_TYPE Debug)

find_package(Boost 1.82.0)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(bulk 
  src/main.cpp
  src/bulk.cpp  
  src/bulk.h  
)

add_executable(utest
    tests/utest.cpp
)
target_link_libraries(utest PRIVATE boost::boost )