set(COMPAT_HEADERS
	compat.h
	getutent.h
	glib.h
	lfs.h
	pio.h
	socket.h
	string.h
	time.h)

set(COMPAT_SOURCES
	getutent.c
	inet_aton.c
	memrchr.c
	pio.c
	strcasestr.c
	strtok_r.c)

add_library(syslog-ng ${COMPAT_SOURCES} ${COMPAT_HEADERS})
