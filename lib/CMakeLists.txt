flex_target(CfgLexer
    ${CMAKE_SOURCE_DIR}/lib/cfg-lex.l
    ${CMAKE_BINARY_DIR}/lib/cfg-lex.c
    ${CMAKE_BINARY_DIR}/lib/cfg-lex.h)

set_source_files_properties(${CMAKE_BINARY_DIR}/lib/cfg-lex.h GENERATED)
set_source_files_properties(${CMAKE_BINARY_DIR}/lib/cfg-lex.c GENERATED)

add_subdirectory(compat)
add_subdirectory(control)
add_subdirectory(filter)
add_subdirectory(logmsg)
add_subdirectory(logproto)
add_subdirectory(parser)
add_subdirectory(rewrite)
add_subdirectory(stats)
add_subdirectory(template)
add_subdirectory(transport)
add_subdirectory(value-pairs)

set (LIB_HEADERS
    afinter.h
    alarms.h
    apphook.h
    atomic.h
    block-ref-parser.h
    cache.h
    cfg.h
    cfg-lexer.h
    cfg-lexer-subst.h
    cfg-args.h
    cfg-parser.h
    cfg-tree.h
    children.h
    crypto.h
    dnscache.h
    driver.h
    fdhelpers.h
    file-perms.h
    find-crlf.h
    gprocess.h
    gsockaddr.h
    gsocket.h
    hostname.h
    host-resolve.h
    logmatcher.h
    logmpx.h
    logpipe.h
    logqueue-fifo.h
    logqueue.h
    logreader.h
    logsource.h
    logstamp.h
    logthrdestdrv.h
    logwriter.h
    mainloop.h
    mainloop-call.h
    mainloop-worker.h
    mainloop-io-worker.h
    module-config.h
    memtrace.h
    messages.h
    ml-batched-timer.h
    msg-format.h
    parse-number.h
    pathutils.h
    persist-state.h
    persistable-state-header.h
    persistable-state-presenter.h
    plugin.h
    plugin-types.h
    poll-events.h
    poll-fd-events.h
    pragma-parser.h
    presented-persistable-state.h
    reloc.h
    rcptid.h
    run-id.h
    scratch-buffers.h
    serialize.h
    service-management.h
    seqnum.h
    str-format.h
    str-utils.h
    syslog-names.h
    syslog-ng.h
    string-list.h
    tags.h
    timeutils.h
    tls-support.h
    thread-utils.h
    tlscontext.h
    type-hinting.h
    uuid.h
    userdb.h
    utf8utils.h
    versioning.h
    bookmark.h
    ringbuffer.h
    ack_tracker.h
    host-id.h
    ${COMPAT_HEADERS}
    ${CONTROL_HEADERS}
    ${FILTER_HEADERS}
    ${LOGMSG_HEADERS}
    ${LOGPROTO_HEADERS}
    ${PARSER_HEADERS}
    ${REWRITE_HEADERS}
    ${STATS_HEADERS}
    ${TEMPLATE_HEADERS}
    ${VALUE_PAIRS_HEADERS}
    ${CMAKE_BINARY_DIR}/lib/cfg-grammar.h
    ${CMAKE_BINARY_DIR}/lib/block-ref-grammar.h
    ${CMAKE_BINARY_DIR}/lib/cfg-lex.h
    ${CMAKE_BINARY_DIR}/lib/pragma-grammar.h
    ${CMAKE_BINARY_DIR}/lib/parser/parser-expr-grammar.h)

