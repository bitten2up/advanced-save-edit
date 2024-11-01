cmake_minimum_required(VERSION 3.15)
project(advance-save-edit)

add_subdirectory(src advance-save-edit)
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(advance-save-edit copy_assets)
