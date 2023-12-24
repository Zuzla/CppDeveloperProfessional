cmake_minimum_required(VERSION 3.0.0)
project(bayan CXX)
set (CMAKE_CXX_STANDARD 20)

find_package(Boost 1.82.0)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

set (THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(bayan 
  src/main.cpp
  src/files.h
  src/files.cpp
  src/file.h
  src/file.cpp
  src/hash.cpp
  src/hash.h
)

target_link_libraries(bayan PRIVATE boost::boost Threads::Threads)

add_executable(utest
    tests/utest.cpp
)
target_link_libraries(utest PRIVATE boost::boost Threads::Threads)