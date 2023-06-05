#include <iostream>
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

    // allocating::memory *allocator = new allocating::memory_with_descriptors(
    //         2048000, nullptr, logger, allocating::memory::fit_type::first
    //     );

    // allocating::memory *allocator = new allocating::memory_with_list(
    //         2048000, nullptr, logger, allocating::memory::fit_type::first
    //     );

        // allocator = nullptr;

    std::string filename = argv[1];
    process_file(filename, logger);



    // delete builder;
    // delete logger;

    return 0;
}