#
# EmbeddedResource project
# Under the Copyright (C) Christophe-Alexandre Sonntag (http://u4a.at)

# --- PROJECT ---
project(EmbeddedResource)
cmake_minimum_required(VERSION 3.2)
#
set(EMBEDDEDRESOURCE_VERSION_MAJOR 1)
set(EMBEDDEDRESOURCE_VERSION_MINOR 0)

set(PROJECT_EMBEDDEDRESOURCE "erc")
set(PROJECT_EMBEDDEDRESOURCE_MAKER "erc_maker")
set(PROJECT_EMBEDDEDRESOURCE_PROGRAM "embedded_resource_packager")

# --- EXTERNALS LIBS ---
include("external/CMakeLists.txt")

# --- SET CMAKE TOOLS ---
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMakeTools;${CMAKE_MODULE_PATH}")

#
##
#

# --- SET CMAKE MODULES ---
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")

#
## ERC LIB
#

# --- TARGETS PATH ---
set(SRC_PATH "src")
set(HEADER_PATH "include")

# --- COMPILE OPTIONS ---
include_directories(${HEADER_PATH})

#
##
#

# --- INSTALL OPTIONS  ---
set(EMBEDDEDRESOURCE_INSTALL_ERC_MAKER OFF CACHE BOOL "Install erc_maker of EmbeddedResource library")

# --- BUILD OPTIONS  ---
set(EMBEDDEDRESOURCE_BUILD_TESTS ON CACHE BOOL "Build tests for EmbeddedResource library (need second cmake/make compile time)")

#
##
#

# --- PROFILE ENVIRONNEMENT ---
if(CMAKE_COMPILER_IS_GNUCXX)                ## (GNU COMMAND)
  add_definitions("-Wall" "-pedantic")        # Toutes erreurs
  if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")   ## (not debug)
    add_compile_options("-fno-builtin")         ## Break __buildin function (so slowest)
    add_compile_options("-O3")                  ### Optimize
    set(CMAKE_EXE_LINKER_FLAGS "-s")            ### Strip binary (no work on debug)
  endif()
endif()

set(CMAKE_CXX_STANDARD 14)


#
## Independant
#

# --- INSTALL CMakeTools ---
install(DIRECTORY "CMakeTools/." DESTINATION "CMakeTools")

# --- INSTALL LIB DEPENDENCIES ---
INSTALL_LIB_ZLIB_INTERNAL_DEPENDENCIES()

#
## ERC LIB
#

# --- TARGETS FILES ---
file(GLOB_RECURSE TARGET_EMBEDDEDRESOURCE_SRC_FILES "${SRC_PATH}/erc/*.cpp" "${SRC_PATH}/erc/*.c")
file(GLOB_RECURSE TARGET_EMBEDDEDRESOURCE_HEADER_FILES "${HEADER_PATH}/erc/*.h" "${HEADER_PATH}/erc/*.hpp")

# --- BUILDS LIB TARGET STATIC ---
add_library(${PROJECT_EMBEDDEDRESOURCE} STATIC ${TARGET_EMBEDDEDRESOURCE_SRC_FILES} ${TARGET_EMBEDDEDRESOURCE_HEADER_FILES})
#add_library(${PROJECT_EMBEDDEDRESOURCE} SHARED ${TARGET_EMBEDDEDRESOURCE_SRC_FILES} ${TARGET_EMBEDDEDRESOURCE_HEADER_FILES})

## # --- NEXT LIBS ARE IMPLANTED ---
## LINK_DO_WHOLE_ARCHIVE   (${PROJECT_EMBEDDEDRESOURCE})

# --- PRIVATES LIBS ---
LINK_PRIVATE_LIB_ZLIB    (${PROJECT_EMBEDDEDRESOURCE})

# --- INSTALL LIB ---
install(
  TARGETS ${PROJECT_EMBEDDEDRESOURCE}
  LIBRARY DESTINATION "lib"
  ARCHIVE DESTINATION "lib"
  RUNTIME DESTINATION "bin"
)

# --- INSTALL INCLUDE ---
install(DIRECTORY "${HEADER_PATH}/erc/." DESTINATION "include/erc")

#
## ERC_MAKER LIB
#

