# - Try to find the darknet includes and library
# which defines
#
# DARKNET_FOUND - system has darknet
# DARKNET_INCLUDE_DIR - where to find darknet.h
# DARKNET_LIBRARIES - the libraries to link against to use darknet

set( DARKNET_LIB_FOUND FALSE )
set( DARKNET_INC_FOUND FALSE )

find_path( DARKNET_INCLUDE_DIR NAMES darknet.h HINTS /usr/local/include/darknet )

find_path( DARKNET_LIBRARY_DIR NAMES libdarknet.so HINTS /usr/local/lib )

find_library( DARKNET_LIBRARY NAMES darknet HINTS /usr/local/lib )

set( DARKNET_INCLUDE_DIRS ${DARKNET_INCLUDE_DIR} )
set( DARKNET_LIBRARY_DIRS ${DARKNET_LIBRARY_DIR} )
set( DARKNET_LIBRARYS ${DARKNET_LIBRARY} )

if( DARKNET_LIBRARY )
    set( DARKNET_LIB_FOUND TRUE )
endif( DARKNET_LIBRARY )

if( DARKNET_LIB_FOUND )
    message( STATUS "Found DARKNET libraries. " ${DARKNET_LIBRARY} )
else( DARKNET_LIB_FOUND )
    if( DARKNET_FIND_REQUIRED )
        message( FATAL_ERROR "Could'not find DARKNET library" )
    endif( DARKNET_FIND_REQUIRED )
endif( DARKNET_LIB_FOUND )

if( DARKNET_INCLUDE_DIR )
    set( DARKNET_INC_FOUND TRUE )
endif( DARKNET_INCLUDE_DIR )

if( DARKNET_INCLUDE_DIR )
    message( STATUS "Found DARKNET headers. " ${DARKNET_INCLUDE_DIR} )
else( DARKNET_INCLUDE_DIR )
    if( DARKNET_FIND_REQUIRED )
        message( FATAL_ERROR "Could'not find DARKNET headers" )
    endif( DARKNET_FIND_REQUIRED )
endif( DARKNET_INCLUDE_DIR )

MARK_AS_ADVANCED(
    DARKNET_INCLUDE_DIRS
    DARKNET_LIBRARIES_DIRS
    DARKNET_LIBRARIES
)
