#include <iostream>
#include <string>

#include "allocator/allocator.h"
#include "memory/memory.h"


int main() {

    logging::logger_builder *builder = new logger_builder_concrete();

    logging::logger *_logger_allocator = builder
            ->add_stream("log_warning.log", logging::logger::severity::warning)
            ->add_stream("log_trace.log", logging::logger::severity::trace)
            ->add_stream("log_info.log", logging::logger::severity::information)
            ->construct();

    _logger_allocator
            ->log("Logger is built", logging::logger::severity::information)
            ->log("Allocator is instantiated", logging::logger::severity::information);


    allocating::memory *alloc = new allocating::allocator();

    double *constants = reinterpret_cast<double *>(alloc->allocate(sizeof(double) * 2));

    *(constants + 0) = 3.14159;
    *(constants + 1) = 2.71828;

    std::cout << *constants << '\n' << *(constants + 1) << std::endl;
    
    alloc->deallocate(constants);

    delete alloc;
    delete builder;
}