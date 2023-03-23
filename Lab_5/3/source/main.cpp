#include <cstddef>
#include <iostream>
#include "allocator.h"
#include "logger_builder.h"
#include "logger_builder_concrete.h"
#include "memory_with_list.h"


int main() {

    logger_builder *builder = new logger_builder_concrete();
    logger *constructed_logger = builder
        ->add_stream("log.log", logger::severity::information)
        ->add_stream("trace.log", logger::severity::trace)
        ->construct();

    memory_with_list *allocator = new memory_with_list(1000, nullptr, constructed_logger, memory::fit_type::first);
    memory_with_list *inherit_allocator = new memory_with_list(500, allocator, constructed_logger, memory::fit_type::first);

    size_t array_size = 10;
    int *array = reinterpret_cast<int *>(inherit_allocator->allocate(array_size));

    for (size_t i = 0; i < array_size; ++i) {
        array[i] = i * i;
    }

    for (size_t i = 0; i < array_size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;



    double *dd = reinterpret_cast<double *>(allocator->allocate(5));
    
    allocator->deallocate(dd);
    // std::cout << allocator;
    delete allocator;
}