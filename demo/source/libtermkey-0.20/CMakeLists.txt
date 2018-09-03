CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(termkey)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

add_library(termkey
  termkey.c
  driver-csi.c
  driver-ti.c
)
