cmake_minimum_required(VERSION 3.20)

project(Lab-5-3 C CXX)

if (MSVC)
add_compile_options(/W4 /WX)
else()
add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(CMAKE_CXX_STANDARD 14)

add_executable(
    lab5-3
        ../source/main.cpp

        ../source/memory_with_list/memory_with_list.h
        ../source/memory_with_list/memory_with_list.cpp
        
        ../../../logger/source/logger/concrete/logger_builder_concrete.h
        ../../../logger/source/logger/concrete/logger_builder_concrete.cpp
        ../../../logger/source/logger/concrete/logger_concrete.h
        ../../../logger/source/logger/concrete/logger_concrete.cpp

        ../../../logger/source/logger/complete/complete_logger.h
        ../../../logger/source/logger/complete/complete_logger.cpp
        
        ../../../logger/source/logger/concrete/json.hpp
        ../../../logger/source/logger/prototypes/logger.h
        ../../../logger/source/logger/prototypes/logger.cpp
        ../../../logger/source/logger/prototypes/logger_builder.h
        ../../../logger/source/logger/prototypes/logger_builder.cpp
        ../../../logger/source/time/my_time.cpp
        ../../../logger/source/time/my_time.h

        ../../2/source/memory/memory.h
        ../../2/source/memory/memory.cpp
        ../../2/source/allocator/allocator.h
        ../../2/source/allocator/allocator.cpp
)

target_include_directories(
    lab5-3
    PRIVATE
    ../../../logger/source/logger/complete/
    ../../../logger/source/logger/concrete/
    ../../../logger/source/logger/prototypes/
    ../../../logger/source/time/
    ../../../logger/source/logger/
    ../../2/source/memory/
    ../../2/source/allocator
    ../source/memory_with_list/
)