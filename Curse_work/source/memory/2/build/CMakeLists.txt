cmake_minimum_required(VERSION 3.20)

project(Lab-5-2 C CXX)

if (MSVC)
add_compile_options(/W4 /WX)
else()
add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(CMAKE_CXX_STANDARD 17)

add_executable(
    lab5-2
        ../source/main.cpp
        ../source/allocator/allocator.h
        ../source/allocator/allocator.cpp
        ../source/memory/memory.h
        ../source/memory/memory.cpp
        ../../../logger/source/logger/concrete/logger_builder_concrete.h
        ../../../logger/source/logger/concrete/logger_builder_concrete.cpp
        ../../../logger/source/logger/concrete/logger_concrete.h
        ../../../logger/source/logger/concrete/logger_concrete.cpp
        ../../../logger/source/logger/concrete/json.hpp
        ../../../logger/source/logger/prototypes/logger.h
        ../../../logger/source/logger/prototypes/logger.cpp
        ../../../logger/source/logger/prototypes/logger_builder.h
        ../../../logger/source/logger/prototypes/logger_builder.cpp
        ../../../logger/source/time/my_time.cpp
        ../../../logger/source/time/my_time.h
)