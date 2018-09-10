add_executable(${PROJECT_NAME}
  main.cpp
  )

add_library(${PROJECT_NAME}-tui
  KeyboardInput.cpp
  Ncurses.cpp
  NcursesWindow.cpp
  StatusBar.cpp
  Minibuffer.cpp
  )

add_library(${PROJECT_NAME}-model
  ApplicationModel.cpp
  FileModel.cpp
  )

add_library(${PROJECT_NAME}-presenter
  ApplicationController.cpp
  )

add_library(${PROJECT_NAME}-types
  INTERFACE
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
