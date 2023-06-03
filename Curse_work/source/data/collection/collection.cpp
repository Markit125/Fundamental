#include "collection.h"


allocating::memory *collection::get_allocator() const {
    return _allocator;
}


logging::logger *collection::get_logger() const {
    return _logger;
}


collection::~collection() {
    delete _collections;
}


collection::collection(allocating::memory *allocator, logging::logger *logger)
    : _collections(new avl_tree<type_key, type_value, comparers>(allocator, logger)),
     _allocator(allocator), _logger(logger) {

}