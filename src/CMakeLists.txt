add_executable(${PROJECT_NAME}
  main.cpp
  KeyboardInput.cpp
  )

target_link_libraries(${PROJECT_NAME}
  termkey
  ncurses
  boost_program_options
  boost_system
  boost_filesystem
  )
