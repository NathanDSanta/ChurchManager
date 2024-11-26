cmake_minimum_required(VERSION 3.21)
project(ChurchManager LANGUAGES CXX)

find_package(Slint QUIET)
if (NOT Slint_FOUND)
  message("Slint could not be located in the CMake module search path. Downloading it from Git and building it locally")
  include(FetchContent)
  FetchContent_Declare(
    Slint
    GIT_REPOSITORY https://github.com/slint-ui/slint.git
    # `release/1` will auto-upgrade to the latest Slint >= 1.0.0 and < 2.0.0
    # `release/1.0` will auto-upgrade to the latest Slint >= 1.0.0 and < 1.1.0
    GIT_TAG release/1
    SOURCE_SUBDIR api/cpp
  )
  FetchContent_MakeAvailable(Slint)
endif (NOT Slint_FOUND)

include_directories(sqlite)
add_library(sqlite3 STATIC sqlite/sqlite3.c sqlite/sqlite3.h)
set_target_properties(sqlite3 PROPERTIES LINKER_LANGUAGE C)

add_executable(ChurchManager src/main.cpp)
target_link_libraries(ChurchManager PRIVATE Slint::Slint sqlite3)
slint_target_sources(ChurchManager ui/app-window.slint)
# On Windows, copy the Slint DLL next to the application binary so that it's found.
if (WIN32)
    add_custom_command(TARGET ChurchManager POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:ChurchManager> $<TARGET_FILE_DIR:ChurchManager> COMMAND_EXPAND_LISTS)
endif()
