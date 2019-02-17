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
    EXPORT fastdl-targets
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

install(
    EXPORT fastdl-targets
    NAMESPACE fastdl::
    FILE fastdl-config.cmake
    DESTINATION lib/cmake/fastdl
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    fastdl-config-version.cmake
    VERSION ${version}
    COMPATIBILITY SameMinorVersion
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/fastdl-config-version.cmake DESTINATION lib/cmake/fastdl)
