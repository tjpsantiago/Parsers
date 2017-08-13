file( GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/hdr )

add_library( libcommon STATIC ${SOURCES} )
