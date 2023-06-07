cmake_minimum_required(VERSION 3.20)

project(Curse_work C CXX)

if (MSVC)
add_compile_options(/W4 /WX)
else()
add_compile_options(-Wall -Wextra -pedantic -Werror -ld -Wno-unused-variable -Wno-unused-parameter -w -fcompare-debug-second)
endif()

set(CMAKE_CXX_STANDARD 14)

add_executable(
    client
        ../main.cpp

        ../../logger/source/logger/concrete/logger_builder_concrete.h
        ../../logger/source/logger/prototypes/logger.h
        
        ../../logger/source/logger/concrete/json.hpp
        ../../logger/source/logger/prototypes/logger.h
        ../../logger/source/logger/prototypes/logger.cpp
        ../../logger/source/logger/prototypes/logger_builder.h
        ../../logger/source/logger/prototypes/logger_builder.cpp
        ../../logger/source/logger/concrete/logger_builder_concrete.h
        ../../logger/source/logger/concrete/logger_builder_concrete.cpp
        ../../logger/source/logger/concrete/logger_concrete.h
        ../../logger/source/logger/concrete/logger_concrete.cpp
        ../../logger/source/logger/complete/complete_logger.h
        ../../logger/source/logger/complete/complete_logger.cpp

        ../../logger/source/time/my_time.cpp
        ../../logger/source/time/my_time.h


)