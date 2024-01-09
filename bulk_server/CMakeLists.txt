cmake_minimum_required(VERSION 3.0.0)

set (PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set (PROJECT_VESRION 0.0.${PATCH_VERSION})
project(bulk_server VERSION ${PROJECT_VESRION})

set (CMAKE_CXX_STANDARD 20)

find_package(Boost 1.82.0)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(bulk_server
  src/async.cpp 
  src/async.h
  src/bulk.cpp  
  src/bulk.h  
  src/log.h
  src/log_console.h  
  src/logger_async.h  
  src/connection.cpp  
  src/connection.h
  src/log_file.h
  src/server.h
  src/server.cpp
  src/main.cpp
)

target_link_libraries(bulk_server PRIVATE boost::boost)

install(TARGETS bulk_server RUNTIME DESTINATION bin)

target_compile_options(bulk_server PRIVATE
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