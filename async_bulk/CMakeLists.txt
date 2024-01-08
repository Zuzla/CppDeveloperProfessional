cmake_minimum_required(VERSION 3.0.0)
project(bulk CXX)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_BUILD_TYPE Debug)

find_package(Boost 1.82.0)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

add_library(async SHARED
  src/async.cpp 
  src/async.h
  src/bulk.cpp  
  src/bulk.h  
  src/log.h
  src/log_console.h  
  src/logger_async.h  
  src/log_file.h
)

add_executable(bulk 
  src/main.cpp
)

target_link_libraries(bulk PRIVATE boost::boost async)

add_executable(utest
    tests/utest.cpp
)
target_link_libraries(utest PRIVATE boost::boost )