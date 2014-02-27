# - Try to find Cocos2d
# Once done, this will define
#
#  COCOS2D_FOUND - system has Cocos2d
#  COCOS2D_INCLUDE_DIRS - the Cocos2d include directories 
#  COCOS2D_LIBRARIES - link these to use Cocos2d
#  COCOS2D_LIB_DIR - the directory of Cocos2d libraries

include(FindPkgMacros)
findpkg_begin(COCOS2D)

if (NOT COCOS2D_HOME)
	set(COCOS2D_HOME "../cocos2d-x" CACHE PATH "location of cocos2d source")
endif()

getenv_path(COCOS2D_HOME)

# redo search if prefix path changed
clear_if_changed(COCOS2D_HOME
  COCOS2D_LIBRARY_REL
  COCOS2D_LIBRARY_DBG
  OPENGLES_LIBRARY_REL
  OPENGLES_LIBRARY_DBG
  COCOS2D_SOURCE_DIR
)

set(COCOS2D_LIBRARY_NAMES libcocos2d cocos2d)
use_pkgconfig(COCOS2D_PKGC Cocos2d)

findpkg_framework(COCOS2D)

find_path(COCOS2D_SOURCE_DIR NAMES "include/cocos2d.h" HINTS ${COCOS2D_HOME} ${COCOS2D_PKGC_INCLUDE_DIRS} PATH_SUFFIXES "cocos2dx")
find_path(GLES_INCLUDE_DIR NAMES "GL/glew.h" HINTS ${COCOS2D_HOME} PATH_SUFFIXES "cocos2dx/platform/third_party/win32/OGLES")
find_library(COCOS2D_LIBRARY_REL NAMES ${COCOS2D_LIBRARY_NAMES} HINTS ${COCOS2D_HOME} ${COCOS2D_PKGC_LIBRARY_DIRS} PATH_SUFFIXES "Release.win32" "Release")
find_library(COCOS2D_LIBRARY_DBG NAMES ${COCOS2D_LIBRARY_NAMES} HINTS ${COCOS2D_HOME} ${COCOS2D_PKGC_LIBRARY_DIRS} PATH_SUFFIXES "Debug.win32" "Debug")
find_library(OPENGLES_LIBRARY_REL NAMES glew32 libgles HINTS ${COCOS2D_HOME} ${COCOS2D_PKGC_LIBRARY_DIRS} PATH_SUFFIXES "Release.win32" "Release")
find_library(OPENGLES_LIBRARY_DBG NAMES glew32 libgles HINTS ${COCOS2D_HOME} ${COCOS2D_PKGC_LIBRARY_DIRS} PATH_SUFFIXES "Debug.win32" "Debug")
make_library_set(COCOS2D_LIBRARY)
make_library_set(OPENGLES_LIBRARY)

set(COCOS2D_INCLUDE_DIR ${COCOS2D_SOURCE_DIR} ${COCOS2D_SOURCE_DIR}/platform ${COCOS2D_SOURCE_DIR}/platform/win32 "${COCOS2D_SOURCE_DIR}/include" ${GLES_INCLUDE_DIR})
set(COCOS2D_LIBRARY ${COCOS2D_LIBRARY} ${OPENGLES_LIBRARY})

findpkg_finish(COCOS2D)
#add_parent_dir(OIS_INCLUDE_DIRS OIS_INCLUDE_DIR)


