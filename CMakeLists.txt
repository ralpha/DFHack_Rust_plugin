cmake_minimum_required(VERSION 3.9)

project(HelloRust LANGUAGES CXX)

# Add CPP code that links CPP to Rust
add_library(HelloRust STATIC hello.cpp)

# Enable ExternalProject CMake module
include(ExternalProject)

# Set default ExternalProject root directory
set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/rust)

# Add Project that builds rust code with `cargo build`
ExternalProject_Add(
    hellorust_ext_proj
    DOWNLOAD_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND cargo build COMMAND cargo build --release
    BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dfplugin_test"
    INSTALL_COMMAND ""
    LOG_BUILD ON)

# Create dependency for hellorust_ext_proj
add_dependencies(HelloRust hellorust_ext_proj)

# Specify Example's link libraries
target_link_libraries(HelloRust
    debug "${CMAKE_CURRENT_SOURCE_DIR}/dfplugin_test/target/debug/libdfplugin_test.a"
    optimized "${CMAKE_CURRENT_SOURCE_DIR}/dfplugin_test/target/release/libdfplugin_test.a"
    ws2_32 userenv advapi32)
# As noted in source [4] this might have to be changes for different systems.
# this seems to work for my Linux system, and for there Windows system

set_target_properties(HelloRust PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
# Set cmake flas for pthread. Otherwise you get compile errors
set( CMAKE_CXX_FLAGS " -pthread " )

# link CPP and Rust compiled .a file, using release build here. Should be updated.
DFHACK_PLUGIN(hellorust hello.cpp LINK_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/dfplugin_test/target/release/libdfplugin_test.a)

# Sources to create this:
# [1] https://amirkoblog.wordpress.com/2018/07/05/calling-rust-code-from-c-c/
# [2] https://blog.devolutions.net/2018/06/insider-series-using-rust-code-in-a-cc-project-with-cmake
# [3] https://gitlab.com/Fraser999/Rust-From-CXX/-/blob/master/CMakeLists.txt
# [4] https://stackoverflow.com/questions/31162438/how-can-i-build-rust-code-with-a-c-qt-cmake-project
