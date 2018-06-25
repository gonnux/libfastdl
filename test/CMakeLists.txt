add_library(fastdl_test_lib SHARED fastdl_test_lib.c)
set_target_properties(fastdl_test_lib PROPERTIES
                                      C_STANDARD 11
                                      POSITION_INDEPENDENT_CODE on)

add_executable(fastdl_test fastdl_test.c)
set_target_properties(fastdl_test PROPERTIES
                                  C_STANDARD 11)
target_link_libraries(fastdl_test fastdl cmocka)
add_test(NAME fastdl_test COMMAND fastdl_test)

add_executable(dl_test dl_test.c)
set_target_properties(dl_test PROPERTIES
                              C_STANDARD 11)
target_link_libraries(dl_test dl cmocka)
add_test(NAME dl_test COMMAND dl_test)
