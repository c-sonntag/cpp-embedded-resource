#
# EmbeddedResource project - externals builds
# Under the Copyright (C) Christophe-Alexandre Sonntag (http://u4a.at)

# --- EXTERNAL SETS ---
set(EXTERNAL_ZLIB_DIR       "zlib-master")
set(EXTERNAL_TINYXML2_DIR   "tinyxml2-master-6.2.0")
set(EXTERNAL_GTEST_DIR      "googletest-master")
set(EXTERNAL_PICOSHA2_DIR   "picosha2-master")

#
##
#

# --- EXTERNAL : ZLIB ---
set(ZLIB_SOURCE  "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_ZLIB_DIR}")
set(ZLIB_BUILD   "${CMAKE_CURRENT_BINARY_DIR}/zlib")
set(PROJECT_ZLIB_STATIC zlibstatic)
#
add_subdirectory(${ZLIB_SOURCE} ${ZLIB_BUILD})
#
macro(LINK_PRIVATE_LIB_ZLIB PROJECT_TARGET)
  target_include_directories(${PROJECT_TARGET} PRIVATE ${ZLIB_SOURCE})
  target_include_directories(${PROJECT_TARGET} PRIVATE ${ZLIB_BUILD})
  target_link_libraries     (${PROJECT_TARGET} PRIVATE ${PROJECT_ZLIB_STATIC})
endmacro()
#
set(ZLIB_SOURCE          ${ZLIB_SOURCE}         PARENT_SCOPE)
set(ZLIB_BUILD           ${ZLIB_BUILD}          PARENT_SCOPE)
set(PROJECT_ZLIB_STATIC  ${PROJECT_ZLIB_STATIC} PARENT_SCOPE)

#
##
#

# --- EXTERNAL : TINYXML2 ---
set(TINYXML2_SOURCE  "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_TINYXML2_DIR}")
set(TINYXML2_BUILD   "${CMAKE_CURRENT_BINARY_DIR}/tinyxml2")
set(PROJECT_TINYXML2_STATIC tinyxml2_static)
#
set(BUILD_SHARED_LIBS OFF)
set(BUILD_STATIC_LIBS ON)
set(BUILD_TESTS OFF)
add_subdirectory(${TINYXML2_SOURCE} ${TINYXML2_BUILD})
#
macro(LINK_PRIVATE_LIB_TINYXML2 PROJECT_TARGET)
  target_include_directories(${PROJECT_TARGET} PRIVATE ${TINYXML2_SOURCE})
  target_link_libraries     (${PROJECT_TARGET} PRIVATE ${PROJECT_TINYXML2_STATIC})
endmacro()
#
set(TINYXML2_SOURCE          ${TINYXML2_SOURCE}         PARENT_SCOPE)
set(TINYXML2_BUILD           ${TINYXML2_BUILD}          PARENT_SCOPE)
set(PROJECT_TINYXML2_STATIC  ${PROJECT_TINYXML2_STATIC} PARENT_SCOPE)

#
##
#

# --- EXTERNAL : GTEST ---
set(GTEST_SOURCE  "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_GTEST_DIR}")
set(GTEST_BUILD   "${CMAKE_CURRENT_BINARY_DIR}/gtest")
set(PROJECT_GTEST_STATIC      gtest)
#
set(BUILD_GMOCK OFF)
set(BUILD_GTEST ON)
set(INSTALL_GTEST OFF)
set(INSTALL_GMOCK OFF)
set(BUILD_SHARED_LIBS OFF)
set(gtest_build_tests OFF)
set(gtest_build_samples OFF)
set(gtest_disable_pthreads OFF)
set(gtest_hide_internal_symbols OFF)
add_subdirectory(${GTEST_SOURCE} ${GTEST_BUILD})
#
macro(LINK_PRIVATE_LIB_GTEST PROJECT_TARGET)
  target_include_directories(${PROJECT_TARGET} PRIVATE "${GTEST_SOURCE}/googletest/include")
  target_link_libraries     (${PROJECT_TARGET} PRIVATE ${PROJECT_GTEST_STATIC})
endmacro()
#
set(GTEST_SOURCE               ${GTEST_SOURCE}              PARENT_SCOPE)
set(GTEST_BUILD                ${GTEST_BUILD}               PARENT_SCOPE)
set(PROJECT_GTEST_STATIC       ${PROJECT_GTEST_STATIC}      PARENT_SCOPE)

#
##
#

# --- EXTERNAL : PICOSHA2 ---
set(PICOSHA2_SOURCE  "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PICOSHA2_DIR}")
#
macro(LINK_PRIVATE_LIB_PICOSHA2 PROJECT_TARGET)
  target_include_directories(${PROJECT_TARGET} PRIVATE "${PICOSHA2_SOURCE}")
endmacro()
#
set(PICOSHA2_SOURCE               ${PICOSHA2_SOURCE}              PARENT_SCOPE)



