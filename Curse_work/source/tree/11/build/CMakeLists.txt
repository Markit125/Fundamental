cmake_minimum_required(VERSION 3.20)

project(Lab-5-11 C CXX)

if (MSVC)
add_compile_options(/W4 /WX)
else()
add_compile_options(-Wall -Wextra -pedantic -Werror -ld)
endif()

set(CMAKE_CXX_STANDARD 14)

add_executable(
    lab5-11
        ../source/main.cpp
        ../../../memory/3/source/memory_with_list/memory_with_list.h
        ../../../memory/3/source/memory_with_list/memory_with_list.cpp

        ../../../memory/4/source/memory_with_descriptors/memory_with_descriptors.h
        ../../../memory/4/source/memory_with_descriptors/memory_with_descriptors.cpp
        
        ../../../logger/source/logger/concrete/json.hpp
        ../../../logger/source/logger/prototypes/logger.h
        ../../../logger/source/logger/prototypes/logger.cpp
        ../../../logger/source/logger/prototypes/logger_builder.h
        ../../../logger/source/logger/prototypes/logger_builder.cpp
        ../../../logger/source/logger/concrete/logger_builder_concrete.h
        ../../../logger/source/logger/concrete/logger_builder_concrete.cpp
        ../../../logger/source/logger/concrete/logger_concrete.h
        ../../../logger/source/logger/concrete/logger_concrete.cpp
        ../../../logger/source/logger/complete/complete_logger.h
        ../../../logger/source/logger/complete/complete_logger.cpp
        ../../../logger/source/time/my_time.cpp
        ../../../logger/source/time/my_time.h

        ../../../memory/2/source/memory/memory.h
        ../../../memory/2/source/memory/memory.cpp
        ../../../memory/2/source/allocator/allocator.h
        ../../../memory/2/source/allocator/allocator.cpp

        ../source/allocator/safe_allocator.h
        ../source/allocator/safe_allocator.cpp
        
        ../source/tree/binary_search_tree.h
        ../source/tree/binary_search_tree.cpp
        ../source/tree/associative_container.h

)

target_include_directories(
    lab5-11
    PRIVATE
        ../../../logger/source/logger/complete/
        ../../../logger/source/logger/concrete/
        ../../../logger/source/logger/prototypes/
        ../../../logger/source/time/
        ../../../logger/source/logger/
        ../../../memory/2/source/memory/
        ../../../memory/2/source/allocator/
        ../../../memory/3/source/memory_with_list/
        ../../../memory/4/source/memory_with_descriptors/
        ../source/tree/
        ../source/exception/
        ../source/allocator/
        ../source
)