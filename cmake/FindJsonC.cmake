# - Try to find the json-c includes and library
# which defines
#
# JSONC_FOUND - system has json-c
# JSONC_INCLUDE_DIR - where to find json.h
# JSONC_LIBRARIES - the libraries to link against to use json-c

set( JSONC_LIB_FOUND FALSE )
set( JSONC_INC_FOUND FALSE )

find_path( JSONC_INCLUDE_DIR NAMES json-c/json.h HINTS /usr/local/include )

find_path( JSONC_LIBRARY_DIR NAMES libjson-c.so HINTS /usr/local/lib )

find_library( JSONC_LIBRARY NAMES json-c HINTS /usr/local/lib )

set( JSONC_INCLUDE_DIRS ${JSONC_INCLUDE_DIR} )
set( JSONC_LIBRARY_DIRS ${JSONC_LIBRARY_DIR} )
set( JSONC_LIBRARYS ${JSONC_LIBRARY} )

if( JSONC_LIBRARY )
    set( JSONC_LIB_FOUND TRUE )
endif( JSONC_LIBRARY )

if( JSONC_LIB_FOUND )
    message( STATUS "Found JSONC libraries. " ${JSONC_LIBRARY} )
else( JSONC_LIB_FOUND )
    if( JSONC_FIND_REQUIRED )
        message( FATAL_ERROR "Could'not find JSONC library" )
    endif( JSONC_FIND_REQUIRED )
endif( JSONC_LIB_FOUND )

if( JSONC_INCLUDE_DIR )
    set( JSONC_INC_FOUND TRUE )
endif( JSONC_INCLUDE_DIR )

if( JSONC_INCLUDE_DIR )
    message( STATUS "Found JSONC headers. " ${JSONC_INCLUDE_DIR} )
else( JSONC_INCLUDE_DIR )
    if( JSONC_FIND_REQUIRED )
        message( FATAL_ERROR "Could'not find JSONC headers" )
    endif( JSONC_FIND_REQUIRED )
endif( JSONC_INCLUDE_DIR )

MARK_AS_ADVANCED(
    JSONC_INCLUDE_DIRS
    JSONC_LIBRARIES_DIRS
    JSONC_LIBRARIES
)
