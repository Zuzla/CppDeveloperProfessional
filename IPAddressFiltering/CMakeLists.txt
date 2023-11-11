cmake_minimum_required(VERSION 3.0.0)
project(ip_filter VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
conan_basic_setup(TARGETS)
add_executable(ip_filter 
    src/main.cpp
)

add_executable(google_test
    tests/gtest_main.cpp
    src/main.cpp
)
target_link_libraries(google_test PRIVATE CONAN_PKG::gtest) 

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
