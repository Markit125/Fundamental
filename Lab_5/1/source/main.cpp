#include "logger/configure/configure_file.h"


int main() {
    logger_builder* builder = new logger_builder_concrete();
    configurator* conf = new configurator();

    logger *constructed_logger = builder
        ->add_stream("file1.txt", logger::severity::critical)
        ->add_stream("file2.txt", logger::severity::debug)
        ->add_stream("file3.txt", logger::severity::trace)
        ->construct();

    logger *constructed_logger_2 = builder
        ->add_stream("file4.txt", logger::severity::warning)
        ->add_stream("console", logger::severity::information)
        ->construct();


    logger *logger_from_configuration_file = conf->configure_from_file("../test_files/conf.txt");
    if (logger_from_configuration_file == nullptr) {
        std::cout << "File corrupted!\n";
        constructed_logger->log("Configuration file is corrupted!", logger::severity::critical);
        delete constructed_logger_2;
        delete constructed_logger;
        delete builder;

        return 1;
    }

    logger_from_configuration_file->log("GRANDI", logger::severity::error);


    constructed_logger
        ->log("kek lol 123", logger::severity::information);

    constructed_logger_2
        ->log("123 kek lol", logger::severity::error);
        
    constructed_logger
        ->log("You are Giant", logger::severity::critical);

    logger_from_configuration_file->log("Configurated", logger::severity::trace);

    
    delete constructed_logger_2;
    delete constructed_logger;
    delete builder;

    return 0;
}