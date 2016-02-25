set(PDBTOOL_SOURCES pdbtool.c)
add_executable(pdbtool ${PDBTOOL_SOURCES})
target_link_libraries(pdbtool patterndb)
target_include_directories(pdbtool PRIVATE ${CMAKE_SOURCE_DIR}/modules/dbparser ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
