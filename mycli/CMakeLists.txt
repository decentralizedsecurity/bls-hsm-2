#
# Copyright (c) 2021 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: Apache-2.0
#

cmake_minimum_required(VERSION 3.20)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

get_target_property(TFM_BINARY_DIR tfm TFM_BINARY_DIR)
configure_file(
  ${CMAKE_CURRENT_LIST_DIR}/../secure_partition/tfm_manifest_list.yaml.in
  ${CMAKE_CURRENT_BINARY_DIR}/secure_partition/tfm_manifest_list.yaml
)

set_property(TARGET zephyr_property_target
  APPEND PROPERTY TFM_CMAKE_OPTIONS
  -DTFM_EXTRA_MANIFEST_LIST_FILES=${CMAKE_CURRENT_BINARY_DIR}/secure_partition/tfm_manifest_list.yaml
  -DTFM_EXTRA_PARTITION_PATHS=${CMAKE_CURRENT_LIST_DIR}/../secure_partition
)

project(mycli)
add_definitions(-DNRF -DTFM)

target_sources(app PRIVATE
  src/main.c
  src/secure_partition_interface.c
  ../lib/bls_hsm_ns.c
  ../lib/common.c
)

zephyr_library_include_directories(
  ../lib/
)

#add_library(testlib STATIC IMPORTED)
#target_link_libraries(app PUBLIC ${APPLICATION_SOURCE_DIR}/../lib/libblst.a)

#add_library(mylib_lib STATIC IMPORTED GLOBAL)
#add_dependencies(
#  mylib_lib
#  mylib_project
#  )
#set_target_properties(mylib_lib PROPERTIES IMPORTED_LOCATION             ${APPLICATION_SOURCE_DIR}/../lib/libblst.a)
#set_target_properties(mylib_lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${APPLICATION_SOURCE_DIR}/../lib)

#target_link_libraries(app PUBLIC mylib_lib)

target_include_directories(app PRIVATE
  $<TARGET_PROPERTY:tfm,TFM_BINARY_DIR>/install/interface/include
)

target_compile_definitions(app
    PRIVATE TFM_PARTITION_DUMMY_PARTITION
)
