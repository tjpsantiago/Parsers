file( GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
include_directories(
    ${PROJECT_SOURCE_DIR}/common/hdr
    ${CMAKE_CURRENT_SOURCE_DIR}/hdr
    ${CMAKE_CURRENT_SOURCE_DIR}/hdr/types
)

add_executable( StatusPduParser main.cpp ${SOURCES})
target_link_libraries( StatusPduParser libcommon )

add_library( libstatuspdu STATIC ${SOURCES} )
target_link_libraries( libstatuspdu libcommon )
