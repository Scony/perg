CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(perg)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

include_directories(
  libtermkey-0.20
)

add_executable(perg
  main.cpp
  ApplicationController.cpp
  FileController.cpp
  File.cpp
  Grep.cpp
  Minibuffer.cpp
  StatusBar.cpp
  TextBuffer.cpp
  StaticTextBuffer.cpp
  TextWindow.cpp
  Window.cpp
  Region.cpp
)

add_subdirectory(libtermkey-0.20)

target_link_libraries(perg ncurses pthread termkey)
