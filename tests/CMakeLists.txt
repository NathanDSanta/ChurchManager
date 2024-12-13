
message(STATUS "Current project name is ${CMAKE_PROJECT_NAME}")

set( SRC_FILES
  ${CMAKE_SOURCE_DIR}/tests/cppReadTest/main.cpp
  ${CMAKE_SOURCE_DIR}/tests/cppReadTest/Database.cpp
  ${CMAKE_SOURCE_DIR}/tests/cppReadTest/Error.cpp
  ${CMAKE_SOURCE_DIR}/tests/cppReadTest/ErrorHandler.cpp
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tests/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tests/bin)

if(WIN32)
  add_executable(cppReadTest ${SRC_FILES} ${CMAKE_SOURCE_DIR}/sqlite/sqlite3.obj)
  add_executable(sqliteTest ${CMAKE_SOURCE_DIR}/tests/sqlite_test/main.cpp ${CMAKE_SOURCE_DIR}/sqlite/sqlite3.obj)
else()
  add_executable(cppReadTest ${SRC_FILES} ${CMAKE_SOURCE_DIR}/sqlite/sqlite3.o)
  add_executable(sqliteTest ${CMAKE_SOURCE_DIR}/tests/sqlite_test/main.cpp ${CMAKE_SOURCE_DIR}/sqlite/sqlite3.o)
endif()
add_executable(excelReadTest ${CMAKE_SOURCE_DIR}/tests/excelReading/main.cpp)

target_link_libraries(cppReadTest PRIVATE Slint::Slint)
target_link_libraries(excelReadTest PRIVATE xlnt)
target_include_directories(cppReadTest PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/headers)
target_include_directories(sqliteTest PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/headers)
add_custom_command(TARGET cppReadTest POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/databases/test.db  $<TARGET_FILE_DIR:cppReadTest> COMMAND_EXPAND_LISTS)
add_custom_command(TARGET excelReadTest POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/tests/excelReading/test.xlsx  $<TARGET_FILE_DIR:excelReadTest> COMMAND_EXPAND_LISTS)
if (WIN32)
    add_custom_command(TARGET excelReadTest POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${CMAKE_PROJECT_NAME}> $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif()
