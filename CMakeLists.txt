cmake_minimum_required(VERSION 3.21)

project(DinguxCommander
  VERSION 0.0.1
  LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ASAN "Enable address sanitizer" ON)
option(UBSAN "Enable undefined behaviour sanitizer" ON)

if(CMAKE_BUILD_TYPE MATCHES "Release")

  # Enable link-time optimization if supported.
  include(CheckIPOSupported)
  check_ipo_supported(RESULT ipo_supported OUTPUT ipo_check_output)
  if(ipo_supported)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
  else()
    message(WARNING "LTO is not supported: ${ipo_check_output}\n")
  endif()

  set(ASAN OFF)
  set(UBSAN OFF)
endif()

set(DinguxCommander_SRCS
  axis_direction.cpp
  commander.cpp
  config.cpp
  controller_buttons.cpp
  dialog.cpp
  fileLister.cpp
  fileutils.cpp
  keyboard.cpp
  main.cpp
  panel.cpp
  resourceManager.cpp
  screen.cpp
  sdl_ttf_multifont.cpp
  sdlutils.cpp
  text_edit.cpp
  utf8.cpp
  text_viewer.cpp
  image_viewer.cpp
  window.cpp
)

set(BIN_TARGET commander)
add_executable(${BIN_TARGET} ${DinguxCommander_SRCS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2_image REQUIRED IMPORTED_TARGET SDL2_image)
pkg_check_modules(SDL2_ttf REQUIRED IMPORTED_TARGET SDL2_ttf)
pkg_check_modules(SDL2_gfx REQUIRED IMPORTED_TARGET SDL2_gfx)
pkg_check_modules(fontconfig REQUIRED IMPORTED_TARGET fontconfig)

target_link_libraries(${BIN_TARGET} PRIVATE
  PkgConfig::SDL2
  PkgConfig::SDL2_image
  PkgConfig::SDL2_ttf
  PkgConfig::SDL2_gfx
  PkgConfig::fontconfig
  m
)

set_target_properties(${BIN_TARGET} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

if(ASAN)
  target_compile_options(${BIN_TARGET} PUBLIC -fsanitize=address -fsanitize-recover=address)
  target_link_libraries(${BIN_TARGET} PUBLIC -fsanitize=address -fsanitize-recover=address)
endif()

if(UBSAN)
  target_compile_options(${BIN_TARGET} PUBLIC -fsanitize=undefined)
  target_link_libraries(${BIN_TARGET} PUBLIC -fsanitize=undefined)
endif()

install(
  TARGETS ${BIN_TARGET}
  RUNTIME DESTINATION bin)
install(
  DIRECTORY "${PROJECT_SOURCE_DIR}/res"
  DESTINATION share/commander
  FILES_MATCHING PATTERN "*.png")
