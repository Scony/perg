add_executable(${PROJECT_NAME}
  main.cpp
  )

add_library(${PROJECT_NAME}-tui
  KeyboardInput.cpp
  Ncurses.cpp
  )

add_library(${PROJECT_NAME}-model
  ApplicationModel.cpp
  )

add_library(${PROJECT_NAME}-presenter
  ApplicationController.cpp
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
  )
