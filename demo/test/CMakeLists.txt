CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

find_package(GTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
set(PERG_SOURCE_DIR ${CMAKE_SOURCE_DIR}/source)

include_directories(${GTEST_INCLUDE_DIR})
include_directories(${PERG_SOURCE_DIR})

link_directories(${PERG_SOURCE_DIR})

add_executable(perg-test
  main.cpp
  TextBufferTest.cpp
  GrepTest.cpp
)

target_link_libraries(perg-test perg-library ${GTEST_BOTH_LIBRARIES} pthread)

add_test(NAME perg-test COMMAND perg-test)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose
                  DEPENDS perg-test)
