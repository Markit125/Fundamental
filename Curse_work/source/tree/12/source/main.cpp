#include <iostream>
#include <set>

#include "logger_builder_concrete.h"
#include "memory_with_list.h"
#include "../../../memory/4/source/memory_with_descriptors/memory_with_descriptors.h"
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

    allocating::memory *allocator = new allocating::memory_with_descriptors(2048000, nullptr, logger, allocating::memory::fit_type::first);

    associative_container<int, std::string> *tree =
            new avl_tree<int, std::string, integer_comparator>(allocator, logger);



    std::set<int> s;

    srand(time(NULL));

    for (int i = 0; i < 1000; ++i) {

        // if (rand() & 1) {
            int key = rand() % 10000;
            tree->insert(key, "kjnf");
            // std::cout << "Insert " << key << std::endl;
            s.insert(key);
            // std::cout << "Inserted\n";
        // }
        //  else if (!s.empty()) {
        //     size_t item = rand() % s.size();
        //     auto it = s.begin();

        //     for (size_t k = 0; k < item; ++k, ++it);

        //     std::cout << "Remove " << *it << std::endl;
        //     tree->remove(*it);
        //     s.erase(*it);
        // }
        // tree->print_container();

    }

    tree->print_container_logger();

    delete tree;
    delete builder;
    delete allocator;


}