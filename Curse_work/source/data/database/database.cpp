#include "database.h"
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// creating

int database::create_pool(std::vector<std::string> &query) {

    pool *new_pool = reinterpret_cast<pool *>(safe_allocate(sizeof(pool)));
    new (new_pool) pool;
    safe_log("Memory for pool is allocated", logging::logger::severity::information);

    _data_bases->insert(query[0], std::move(new_pool));

    safe_log("Pool created", logging::logger::severity::information);

    return 0;
}


int database::create_scheme(std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    if (!(_data_bases->find(query[0], &pool_found))) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }


    scheme *new_scheme = reinterpret_cast<scheme *>(safe_allocate(sizeof(scheme)));
    new (new_scheme) scheme;
    safe_log("Memory for scheme is allocated", logging::logger::severity::information);

    (*pool_found.second)->_pools->insert(query[1], std::move(new_scheme));
    safe_log("Scheme created", logging::logger::severity::information);

    return 0;
}


int database::create_collection(std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    if (!(_data_bases->find(query[0], &pool_found))) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    std::pair<std::string, scheme **> scheme_found;

    if (!((*pool_found.second)->_pools->find(query[1], &scheme_found))) {
        throw std::runtime_error("Scheme " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + " doesn't exists!\n");
    }

    collection *new_collection = reinterpret_cast<collection *>(safe_allocate(sizeof(collection)));
    new (new_collection) collection;
    safe_log("Memory for collection is allocated", logging::logger::severity::information);

    (*scheme_found.second)->_schemes->insert(query[2], std::move(new_collection));

    safe_log("Collection created", logging::logger::severity::information);
    
    return 0;
}


// deleting


int database::delete_pool(std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    if (!(_data_bases->find(query[0], &pool_found))) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    _data_bases->remove(query[0]);

    safe_log("Pool removed", logging::logger::severity::information);

    return 0;
}


int database::delete_scheme(std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    if (!(_data_bases->find(query[0], &pool_found))) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    std::pair<std::string, scheme **> scheme_found;

    if (!((*pool_found.second)->_pools->find(query[1], &scheme_found))) {
        throw std::runtime_error("Scheme " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + " doesn't exists!\n");
    }

    (*pool_found.second)->_pools->remove(query[1]);
    safe_log("Scheme removed", logging::logger::severity::information);

    return 0;
}


int database::delete_collection(std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    if (!(_data_bases->find(query[0], &pool_found))) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    std::pair<std::string, scheme **> scheme_found;

    if (!((*pool_found.second)->_pools->find(query[1], &scheme_found))) {
        throw std::runtime_error("Scheme " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + " doesn't exists!\n");
    }

    std::pair<std::string, collection **> collection_found;

    if (!((*scheme_found.second)->_schemes->find(query[2], &collection_found))) {
        throw std::runtime_error("Collection " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + "/" + cast_to_str(query[2]) + " doesn't exists!\n");
    }


    (*scheme_found.second)->_schemes->remove(query[2]);

    safe_log("Collection removed", logging::logger::severity::information);
    
    return 0;
}

database::database(allocating::memory *allocator, logging::logger *logger)
    : _data_bases(new avl_tree<std::string, pool *, comparers>(allocator, logger)),
     _allocator(allocator), _logger(logger) {

}

database::~database() {
    delete _data_bases;
}


allocating::memory *database::get_allocator() const {
    return _allocator;
}


logging::logger *database::get_logger() const {
    return _logger;
}