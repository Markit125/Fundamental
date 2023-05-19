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
        ../../3/source/memory_with_list/memory_with_list.h
        ../../3/source/memory_with_list/memory_with_list.cpp

        ../../4/source/memory_with_descriptors/memory_with_descriptors.h
        ../../4/source/memory_with_descriptors/memory_with_descriptors.cpp
        
        ../../1/source/logger/concrete/json.hpp
        ../../1/source/logger/prototypes/logger.h
        ../../1/source/logger/prototypes/logger.cpp
        ../../1/source/logger/prototypes/logger_builder.h
        ../../1/source/logger/prototypes/logger_builder.cpp
        ../../1/source/logger/concrete/logger_builder_concrete.h
        ../../1/source/logger/concrete/logger_builder_concrete.cpp
        ../../1/source/logger/concrete/logger_concrete.h
        ../../1/source/logger/concrete/logger_concrete.cpp
        ../../1/source/logger/complete/complete_logger.h
        ../../1/source/logger/complete/complete_logger.cpp
        ../../1/source/time/my_time.cpp
        ../../1/source/time/my_time.h

        ../../2/source/memory/memory.h
        ../../2/source/memory/memory.cpp
        ../../2/source/allocator/allocator.h
        ../../2/source/allocator/allocator.cpp

        ../source/allocator/safe_allocator.h
        ../source/allocator/safe_allocator.cpp

        # ../source/exception/not_implemented.h
        # ../source/exception/not_implemented.cpp
        
        ../source/tree/binary_search_tree.h
        ../source/tree/binary_search_tree.cpp
        ../source/tree/associative_container.h

)

target_include_directories(
    lab5-11
    PRIVATE
        ../../1/source/logger/complete/
        ../../1/source/logger/concrete/
        ../../1/source/logger/prototypes/
        ../../1/source/time/
        ../../1/source/logger/
        ../../2/source/memory/
        ../../2/source/allocator/
        ../../3/source/memory_with_list/
        ../../4/source/memory_with_descriptors/
        ../source/tree/
        ../source/exception/
        ../source/allocator/
        ../source
)