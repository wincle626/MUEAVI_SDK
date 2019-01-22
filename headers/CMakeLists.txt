# add source
aux_source_directory(. HEADER_SRCS)
include_directories( MUEAVISOFT PUBLIC $ENV{C_INCLUDE_PATH} )
include_directories( MUEAVISOFT PUBLIC $ENV{CPLUS_INCLUDE_PATH} )
