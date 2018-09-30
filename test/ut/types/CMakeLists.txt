add_executable(${PROJECT_NAME}-types-ut
  $<TARGET_OBJECTS:gtest>
  RegionTests.cpp
  TextViewTests.cpp
  )

target_link_libraries(${PROJECT_NAME}-types-ut
  ${PROJECT_NAME}-types
  pthread
  )

target_include_directories(${PROJECT_NAME}-types-ut
  PRIVATE
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/3rdparty/gtest
  )

add_test(NAME ${PROJECT_NAME}-types-ut
  COMMAND ./${PROJECT_NAME}-types-ut
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
  )
