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
        ../../1/source/logger/concrete/logger_builder_concrete.h
        ../../1/source/logger/concrete/logger_builder_concrete.cpp
        ../../1/source/logger/concrete/logger_concrete.h
        ../../1/source/logger/concrete/logger_concrete.cpp
        ../../1/source/logger/concrete/json.hpp
        ../../1/source/logger/prototypes/logger.h
        ../../1/source/logger/prototypes/logger.cpp
        ../../1/source/logger/prototypes/logger_builder.h
        ../../1/source/logger/prototypes/logger_builder.cpp
        ../../1/source/time/my_time.cpp
        ../../1/source/time/my_time.h
)