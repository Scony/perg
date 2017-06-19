CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(perg)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

include_directories(
  libtermkey-0.20
)

add_subdirectory(libtermkey-0.20)

add_library(perg-library
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
  Termkey.cpp
  Event.cpp
)

add_executable(perg
  main.cpp
)

target_link_libraries(perg-library ncurses pthread termkey)
target_link_libraries(perg perg-library)

add_dependencies(perg perg-library)
