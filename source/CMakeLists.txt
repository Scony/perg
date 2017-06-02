CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(perg)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

add_executable(perg
  main.cpp
  Controller.cpp
  File.cpp
  Grep.cpp
  Minibuffer.cpp
  StatusBar.cpp
  TextBuffer.cpp
  TextWindow.cpp
  Window.cpp
)

target_link_libraries(perg ncurses)