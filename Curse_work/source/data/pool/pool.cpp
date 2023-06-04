#include "pool.h"


allocating::memory *pool::get_allocator() const {
    return _allocator;
}


logging::logger *pool::get_logger() const {
    return _logger;
}


pool::~pool() {
    delete _schemes;
}


pool::pool(allocating::memory *allocator, logging::logger *logger)
    : _schemes(new avl_tree<std::string, scheme *, comparers>(allocator, logger)),
     _allocator(allocator), _logger(logger) {

}