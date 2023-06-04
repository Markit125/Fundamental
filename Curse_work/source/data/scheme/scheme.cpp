#include "scheme.h"


allocating::memory *scheme::get_allocator() const {
    return _allocator;
}


logging::logger *scheme::get_logger() const {
    return _logger;
}


scheme::~scheme() {
    delete _collections;
}


scheme::scheme(allocating::memory *allocator, logging::logger *logger)
    : _collections(new avl_tree<std::string, collection *, comparers>(allocator, logger)),
     _allocator(allocator), _logger(logger) {

}