cmake_minimum_required(VERSION 3.21) 
project(ChurchManager LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# ADDITIONAL LIBRARIES

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

find_package(xlnt)
if(NOT xlnt_FOUND)
  message("xlnt could not be located in the CMake module search path. Downloading it from Git and building it locally")
  include(FetchContent)
  FetchContent_Declare(
    xlnt
    GIT_REPOSITORY https://github.com/tfussell/xlnt.git
    GIT_TAG master
  )
FetchContent_MakeAvailable(xlnt)
endif()

find_package(libharu)
if(NOT libharu_FOUND)
  message("libharu could not be located in the CMake module search path. Downloading it from Git and building it locally")
  include(FetchContent)
  FetchContent_Declare(
    libharu
    GIT_REPOSITORY https://github.com/libharu/libharu.git
    GIT_TAG master
  )
FetchContent_MakeAvailable(libharu)
endif()

find_package(jsoncpp)
if(NOT jsoncpp_FOUND)
  message( "Jsoncpp could not be located in the cmake module search path. Downloading it from Git and building it locally" )
  include(FetchContent)
  FetchContent_Declare(
    jsoncpp
    GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
    GIT_TAG master
  )
  FetchContent_MakeAvailable(jsoncpp)
endif()


find_package(curl)
if(NOT curl_FOUND)
  message( "Curl could not be located in the cmake module search path. Downloading it from Git and building it locally" )
  include(FetchContent)
  FetchContent_Declare(
    curl
    GIT_REPOSITORY https://github.com/curl/curl.git
    GIT_TAG master
  )
  FetchContent_MakeAvailable(curl)
endif()



if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_executable(${CMAKE_PROJECT_NAME} src/main.cpp sqlite/sqlite3.obj)
else()
  add_executable(${CMAKE_PROJECT_NAME} src/main.cpp sqlite/sqlite3.o)
  set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}"
  )
endif()
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY SLINT_EMBED_RESOURCES embed-files)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/headers)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Slint::Slint)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE xlnt)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE hpdf)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE jsoncpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE libcurl)
slint_target_sources(${CMAKE_PROJECT_NAME} ui/app-window.slint)
# On Windows, copy the Slint DLL next to the application binary so that it's found.
if (WIN32)
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${CMAKE_PROJECT_NAME}> $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif()
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  message("Adding custom database copying command (Debug)")
  add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/databases/test.db  $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}> COMMAND_EXPAND_LISTS)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
  message("Adding custom database copying command (Release)")
  add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/databases/data.db $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif()

project(Tests LANGUAGES CXX)
add_subdirectory(tests)
