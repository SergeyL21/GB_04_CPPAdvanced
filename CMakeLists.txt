cmake_minimum_required(VERSION 3.1.0)

project(GB_CppAdvanced)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
  main.cpp
  test_module.cpp
  lesson_1.cpp
)

set(OTHER_FILES
  db.txt
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${OTHER_FILES})

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_CURRENT_SOURCE_DIR}/db.txt
                   $<TARGET_FILE_DIR:${PROJECT_NAME}>)
