#
# Locate and configure the Google Protocol Buffers library.
#
# See FindProtobuf_cmake_3_9_0.cmake or system's FindProtobuf for cmake > 3.9
# for full documentation.
#

# Pull in FindProtobuf from CMake project
if(CMAKE_VERSION VERSION_LESS "3.9")
  # Versions prior to 3.9 don't have IMPORTED targets
  include(${CMAKE_CURRENT_LIST_DIR}/FindProtobuf_cmake_3_9_0.cmake)
else()
  include(${CMAKE_ROOT}/Modules/FindProtobuf.cmake)
endif()

# By default have PROTOBUF_GENERATE_CPP macro pass -I to protoc
# for each directory where a proto file is referenced.
if (NOT DEFINED PROTOBUF_GENERATE_CPP_APPEND_PATH_FROM_INPUT_FILES)
  set(PROTOBUF_GENERATE_CPP_APPEND_PATH_FROM_INPUT_FILES TRUE)
endif()
if (NOT DEFINED PROTOBUF_GENERATE_USE_CURRENT_SOURCE_DIR_AS_PATH)
  set(PROTOBUF_GENERATE_USE_CURRENT_SOURCE_DIR_AS_PATH TRUE)
endif()

# Try to reduce some of the -lpthread duplication. Really needs fixing upstream
# Only an issue for projects that call us repeatedly
list(REMOVE_DUPLICATES Protobuf_LIBRARIES)
