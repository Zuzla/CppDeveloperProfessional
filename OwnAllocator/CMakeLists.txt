cmake_minimum_required(VERSION 3.0.0)
project(own_allocator VERSION 0.1.0 LANGUAGES C CXX)


add_executable(own_allocator 
    src/main.cpp
    src/allocator.h
    src/vector.h
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
