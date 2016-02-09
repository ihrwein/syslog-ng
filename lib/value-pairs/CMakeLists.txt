set(VALUE_PAIRS_HEADERS
    value-pairs.h
    transforms.h
    cmdline.h
    evttag.h)

set(VALUE_PAIRS_SOURCES
    value-pairs.c
    transforms.c
    cmdline.c
    evttag.c)

add_library(value-pairs OBJECT ${VALUE_PAIRS_SOURCES} ${VALUE_PAIRS_HEADERS})
