add_executable(${PROJECT_NAME}
  main.cpp
  )

add_library(${PROJECT_NAME}-tui
  STATIC
  KeyboardInput.cpp
  Ncurses.cpp
  NcursesWindow.cpp
  StatusBar.cpp
  Minibuffer.cpp
  TextWindow.cpp
  )

add_library(${PROJECT_NAME}-model
  STATIC
  ApplicationModel.cpp
  FileModel.cpp
  FileReader.cpp
  IWorker.cpp
  GrepModel.cpp
  GrepProcessor.cpp
  )

add_library(${PROJECT_NAME}-presenter
  STATIC
  ApplicationController.cpp
  FileController.cpp
  TextWindowController.cpp
  )

add_library(${PROJECT_NAME}-types
  STATIC
  types/TextView.cpp
  )

target_link_libraries(${PROJECT_NAME}
  ${PROJECT_NAME}-tui
  ${PROJECT_NAME}-model
  ${PROJECT_NAME}-presenter
  ncurses
  boost_program_options
  boost_system
  boost_filesystem
  )

target_link_libraries(${PROJECT_NAME}-tui
  termkey
  ${PROJECT_NAME}-types
  )

target_link_libraries(${PROJECT_NAME}-presenter
  ${PROJECT_NAME}-types
  ${PROJECT_NAME}-tui
  )

target_include_directories(${PROJECT_NAME}-types
  INTERFACE
  types/
  )

target_link_libraries(${PROJECT_NAME}-model
  pthread
  )
