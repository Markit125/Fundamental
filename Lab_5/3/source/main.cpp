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
        ->add_stream("debug.log", logger::severity::debug)
        ->construct();

    memory_with_list *allocator = new memory_with_list(250, nullptr, constructed_logger, memory::fit_type::first);
    memory_with_list *inherit_allocator = new memory_with_list(100, allocator, constructed_logger, memory::fit_type::first);

    constructed_logger->log("Inherit allocator allocated in outer", logger::severity::debug);
    constructed_logger->log("Inherit allocator " + inherit_allocator->print_allocator(inherit_allocator), logger::severity::debug);
    constructed_logger->log("Outer allocator " + allocator->print_allocator(allocator), logger::severity::debug);

    size_t array_size = 10;
    int *array = reinterpret_cast<int *>(inherit_allocator->allocate(sizeof(int) * array_size));
    
    

    constructed_logger->log("Array in inherited allocator", logger::severity::debug);
    constructed_logger->log("Inherit allocator " + inherit_allocator->print_allocator(inherit_allocator), logger::severity::debug);
    constructed_logger->log("Outer allocator " + allocator->print_allocator(allocator), logger::severity::debug);


    double *dd = reinterpret_cast<double *>(allocator->allocate(16));
    
    *dd = 1;

    constructed_logger->log("16 - 1 bytes of memory " + allocator->print_memory(dd), logger::severity::debug);
    constructed_logger->log("16 bytes in outer allocator", logger::severity::debug);
    constructed_logger->log("Inherit allocator " + inherit_allocator->print_allocator(inherit_allocator), logger::severity::debug);
    constructed_logger->log("Outer allocator " + allocator->print_allocator(allocator), logger::severity::debug);

    // constructed_logger->log("Array in memory " + inherit_allocator->print_memory(array), logger::severity::trace);
    // std::cout << "giant\n";
    // constructed_logger->log("Inherit allocator " + inherit_allocator->print_allocator(inherit_allocator), logger::severity::trace);
    // constructed_logger->log("5 bytes of memory " + allocator->print_memory(dd), logger::severity::trace);

    // TODO: deallocation
    // allocator->deallocate(dd);
    // allocator->deallocate(array);

    for (size_t i = 0; i < array_size; ++i) {
        array[i] = i * i;
    }

    for (size_t i = 0; i < array_size; ++i) {
        std::cout << array[i] << " ";
    }

    *dd = 99999;
    std::cout << std::endl << "Double: " << *dd << std::endl;

    // allocator->deallocate(inherit_allocator);

    // delete inherit_allocator;
    delete allocator;
}