CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(perg-test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

include_directories(../source)

add_executable(perg-test
  main.cpp
  TextBufferTest.cpp
  ../source/TextBuffer.cpp
)

target_link_libraries(perg-test gtest gtest_main)
