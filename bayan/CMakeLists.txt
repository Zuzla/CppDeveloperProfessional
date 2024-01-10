cmake_minimum_required(VERSION 3.0.0)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(bayan VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

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

install(TARGETS bayan RUNTIME DESTINATION bin)

target_compile_options(bayan PRIVATE
        -Wall -Wextra -pedantic
    )

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

SET(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_SOURCE_DIR}/build/packages")

set(CPACK_GENERATOR DEB)
SET(CPACK_OUTPUT_FILE_PREFIX packages)
set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
