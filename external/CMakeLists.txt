#
# EmbeddedResource project - externals builds
# Under the Copyright (C) Christophe-Alexandre Sonntag (http://u4a.at)


# ---  ---
include (ExternalProject)
set(EXTERNAL_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external")


# --- EXTERNAL SETS ---
set(EXTERNAL_ZLIB_DIR       "zlib-master")
set(EXTERNAL_TINYXML2_DIR   "tinyxml2-master-6.2.0")
set(EXTERNAL_GTEST_DIR      "googletest-master")
set(EXTERNAL_PICOSHA2_DIR   "picosha2-master")

#
##
#

## macro(LINK_DO_WHOLE_ARCHIVE target)
##   if(MSVC)
##     set(flags "/WHOLEARCHIVE")
##   elseif (APPLE)
##     set(flags "-Wl,-all_load")
##   elseif(CMAKE_COMPILER_IS_GNUCXX)
##     set(flags "-Wl,--whole-archive")
##   else()
##     message(FATAL_ERROR "[LINK_SET_WHOLE_ARCHIVE] Can't know compiler flag")
##   endif()
##   #
##   set_target_properties(${target} PROPERTIES LINK_FLAGS ${flags})
## endmacro()

#
##
#

# --- EXTERNAL : ZLIB ---
set(ZLIB_SOURCE             "${EXTERNAL_SOURCE_DIR}/${EXTERNAL_ZLIB_DIR}")
set(ZLIB_PREFIX              "external/zlib")
set(ZLIB_BUILD               "${CMAKE_CURRENT_BINARY_DIR}/${ZLIB_PREFIX}/build")
set(ZLIB_INSTALL             "${CMAKE_CURRENT_BINARY_DIR}/${ZLIB_PREFIX}/install")
#set(ZLIB_INSTALL            "${CMAKE_INSTALL_PREFIX}/internal/zlib")
##set(PROJECT_ZLIB_SHARED     "${ZLIB_BUILD}/libzlib.dll.a")    # todo for other system
##set(PROJECT_ZLIB_SHARED_DEP "${ZLIB_BUILD}/libzlib.dll")

if(MINGW)
  set(PROJECT_ZLIB_STATIC     "${ZLIB_BUILD}/libzlibstatic.a")
elseif(MSVC)
  set(PROJECT_ZLIB_STATIC     "${ZLIB_BUILD}/zlibstatic.lib")
elseif(GNU)
  set(PROJECT_ZLIB_STATIC     "${ZLIB_BUILD}/libz.a")
else()
  message(FATAL_ERROR "Can't get the Static Zlib for link later")
endif()

#
ExternalProject_Add(
  zlib
  PREFIX ${ZLIB_PREFIX}
  SOURCE_DIR ${ZLIB_SOURCE}
  BINARY_DIR ${ZLIB_BUILD}
  INSTALL_DIR ${ZLIB_INSTALL}
  BUILD_IN_SOURCE OFF
  BUILD_BYPRODUCTS ${PROJECT_ZLIB_STATIC}
  #STEP_TARGETS build
  EXCLUDE_FROM_ALL TRUE
  CMAKE_CACHE_ARGS
    -DCMAKE_BUILD_TYPE:STRIFNG=Release
    -DCMAKE_INSTALL_PREFIX:STRING=${ZLIB_INSTALL}
)
#
##set(ZLIB_SOURCES  "${EXTERNAL_SOURCE_DIR}/${EXTERNAL_ZLIB_DIR}")
##set(ZLIB_SOURCES_CONTRIB  "${ZLIB_SOURCE}/contrib/iostream3/zfstream.cc")
##set(ZLIB_INCLUDES_CONTRIB "${ZLIB_SOURCE}/contrib/iostream3")
#
macro(LINK_PRIVATE_LIB_ZLIB PROJECT_TARGET)
  #add_dependencies(${PROJECT_TARGET} zlib-build)
  add_dependencies(${PROJECT_TARGET} zlib)
  target_include_directories(${PROJECT_TARGET} PRIVATE ${ZLIB_SOURCE})
  target_include_directories(${PROJECT_TARGET} PRIVATE ${ZLIB_BUILD})
  target_link_libraries     (${PROJECT_TARGET} PRIVATE ${PROJECT_ZLIB_STATIC})
endmacro()
#
macro(INSTALL_LIB_ZLIB_INTERNAL_DEPENDENCIES)
  install(DIRECTORY "${ZLIB_INSTALL}/." DESTINATION "internal/zlib")
endmacro()

#
##
#

# --- EXTERNAL : TINYXML2 ---
set(TINYXML2_SOURCE         "${EXTERNAL_SOURCE_DIR}/${EXTERNAL_TINYXML2_DIR}")
set(TINYXML2_PREFIX          "external/tinyxml2")
set(TINYXML2_BUILD           "${CMAKE_CURRENT_BINARY_DIR}/${TINYXML2_PREFIX}/build")
set(TINYXML2_INSTALL         "${CMAKE_CURRENT_BINARY_DIR}/${TINYXML2_PREFIX}/install")
set(PROJECT_TINYXML2_STATIC "${TINYXML2_BUILD}/libtinyxml2.a")
#
ExternalProject_Add(
  tinyxml2
  PREFIX ${TINYXML2_PREFIX}
  SOURCE_DIR ${TINYXML2_SOURCE}
  BINARY_DIR ${TINYXML2_BUILD}
  INSTALL_DIR ${TINYXML2_INSTALL}
  BUILD_IN_SOURCE OFF
  BUILD_BYPRODUCTS ${PROJECT_TINYXML2_STATIC}
  STEP_TARGETS build
  EXCLUDE_FROM_ALL TRUE
  CMAKE_CACHE_ARGS
    -DCMAKE_BUILD_TYPE:STRING=Release
    -DCMAKE_INSTALL_PREFIX:STRING=${TINYXML2_INSTALL}
    -DBUILD_SHARED_LIBS:BOOL=OFF
    -DBUILD_STATIC_LIBS:BOOL=ON
    -DBUILD_TESTS:BOOL=OFF
)
#
macro(LINK_PRIVATE_LIB_TINYXML2 PROJECT_TARGET)
  add_dependencies(${PROJECT_TARGET} tinyxml2-build)
  target_include_directories(${PROJECT_TARGET} PRIVATE ${TINYXML2_SOURCE})
  target_link_libraries     (${PROJECT_TARGET} PRIVATE ${PROJECT_TINYXML2_STATIC})
endmacro()


#
##
#

# --- EXTERNAL : GTEST ---
set(GTEST_SOURCE          "${EXTERNAL_SOURCE_DIR}/${EXTERNAL_GTEST_DIR}")
set(GTEST_PREFIX          "external/gtest")
set(GTEST_BUILD           "${CMAKE_CURRENT_BINARY_DIR}/${GTEST_PREFIX}/build")
set(GTEST_INSTALL         "${CMAKE_CURRENT_BINARY_DIR}/${GTEST_PREFIX}/install")
set(PROJECT_GTEST_STATIC  "${GTEST_BUILD}/googletest/libgtest.a")
#
ExternalProject_Add(
  gtest
  PREFIX ${GTEST_PREFIX}
  SOURCE_DIR ${GTEST_SOURCE}
  BINARY_DIR ${GTEST_BUILD}
  INSTALL_DIR ${GTEST_INSTALL}
  BUILD_IN_SOURCE OFF
  BUILD_BYPRODUCTS ${PROJECT_GTEST_STATIC}
  STEP_TARGETS build
  EXCLUDE_FROM_ALL TRUE
  CMAKE_CACHE_ARGS
    -DCMAKE_BUILD_TYPE:STRING=Release
    -DBUILD_GMOCK:BOOL=OFF
    -DBUILD_GTEST:BOOL=ON
    -DINSTALL_GTEST:BOOL=OFF
    -DINSTALL_GMOCK:BOOL=OFF
    -DBUILD_SHARED_LIBS:BOOL=OFF
    -Dgtest_build_tests:BOOL=OFF
    -Dgtest_build_samples:BOOL=OFF
 #   -Dgtest_disable_pthreads:BOOL=OFF
    -Dgtest_hide_internal_symbols:BOOL=OFF
    -DCMAKE_INSTALL_PREFIX:STRING=${GTEST_INSTALL}
)
#
macro(LINK_PRIVATE_LIB_GTEST PROJECT_TARGET)
  add_dependencies(${PROJECT_TARGET} gtest-build)
  target_include_directories(${PROJECT_TARGET} PRIVATE "${GTEST_SOURCE}/googletest/include")
  target_link_libraries     (${PROJECT_TARGET} PRIVATE ${PROJECT_GTEST_STATIC})
endmacro()

#
##
#

# --- EXTERNAL : PICOSHA2 ---
set(PICOSHA2_SOURCE  "${EXTERNAL_SOURCE_DIR}/${EXTERNAL_PICOSHA2_DIR}")
#
macro(LINK_PRIVATE_LIB_PICOSHA2 PROJECT_TARGET)
  target_include_directories(${PROJECT_TARGET} PRIVATE "${PICOSHA2_SOURCE}")
endmacro()


