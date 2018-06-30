#
# Tools project
# Under the Copyright (C) Christophe-Alexandre Sonntag (http://u4a.at)

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

## # --- SET CMAKE MODULES ---
## set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
## include("CMakeAutoSharedFilesCopier")

## # --- LIB : UNIXFAKE ---
## find_package(UNIXFAKE REQUIRED)
## include_directories(${UNIXFAKE_INCLUDE_DIRS})
## link_directories(${UNIXFAKE_DIRECTORIES})
## link_libraries(${UNIXFAKE_LIBRARIES})
## add_definitions(${UNIXFAKE_DEFINITIONS})
## copy_shared_on_rootbasebin_from_archive(${UNIXFAKE_ROOT} ${UNIXFAKE_LIBRARIES})


# --- PARENT LIB ---
include_directories(${PROJECT_SUBPROJECT_HEADER_PATH})
link_libraries(${PROJECT_SUBPROJECT_LINKING})

#
## TOOLS C++
#

file(GLOB files "*.c" "*.cpp")
foreach(FILE_PATH ${files} )

  #
  get_filename_component(EXECUTABLE_NAME ${FILE_PATH} NAME_WE)

  #
  set(EXTRA_SRC "${CMAKE_SOURCE_DIR}/${EXECUTABLE_NAME}")
  set(EXTRA_FILES "")
  set(WITH_EXTRA "")
  if(EXISTS "${EXTRA_SRC}")
    file(GLOB_RECURSE EXTRA_FILES "${EXTRA_SRC}/*.*")
    set(WITH_EXTRA "(extra)")
  endif()

  #
  message(STATUS "tools : ${EXECUTABLE_NAME} ${WITH_EXTRA}")
  add_executable(${EXECUTABLE_NAME} ${FILE_PATH} ${EXTRA_FILES})
  if(WITH_EXTRA)
    target_include_directories(${EXECUTABLE_NAME} PUBLIC ${EXTRA_SRC})
  endif()

  # --- INSTALL THIS TOOLS ---
  install(TARGETS ${EXECUTABLE_NAME}
          RUNTIME DESTINATION "bin")

endforeach()


# --- PRIVATE LIB for basic_zlib_compression_string ---
LINK_PRIVATE_LIB_ZLIB(basic_zlib_compression_string)



## LINK_PRIVATE_LIB_ZLIB    (${PROJECT_EMBEDDEDRESOURCE})
## LINK_PRIVATE_LIB_TINYXML2(${PROJECT_EMBEDDEDRESOURCE})




