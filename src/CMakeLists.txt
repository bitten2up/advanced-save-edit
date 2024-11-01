if(MSVC AND NOT VCPKG_TOOLCHAIN)
  message(FATAL_ERROR "MSVC is only supported when using vcpkg")
endif()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wpedantic -Wextra -std=c23")

add_executable(advance-save-edit "main.c" "r_render.c")

if(VCPKG_TOOLCHAIN)
  #find_package(sdl2 REQUIRED) # transitively included?
  find_package(sdl2-image REQUIRED)
  find_package(SDL_ttf REQUIRED)
  target_link_libraries(advance-save-edit PRIVATE sdl2-image)
else()
  find_package(PkgConfig REQUIRED)
  #pkg_search_module(SDL2 REQUIRED IMPORTED_TARGET sdl2 SDL2_image) # does not work for unknown reasons
  pkg_search_module(SDL2_IMAGE REQUIRED IMPORTED_TARGET SDL2_image) # transitively includes SDL2
  target_link_libraries(advance-save-edit PRIVATE PkgConfig::SDL2_IMAGE)
  pkg_search_module(SDL2_TTF REQUIRED IMPORTED_TARGET SDL2_ttf) # transitively includes SDL2
  target_link_libraries(advance-save-edit PRIVATE PkgConfig::SDL2_TTF)
endif()
set(DEBUG OFF CACHE BOOL ON)
if (DEBUG) 
    add_definitions(-DDEBUG)
endif()
