#include "logger/configure/configure_file.h"


int main() {
    logging::logger_builder* builder = new logger_builder_concrete();

    logging::logger *constructed_logger = builder
        ->add_stream("file1.txt", logging::logger::severity::critical)
        ->add_stream("file2.txt", logging::logger::severity::debug)
        ->add_stream("file3.txt", logging::logger::severity::trace)
        ->construct();

    logging::logger *constructed_logger_2 = builder
        ->add_stream("file4.txt", logging::logger::severity::warning)
        ->add_stream("console", logging::logger::severity::information)
        ->construct();


    logging::logger *logger_from_configuration_file = builder->construct_configuration("../test_files/conf.json");

    if (logger_from_configuration_file == nullptr) {
        std::cout << "File corrupted!\n";
        constructed_logger->log("Configuration file is corrupted!", logging::logger::severity::critical);
        delete constructed_logger_2;
        delete constructed_logger;
        delete builder;

        return 1;
    }

    logger_from_configuration_file->log("GRANDI", logging::logger::severity::error);


    constructed_logger
        ->log("kek lol 123", logging::logger::severity::information);

    constructed_logger_2
        ->log("123 kek lol", logging::logger::severity::error);
        
    constructed_logger
        ->log("You are Giant", logging::logger::severity::critical);

    logger_from_configuration_file->log("Configurated", logging::logger::severity::trace);

    
    delete constructed_logger_2;
    delete constructed_logger;
    delete builder;

    return 0;
}