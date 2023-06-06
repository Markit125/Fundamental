#include "pool.h"
#include <sstream>


allocating::memory *pool::get_allocator() const {
    return _allocator;
}


logging::logger *pool::get_logger() const {
    return _logger;
}


pool::~pool() {
    
    safe_log("Pool destructor", logging::logger::severity::warning);
    _schemes->print_container();
    _schemes->~associative_container();
    safe_deallocate(_schemes);
}


pool::pool(allocating::memory *allocator, logging::logger *logger)
    : _allocator(allocator), _logger(logger) {

    _schemes = reinterpret_cast<avl_tree<std::string, scheme, comparers> *>(safe_allocate(sizeof(avl_tree<std::string, scheme, comparers>)));
    new (_schemes) avl_tree<std::string, scheme, comparers>(allocator, logger);

    safe_log("Pool constructor", logging::logger::severity::warning);
}


// creating

int pool::create_scheme(std::vector<std::string> &query) {

    scheme *new_scheme = reinterpret_cast<scheme *>(safe_allocate(sizeof(scheme)));
    new (new_scheme) scheme(_allocator, _logger);
    safe_log("Memory for scheme is allocated", logging::logger::severity::information);

    _schemes->insert(query[1], std::move(*new_scheme));
    safe_log("Scheme created", logging::logger::severity::information);

    return 0;
}


int pool::create_collection(std::vector<std::string> &query) {

    std::pair<std::string, scheme *> scheme_found;

    try {
        _schemes->find(query[1], &scheme_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Scheme " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + " doesn't exists!\n");
    }

    (*scheme_found.second).create_collection(query);
    
    return 0;
}


int pool::create_note(std::stringstream &file, std::vector<std::string> &query) {

    std::pair<std::string, scheme *> scheme_found;

    try {
        _schemes->find(query[1], &scheme_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Scheme " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + " doesn't exists!\n");
    }

    (*scheme_found.second).create_note(file, query);
    
    return 0;
}


// reading

int pool::read_note(std::stringstream &file, std::stringstream &out_stream, std::vector<std::string> &query) {

    std::pair<std::string, scheme *> scheme_found;

    try {
        _schemes->find(query[1], &scheme_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Scheme " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + " doesn't exists!\n");
    }

    (*scheme_found.second).read_note(file, out_stream, query);

    return 0;
}


int pool::read_note_range(std::stringstream &file, std::stringstream &out_stream, std::vector<std::string> &query) {

    std::pair<std::string, scheme *> scheme_found;

    try {
        _schemes->find(query[1], &scheme_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Scheme " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + " doesn't exists!\n");
    }

    (*scheme_found.second).read_note_range(file, out_stream, query);

    return 0;
}


// deleting

int pool::delete_scheme(std::vector<std::string> &query) {

    std::pair<std::string, scheme *> scheme_found;

    try {
        _schemes->find(query[1], &scheme_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Scheme " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + " doesn't exists!\n");
    }

    _schemes->remove(query[1]);
    safe_log("Scheme removed", logging::logger::severity::information);

    return 0;
}


int pool::delete_collection(std::vector<std::string> &query) {

    std::pair<std::string, scheme *> scheme_found;

    try {
        _schemes->find(query[1], &scheme_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Scheme " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + " doesn't exists!\n");
    }

    (*scheme_found.second).delete_collection(query);

    return 0;
}


int pool::delete_note(std::stringstream &file, std::vector<std::string> &query) {

    std::pair<std::string, scheme *> scheme_found;

    try {
        _schemes->find(query[1], &scheme_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Scheme " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + " doesn't exists!\n");
    }

    (*scheme_found.second).delete_note(file, query);

    return 0;
}

