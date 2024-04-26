# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(peripheral_hr)

target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE
  ${app_sources}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/r_enc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/bluetooth.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/imu.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rc_filter.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/bme.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/temp.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/hr.c
  )

zephyr_library_include_directories(${ZEPHYR_BASE}/samples/bluetooth)
