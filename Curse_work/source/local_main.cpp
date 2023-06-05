#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "processing/processing.h"
#include "logger/source/logger/concrete/logger_builder_concrete.h"


int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cout << "You should pass only filename with commands" << std::endl;
        return 1;
    }

    if (argc > 2) {
        std::cout << "You should pass only filename with commands" << std::endl;
        return 2;
    }


    logging::logger_builder *builder = new logger_builder_concrete();

    if (nullptr == builder) {
        std::cout << "Cannot allocate memory for builder" << std::endl;
        return -1;
    }


    logging::logger *logger;

    try {
        logger = builder->construct_configuration("../source/configuration/conf.json");
    } catch (std::runtime_error &ex) {
        std::cout << ex.what() << std::endl;
        return -2;
    }


    std::string filename = argv[1];

    std::ifstream file = open_file(filename);

    if (!file.is_open()) {
        std::cout << "File was not opened" << std::endl;
        return -3;
    }

    database *db = new database(logger);

    if (nullptr == db) {
        std::cout << "Cannot allocate memory for database" << std::endl;
        return -4;
    }

    std::stringstream ss;

    std::string word;
    while (file >> word) {
        ss << word << ' ';
    }

    std::cout << ss.str();

    process_file(db, ss, logger);



    delete builder;
    delete logger;

    return 0;
}