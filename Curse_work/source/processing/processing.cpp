#include <stdexcept>
#include "processing.h"


int process_file(std::string &filename, allocating::memory *allocator, logging::logger *logger) {

    std::ifstream file = open_file(filename);

    database *db = new database(allocator, logger);

    std::string word;

    bool fail;

    std::vector<std::string> query(4);

    while (file >> word) {

        fail = true;

        std::cout << word;

        // if (logger) logger->log("HERE", logging::logger::severity::information);

        if (word == "create") {


            if (file >> word) {
                
                if (word == "pool") {

                    if (file >> word) {
                        // pool

                        query[0] = word;

                        if (validate(word)) {
                            fail = db->create_pool(query);
                            if (logger) logger->log("created poll outside", logging::logger::severity::information);
                        }
                    }


                } else if (word == "scheme") {

                    if (file >> word) {
                        // pool

                        query[0] = word;

                        if (file >> word) {
                            // scheme

                            query[1] = word;

                            if (validate(word)) {
                                fail = db->create_scheme(query);
                                if (logger) logger->log("created scheme outside", logging::logger::severity::information);
                            }
                        }

                    }



                } else if (word == "collection") {

                    if (file >> word) {
                        // pool

                        query[0] = word;

                        if (file >> word) {
                            // scheme

                            query[1] = word;

                            if (file >> word) {
                                // collecion

                                query[2] = word;

                                if (validate(word)) {

                                    fail = db->create_collection(query);
                                    if (logger) logger->log("created collection outside", logging::logger::severity::information);

                                }
                            }

                        }

                    }




                } else {
                    throw std::runtime_error("No such container!");
                }
            }






        } else if (word == "delete") {
            







        } else {
            throw std::runtime_error("No such command!");
        }


        if (fail) {
            throw std::runtime_error("Invalid name!");
        }

    }


    if (logger) logger->log("EnD", logging::logger::severity::information);

    return 0;
}





int validate(std::string &string) {

    for (char c : string) {
        if (c == '\n' || c == '\t' || c == ' ') {
            return 0;
        }
    }

    return 1;
}