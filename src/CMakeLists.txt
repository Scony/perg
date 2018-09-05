add_executable(${PROJECT_NAME}
  main.cpp
  KeyboardInput.cpp
  )

target_link_libraries(${PROJECT_NAME}
  termkey
  ncurses
  )
