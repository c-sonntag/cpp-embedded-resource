#
# EmbeddedResource project
# Under the Copyright (C) Christophe-Alexandre Sonntag (http://u4a.at)

#
##
set(ERC_POSSIBLE_PATH
  "${ERC_ROOT}"
  "${ERC_SUFFIX}"
  "${CMAKE_SOURCE_DIR}/external/erc"
  "${CMAKE_SOURCE_DIR}/thirdparty/erc"
  "${CMAKE_SOURCE_DIR}/third-party/erc"
)

#
##
find_path(
  ERC_INCLUDE_DIRS
  NAMES "erc/file.h"
  PATHS ${ERC_POSSIBLE_PATH}
  PATH_SUFFIXES "include/"
)
set(ERC_INCLUDE_DIR ${ERC_INCLUDE_DIRS})

#
##
set(ERC_LIBRARIES_NAME "liberc")


#
##
find_library(
  ERC_LIBRARIES
  NAMES
    "${ERC_LIBRARIES_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX}"
  PATHS ${ERC_POSSIBLE_PATH}
  PATH_SUFFIXES "lib/"
)

#
##
find_program(
  ERC_BINARY_PACKAGER
  NAMES "embedded_resource_packager"
  PATHS ${ERC_POSSIBLE_PATH}
  PATH_SUFFIXES "bin/"
)

#
##
find_path(
  ERC_CMAKE_TOOLS_DIRS
  NAMES "EmbeddedResource.cmake"
  PATHS ${ERC_POSSIBLE_PATH}
  PATH_SUFFIXES "CMakeTools/"
)


#
##
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ERC REQUIRED_VARS ERC_INCLUDE_DIRS ERC_LIBRARIES ERC_BINARY_PACKAGER ERC_CMAKE_TOOLS_DIRS)

#
##
include(${ERC_CMAKE_TOOLS_DIRS})

#
##
set(EmbeddedResource_INCLUDE_DIR           ${ERC_INCLUDE_DIR})
set(EmbeddedResource_INCLUDE_DIRS          ${ERC_INCLUDE_DIRS})
set(EmbeddedResource_DIRECTORIES           ${ERC_DIRECTORIES})
set(EmbeddedResource_LIBRARIES             ${ERC_LIBRARIES})
set(EmbeddedResource_DEFINITIONS           ${ERC_DEFINITIONS})
set(EmbeddedResource_BINARY_PACKAGER       ${ERC_BINARY_PACKAGER})
set(EmbeddedResource_ERC_CMAKE_TOOLS_DIRS  ${ERC_CMAKE_TOOLS_DIRS})

