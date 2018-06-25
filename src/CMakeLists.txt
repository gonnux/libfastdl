add_library(fastdl SHARED fastdl.c)
target_link_libraries(fastdl dl)
set_target_properties(fastdl PROPERTIES
                             VERSION "0.1.1"
                             SOVERSION "0.1.0"
                             PUBLIC_HEADER "fastdl.h")
install(TARGETS fastdl
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include)
