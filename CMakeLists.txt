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

# --- EXTERNALS LIBS ---
add_subdirectory("external")

#
##
#


# --- SET CMAKE MODULES ---
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")

## # --- LIB : UNIXFAKE ---
## find_package(UNIXFAKE REQUIRED)
## include_directories(${UNIXFAKE_INCLUDE_DIRS})
## link_directories(${UNIXFAKE_DIRECTORIES})
## link_libraries(${UNIXFAKE_LIBRARIES})
## add_definitions(${UNIXFAKE_DEFINITIONS})
## copy_shared_on_rootbasebin_from_archive(${UNIXFAKE_ROOT} ${UNIXFAKE_LIBRARIES})

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

# --- BUILD OPTIONS  ---
SET(EMBEDDEDRESOURCE_BUILD_TOOLS ON CACHE BOOL "Build tools for EmbeddedResource library")
SET(EMBEDDEDRESOURCE_BUILD_EXAMPLES ON CACHE BOOL "Build examples for EmbeddedResource library")
SET(EMBEDDEDRESOURCE_BUILD_TESTS ON CACHE BOOL "Build tests for EmbeddedResource library")

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
## ERC LIB
#

# --- TARGETS FILES ---
file(GLOB_RECURSE TARGET_EMBEDDEDRESOURCE_SRC_FILES "${SRC_PATH}/erc/*.cpp" "${SRC_PATH}/erc/*.c")
file(GLOB_RECURSE TARGET_EMBEDDEDRESOURCE_HEADER_FILES "${HEADER_PATH}/erc/*.h" "${HEADER_PATH}/erc/*.hpp")

# --- BUILDS LIB TARGET STATIC ---
add_library(${PROJECT_EMBEDDEDRESOURCE} STATIC ${TARGET_EMBEDDEDRESOURCE_SRC_FILES} ${TARGET_EMBEDDEDRESOURCE_HEADER_FILES})

# --- PRIVATES LIBS ---
LINK_PRIVATE_LIB_ZLIB    (${PROJECT_EMBEDDEDRESOURCE})

# --- INSTALL LIB ---
install(TARGETS ${PROJECT_EMBEDDEDRESOURCE}
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib")

# --- INSTALL INCLUDE ---
install(DIRECTORY "${HEADER_PATH}/." DESTINATION "include")


#
## ERC_MAKER LIB
#

# --- TARGETS FILES ---
file(GLOB_RECURSE TARGET_EMBEDDEDRESOURCE_MAKER_SRC_FILES "${SRC_PATH}/erc_maker/*.cpp" "${SRC_PATH}/erc_maker/*.c")
file(GLOB_RECURSE TARGET_EMBEDDEDRESOURCE_MAKER_HEADER_FILES "${HEADER_PATH}/erc_maker/*.h" "${HEADER_PATH}/erc_maker/*.hpp")

# --- BUILDS LIB TARGET STATIC ---
add_library(${PROJECT_EMBEDDEDRESOURCE_MAKER} STATIC ${TARGET_EMBEDDEDRESOURCE_MAKER_SRC_FILES} ${TARGET_EMBEDDEDRESOURCE_MAKER_HEADER_FILES})

# --- PRIVATES LIBS ---
LINK_PRIVATE_LIB_ZLIB    (${PROJECT_EMBEDDEDRESOURCE_MAKER})
LINK_PRIVATE_LIB_TINYXML2(${PROJECT_EMBEDDEDRESOURCE_MAKER})
LINK_PRIVATE_LIB_PICOSHA2(${PROJECT_EMBEDDEDRESOURCE_MAKER})

# --- LIB : STD-FILESYSTEM ---
if(CMAKE_COMPILER_IS_GNUCXX)
  target_link_libraries(${PROJECT_EMBEDDEDRESOURCE} PRIVATE "-lstdc++fs")
else()
  message(WARNING "TODO FIX IT : Unknown linker Filesystem lib support")
endif()

# --- INSTALL LIB ---
install(TARGETS ${PROJECT_EMBEDDEDRESOURCE_MAKER}
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib")

# --- INSTALL INCLUDE ---
install(DIRECTORY "${HEADER_PATH}/." DESTINATION "include")



#
##
#

set(PROJECT_EMBEDDEDRESOURCE_HEADER_PATH "${CMAKE_CURRENT_LIST_DIR}/${HEADER_PATH}")

#
##
#

# --- BUILDS TOOLS ---
if(${EMBEDDEDRESOURCE_BUILD_TOOLS})
  add_subdirectory("tools/")
endif()

# # --- BUILDS EXAMPLES ---
# if(${EMBEDDEDRESOURCE_BUILD_EXAMPLES})
#  add_subdirectory("examples/")
# endif()

# --- BUILDS TESTS ---
if(${EMBEDDEDRESOURCE_BUILD_TESTS})
  add_subdirectory("tests/")
endif()

