#
# EmbeddedResource project - externals builds
# Under the Copyright (C) Christophe-Alexandre Sonntag (http://u4a.at)

# --- KEEP CMAKE_INSTALL_PREFIX ---
set(ORIGINAL_CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
macro(SetExternalInstallPrefix Name)
  set(CMAKE_INSTALL_BINDIR)
  set(CMAKE_INSTALL_SBINDIR)
  set(CMAKE_INSTALL_LIBEXECDIR)
  set(CMAKE_INSTALL_SYSCONFDIR)
  set(CMAKE_INSTALL_SHAREDSTATEDIR)
  set(CMAKE_INSTALL_LOCALSTATEDIR)
  set(CMAKE_INSTALL_RUNSTATEDIR)
  set(CMAKE_INSTALL_LIBDIR)
  set(CMAKE_INSTALL_INCLUDEDIR)
  set(CMAKE_INSTALL_OLDINCLUDEDIR)
  set(CMAKE_INSTALL_DATAROOTDIR)
  set(CMAKE_INSTALL_DATADIR)
  set(CMAKE_INSTALL_INFODIR)
  set(CMAKE_INSTALL_LOCALEDIR)
  set(CMAKE_INSTALL_MANDIR)
  set(CMAKE_INSTALL_DOCDIR)
  set(CMAKE_INSTALL_PREFIX "${ORIGINAL_CMAKE_INSTALL_PREFIX}/external/${Name}" CACHE PATH "(external set)" FORCE)
  include(GNUInstallDirs)
endmacro()

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
SetExternalInstallPrefix("zlib")
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
SetExternalInstallPrefix("tinyxml2")
set(BUILD_SHARED_LIBS    OFF                 CACHE BOOL "(external set)" FORCE)
set(BUILD_STATIC_LIBS    ON                  CACHE BOOL "(external set)" FORCE)
set(BUILD_TESTS          OFF                 CACHE BOOL "(external set)" FORCE)
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
SetExternalInstallPrefix("gtest")
set(BUILD_GMOCK                 OFF              CACHE BOOL "(external set)" FORCE)
set(BUILD_GTEST                 ON               CACHE BOOL "(external set)" FORCE)
set(INSTALL_GTEST               OFF              CACHE BOOL "(external set)" FORCE)
set(INSTALL_GMOCK               OFF              CACHE BOOL "(external set)" FORCE)
set(BUILD_SHARED_LIBS           OFF              CACHE BOOL "(external set)" FORCE)
set(gtest_build_tests           OFF              CACHE BOOL "(external set)" FORCE)
set(gtest_build_samples         OFF              CACHE BOOL "(external set)" FORCE)
set(gtest_disable_pthreads      OFF              CACHE BOOL "(external set)" FORCE)
set(gtest_hide_internal_symbols OFF              CACHE BOOL "(external set)" FORCE)
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

#
##
#

# --- RESTORE CMAKE_INSTALL_PREFIX ---
set(CMAKE_INSTALL_PREFIX "${ORIGINAL_CMAKE_INSTALL_PREFIX}" CACHE PATH "Installation prefix" FORCE)