# --- TARGETS FILES ---
file(GLOB_RECURSE TARGET_EMBEDDEDRESOURCE_MAKER_SRC_FILES "${SRC_PATH}/erc_maker/*.cpp" "${SRC_PATH}/erc_maker/*.c")
file(GLOB_RECURSE TARGET_EMBEDDEDRESOURCE_MAKER_HEADER_FILES "${HEADER_PATH}/erc_maker/*.h" "${HEADER_PATH}/erc_maker/*.hpp")

# --- BUILDS LIB TARGET STATIC ---
add_library(${PROJECT_EMBEDDEDRESOURCE_MAKER} STATIC ${TARGET_EMBEDDEDRESOURCE_MAKER_SRC_FILES} ${TARGET_EMBEDDEDRESOURCE_MAKER_HEADER_FILES})

# --- LIB : ERC ---
target_link_libraries(${PROJECT_EMBEDDEDRESOURCE_MAKER} PRIVATE ${PROJECT_EMBEDDEDRESOURCE})

# --- LIB : STD-FILESYSTEM ---
if(CMAKE_COMPILER_IS_GNUCXX)
  target_link_libraries(${PROJECT_EMBEDDEDRESOURCE_MAKER} PRIVATE "-lstdc++fs")
else()
  message(WARNING "TODO FIX IT : Unknown linker Filesystem lib support")
endif()

## # --- NEXT LIBS ARE IMPLANTED ---
## LINK_DO_WHOLE_ARCHIVE   (${PROJECT_EMBEDDEDRESOURCE_MAKER})

# --- PRIVATES LIBS ---
LINK_PRIVATE_LIB_TINYXML2(${PROJECT_EMBEDDEDRESOURCE_MAKER})
LINK_PRIVATE_LIB_PICOSHA2(${PROJECT_EMBEDDEDRESOURCE_MAKER})

# --- INSTALL ERC_MAKER ? ---
if(${EMBEDDEDRESOURCE_INSTALL_ERC_MAKER})

  # --- INSTALL LIB ---
  install(
    TARGETS ${PROJECT_EMBEDDEDRESOURCE_MAKER}
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
   )

  # --- INSTALL INCLUDE ---
  install(DIRECTORY "${HEADER_PATH}/erc_maker/." DESTINATION "include/erc_maker")

endif()

#
## EMBEDDED_RESOURCE_PACKAGER PROGRAM
#

# --- TARGETS FILES ---
file(GLOB_RECURSE TARGET_EMBEDDEDRESOURCE_PROGRAM_SRC_FILES "${SRC_PATH}/embedded_resource_packager/*.cpp" "${SRC_PATH}/embedded_resource_packager/*.c")
file(GLOB_RECURSE TARGET_EMBEDDEDRESOURCE_PROGRAM_HEADER_FILES "${SRC_PATH}/embedded_resource_packager/*.h" "${SRC_PATH}/embedded_resource_packager/*.hpp")

# --- BUILDS LIB TARGET STATIC ---
add_executable(${PROJECT_EMBEDDEDRESOURCE_PROGRAM} ${TARGET_EMBEDDEDRESOURCE_PROGRAM_SRC_FILES} ${TARGET_EMBEDDEDRESOURCE_PROGRAM_HEADER_FILES})

# --- PRIVATES LIBS ---
target_link_libraries(${PROJECT_EMBEDDEDRESOURCE_PROGRAM} PRIVATE ${PROJECT_EMBEDDEDRESOURCE})
target_link_libraries(${PROJECT_EMBEDDEDRESOURCE_PROGRAM} PRIVATE ${PROJECT_EMBEDDEDRESOURCE_MAKER})

# --- INSTALL PROGRAM ---
install(TARGETS ${PROJECT_EMBEDDEDRESOURCE_PROGRAM} RUNTIME DESTINATION "bin")


#
## For subproject like tests
#

set(PROJECT_EMBEDDEDRESOURCE_HEADER_PATH "${CMAKE_CURRENT_LIST_DIR}/${HEADER_PATH}")

find_program(
  ERC_BINARY_PACKAGER
  NAMES ${PROJECT_EMBEDDEDRESOURCE_PROGRAM}
  PATHS ${CMAKE_CURRENT_BINARY_DIR}
)

#
##
#


# --- BUILDS TESTS ---
if(${EMBEDDEDRESOURCE_BUILD_TESTS} AND EXISTS ${ERC_BINARY_PACKAGER})
  add_subdirectory("tests/")
endif()

