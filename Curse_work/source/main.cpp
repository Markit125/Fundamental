#include <iostream>
#include "memory/4/source/memory_with_descriptors/memory_with_descriptors.h"
#include "processing/processing.h"
#include "logger/source/logger/concrete/logger_builder_concrete.h"


int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cout << "You should pass filename with arguments" << std::endl;
        return 1;
    }


    logging::logger_builder *builder = new logger_builder_concrete();
    logging::logger *logger =
        builder->construct_configuration("../source/configuration/conf.json");

    allocating::memory *allocator = new allocating::memory_with_descriptors(
            2048000, nullptr, logger, allocating::memory::fit_type::first
        );


    std::string filename = argv[1];
    process_file(filename, allocator, logger);



    delete builder;
    delete allocator;
    delete logger;

    return 0;
}