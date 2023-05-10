#include <iostream>
#include <ostream>
#include <string>

#include "binary_search_tree.h"
#include "logger_builder_concrete.h"
#include "memory_with_list.h"


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

    // logger = nullptr;

    allocating::memory *allocator = new allocating::memory_with_list(2048, nullptr, logger, allocating::memory::fit_type::first);

    associative_container<int, std::string> *tree =
            new binary_search_tree<int, std::string, integer_comparator>(allocator, logger);


    tree->insert(5, "five");
    tree->insert(2, "two");
    tree->insert(1, "one");
    tree->insert(4, "four");
    tree->insert(3, "three");
    tree->insert(6, "six");

    std::cout << "get:\n";

    std::cout << tree->get(5) << std::endl;
    std::cout << tree->get(2) << std::endl;
    std::cout << tree->get(1) << std::endl;
    std::cout << tree->get(4) << std::endl;
    std::cout << tree->get(3) << std::endl;
    std::cout << tree->get(6) << std::endl;
    std::cout << std::endl;


    tree->print_container();

    tree->remove(6);
    std::cout << "\nremoved " << 6;
    tree->print_container();

    tree->remove(2);
    std::cout << "\nremoved " << 2;
    tree->print_container();
    tree->remove(4);
    std::cout << "\nremoved " << 4;
    tree->print_container();
    tree->remove(3);
    std::cout << "\nremoved " << 3;
    tree->print_container();
    tree->remove(5);
    std::cout << "\nremoved " << 5;
    tree->print_container();
    tree->remove(1);
    std::cout << "\nremoved " << 1;
    tree->print_container();

    // for (int i = 0; i < 1000; ++i) {
    //     tree->insert(10, "jfngjfngfdknggjroqegijmrgcjqperogcer,gjfogeqroigjcogj");
    //     tree->remove(10);
    // }


    delete tree;
    delete allocator;
    delete logger;
    delete builder;
}