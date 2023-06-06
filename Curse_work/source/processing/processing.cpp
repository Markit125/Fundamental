#include <sstream>
#include <stdexcept>
#include <string>
#include "processing.h"


// int process_file(database *&db, std::string &filename, logging::logger *logger) {
int process_file(database *&db, std::stringstream &in_stream, std::stringstream &out_stream, logging::logger *logger) {

    std::string word;

    std::vector<std::string> query(4);

    out_stream << "\n-----------------\n\n";

    while (get_word(in_stream, word)) {

        if (word == "create") {

            if (!get_word(in_stream, word)) {
                out_stream << "Expected container type" << std::endl; break;
            }
            
            if (word == "pool") {

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected allocator type [ GH | DF | DB | DW | LF | LB | LW ]" << std::endl; break;
                }
                // allocator
                query[1] = word;

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected pool name" << std::endl; break;
                }
                // pool
                query[0] = word;

                if (!validate(word)) {
                    out_stream << "Pool name contains denied symbols" << std::endl; break;
                }

                try {
                    db->create_pool(query);
                    if (logger) logger->log("created pool outside", logging::logger::severity::debug);
                } catch (std::runtime_error &ex) {
                    out_stream << ex.what() << std::endl;
                }

            } else if (word == "scheme") {

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected pool name" << std::endl; break;
                }
                // pool
                query[0] = word;

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected scheme name" << std::endl; break;
                }
                // scheme
                query[1] = word;

                if (!validate(word)) {
                    out_stream << "Pool name contains denied symbols" << std::endl; break;
                }

                try {
                    db->create_scheme(query);
                    if (logger) logger->log("created scheme outside", logging::logger::severity::debug);
                } catch (std::runtime_error &ex) {
                    out_stream << ex.what() << std::endl;
                }

            } else if (word == "collection") {

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected pool name" << std::endl; break;
                }
                // pool
                query[0] = word;

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected scheme name" << std::endl; break;
                }
                // scheme
                query[1] = word;

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected collection name" << std::endl; break;
                }
                // collecion
                query[2] = word;

                if (!validate(word)) {
                    out_stream << "Pool name contains denied symbols" << std::endl; break;
                }

                try {
                    db->create_collection(query);
                    if (logger) logger->log("created collection outside", logging::logger::severity::debug);
                } catch (std::runtime_error &ex) {
                    out_stream << ex.what() << std::endl;
                }
            

            } else if (word == "note") {

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected pool name" << std::endl; break;
                }
                // pool
                query[0] = word;

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected scheme name" << std::endl; break;
                }
                // scheme
                query[1] = word;

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected collection name" << std::endl; break;
                }
                // collection
                query[2] = word;

                // note
                try {
                    db->create_note(in_stream, query);
                    if (logger) logger->log("created note outside", logging::logger::severity::debug);
                } catch (std::runtime_error &ex) {
                    out_stream << ex.what() << std::endl;
                }

            } else {
                out_stream << "No such container: " << word << std::endl;
            }

        } else if (word == "delete") {
            
            if (!get_word(in_stream, word)) {
                out_stream << "Expected container type" << std::endl; break;
            }
                
            if (word == "pool") {

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected pool name";
                }
                // pool
                query[0] = word;

                try {
                    db->delete_pool(query);
                    if (logger) logger->log("deleted pool outside", logging::logger::severity::debug);
                } catch (std::runtime_error &ex) {
                    out_stream << ex.what() << std::endl;
                }

            } else if (word == "scheme") {

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected pool name" << std::endl; break;
                }
                // pool
                query[0] = word;

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected scheme name" << std::endl; break;
                }
                // scheme
                query[1] = word;

                try {
                    db->delete_scheme(query);
                    if (logger) logger->log("deleted scheme outside", logging::logger::severity::debug);
                } catch (std::runtime_error &ex) {
                    out_stream << ex.what() << std::endl;
                }
                
            } else if (word == "collection") {

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected pool name" << std::endl; break;
                }
                // pool
                query[0] = word;

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected scheme name" << std::endl; break;
                }
                // scheme
                query[1] = word;

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected collection name" << std::endl; break;
                }
                // collection
                query[2] = word;

                try {
                    db->delete_collection(query);
                    if (logger) logger->log("deleted collection outside", logging::logger::severity::debug);
                } catch (std::runtime_error &ex) {
                    out_stream << ex.what() << std::endl;
                }
                    
            } else if (word == "note") {

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected pool name" << std::endl; break;
                }
                // pool
                query[0] = word;

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected scheme name" << std::endl; break;
                }
                // scheme
                query[1] = word;

                if (!get_word(in_stream, word)) {
                    out_stream << "Expected collection name" << std::endl; break;
                }
                // collecion
                query[2] = word;

                // note
                try {
                    db->delete_note(in_stream, query);
                    if (logger) logger->log("deleted note outside", logging::logger::severity::debug);
                } catch (std::runtime_error &ex) {
                    out_stream << ex.what() << std::endl;
                }

            } else {
                out_stream << "No such container: " << word << std::endl;
            }


        } else if (word == "read") {

            if (!get_word(in_stream, word)) {
                out_stream << "Expected pool name" << std::endl; break;
            }
            // pool
            query[0] = word;

            if (!get_word(in_stream, word)) {
                out_stream << "Expected scheme name" << std::endl; break;
            }
            // scheme
            query[1] = word;

            if (!get_word(in_stream, word)) {
                out_stream << "Expected collection name" << std::endl; break;
            }
            // collecion
            query[2] = word;

            // note
            try {
                db->read_note(in_stream, out_stream, query);
                if (logger) logger->log("read note outside", logging::logger::severity::debug);
            } catch (std::runtime_error &ex) {
                out_stream << ex.what() << std::endl;
            }

        } else if (word == "read_range") {

            if (!get_word(in_stream, word)) {
                out_stream << "Expected pool name" << std::endl; break;
            }
            // pool
            query[0] = word;

            if (!get_word(in_stream, word)) {
                out_stream << "Expected scheme name" << std::endl; break;
            }
            // scheme
            query[1] = word;

            if (!get_word(in_stream, word)) {
                out_stream << "Expected collection name" << std::endl; break;
            }
            // collecion
            query[2] = word;

            // note
            try {
                db->read_note_range(in_stream, out_stream, query);
                if (logger) logger->log("read note range outside", logging::logger::severity::debug);
            } catch (std::runtime_error &ex) {
                out_stream << ex.what() << std::endl;
            }
            
        } else {
            out_stream << "No such command: " << word << std::endl;
        }
    }

    if (logger) logger->log("EnD", logging::logger::severity::debug);

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