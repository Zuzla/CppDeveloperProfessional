cmake_minimum_required(VERSION 3.0.0)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(matrix VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

include(CTest)
enable_testing()

add_executable(matrix src/main.cpp src/matrix.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

install(TARGETS matrix RUNTIME DESTINATION bin)

target_compile_options(matrix PRIVATE
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
