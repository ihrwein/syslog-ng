set(CONTROL_HEADERS
	control.h
	control-server.h)

set(CONTROL_SOURCES
	control.c
	control-server.c
  control-server-unix.c
)

add_library(control OBJECT ${CONTROL_SOURCES} ${CONTROL_HEADERS})
