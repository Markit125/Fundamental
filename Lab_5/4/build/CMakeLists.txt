cmake_minimum_required(VERSION 3.20)

project(Lab-5-4 C CXX)

if (MSVC)
add_compile_options(/W4 /WX)
else()
add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(CMAKE_CXX_STANDARD 14)

add_executable(
    lab5-4
        ../source/main.cpp
        
        ../source/memory_with_descriptors/memory_with_descriptors.h
        ../source/memory_with_descriptors/memory_with_descriptors.cpp

        ../../1/source/logger/concrete/logger_builder_concrete.h
        ../../1/source/logger/concrete/logger_builder_concrete.cpp
        ../../1/source/logger/concrete/logger_concrete.h
        ../../1/source/logger/concrete/logger_concrete.cpp

        ../../1/source/logger/complete/complete_logger.h
        ../../1/source/logger/complete/complete_logger.cpp
        
        ../../1/source/logger/concrete/json.hpp
        ../../1/source/logger/prototypes/logger.h
        ../../1/source/logger/prototypes/logger.cpp
        ../../1/source/logger/prototypes/logger_builder.h
        ../../1/source/logger/prototypes/logger_builder.cpp
        ../../1/source/time/my_time.cpp
        ../../1/source/time/my_time.h

        ../../2/source/memory/memory.h
        ../../2/source/memory/memory.cpp
        ../../2/source/allocator/allocator.h
        ../../2/source/allocator/allocator.cpp
        
)

target_include_directories(
    lab5-4
    PRIVATE
    ../source/memory_with_descriptors/
    ../../1/source/logger/concrete/
    ../../1/source/logger/prototypes/
    ../../1/source/time/
    ../../1/source/logger/
    ../../2/source/memory/
    ../../2/source/allocator/
)