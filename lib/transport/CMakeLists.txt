set(TRANSPORT_HEADERS
	logtransport.h
	transport-aux-data.h
	transport-tls.h
	transport-file.h
	transport-pipe.h
	transport-device.h
	transport-socket.h)

set(TRANSPORT_SOURCES
	logtransport.c
	transport-aux-data.c
	transport-file.c
	transport-pipe.c
	transport-device.c
	transport-socket.c
	transport-tls.c)

add_library(syslog-ng ${TRANSPORT_SOURCES} ${TRANSPORT_HEADERS})
