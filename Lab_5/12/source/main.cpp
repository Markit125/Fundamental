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

    allocating::memory *allocator = new allocating::memory_with_list(2048000, nullptr, logger, allocating::memory::fit_type::first);

    associative_container<int, std::string> *tree =
            new avl_tree<int, std::string, integer_comparator>(allocator, logger);



    std::set<int> s;

    srand(time(NULL));

    for (int i = 0; i < 200; ++i) {

        if (rand() & 1) {
            int key = rand() % 500;
            tree->insert(key, "kjnf");
            std::cout << "Insert " << key << std::endl;
            s.insert(key);
            std::cout << "Inserted\n";
        } else if (!s.empty()) {
            size_t item = rand() % s.size();
            auto it = s.begin();

            for (size_t k = 0; k < item; ++k, ++it);

            std::cout << "Remove " << *it << std::endl;
            tree->remove(*it);
            s.erase(*it);
        }
        tree->print_container();

    }


    // int a[] = {1, 3, 2};
    // int a[] = {1, 2, 3, 4, 5};

    int a[] = {1, 2, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 3, 4, 5, 6, 7};

    for (int i : a) {
        tree->insert(i, "dc");
        tree->print_container();
    }

    int b[] = {10, 13};

    for (int i : b) {
        tree->remove(i);
        tree->print_container();
    }


    // tree->insert(5, "five");
    // std::cout << "\n\n\n\ninserted " << 5;
    // tree->print_container();
    // tree->insert(2, "two");
    // std::cout << "\n\n\n\ninserted " << 2;
    // tree->print_container();
    // tree->insert(1, "one");
    // std::cout << "\n\n\n\ninserted " << 1;
    // tree->print_container();
    // tree->insert(4, "four");
    // std::cout << "\n\n\n\ninserted " << 4;
    // tree->print_container();
    // tree->insert(3, "three");
    // std::cout << "\n\n\n\ninserted " << 3;
    // tree->print_container();
    // tree->insert(6, "six");
    // std::cout << "\n\n\n\ninserted " << 6;
    // tree->print_container();

    // std::cout << "get:\n";

    // std::cout << tree->get(5) << std::endl;
    // std::cout << tree->get(2) << std::endl;
    // std::cout << tree->get(1) << std::endl;
    // std::cout << tree->get(4) << std::endl;
    // std::cout << tree->get(3) << std::endl;
    // std::cout << tree->get(6) << std::endl;
    // std::cout << std::endl;


    // tree->print_container();

    // tree->remove(6);
    // std::cout << "\n\n\n\nremoved " << 6;
    // tree->print_container();

    // tree->remove(2);
    // std::cout << "\n\n\n\nremoved " << 2;
    // tree->print_container();
    // tree->remove(5);
    // std::cout << "\n\n\n\nremoved " << 5;
    // tree->print_container();
    // tree->remove(4);
    // std::cout << "\n\n\n\nremoved " << 4;
    // tree->print_container();
    // tree->remove(3);
    // std::cout << "\n\n\n\nremoved " << 3;
    // tree->print_container();
    // tree->remove(1);
    // std::cout << "\n\n\n\nremoved " << 1;
    // tree->print_container();

    delete tree;


}