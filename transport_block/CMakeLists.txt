file( GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )
set( STATUS_PDU_PARSER_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/status_pdu
    ${PROJECT_SOURCE_DIR}/status_pdu/hdr
    ${PROJECT_SOURCE_DIR}/status_pdu/hdr/types
)
include_directories(
    ${STATUS_PDU_PARSER_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/common/hdr
    ${CMAKE_CURRENT_SOURCE_DIR}/hdr
    ${CMAKE_CURRENT_SOURCE_DIR}/hdr/types
)

add_executable( TransportBlockParser main.cpp ${SOURCES} )
target_link_libraries( TransportBlockParser libcommon )
target_link_libraries( TransportBlockParser libstatuspdu )
