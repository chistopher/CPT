
project(CPT)

# CMake version
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 17)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(
        # warnings
        -Wall -Wextra -Wshadow -Wfloat-equal -Wconversion
        # sanitizers
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        -fno-sanitize-recover=all
    )
    add_link_options(
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
    )
endif()

add_subdirectory(source)

