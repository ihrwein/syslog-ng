set(VALUE_PAIRS_HEADERS
    lib/value-pairs/value-pairs.h
    lib/value-pairs/transforms.h
    lib/value-pairs/cmdline.h
    lib/value-pairs/evttag.h
    PARENT_SCOPE)

set(VALUE_PAIRS_SOURCES
    lib/value-pairs/value-pairs.c
    lib/value-pairs/transforms.c
    lib/value-pairs/cmdline.c
    lib/value-pairs/evttag.c
    PARENT_SCOPE)

add_library(value-pairs OBJECT ${VALUE_PAIRS_SOURCES} ${VALUE_PAIRS_HEADERS})
