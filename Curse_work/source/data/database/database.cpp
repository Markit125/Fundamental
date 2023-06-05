#include "database.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// creating

int database::create_pool(std::vector<std::string> &query) {

    pool *new_pool = reinterpret_cast<pool *>(safe_allocate(sizeof(pool)));
    new (new_pool) pool(_allocator, _logger);
    safe_log("Memory for pool is allocated", logging::logger::severity::information);

    _pools->insert(query[0], std::move(new_pool));

    safe_log("Pool created", logging::logger::severity::information);

    return 0;
}


int database::create_scheme(std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    try {
        _pools->find(query[0], &pool_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    (*pool_found.second)->create_scheme(query);

    return 0;
}


int database::create_collection(std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    try {
        _pools->find(query[0], &pool_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    (*pool_found.second)->create_collection(query);
    
    return 0;
}


int database::create_note(std::ifstream &file, std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    try {
        _pools->find(query[0], &pool_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    (*pool_found.second)->create_note(file, query);
    
    return 0;
}


//reading

int database::read_note(std::ifstream &file, std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    try {
        _pools->find(query[0], &pool_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    (*pool_found.second)->read_note(file, query);

    return 0;
}


int database::read_note_range(std::ifstream &file, std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    try {
        _pools->find(query[0], &pool_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    (*pool_found.second)->read_note_range(file, query);

    return 0;
}

// deleting


int database::delete_pool(std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    try {
        _pools->find(query[0], &pool_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    _pools->remove(query[0]);

    safe_log("Pool removed", logging::logger::severity::information);

    return 0;
}


int database::delete_scheme(std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    try {
        _pools->find(query[0], &pool_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    (*pool_found.second)->delete_scheme(query);

    return 0;
}


int database::delete_collection(std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    try {
        _pools->find(query[0], &pool_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    (*pool_found.second)->delete_collection(query);
    
    return 0;
}


int database::delete_note(std::ifstream &file, std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    try {
        _pools->find(query[0], &pool_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    (*pool_found.second)->delete_note(file, query);
    
    return 0;
}



database::database(allocating::memory *allocator, logging::logger *logger)
    : _pools(new avl_tree<std::string, pool *, comparers>(allocator, logger)),
     _allocator(allocator), _logger(logger) {

}

database::~database() {
    std::cout << "GGGGGGGGGGGGGGGGGGGGGGGgg\n";
    safe_log("Database destructor", logging::logger::severity::warning);
    _pools->~associative_container();
    safe_log("Database destructor _pools destructed", logging::logger::severity::warning);
    safe_deallocate(_pools);
    
}


allocating::memory *database::get_allocator() const {
    return _allocator;
}


logging::logger *database::get_logger() const {
    return _logger;
}