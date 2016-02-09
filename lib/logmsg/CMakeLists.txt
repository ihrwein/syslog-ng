set(LOGMSG_HEADERS
    gsockaddr-serialize.h
    logmsg.h
    logmsg-serialize.h
    nvtable.h
    nvtable-serialize.h
    nvtable-serialize-endianutils.h
    sdata-serialize.h
    tags-serialize.h
    timestamp-serialize.h)

set(LOGMSG_SOURCES
    gsockaddr-serialize.c
    logmsg.c
    logmsg-serialize.c
    nvtable.c
    nvtable-serialize.c
    sdata-serialize.c
    tags-serialize.c
    timestamp-serialize.c)

add_library(logmsg OBJECT ${LOGMSG_SOURCES} ${LOGMSG_HEADERS})
