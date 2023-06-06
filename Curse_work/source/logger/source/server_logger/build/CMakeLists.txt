cmake_minimum_required(VERSION 3.20)

project(Server_logger C CXX)

if (MSVC)
add_compile_options(/W4 /WX)
else()
add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(CMAKE_CXX_STANDARD 14)

add_executable(
    server_logger
        ../source/main.cpp
        ../source/logger/server_logger.h
        ../source/logger/server_logger.cpp
        ../source/builder/logger_server_builder_concrete.h
        ../source/builder/logger_server_builder_concrete.cpp

        ../source/builder/json.hpp
        ../../logger/prototypes/logger.h
        ../../logger/prototypes/logger.cpp
        ../../logger/prototypes/logger_builder.h
        ../../logger/prototypes/logger_builder.cpp
        ../../time/my_time.cpp
        ../../time/my_time.h
)