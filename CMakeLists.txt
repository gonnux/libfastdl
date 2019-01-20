cmake_minimum_required(VERSION 2.8)
project(libfastdl C)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

set(fastdl_version "0.1.1")
set(fastdl_soversion "0.1")

if(CMAKE_VERSION VERSION_LESS "3.1")
  if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set (CMAKE_C_FLAGS "-std=gnu11 ${CMAKE_C_FLAGS}")
  endif()
else()
  set(CMAKE_C_STANDARD 11)
endif()

execute_process(COMMAND git shortlog --all -nse --no-merges HEAD OUTPUT_FILE "${CMAKE_SOURCE_DIR}/AUTHORS")
add_custom_target(authors ALL git shortlog --all -nse --no-merges HEAD > "${CMAKE_SOURCE_DIR}/AUTHORS")

add_subdirectory(src)
enable_testing()
add_subdirectory(test)
