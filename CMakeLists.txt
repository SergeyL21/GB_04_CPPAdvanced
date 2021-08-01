cmake_minimum_required(VERSION 3.1.0)

project(GB_CppAdvanced)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

# включение сборки и тестирования с protobuf
set(CMAKE_ENABLE_PROTOBUF_SECTION OFF)
# включение сборки с google test
set(CMAKE_ENABLE_GOOGLE_TEST_SECTION ON)

set(SOURCE_FILES
  main.cpp
  test_module.cpp
  lesson_1.cpp
  lesson_2.cpp
  lesson_3.cpp
  lesson_4.cpp
  lesson_5.cpp
  lesson_6.cpp
  lesson_7.cpp
)

set(OTHER_FILES
  db.txt
  war_and_peace_pt1.txt
  protobuf/data.proto
)

set(LOCAL_INCLUDE_DIRS)
set(LOCAL_LINK_LIBS)

if (CMAKE_ENABLE_PROTOBUF_SECTION)
  add_definitions(-DENABLE_PROTOBUF_SECTION)
  list(APPEND SOURCE_FILES protobuf/data.pb.cc)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  list(APPEND LOCAL_INCLUDE_DIRS ${CONAN_INCLUDE_DIRS_PROTOBUF})
  list(APPEND LOCAL_LINK_LIBS ${CONAN_LIB_DIRS_PROTOBUF}/libprotobuf.lib)
endif()

if (CMAKE_ENABLE_GOOGLE_TEST_SECTION)
  add_definitions(-DENABLE_GOOGLE_TEST_SECTION)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  list(APPEND LOCAL_INCLUDE_DIRS ${CONAN_INCLUDE_DIRS_GTEST})
  list(APPEND LOCAL_LINK_LIBS ${CONAN_LIB_DIRS_GTEST}/gtest.lib)
endif()

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${OTHER_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${LOCAL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LINK_LIBS})

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_CURRENT_SOURCE_DIR}/db.txt
                   $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                  COMMAND ${CMAKE_COMMAND} -E copy
                  ${CMAKE_CURRENT_SOURCE_DIR}/war_and_peace_pt1.txt
                  $<TARGET_FILE_DIR:${PROJECT_NAME}>)
