

#------------------------cmake optoin----------------------------
cmake_minimum_required( VERSION 3.8 FATAL_ERROR )
# set cmake configuration directory
set( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" )
# Minimum compiler version check: GCC >= 4.8
if ( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND
    CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8 )
    message( FATAL_ERROR "GCC 4.8 or later is required." )
endif ()
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 " )
message( " Use C++11 standard " )
cmake_policy( SET CMP0015 NEW )
cmake_policy( SET CMP0022 NEW )
cmake_policy( SET CMP0037 NEW )
cmake_policy( SET CMP0048 NEW )
#


#-----------------------project option--------------------------
set( PROJECT_NAME "MUEAVISOFT" )
set( PROJECT_DESCRIPTION "The software package for MUEAVI project" )
set( PROJECT_VERSION 0.1.0 )
set( PROJECT_LANGUAGE CXX )
project( MUEAVISOFT
    DESCRIPTION ${PROJECT_DESCRIPTION}
    VERSION ${PROJECT_VERSION}
    LANGUAGES ${PROJECT_LANGUAGE}
)
message( "${PROJECT_DESCRIPTION} of version ${PROJECT_VERSION} using ${PROJECT_LANGUAGE}" )
#


#-------------------------source--------------------------------
# MUEAVIE source structure
if (NOT DOC_DIR)
    set( DOC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/docs" )
endif ()
if (NOT DEV_DIR)
    set( DEV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/devices" )
endif ()
if (NOT SYS_DIR)
    set( SYS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/system" )
endif ()
if (NOT HEAD_DIR)
    set( HEAD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/headers" )
endif ()
if(NOT TEST_DIR)
    set( TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif ()
# add subdirectory
add_subdirectory( ${DOC_DIR} )
add_subdirectory( ${DEV_DIR} )
add_subdirectory( ${SYS_DIR} )
add_subdirectory( ${HEAD_DIR} )
include_directories( ${HEAD_DIR} )
#


#----------------------build-options-----------------------------
# Defines the CMAKE_INSTALL_LIBDIR, CMAKE_INSTALL_BINDIR and many other useful macros.
# See https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html
include(GNUInstallDirs)
# Shared/Dynamic or Static library?
option(BUILD_SHARED_LIBS "Build libraries as shared as opposed to static" ON)
# Build type
include("BuildsystemFunctions")
mrg_setup_cmake_build_type("Release")
mrg_setup_executable_rpath()
# Support RPATH?
option(ENABLE_RPATH "Enable RPATH for this library" ON)
mark_as_advanced(ENABLE_RPATH)
include(AddInstallRPATHSupport)
add_install_rpath_support(BIN_DIRS "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}"
                          LIB_DIRS "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}"
                          INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}"
                          DEPENDS ENABLE_RPATH
                          USE_LINK_PATH)
# Add the uninstall target
include(AddUninstallTarget)
# Build test binary
option(BUILD_TEST "Create tests using CMake" ON)
if(BUILD_TEST)
    add_subdirectory( ${TEST_DIR} )
endif()
# Build seperate library
option(BUILD_SEPERATE_LIB "Create seperate library for devices and system" ON)
# install locally
option(INSTALL_LOCAL "Make the installation at local folder instead of system directory" ON)
#


#----------------------pre-requiiste-----------------------------
# Boost >1.58 required
find_package( Boost COMPONENTS thread system REQUIRED )
#include_directories( SYSTEM ${Boost_INCLUDE_DIRS})
#link_directories( ${Boost_LIBRARY_DIRS} )
message( "Boost root directory: ${BOOST_ROOT}")
message( "Boost header directory: ${Boost_INCLUDE_DIRS}" )
message( "Boost library directory: ${Boost_LIBRARY_DIRS}" )
message( "Boost system library: ${Boost_LIBRARIES}" )
message( "Boost thread library: ${Boost_THREAD_LIBRARY}" )
message( "Boost system library: ${Boost_SYSTEM_LIBRARY}" )
# OpenCV > 3.4.1 required
find_package( OpenCV REQUIRED )
#include_directories( SYSTEM ${OpenCV_INCLUDE_DIRS} )
#link_directories( ${OpenCV_LIBS} )
message( "OpenCV header directory: ${OpenCV_INCLUDE_DIRS}" )
message( "OpenCV library directory: ${OpenCV_INSTALL_PATH}/lib" )
message( "OpenCV library: ${OpenCV_LIBRARIES}" )
# Protobuf > 3.9 required
find_package( Protobuf REQUIRED )
find_path( PROTOBUF_LIB_DIR NAMES libprotobuf.so HINTS /usr/local/lib/ )
#include_directories( SYSTEM ${Protobuf_INCLUDE_DIRS} )
#link_directories( SYSTEM ${PROTOBUF_LIB_DIR} )
message( "Protobuf header directory: ${Protobuf_INCLUDE_DIRS}" )
message( "Protobuf library directory: ${PROTOBUF_LIB_DIR}" )
message( "Protobuf library: ${Protobuf_LIBRARIES}" )
# URG 2D/3D required
find_package( Urg REQUIRED )
#include_directories( SYSTEM ${URG_C_INCLUDE_DIR} )
#include_directories( SYSTEM ${URG_CPP_INCLUDE_DIR} )
#include_directories( SYSTEM ${URG3D_INCLUDE_DIR} )
#link_directories( ${URG_C_LIBRARY_DIR} )
#link_directories( ${URG_CPP_LIBRARY_DIR} )
#link_directories( ${URG3D_LIBRARY_DIR} )
message( "URG_C header directory: ${URG_C_INCLUDE_DIR}" )
message( "URG_CPP header directory: ${URG_CPP_INCLUDE_DIR}" )
message( "URG3D header directory: ${URG3D_INCLUDE_DIR}" )
message( "URG_C library directory: ${URG_C_LIBRARY_DIR}" )
message( "URG_CPP library directory: ${URG_CPP_LIBRARY_DIR}" )
message( "URG3D library directory: ${URG3D_LIBRARY_DIR}" )
message( "URG library: ${URG_LIBRARIES}" )
# Eigen required
find_package( Eigen REQUIRED )
#include_directories( SYSTEM ${EIGEN_INCLUDE_DIRS} )
#link_directories( ${EIGEN_LIBRARIES} )
message( "Eigen header directory: ${EIGEN_INCLUDE_DIRS}" )
message( "Eigen library directory: ${EIGEN_LIBRARIES}" )
# VTK > 8.1.1 required
find_package( VTK REQUIRED )
#include_directories( SYSTEM ${VTK_INCLUDE_DIRS} )
#link_directories( ${VTK_LIBRARY_DIRS} )
message( "VTK header directory: ${VTK_INCLUDE_DIRS}" )
message( "VTK library directory: ${VTK_INSTALL_PREFIX}/lib" )
message( "VTK library: ${VTK_LIBRARIES}" )
# PCL >1.8 required
find_package( PCL REQUIRED )
#include_directories( SYSTEM ${PCL_INCLUDE_DIRS} )
#link_directories( ${PCL_LIBRARY_DIRS} )
message( "PCL header directory: ${PCL_INCLUDE_DIRS}" )
message( "PCL library directory: ${PCL_LIBRARY_DIRS}" )
message( "PCL library: ${PCL_LIBRARIES}" )
# UDT4 required
find_package( Udt REQUIRED )
#include_directories( SYSTEM ${UDT_INCLUDE_DIRS} )
#link_directories( ${UDT_LIBRARY_DIRS} )
message( "UDT header directory: ${UDT_INCLUDE_DIRS}" )
message( "UDT library directory: ${UDT_LIBRARY_DIRS}" )
message( "UDT library: ${UDT_LIBRARYS}" )
# JSON-C required
find_package( JsonC REQUIRED )
#include_directories( SYSTEM ${JSONC_INCLUDE_DIRS} )
#link_directories( ${JSONC_LIBRARY_DIRS} )
message( "JSON header directory: ${JSONC_INCLUDE_DIRS}" )
message( "JSON library directory: ${JSONC_LIBRARY_DIRS}" )
message( "JSON library: ${JSONC_LIBRARYS}" )
# QuanergyClient required
find_package( QuanergyClient REQUIRED )
message( "QuanergyClient header directory: ${QuanergyClient_INCLUDE_DIRS}" )
message( "QuanergyClient library directory: ${QuanergyClient_LIBRARY_DIRS}" )
message( "QuanergyClient library: ${QuanergyClient_LIBRARYS}" )
#


#------------------library installation------------------------
include_directories( SYSTEM $ENV{C_INCLUDE_PATH} )
include_directories( SYSTEM $ENV{CPLUS_INCLUDE_PATH} )
link_directories( $ENV{LD_LIBRARY_PATH} )
message("C_INCLUDE_PATH: $ENV{C_INCLUDE_PATH}")
message("CPLUS_INCLUDE_PATH: $ENV{CPLUS_INCLUDE_PATH}")
message("LD_LIBRARY_PATH: $ENV{LD_LIBRARY_PATH}")
# MUEAVI output structure
if ( NOT MUEAVI_INSTALL_EXEC_DIR )
    set( MUEAVI_INSTALL_EXEC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/install/bin" )
endif ()
if ( NOT MUEAVI_INSTALL_DOC_DIR )
    set( MUEAVI_INSTALL_DOC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/install/doc" )
endif ()
if( NOT MUEAVI_INSTALL_LIB_DIR )
    set( MUEAVI_INSTALL_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/install/lib" )
endif ()
if( NOT MUEAVI_INSTALL_INC_DIR )
    set( MUEAVI_INSTALL_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/install/include" )
endif ()
# build shared library
set( MUEAVISOFT_SRC
    devices/imu/imu.cpp
    devices/lidar/lidar.cpp
    devices/lidar/urg2d.cpp
    devices/lidar/urg3d.cpp
    devices/lidar/quanergym8.cpp
    devices/ptzcam/ptzcam.cpp
    devices/radar/radar.cpp
    system/common/debug.cpp
    system/common/mathformat.cpp
    system/common/file.cpp
    system/common/system.cpp
    system/common/visualizer_module.cpp
#    system/common/profiling.cpp
    system/keyboard/key.cpp
    system/network/curl.cpp
    system/network/nas.cpp
    system/network/pkg.cpp
    system/network/socket.cpp
    system/network/tcp.cpp
    system/network/udp.cpp
#    system/objectdetect/
#    system/objecttrack
#    system/synchronize/timestamp.cpp
#    system/trajectorypredict
)
set( MUEAVISOFT_INC
    headers/common.hpp
    headers/curl.hpp
    headers/debug.hpp
    headers/imu.hpp
    headers/key.hpp
    headers/lidar.hpp
    headers/nas.hpp
    headers/mathformat.hpp
    headers/file.hpp
    headers/system.hpp
    headers/pkg.hpp
#    headers/profiling.hpp
    headers/ptzcam.hpp
    headers/radar.hpp
#    headers/timestamp.hpp
    headers/socket.hpp
    headers/tcp.hpp
    headers/udp.hpp
    headers/urg2d.hpp
    headers/urg3d.hpp
    headers/quanergym8.hpp
    headers/visualizer_module.hpp
    headers/pcl_pointxyzir.hpp
)
add_library( MUEAVISOFT_LIB SHARED
    ${MUEAVISOFT_SRC} ${MUEAVISOFT_INC}
)
set_target_properties( MUEAVISOFT_LIB PROPERTIES LINKER_LANGUAGE ${PROJECT_LANGUAGE} )
set_target_properties( MUEAVISOFT_LIB PROPERTIES VERSION "${PROJECT_VERSION}")
set_target_properties( MUEAVISOFT_LIB PROPERTIES DESCRIPTION ${PROJECT_DESCRIPTION})
target_include_directories( MUEAVISOFT_LIB
    PUBLIC ${MUEAVI_INSTALL_INC_DIR}
    PUBLIC ${HEAD_DIR}
    PUBLIC ${EIGEN_INCLUDE_DIRS}
    PUBLIC ${Boost_INCLUDE_DIRS}
    PUBLIC ${OpenCV_INCLUDE_DIRS}
    PUBLIC ${Protobuf_INCLUDE_DIRS}
    PUBLIC ${PCL_INCLUDE_DIRS}
    PUBLIC ${URG_INCLUDE_DIRS}
    PUBLIC ${UDT_INCLUDE_DIR}
    PUBLIC ${JSONC_INCLUDE_DIRS}
    PUBLIC ${QuanergyClient_INCLUDE_DIRS}
)
target_link_libraries( MUEAVISOFT_LIB
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC ${OpenCV_LIBS}
    PUBLIC ${Protobuf_LIBRARIES}
    PUBLIC ${URG_LIBRARIES}
    PUBLIC ${VTK_LIBRARIES}
    PUBLIC ${PCL_LIBRARIES}
    PUBLIC ${UDT_LIBRARYS}
    PUBLIC ${JSONC_LIBRARYS}
    PUBLIC ${QuanergyClient_LIBRARYS}
    PUBLIC m
    PUBLIC pthread
    PUBLIC curl
    PUBLIC dl
    PUBLIC rt
    PUBLIC json-c
)
if ( BUILD_TEST )
    # build test binary
    aux_source_directory( ${TEST_DIR} TEST_SRCS )
#    set ( SOURCE_FILES
#        # ... several C++-source files
#        ${MUEAVISOFT_SRC}
#        ${MUEAVISOFT_INC}
#    )
#    add_library( MUEAVISOFT_OBJECTS OBJECT
#        ${SOURCE_FILES}
#    )
#    set_target_properties( MUEAVISOFT_OBJECTS PROPERTIES LINKER_LANGUAGE ${PROJECT_LANGUAGE} )
#    set_target_properties( MUEAVISOFT_OBJECTS PROPERTIES VERSION "${PROJECT_VERSION}")
#    set_target_properties( MUEAVISOFT_OBJECTS PROPERTIES DESCRIPTION ${PROJECT_DESCRIPTION})
#    add_executable( MUEAVISOFT_TEST ${TEST_SRCS} ${MUEAVISOFT_INC} $<TARGET_OBJECTS:MUEAVISOFT_OBJECTS> )
    add_executable( MUEAVISOFT_TEST ${TEST_SRCS} ${MUEAVISOFT_SRC} ${MUEAVISOFT_INC} )    
    target_include_directories( MUEAVISOFT_TEST SYSTEM
        PUBLIC ${MUEAVI_INSTALL_INC_DIR}
        PUBLIC ${HEAD_DIR}
        PUBLIC ${EIGEN_INCLUDE_DIRS}
        PUBLIC ${Boost_INCLUDE_DIRS}
        PUBLIC ${OpenCV_INCLUDE_DIRS}
        PUBLIC ${Protobuf_INCLUDE_DIRS}
        PUBLIC ${PCL_INCLUDE_DIRS}
        PUBLIC ${URG_INCLUDE_DIRS}
        PUBLIC ${UDT_INCLUDE_DIR}
        PUBLIC ${JSONC_INCLUDE_DIRS}
        PUBLIC ${QuanergyClient_INCLUDE_DIRS}
    )
    target_link_libraries( MUEAVISOFT_TEST
        PUBLIC ${Boost_LIBRARIES}
        PUBLIC ${OpenCV_LIBS}
        PUBLIC ${Protobuf_LIBRARIES}
        PUBLIC ${URG_LIBRARIES}
        PUBLIC ${VTK_LIBRARIES}
        PUBLIC ${PCL_LIBRARIES}
        PUBLIC ${UDT_LIBRARYS}
        PUBLIC ${JSONC_LIBRARYS}
        PUBLIC ${QuanergyClient_LIBRARYS}
        PUBLIC m
        PUBLIC pthread
        PUBLIC curl
        PUBLIC dl
        PUBLIC rt
        PUBLIC json-c
    )
endif ()
# installation
if ( NOT INSTALL_LOCAL )
    if ( BUILD_TEST )
        install( TARGETS MUEAVISOFT_TEST DESTINATION "/usr/local/mueavisoft/bin" )
    endif()
    install( TARGETS MUEAVISOFT_LIB DESTINATION "/usr/local/mueavisoft/lib" )
    install( FILES ${MUEAVISOFT_INC} DESTINATION "/usr/local/mueavisoft/include" )
else ()
    if ( BUILD_TEST )
        install( TARGETS MUEAVISOFT_TEST DESTINATION ${MUEAVI_INSTALL_EXEC_DIR} )
    endif ()
    install( TARGETS MUEAVISOFT_LIB DESTINATION ${MUEAVI_INSTALL_LIB_DIR} )
    install( FILES ${MUEAVISOFT_INC} DESTINATION ${MUEAVI_INSTALL_INC_DIR} )
endif ()
#

#------------------copy testing files--------------------
file(GLOB MY_PUBLIC_HEADERS
    "test/testdata/*.jpg"
)
file(COPY ${MY_PUBLIC_HEADERS} DESTINATION ".")
#
