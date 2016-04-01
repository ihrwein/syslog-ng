set(syslog_ng_bin_sources
    main.c)

add_executable(syslog-ng-bin ${syslog_ng_bin_sources})
SET_TARGET_PROPERTIES(syslog-ng-bin PROPERTIES OUTPUT_NAME syslog-ng)

link_directories(${CMAKE_CURRENT_BINARY_DIR}/lib/)
target_link_libraries(syslog-ng-bin PRIVATE syslog-ng ${Eventlog_LIBRARIES} ${GLIB_LIBRARIES} ${LIBPCRE_LIBRARIES})

install(TARGETS syslog-ng-bin RUNTIME DESTINATION sbin)
