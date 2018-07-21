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

# --- DIRECTORY DEF : TESTS ---
add_definitions("-D_TESTS_DIRECTORY_PATH=\"${CMAKE_CURRENT_LIST_DIR}\"")

#
##
#

# --- TARGETS PATH ---
set(SRC_PATH ".")
set(HEADER_PATH ".")

# --- TARGETS FILES ---
file(GLOB_RECURSE TARGET_SRC_FILES "${SRC_PATH}/*.cpp" "${SRC_PATH}/*.c")
file(GLOB_RECURSE TARGET_HEADER_FILES "${HEADER_PATH}/*.h" "${HEADER_PATH}/*.hpp")

# --- COMPILE OPTIONS ---
include_directories(${HEADER_PATH})

#
## TESTS C++
#

# --- BUILD TESTS PROGRAM ---
add_executable(${PROJECT_NAME} ${TARGET_SRC_FILES} ${TARGET_HEADER_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
LINK_PRIVATE_LIB_GTEST(${PROJECT_NAME})

# --- INSTALL TESTS PROGRAM ---
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "bin")

