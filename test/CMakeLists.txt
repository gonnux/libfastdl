add_library(fastdl_test_lib SHARED)
target_sources(fastdl_test_lib PRIVATE fastdl_test_lib.c)
set_target_properties(
    fastdl_test_lib
    PROPERTIES
    C_STANDARD 11
    POSITION_INDEPENDENT_CODE on
)

add_executable(fastdl_test fastdl_test.c)
target_link_libraries(fastdl_test fastdl cmocka)
set_target_properties(fastdl_test PROPERTIES C_STANDARD 11)
add_test(NAME fastdl_test COMMAND fastdl_test)

add_executable(dl_test dl_test.c)
target_link_libraries(dl_test dl cmocka)
set_target_properties(dl_test PROPERTIES C_STANDARD 11)
add_test(NAME dl_test COMMAND dl_test)
