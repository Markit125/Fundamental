cmake_minimum_required(VERSION 3.20)

project(Curse_work C CXX)

if (MSVC)
add_compile_options(/W4 /WX)
else()
add_compile_options(-Wall -Wextra -pedantic -Werror -ld -Wno-unused-variable -Wno-unused-parameter -w -fcompare-debug-second)
endif()

set(CMAKE_CXX_STANDARD 14)

add_executable(
    cw
        ../source/main.cpp
        
        ../source/memory/3/source/memory_with_list/memory_with_list.h
        ../source/memory/3/source/memory_with_list/memory_with_list.cpp

        ../source/memory/4/source/memory_with_descriptors/memory_with_descriptors.h
        ../source/memory/4/source/memory_with_descriptors/memory_with_descriptors.cpp
        
        ../source/logger/source/logger/concrete/json.hpp
        ../source/logger/source/logger/prototypes/logger.h
        ../source/logger/source/logger/prototypes/logger.cpp
        ../source/logger/source/logger/prototypes/logger_builder.h
        ../source/logger/source/logger/prototypes/logger_builder.cpp
        ../source/logger/source/logger/concrete/logger_builder_concrete.h
        ../source/logger/source/logger/concrete/logger_builder_concrete.cpp
        ../source/logger/source/logger/concrete/logger_concrete.h
        ../source/logger/source/logger/concrete/logger_concrete.cpp
        ../source/logger/source/logger/complete/complete_logger.h
        ../source/logger/source/logger/complete/complete_logger.cpp
        ../source/logger/source/time/my_time.cpp
        ../source/logger/source/time/my_time.h

        ../source/memory/2/source/memory/memory.h
        ../source/memory/2/source/memory/memory.cpp
        ../source/memory/2/source/allocator/allocator.h
        ../source/memory/2/source/allocator/allocator.cpp

        ../source/tree/11/source/allocator/safe_allocator.h
        ../source/tree/11/source/allocator/safe_allocator.cpp
        
        ../source/tree/11/source/tree/binary_search_tree.h
        ../source/tree/11/source/tree/binary_search_tree.cpp
        ../source/tree/11/source/tree/associative_container.h

        ../source/tree/12/source/avl/avl.h
        ../source/tree/12/source/avl/avl.cpp

        ../source/file_opening/file_opening.h
        ../source/file_opening/file_opening.cpp

        ../source/processing/processing.h
        ../source/processing/processing.cpp

        ../source/data/data_type/data_type.h

        ../source/data/database/database.h
        ../source/data/database/database.cpp

        ../source/data/pool/pool.h
        ../source/data/pool/pool.cpp

        ../source/data/scheme/scheme.h
        ../source/data/scheme/scheme.cpp

        ../source/data/collection/collection.h
        ../source/data/collection/collection.cpp



)

target_include_directories(
    cw
    PRIVATE
        ../source/logger/source/logger/complete/
        ../source/logger/source/logger/concrete/
        ../source/logger/source/logger/prototypes/
        ../source/logger/source/time/
        ../source/logger/source/logger/
        ../source/memory/2/source/memory/
        ../source/memory/2/source/allocator/
        ../source/memory/3/source/memory_with_list/
        ../source/tree/11/source/tree/
        ../source/tree/11/source/allocator/
        ../source/tree/12/source/avl/
        ../source/tree/12/source
        ../source/
)