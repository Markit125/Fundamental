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

    void *new_memory = operator new(sizeof(size_t) + targer_size);
    
    size_t *size = static_cast<size_t *>(new_memory);
    *size = targer_size;

    _logger_allocator
            ->log("Allocated " + std::to_string(*size) + " bytes of memory at "
            + cast_to_str(new_memory), logger::severity::information);

    return static_cast<void *>(static_cast<size_t *>(new_memory) + 1);
}


void allocator::deallocate(void * const target_to_dealloc) const {

    size_t *target_size = static_cast<size_t *>(target_to_dealloc) - 1;
    size_t size = *target_size;


    _logger_allocator
            ->log("Deallocated " + cast_to_str(size) + " bytes of memory from "
            + cast_to_str(target_size) + " that contained bytes: "
            + get_bytes(target_to_dealloc),
            logger::severity::information);

    std::cout << "size = " << get_size(target_to_dealloc) << '\n';

    operator delete(static_cast<void *>(target_size));
}


allocator::~allocator() {

    _logger_allocator
            ->log("Allocator is destroyed", logger::severity::information);

    delete _logger_allocator;
}


size_t allocator::get_size(void * const object) const {
    
    return *(static_cast<size_t *>(object) - 1);
}


std::string allocator::get_bytes(void * const memory) const {
    size_t size = allocator::get_size(memory);
    unsigned char *ptr = static_cast<unsigned char *>(memory);
    std::stringstream ss;
    while (size-- > 0) {
        ss << static_cast<int>((*ptr)++) << ' ';
    }

    return ss.str();
}