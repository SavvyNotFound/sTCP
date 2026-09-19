cmake_minimum_required(VERSION 3.16)
project(sTCP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ALLOWED_BUILD_TYPES Debug Release Dist)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

if(NOT CMAKE_BUILD_TYPE IN_LIST ALLOWED_BUILD_TYPES)
    message(FATAL_ERROR "Invalid build type '${CMAKE_BUILD_TYPE}'. Allowed types: ${ALLOWED_BUILD_TYPES}")
endif()

if (WIN32)
    add_compile_definitions(${PROJECT_NAME}_WINDOW)
elseif (LINUX)
    add_compile_definitions(${PROJECT_NAME}_LINUX)
elseif (APPLE)
    add_compile_definitions(${PROJECT_NAME}_MAC)
endif()

add_compile_options(
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O2>
    $<$<CONFIG:Dist>:-O3>
)

add_subdirectory(sTCP)
add_subdirectory(App)
