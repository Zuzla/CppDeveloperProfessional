cmake_minimum_required(VERSION 3.0.0)
project(bulk CXX)
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

set(CPACK_GENERATOR DEB)
SET(CPACK_OUTPUT_FILE_PREFIX packages)