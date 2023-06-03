#include "database.h"
#include <string>
#include <utility>
#include <vector>


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
        return 1;
    }


    scheme *new_scheme = reinterpret_cast<scheme *>(safe_allocate(sizeof(scheme)));
    new (new_scheme) scheme;
    safe_log("Memory for scheme is allocated", logging::logger::severity::information);
    

    safe_log(cast_to_str((pool_found.first)), logging::logger::severity::information);
    safe_log(cast_to_str((*(pool_found.second))->_pools), logging::logger::severity::information);
    // TODO zero pointer         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^


    (*pool_found.second)->_pools->insert(query[1], std::move(new_scheme));
safe_log("HEEEEEEEEE", logging::logger::severity::information);
    safe_log("Scheme created", logging::logger::severity::information);

    return 0;
}


int database::create_collection(std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    if (!(_data_bases->find(query[0], &pool_found))) {
        return 1;
    }

    std::pair<std::string, scheme **> scheme_found;

    if (!((*pool_found.second)->_pools->find(query[1], &scheme_found))) {
        return 2;
    }

    collection *new_collection = reinterpret_cast<collection *>(safe_allocate(sizeof(collection)));
    new (new_collection) collection;
    safe_log("Memory for collection is allocated", logging::logger::severity::information);

    (*scheme_found.second)->_schemes->insert(query[2], std::move(new_collection));

    safe_log("Collection created", logging::logger::severity::information);
    
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