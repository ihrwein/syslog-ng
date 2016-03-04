include(LibFindMacros)

libfind_pkg_check_modules(Libsystemd_PKGCONF libsystemd)

libfind_pkg_detect(Libsystemd systemd FIND_PATH sd-daemon.h PATH_SUFFIXES systemd FIND_LIBRARY systemd)
set(Libsystemd_PROCESS_INCLUDES Libsystemd_INCLUDE_DIR)
set(Libsystemd_PROCESS_LIBS Libsystemd_LIBRARY)
libfind_process(Libsystemd)
