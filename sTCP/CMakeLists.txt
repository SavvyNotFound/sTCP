cmake_minimum_required(VERSION 3.16)
project(sTCP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${PROJECT_NAME})

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# SPDLOG
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        spdlog
    PUBLIC
)

# Compile defs
target_compile_definitions(${PROJECT_NAME} PUBLIC
    $<$<CONFIG:Debug>:${PROJECT_NAME}_DEBUG;${PROJECT_NAME}_ENABLE_ASSERTS>
    $<$<CONFIG:Release>:${PROJECT_NAME}_RELEASE>
    $<$<CONFIG:Dist>:${PROJECT_NAME}_DIST>
    SPDLOG_COMPILED_LIB
)

# Include Dirs
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
)
