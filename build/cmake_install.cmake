# Install script for directory: /home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/bin/MUEAVISOFT_TEST" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/bin/MUEAVISOFT_TEST")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/bin/MUEAVISOFT_TEST"
         RPATH "$ORIGIN/../lib:$ORIGIN/:/usr/local/cuda-9.2/lib64:/usr/local/lib:/home/mueavi-pc-01/HumanDrive/QT/qt-everywhere-opensource-src-5.6.3/install/lib")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/bin/MUEAVISOFT_TEST")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/bin" TYPE EXECUTABLE FILES "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/build/MUEAVISOFT_TEST")
  if(EXISTS "$ENV{DESTDIR}/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/bin/MUEAVISOFT_TEST" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/bin/MUEAVISOFT_TEST")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/bin/MUEAVISOFT_TEST"
         OLD_RPATH "/usr/local/cuda-9.2/lib64:/usr/local/lib:/home/mueavi-pc-01/HumanDrive/QT/qt-everywhere-opensource-src-5.6.3/install/lib::::::::::::::::::::::::"
         NEW_RPATH "$ORIGIN/../lib:$ORIGIN/:/usr/local/cuda-9.2/lib64:/usr/local/lib:/home/mueavi-pc-01/HumanDrive/QT/qt-everywhere-opensource-src-5.6.3/install/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/bin/MUEAVISOFT_TEST")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/lib/libMUEAVISOFT_LIB.so.0.1.0"
      "$ENV{DESTDIR}/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/lib/libMUEAVISOFT_LIB.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "$ORIGIN/../lib:$ORIGIN/:/usr/local/cuda-9.2/lib64:/usr/local/lib:/home/mueavi-pc-01/HumanDrive/QT/qt-everywhere-opensource-src-5.6.3/install/lib")
    endif()
  endforeach()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/lib/libMUEAVISOFT_LIB.so.0.1.0;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/lib/libMUEAVISOFT_LIB.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/lib" TYPE SHARED_LIBRARY FILES
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/build/libMUEAVISOFT_LIB.so.0.1.0"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/build/libMUEAVISOFT_LIB.so"
    )
  foreach(file
      "$ENV{DESTDIR}/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/lib/libMUEAVISOFT_LIB.so.0.1.0"
      "$ENV{DESTDIR}/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/lib/libMUEAVISOFT_LIB.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/usr/local/cuda-9.2/lib64:/usr/local/lib:/home/mueavi-pc-01/HumanDrive/QT/qt-everywhere-opensource-src-5.6.3/install/lib::::::::::::::::::::::::"
           NEW_RPATH "$ORIGIN/../lib:$ORIGIN/:/usr/local/cuda-9.2/lib64:/usr/local/lib:/home/mueavi-pc-01/HumanDrive/QT/qt-everywhere-opensource-src-5.6.3/install/lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/common.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/curl.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/debug.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/imu.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/key.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/lidar.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/nas.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/mathformat.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/file.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/system.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/pkg.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/ptzcam.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/radar.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/socket.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/tcp.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/udp.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/urg2d.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/urg3d.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/quanergym8.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/visualizer_module.hpp;/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include/pcl_pointxyzir.hpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/install/include" TYPE FILE FILES
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/common.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/curl.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/debug.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/imu.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/key.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/lidar.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/nas.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/mathformat.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/file.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/system.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/pkg.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/ptzcam.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/radar.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/socket.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/tcp.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/udp.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/urg2d.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/urg3d.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/quanergym8.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/visualizer_module.hpp"
    "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/headers/pcl_pointxyzir.hpp"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/build/docs/cmake_install.cmake")
  include("/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/build/devices/cmake_install.cmake")
  include("/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/build/system/cmake_install.cmake")
  include("/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/build/headers/cmake_install.cmake")
  include("/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/build/test/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/mueavi-pc-01/HumanDrive/workspaces/vscodeworkspace/MUEAVI_SDK1/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
