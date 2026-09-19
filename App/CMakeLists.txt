cmake_minimum_required(VERSION 3.16)
project(App)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${PROJECT_NAME})

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCE_FILES "src/*.cpp")

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/sTCP/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE sTCP)

# add_custom_target(${PROJECT_NAME}_copy_assets
#     COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
#     COMMENT "Example"
# )
# add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_copy_assets)
