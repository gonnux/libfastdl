add_library(fastdl SHARED)
target_sources(fastdl PRIVATE fastdl.c)
target_compile_options(fastdl PRIVATE -Wall)
set_target_properties(
    fastdl
    PROPERTIES
    C_STANDARD 11
    VERSION ${version}
    SOVERSION ${soversion}
    PUBLIC_HEADER "fastdl.h"
)

target_link_libraries(fastdl dl)

install(
    TARGETS fastdl
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)
