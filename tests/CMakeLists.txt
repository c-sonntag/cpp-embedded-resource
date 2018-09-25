#
# UnitsTests project - Embedded Resource
# Under the Copyright (C) Christophe-Alexandre Sonntag (http://u4a.at)

# --- PROJECT ---
project(UnitsTests)
cmake_minimum_required(VERSION 3.2)

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
##
#

# --- PARENT LIB ---
include_directories(${PROJECT_EMBEDDEDRESOURCE_HEADER_PATH})
link_libraries(${PROJECT_EMBEDDEDRESOURCE})
link_libraries(${PROJECT_EMBEDDEDRESOURCE_MAKER})

# --- DIRECTORY DEF : TESTS ---
add_definitions("-D_TESTS_DIRECTORY_PATH=\"${CMAKE_CURRENT_LIST_DIR}\"")

#
##
#

# --- TARGETS PATH ---
set(SRC_PATH ".")
set(HEADER_PATH ".")

# --- COMPILE OPTIONS ---
include_directories(${HEADER_PATH})

#
## FIND_PACKAGE ERC (without installation)
#
include("EmbeddedResource")

#
## TESTS C++
#

set(TESTS_RES_DIR
  "relative_files/relative_files_resource.erc"
 # "relative_directory/relative_directory_resource.erc"
)

# --- BUILD TESTS STATIC LIB  ---
file(GLOB_RECURSE tests_static_files "tests_static/*.h" "tests_static/*.cpp")
add_library("tests_static" STATIC ${tests_static_files})
erc_add_resources("tests_static" ${TESTS_RES_DIR} "tests_static/source_info.erc")

# --- BUILD TESTS SHARED LIB  ---
file(GLOB_RECURSE tests_shared_files "tests_shared/*.h" "tests_shared/*.cpp")
add_library("tests_shared" SHARED ${tests_shared_files})
erc_add_resources("tests_shared" ${TESTS_RES_DIR} "tests_shared/source_info.erc")
if(GNU)
  target_compile_options("tests_shared" PRIVATE "-fPIC")
endif()


# --- BUILD TESTS PROGRAM ---
file(GLOB_RECURSE unitstest_program_files "unitstest_program/*.h" "unitstest_program/*.cpp")
add_executable("unitstest_program" ${unitstest_program_files})
LINK_PRIVATE_LIB_GTEST("unitstest_program")
#
target_link_libraries("unitstest_program" PRIVATE "tests_static")
target_link_libraries("unitstest_program" PRIVATE "tests_shared")
#
erc_add_resources("unitstest_program" ${TESTS_RES_DIR} "unitstest_program/source_info.erc")
