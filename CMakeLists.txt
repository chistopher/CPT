
project(CPT)

# CMake version
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 17)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wshadow -Wfloat-equal)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(
                -fsanitize=address,undefined
                -fno-omit-frame-pointer
                -fno-sanitize-recover=all
        )
        add_link_options(
                -fsanitize=address,undefined
                -fno-omit-frame-pointer)
        # add_compile_definitions(_GLIBCXX_DEBUG) # gcc only
    endif()
endif()

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/source")
    add_subdirectory(source)
endif()
