# - Try to find the QuanergyClient includes and library
# which defines
#
# QuanergyClient_FOUND - system has QuanergyClient
# QuanergyClient_INCLUDE_DIR - where to find json.h
# QuanergyClient_LIBRARIES - the libraries to link against to use QuanergyClient

set( QuanergyClient_LIB_FOUND FALSE )
set( QuanergyClient_INC_FOUND FALSE )

find_path( QuanergyClient_INCLUDE_DIR NAMES quanergy/client/version.h HINTS /usr/local/include )

find_path( QuanergyClient_LIBRARY_DIR NAMES libquanergy_client.so HINTS /usr/local/lib )

find_library( QuanergyClient_LIBRARY NAMES quanergy_client HINTS /usr/local/lib )

set( QuanergyClient_INCLUDE_DIRS ${QuanergyClient_INCLUDE_DIR} )
set( QuanergyClient_LIBRARY_DIRS ${QuanergyClient_LIBRARY_DIR} )
set( QuanergyClient_LIBRARYS ${QuanergyClient_LIBRARY} )

if( QuanergyClient_LIBRARY )
    set( QuanergyClient_LIB_FOUND TRUE )
endif( QuanergyClient_LIBRARY )

if( QuanergyClient_LIB_FOUND )
    message( STATUS "Found QuanergyClient libraries. " ${QuanergyClient_LIBRARY} )
else( QuanergyClient_LIB_FOUND )
    if( QuanergyClient_FIND_REQUIRED )
        message( FATAL_ERROR "Could'not find QuanergyClient library" )
    endif( QuanergyClient_FIND_REQUIRED )
endif( QuanergyClient_LIB_FOUND )

if( QuanergyClient_INCLUDE_DIR )
    set( QuanergyClient_INC_FOUND TRUE )
endif( QuanergyClient_INCLUDE_DIR )

if( QuanergyClient_INCLUDE_DIR )
    message( STATUS "Found QuanergyClient headers. " ${QuanergyClient_INCLUDE_DIR} )
else( QuanergyClient_INCLUDE_DIR )
    if( QuanergyClient_FIND_REQUIRED )
        message( FATAL_ERROR "Could'not find QuanergyClient headers" )
    endif( QuanergyClient_FIND_REQUIRED )
endif( QuanergyClient_INCLUDE_DIR )

MARK_AS_ADVANCED(
    QuanergyClient_INCLUDE_DIRS
    QuanergyClient_LIBRARIES_DIRS
    QuanergyClient_LIBRARIES
)
