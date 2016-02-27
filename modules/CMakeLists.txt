
option(ENABLE_AMQP "Enable AMQP module" ON)
if(ENABLE_AMQP)
    add_subdirectory(afamqp)
endif(ENABLE_AMQP)

add_subdirectory(affile)
add_subdirectory(afprog)
add_subdirectory(afsmtp)
add_subdirectory(native)
add_subdirectory(csvparser)
add_subdirectory(date)
add_subdirectory(dbparser)
add_subdirectory(kvformat)
