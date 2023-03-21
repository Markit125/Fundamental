cmake_minimum_required(VERSION 3.20)

project(Lab-5-1 C CXX)

if (MSVC)
add_compile_options(/W4 /WX)
else()
add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(CMAKE_CXX_STANDARD 17)

add_executable(
    lab5-1
        ../source/main.cpp
        ../source/logger/concrete/logger_builder_concrete.h
        ../source/logger/concrete/logger_builder_concrete.cpp
        ../source/logger/concrete/logger_concrete.h
        ../source/logger/concrete/logger_concrete.cpp
        ../source/logger/concrete/json.hpp
        ../source/logger/prototypes/logger.h
        ../source/logger/prototypes/logger.cpp
        ../source/logger/prototypes/logger_builder.h
        ../source/logger/prototypes/logger_builder.cpp
        ../source/time/my_time.cpp
        ../source/time/my_time.h
        ../source/logger/configure/configure_file.h
        ../source/logger/configure/configure_file.cpp
)