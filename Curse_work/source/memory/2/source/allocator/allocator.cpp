#include "allocator.h"
// #include "../../../../logger/source/logger/prototypes/logger.h"
#include <cstddef>
#include <string>
#include <sstream>


allocating::allocator::allocator(logging::logger *logger) {

    _logger_allocator = logger;
}


template <class T>
std::string cast_to_str(const T& object) {
    std::stringstream ss;
    ss << object;
    return ss.str();
}


void *allocating::allocator::allocate(size_t const targer_size) const {

    void *new_memory = ::operator new(sizeof(size_t) + targer_size);
    
    size_t *size = reinterpret_cast<size_t *>(new_memory);
    *size = targer_size;

    _logger_allocator
            ->log("Allocated " + std::to_string(*size) + " bytes of memory at "
            + cast_to_str(new_memory), logging::logger::severity::information);

    return reinterpret_cast<void *>(reinterpret_cast<size_t *>(new_memory) + 1);
}


void allocating::allocator::deallocate(void * const target_to_dealloc) const {

    size_t *target_size = reinterpret_cast<size_t *>(target_to_dealloc) - 1;
    void *v_ptr = reinterpret_cast<void *>(target_size);

    _logger_allocator
            ->log("Deallocated " + cast_to_str(*target_size) + " bytes of memory from "
            + cast_to_str(target_size) + " that contained bytes: [ "
            + get_bytes(target_to_dealloc) + " ]",
            logging::logger::severity::information);

    ::operator delete(v_ptr);

    // allocating::allocator::operator delete(v_ptr, *target_size + sizeof(size_t));
    // ::operator delete(reinterpret_cast<void *>(target_size)); //, target_size + sizeof(size_t));
}


allocating::allocator::~allocator() {

    _logger_allocator
            ->log("Allocator is destroyed", logging::logger::severity::information);

}


size_t allocating::allocator::get_size_block(const void * const object) const {
    
    return *(reinterpret_cast<size_t *>(const_cast<void *>(object)) - 1);
}


std::string allocating::allocator::get_bytes(void * const memory) const {
    
    size_t size = allocating::allocator::get_size_block(memory);
    unsigned char *ptr = reinterpret_cast<unsigned char *>(memory);
    std::stringstream ss;
    while (size-- > 0) {
        ss << static_cast<int>(*(ptr++)) << ' ';
    }

    return ss.str();
}