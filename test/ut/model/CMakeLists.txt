add_executable(${PROJECT_NAME}-model-ut
  $<TARGET_OBJECTS:gtest>
  )

target_link_libraries(${PROJECT_NAME}-model-ut
  ${PROJECT_NAME}-model
  pthread
  )

target_include_directories(${PROJECT_NAME}-model-ut
  PRIVATE
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/3rdparty/gtest
  )

add_test(NAME ${PROJECT_NAME}-model-ut
  COMMAND ./${PROJECT_NAME}-model-ut
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
  )
