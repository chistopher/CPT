cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(CPT)
set (CMAKE_CXX_STANDARD 20)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(
        # warnings
        -Wall -Wextra -Wshadow -Wfloat-equal -Wconversion
        -Wno-sign-conversion # we often compare int to size_t
        -Wvla # warn for variable length arrays
        # sanitizers
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        -fno-sanitize-recover=all
        # debug mode of STL
        # -D_GLIBCXX_DEBUG # set debug macro for libstdc++ (gcc std lib)
        # -D_LIBCPP_DEBUG # set debug macro for libc++ (clang std lib)
    )
    add_link_options(
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        # to fix GCC ASAN with certain linux kernel versions
        # unfortunately the current devcontainer needs this
        # see: https://github.com/google/sanitizers/issues/856
        -no-pie
    )
endif()

add_executable(main main.cpp)
