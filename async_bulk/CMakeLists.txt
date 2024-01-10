cmake_minimum_required(VERSION 3.0.0)
project(async CXX)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_BUILD_TYPE Debug)

find_package(Boost 1.82.0)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

add_library(async SHARED
  src/lib/async.cpp 
  src/lib/async.h
  src/lib/bulk.cpp  
  src/lib/bulk.h  
  src/lib/log.h
  src/lib/log_console.h  
  src/lib/logger_async.h  
  src/lib/log_file.h
)

add_executable(bulk 
  src/exe/main.cpp
)

target_link_libraries(bulk PRIVATE boost::boost async)

install(TARGETS async RUNTIME DESTINATION bin)

target_compile_options(bulk PRIVATE
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
