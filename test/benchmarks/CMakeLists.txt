include_directories(
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/3rdparty/google-benchmark/src
  )

add_executable(${PROJECT_NAME}-benchmark
  main.cpp
  )

target_link_libraries(${PROJECT_NAME}-benchmark
  benchmark
  pthread
  )

add_dependencies(${PROJECT_NAME}-benchmark
  benchmark
  )

add_custom_target(${PROJECT_NAME}-benchmark-run
  COMMAND ./${PROJECT_NAME}-benchmark
  DEPENDS ${PROJECT_NAME}-benchmark
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
  )
