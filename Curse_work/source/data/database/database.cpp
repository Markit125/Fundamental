#include "database.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>



// constructor destructor

database::database(logging::logger *logger)
    : _logger(logger) {

    // _pools = reinterpret_cast<avl_tree<std::string, pool, comparers> *>(safe_allocate(sizeof(avl_tree<std::string, pool, comparers>)));
    // new (_pools) avl_tree<std::string, pool, comparers>(nullptr, logger);
    _pools = new avl_tree<std::string, pool, comparers>(nullptr, logger);
    
    safe_log("Database constructor", logging::logger::severity::warning);
}

database::~database() {
    
    safe_log("Database destructor", logging::logger::severity::warning);
    delete _pools;
    
}

// creating

int database::create_pool(std::vector<std::string> &query) {


    bool fail = true;

    allocating::memory *allocator = nullptr;
    allocating::memory::fit_type fit;

    if (query[1] == "GH") {
        fail = false;
    } else if (query[1][0] == 'D' || query[1][0] == 'L') {

        fail = false;

        if (query[1][1] == 'B') {
            fit = allocating::memory::fit_type::best;
        } else if (query[1][1] == 'W') {
            fit = allocating::memory::fit_type::worst;
        } else if (query[1][1] == 'F') {
            fit = allocating::memory::fit_type::first;
        } else {
            fail = true;
        }

        if (query[1][0] == 'D') {
            allocator = new allocating::memory_with_descriptors(2048000, nullptr, _logger, fit);
        } else if (query[1][0] == 'L') {
            allocator = new allocating::memory_with_list(2048000, nullptr, _logger, fit);
        }
    }

    if (fail) {
        throw std::runtime_error("Wrong allocator type!");
    }


    pool *new_pool;

    if (nullptr == allocator) {
        new_pool = new pool(allocator, _logger);
    } else {
        new_pool = reinterpret_cast<pool *>(allocator->allocate(sizeof(pool)));
        new (new_pool) pool(allocator, _logger);
    }


if (_logger) _logger->log("FULL", logging::logger::severity::warning);

    
    safe_log("Memory for pool is allocated", logging::logger::severity::information);

    _pools->insert(query[0], std::move(*new_pool));

    safe_log("Pool created", logging::logger::severity::information);

    return 0;
}


int database::create_scheme(std::vector<std::string> &query) {

    std::pair<std::string, pool *> pool_found;

    try {
        _pools->find(query[0], &pool_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    (*pool_found.second).create_scheme(query);

    return 0;
}


int database::create_collection(std::vector<std::string> &query) {

    std::pair<std::string, pool *> pool_found;

    try {
        _pools->find(query[0], &pool_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    (*pool_found.second).create_collection(query);
    
    return 0;
}


int database::create_note(std::ifstream &file, std::vector<std::string> &query) {

    std::pair<std::string, pool *> pool_found;

    try {
        _pools->find(query[0], &pool_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    (*pool_found.second).create_note(file, query);
    
    return 0;
}


//reading

int database::read_note(std::ifstream &file, std::vector<std::string> &query) {

    std::pair<std::string, pool *> pool_found;

    try {
        _pools->find(query[0], &pool_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    (*pool_found.second).read_note(file, query);

    return 0;
}


int database::read_note_range(std::ifstream &file, std::vector<std::string> &query) {

    std::pair<std::string, pool *> pool_found;

    try {
        _pools->find(query[0], &pool_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    (*pool_found.second).read_note_range(file, query);

    return 0;
}

// deleting


int database::delete_pool(std::vector<std::string> &query) {

    std::pair<std::string, pool *> pool_found;

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

    std::pair<std::string, pool *> pool_found;

    try {
        _pools->find(query[0], &pool_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    (*pool_found.second).delete_scheme(query);

    return 0;
}


int database::delete_collection(std::vector<std::string> &query) {

    std::pair<std::string, pool *> pool_found;

    try {
        _pools->find(query[0], &pool_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    (*pool_found.second).delete_collection(query);
    
    return 0;
}


int database::delete_note(std::ifstream &file, std::vector<std::string> &query) {

    std::pair<std::string, pool *> pool_found;

    try {
        _pools->find(query[0], &pool_found);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    (*pool_found.second).delete_note(file, query);
    
    return 0;
}

logging::logger *database::get_logger() const {
    return _logger;
}