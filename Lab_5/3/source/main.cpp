#include <cstddef>
#include <iostream>
#include "allocator.h"
#include "logger.h"
#include "logger_builder.h"
#include "logger_builder_concrete.h"
#include "memory_with_list.h"


int main() {

    logger_builder *builder = new logger_builder_concrete();
    logger *constructed_logger_0 = builder
        ->add_stream("log.log", logger::severity::information)
        ->add_stream("trace.log", logger::severity::trace)
        ->add_stream("debug.log", logger::severity::debug)
        ->construct();

    logger *constructed_logger_1 = builder
        ->add_stream("log.log", logger::severity::information)
        ->add_stream("trace.log", logger::severity::trace)
        ->add_stream("debug.log", logger::severity::debug)
        ->construct();

    memory *allocator = new memory_with_list(212, nullptr, constructed_logger_1, memory::fit_type::best);
    memory *inherit_allocator = new memory_with_list(100, allocator, constructed_logger_0, memory::fit_type::best);


    size_t array_size = 10;
    int *array = reinterpret_cast<int *>(inherit_allocator->allocate(sizeof(int) * array_size));
    
    constructed_logger_0->log("Array in inherited allocator ================================================================", logger::severity::trace);


    for (size_t i = 0; i < array_size; ++i) {
        array[i] = i * i;
    }

    for (size_t i = 0; i < array_size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    double *dd = reinterpret_cast<double *>(allocator->allocate(16));
    *dd = 99999;
    std::cout << "Double: " << *dd << std::endl;

    allocator->deallocate(dd);


    inherit_allocator->deallocate(array);
    array = reinterpret_cast<int *>(inherit_allocator->allocate(sizeof(int) * array_size));
    
    constructed_logger_0->log("Array in inherited allocator ================================================================", logger::severity::trace);
    
    for (size_t i = 1; i <= array_size; ++i) {
        array[i - 1] = i * i;
    }

    for (size_t i = 0; i < array_size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    inherit_allocator->deallocate(array);


    array = reinterpret_cast<int *>(inherit_allocator->allocate(sizeof(int) * array_size));

    constructed_logger_0->log("Array in inherited allocator ================================================================", logger::severity::trace);

    for (size_t i = 1; i <= array_size; ++i) {
        array[i - 1] = i * (i + 1);
    }

    for (size_t i = 0; i < array_size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    inherit_allocator->deallocate(array);

    array = reinterpret_cast<int *>(inherit_allocator->allocate(sizeof(int) * array_size));

    constructed_logger_0->log("Array in inherited allocator ================================================================", logger::severity::trace);

    for (size_t i = 1; i <= array_size; ++i) {
        array[i - 1] = i * (i + 1);
    }

    for (size_t i = 0; i < array_size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    inherit_allocator->deallocate(array);

    delete inherit_allocator;
    delete allocator;

}