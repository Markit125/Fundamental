#include <iostream>
#include <set>

#include "logger_builder_concrete.h"
#include "memory_with_list.h"
#include "avl/avl.h"


class integer_comparator
{

public:
	int operator()(int lhs, int rhs) {
        return rhs - lhs;
    }
};


int main() {

    logging::logger_builder *builder = new logger_builder_concrete();

    logging::logger *logger = builder
        ->add_stream("log.log", logging::logger::severity::information)
        ->add_stream("trace.log", logging::logger::severity::trace)
        ->add_stream("debug.log", logging::logger::severity::debug)
        ->construct();

    allocating::memory *allocator = new allocating::memory_with_list(2048, nullptr, logger, allocating::memory::fit_type::first);

    associative_container<int, std::string> *tree =
            new avl_tree<int, std::string, integer_comparator>(allocator, logger);

    delete tree;


}