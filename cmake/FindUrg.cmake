# - Try to find the Urg includes and library
# which defines
#
# URG_FOUND - system has URG and URG3D
# URG_INCLUDE_DIR - where to find urg_sensor.h and urg3d_sensor.h
# URG_LIBRARIES - the libraries to link against to use URG

set( URG_LIB_FOUND FALSE )
set( URG_INC_FOUND FALSE )

find_path( URG_C_INCLUDE_DIR NAMES urg_c/urg_sensor.h HINTS /usr/local/include/ )
find_path( URG_CPP_INCLUDE_DIR NAMES urg_cpp/Urg_driver.h HINTS /usr/local/include/ )
find_path( URG3D_INCLUDE_DIR NAMES urg3d_sensor.h HINTS /usr/local/include/ )

find_path( URG_C_LIBRARY_DIR NAMES liburg_c.so HINTS /usr/local/lib/ )
find_path( URG_CPP_LIBRARY_DIR NAMES liburg_cpp.so HINTS /usr/local/lib/ )
find_path( URG3D_LIBRARY_DIR NAMES liburg3d.so HINTS /usr/local/lib/ )

find_library( URG_C_LIBRARY NAMES urg_c HINTS /usr/local/lib/ )
find_library( URG_CPP_LIBRARY NAMES urg_cpp HINTS /usr/local/lib/ )
find_library( URG3D_LIBRARY NAMES urg3d HINTS /usr/local/lib/ )

set( URG_INCLUDE_DIRS
    ${URG_C_INCLUDE_DIR}
    ${URG_CPP_INCLUDE_DIR}
    ${URG3D_INCLUDE_DIR}
)

set( URG_LIBRARIES_DIRS
    ${URG_C_LIBRARY_DIR}
    ${URG_CPP_LIBRARY_DIR}
    ${URG3D_LIBRARY_DIR}
)

set( URG_LIBRARIES
    ${URG_C_LIBRARY}
    ${URG_CPP_LIBRARY}
    ${URG3D_LIBRARY}
)

if( URG_LIBRARIES )
    set( URG_LIB_FOUND TRUE )
endif( URG_LIBRARIES )

if( URG_LIB_FOUND )
    message( STATUS "Found URG libraries. " ${URG_LIBRARIES} )
else( URG_LIB_FOUND )
    if( URG_FIND_REQUIRED )
        message( FATAL_ERROR "Could'not find URG library" )
    endif( URG_FIND_REQUIRED )
endif( URG_LIB_FOUND )

if( URG_INCLUDE )
    set( URG_INC_FOUND TRUE )
endif( URG_INCLUDE )

if( URG_INCLUDE )
    message( STATUS "Found URG headers. " ${URG_INCLUDE} )
else( URG_INCLUDE )
    if( URG_FIND_REQUIRED )
        message( FATAL_ERROR "Could'not find URG headers" )
    endif( URG_FIND_REQUIRED )
endif( URG_INCLUDE )

MARK_AS_ADVANCED(
    URG_C_INCLUDE_DIR
    URG_CPP_INCLUDE_DIR
    URG3D_INCLUDE_DIR
    URG_C_LIBRARY_DIR
    URG_CPP_LIBRARY_DIR
    URG3D_LIBRARY_DIR
    URG_INCLUDE_DIRS
    URG_LIBRARIES_DIRS
    URG_LIBRARIES
)
