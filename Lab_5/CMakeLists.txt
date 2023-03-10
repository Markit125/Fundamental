cmake_minimum_required(VERSION 3.20)

project(Fundamental C CXX)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include(FindThreads)


add_subdirectory(1)
