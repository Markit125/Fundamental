#include "allocator.h"
#include <cstddef>
#include <string>


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


void *allocator::allocate(size_t targer_size) const {

    void *new_memory = operator new(sizeof(size_t) + targer_size);
    
    size_t *size = static_cast<size_t *>(new_memory);
    *size = targer_size;

    _logger_allocator
            ->log("Allocated " + std::to_string(*size) + " bytes of memory", logger::severity::information);

    return static_cast<void *>(static_cast<size_t *>(new_memory) + 1);
}


void allocator::deallocate(void * const target_to_dealloc) const {

    size_t *target_size = static_cast<size_t *>(target_to_dealloc) - 1;
    size_t size = *target_size;

    operator delete(static_cast<void *>(target_size));

    _logger_allocator
            ->log("Deallocated " + std::to_string(size) + " bytes of memory", logger::severity::information);
}


allocator::~allocator() {

    _logger_allocator
            ->log("Allocator is destroyed", logger::severity::information);

    delete _logger_allocator;
}


size_t allocator::get_size(void * const object) const {
    
    size_t *size = static_cast<size_t *>(object) - 1;

    return *size;
}