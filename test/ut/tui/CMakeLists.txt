add_executable(${PROJECT_NAME}-tui-ut
  $<TARGET_OBJECTS:gtest>
  )

target_link_libraries(${PROJECT_NAME}-tui-ut
  ${PROJECT_NAME}-tui
  pthread
  )

target_include_directories(${PROJECT_NAME}-tui-ut
  PRIVATE
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/3rdparty/gtest
  )

add_test(NAME ${PROJECT_NAME}-tui-ut
  COMMAND ./${PROJECT_NAME}-tui-ut
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
  )
