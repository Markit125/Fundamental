#include "scheme.h"


allocating::memory *scheme::get_allocator() const {
    return _allocator;
}


logging::logger *scheme::get_logger() const {
    return _logger;
}


scheme::~scheme() {

    safe_log("Scheme destructor", logging::logger::severity::information);
    _collections->print_container();
    _collections->~associative_container();
    safe_deallocate(_collections);
}


scheme::scheme(allocating::memory *allocator, logging::logger *logger)
    : _allocator(allocator), _logger(logger) {

    _collections = reinterpret_cast<avl_tree<std::string, collection, comparers> *>(safe_allocate(sizeof(avl_tree<std::string, collection, comparers>)));
    new (_collections) avl_tree<std::string, collection, comparers>(allocator, logger);

    safe_log("Scheme constructor", logging::logger::severity::information);
}


// creating

int scheme::create_collection(std::vector<std::string> &query) {

    collection *new_collection = reinterpret_cast<collection *>(safe_allocate(sizeof(collection)));
    new (new_collection) collection(_allocator, _logger);
    safe_log("Memory for collection is allocated", logging::logger::severity::information);

    _collections->insert(query[2], std::move(*new_collection));

    safe_log("Collection created", logging::logger::severity::information);
    
    return 0;
}


int scheme::create_note(std::stringstream &file, std::vector<std::string> &query) {

    std::pair<std::string, collection *> collection_found;

    try {
        _collections->find(query[2], &collection_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Collection " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + "/" + cast_to_str(query[2]) + " doesn't exists!\n");
    }

    (*collection_found.second).create_note(file, query);    
    
    return 0;
}


// reading

int scheme::read_note(std::stringstream &file, std::stringstream &out_stream, std::vector<std::string> &query) {

    std::pair<std::string, collection *> collection_found;

    try {
        _collections->find(query[2], &collection_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Collection " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + "/" + cast_to_str(query[2]) + " doesn't exists!\n");
    }

    (*collection_found.second).read_note(file, out_stream, query);

    return 0;
}


int scheme::read_note_range(std::stringstream &file, std::stringstream &out_stream, std::vector<std::string> &query) {

    std::pair<std::string, collection *> collection_found;

    try {
        _collections->find(query[2], &collection_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Collection " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + "/" + cast_to_str(query[2]) + " doesn't exists!\n");
    }

    (*collection_found.second).read_note_range(file, out_stream, query);

    return 0;
}


// deleting

int scheme::delete_collection(std::vector<std::string> &query) {

    std::pair<std::string, collection *> collection_found;

    try {
        _collections->find(query[2], &collection_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Collection " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + "/" + cast_to_str(query[2]) + " doesn't exists!\n");
    }

    _collections->remove(query[2]);

    safe_log("Collection removed", logging::logger::severity::information);
    
    return 0;
}


int scheme::delete_note(std::stringstream &file, std::vector<std::string> &query) {

    std::pair<std::string, collection *> collection_found;

    try {
        _collections->find(query[2], &collection_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Collection " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + "/" + cast_to_str(query[2]) + " doesn't exists!\n");
    }

    (*collection_found.second).delete_note(file, query);

    return 0;
}

