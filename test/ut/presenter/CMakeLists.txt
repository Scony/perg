add_executable(${PROJECT_NAME}-presenter-ut
  $<TARGET_OBJECTS:gtest>
  )

target_link_libraries(${PROJECT_NAME}-presenter-ut
  ${PROJECT_NAME}-presenter
  pthread
  )

target_include_directories(${PROJECT_NAME}-presenter-ut
  PRIVATE
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/3rdparty/gtest
  )

add_test(NAME ${PROJECT_NAME}-presenter-ut
  COMMAND ./${PROJECT_NAME}-presenter-ut
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
  )
