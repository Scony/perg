add_executable(${PROJECT_NAME}
  main.cpp
  )

add_library(${PROJECT_NAME}-tui
  KeyboardInput.cpp
  Ncurses.cpp
  )

target_link_libraries(${PROJECT_NAME}
  ${PROJECT_NAME}-tui
  ncurses
  boost_program_options
  boost_system
  boost_filesystem
  )

target_link_libraries(${PROJECT_NAME}-tui
  termkey
  )
