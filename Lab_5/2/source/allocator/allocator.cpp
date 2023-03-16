#include "allocator.h"
#include <cstddef>
#include <string>
#include <sstream>


allocator::allocator() {

    logger_builder *builder = new logger_builder_concrete();

    _logger_allocator = builder
            ->add_stream("log_warning.log", logger::severity::warning)
            ->add_stream("log_trace.log", logger::severity::trace)
            ->add_stream("log_info.log", logger::severity::information)
            ->construct();

    _logger_allocator
            ->log("Logger is built", logger::severity::information)
            ->log("Allocator is instantiated", logger::severity::information);

    delete builder;
}


template <class T>
std::string cast_to_str(const T& object) {
    std::stringstream ss;
    ss << object;
    return ss.str();
}


void *allocator::allocate(size_t const targer_size) const {

    void *new_memory = ::operator new(sizeof(size_t) + targer_size);
    
    size_t *size = reinterpret_cast<size_t *>(new_memory);
    *size = targer_size;

    _logger_allocator
            ->log("Allocated " + std::to_string(*size) + " bytes of memory at "
            + cast_to_str(new_memory), logger::severity::information);

    return reinterpret_cast<void *>(reinterpret_cast<size_t *>(new_memory) + 1);
}


void allocator::deallocate(void * const target_to_dealloc) const {

    size_t *target_size = reinterpret_cast<size_t *>(target_to_dealloc) - 1;
    void *v_ptr = reinterpret_cast<void *>(target_size);

    _logger_allocator
            ->log("Deallocated " + cast_to_str(*target_size) + " bytes of memory from "
            + cast_to_str(target_size) + " that contained bytes: [ "
            + get_bytes(target_to_dealloc) + " ]",
            logger::severity::information);

    ::operator delete(v_ptr);

    // allocator::operator delete(v_ptr, *target_size + sizeof(size_t));
    // ::operator delete(reinterpret_cast<void *>(target_size)); //, target_size + sizeof(size_t));
}


allocator::~allocator() {

    _logger_allocator
            ->log("Allocator is destroyed", logger::severity::information);

    delete _logger_allocator;
}


size_t allocator::get_size(void * const object) const {
    
    return *(reinterpret_cast<size_t *>(object) - 1);
}


std::string allocator::get_bytes(void * const memory) const {
    
    size_t size = allocator::get_size(memory);
    unsigned char *ptr = reinterpret_cast<unsigned char *>(memory);
    std::stringstream ss;
    while (size-- > 0) {
        ss << static_cast<int>(*(ptr++)) << ' ';
    }

    return ss.str();
}