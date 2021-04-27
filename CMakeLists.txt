cmake_minimum_required(VERSION 3.12.0)

project(vaslib)

set(VL_BIN_DIR "bin" CACHE STRING "Binaries directory")
set(VL_INCLUDE_DIR "include" CACHE STRING "Includes directory")
set(VL_LIB_DIR "lib" CACHE STRING "Libraries directory")
set(VL_CONFIG_DIR "share/cmake" CACHE STRING "CMake config directory")

add_subdirectory(src)

include(CMakePackageConfigHelpers)
configure_package_config_file(
        ${CMAKE_CURRENT_LIST_DIR}/cmake/vaslibConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/vaslibConfig.cmake
        INSTALL_DESTINATION ${VL_CONFIG_DIR}
)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/vaslibConfigVersion.cmake
        VERSION 2.0.9
        COMPATIBILITY AnyNewerVersion
)

install(EXPORT vaslibTargets
        DESTINATION ${VL_CONFIG_DIR}
        COMPONENT devel
        )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/vaslibConfig.cmake
        DESTINATION ${VL_CONFIG_DIR}
        COMPONENT devel
        )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/vaslibConfigVersion.cmake
        DESTINATION ${VL_CONFIG_DIR}
        COMPONENT devel
        )