set(LIB_SOURCES
    afinter.c
    alarms.c
    apphook.c
    block-ref-parser.c
    cache.c
    cfg.c
    cfg-args.c
    cfg-lexer.c
    cfg-lexer-subst.c
    cfg-parser.c
    cfg-tree.c
    children.c
    dnscache.c
    driver.c
    fdhelpers.c
    file-perms.c
    find-crlf.c
    globals.c
    gprocess.c
    gsockaddr.c
    gsocket.c
    hostname.c
    host-resolve.c
    logmatcher.c
    logmpx.c
    logpipe.c
    logqueue.c
    logqueue-fifo.c
    logreader.c
    logsource.c
    logstamp.c
    logthrdestdrv.c
    logwriter.c
    mainloop.c
    mainloop-call.c
    mainloop-worker.c
    mainloop-io-worker.c
    module-config.c
    memtrace.c
    messages.c
    ml-batched-timer.c
    msg-format.c
    parse-number.c
    pathutils.c
    persist-state.c
    plugin.c
    poll-events.c
    poll-fd-events.c
    pragma-parser.c
    persistable-state-presenter.c
    rcptid.c
    reloc.c
    run-id.c
    scratch-buffers.c
    serialize.c
    service-management.c
    str-format.c
    str-utils.c
    syslog-names.c
    string-list.c
    tags.c
    timeutils.c
    type-hinting.c
    ringbuffer.c
    late_ack_tracker.c
    early_ack_tracker.c
    crypto.c
    tlscontext.c
    uuid.c
    userdb.c
    utf8utils.c
    host-id.c
    ${COMPAT_SOURCES}
    ${CONTROL_SOURCES}
    ${FILTER_SOURCES}
    ${LOGMSG_SOURCES}
    ${LOGPROTO_SOURCES}
    ${PARSER_SOURCES}
    ${REWRITE_SOURCES}
    ${STATS_SOURCES}
    ${TEMPLATE_SOURCES}
    ${VALUE_PAIRS_SOURCES}
    ${CMAKE_BINARY_DIR}/lib/cfg-grammar.c
    #${CMAKE_BINARY_DIR}/lib/block-ref-grammar.c
    ${CMAKE_BINARY_DIR}/lib/cfg-lex.c
    ${CMAKE_BINARY_DIR}/lib/pragma-grammar.c
    ${CMAKE_BINARY_DIR}/lib/parser/parser-expr-grammar.c
    )

bison_target(CfgGrammar
    ${CMAKE_SOURCE_DIR}/lib/cfg-grammar.y
    ${CMAKE_BINARY_DIR}/lib/cfg-grammar.c
    COMPILE_FLAGS ${BISON_FLAGS})
add_flex_bison_dependency(CfgLexer CfgGrammar)

generate_y_from_ym (lib/block-ref-grammar)
bison_target(BlockRefGrammar
    ${CMAKE_BINARY_DIR}/lib/block-ref-grammar.y
    ${CMAKE_BINARY_DIR}/lib/block-ref-grammar.c
    COMPILE_FLAGS ${BISON_FLAGS})
add_flex_bison_dependency(CfgLexer BlockRefGrammar)

generate_y_from_ym (lib/pragma-grammar)
generate_y_from_ym (lib/parser/parser-expr-grammar)

set_source_files_properties(${CMAKE_BINARY_DIR}/lib/block-ref-grammar.h GENERATED)
set_source_files_properties(${CMAKE_BINARY_DIR}/lib/block-ref-grammar.c GENERATED)

bison_target(PragmaGrammar
    ${CMAKE_BINARY_DIR}/lib/pragma-grammar.y
    ${CMAKE_BINARY_DIR}/lib/pragma-grammar.c
    COMPILE_FLAGS ${BISON_FLAGS})

add_flex_bison_dependency(CfgLexer PragmaGrammar)


bison_target(ParserExprGrammar
    ${CMAKE_BINARY_DIR}/lib/parser/parser-expr-grammar.y
    ${CMAKE_BINARY_DIR}/lib/parser/parser-expr-grammar.c
    COMPILE_FLAGS ${BISON_FLAGS})

add_flex_bison_dependency(CfgLexer ParserExprGrammar)

set_source_files_properties(${CMAKE_BINARY_DIR}/lib/cfg-grammar.h GENERATED)
set_source_files_properties(${CMAKE_BINARY_DIR}/lib/cfg-grammar.c GENERATED)

add_library(syslog-ng
    SHARED
    ${LIB_SOURCES}
    ${LIB_HEADERS})

target_link_libraries (syslog-ng ${Glib_LIBRARIES} ${IVYKIS_LIBRARIES} ${EVENTLOG_LIBRARIES} ${FLEX_LIBRARIES} ${BISON_LIBRARIES})

