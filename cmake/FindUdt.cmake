# - Try to find the Udt includes and library
# which defines
#
# UDT_FOUND - system has UDT
# UDT_INCLUDE_DIR - where to find udt.h
# UDT_LIBRARIES - the libraries to link against to use UDT

set( UDT_LIB_FOUND FALSE )
set( UDT_INC_FOUND FALSE )

find_path( UDT_INCLUDE_DIR NAMES udt4/udt.h HINTS /usr/local/include )

find_path( UDT_LIBRARY_DIR NAMES libudt.so HINTS /usr/local/lib )

find_library( UDT_LIBRARY NAMES udt HINTS /usr/local/lib )

set( UDT_INCLUDE_DIRS ${UDT_INCLUDE_DIR} )
set( UDT_LIBRARY_DIRS ${UDT_LIBRARY_DIR} )
set( UDT_LIBRARYS ${UDT_LIBRARY} )

if( UDT_LIBRARY )
    set( UDT_LIB_FOUND TRUE )
endif( UDT_LIBRARY )

if( UDT_LIB_FOUND )
    message( STATUS "Found UDT libraries. " ${UDT_LIBRARY} )
else( UDT_LIB_FOUND )
    if( UDT_FIND_REQUIRED )
        message( FATAL_ERROR "Could'not find UDT library" )
    endif( UDT_FIND_REQUIRED )
endif( UDT_LIB_FOUND )

if( UDT_INCLUDE_DIR )
    set( UDT_INC_FOUND TRUE )
endif( UDT_INCLUDE_DIR )

if( UDT_INCLUDE_DIR )
    message( STATUS "Found UDT headers. " ${UDT_INCLUDE_DIR} )
else( UDT_INCLUDE_DIR )
    if( UDT_FIND_REQUIRED )
        message( FATAL_ERROR "Could'not find UDT headers" )
    endif( UDT_FIND_REQUIRED )
endif( UDT_INCLUDE_DIR )

MARK_AS_ADVANCED(
    UDT_INCLUDE_DIRS
    UDT_LIBRARIES_DIRS
    UDT_LIBRARIES
)

