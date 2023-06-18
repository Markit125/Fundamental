#include <iostream>
#include <set>

#include "../../1/source/logger/concrete/logger_builder_concrete.h"
#include "../../3/source/memory_with_list/memory_with_list.h"
#include "../../4/source/memory_with_descriptors/memory_with_descriptors.h"
#include "splay/splay.h"


class integer_comparator
{

public:
	int operator()(int lhs, int rhs) {
        return rhs - lhs;
    }
};

void my_test();

int main() {

    // my_test();

    // return 0;

    logging::logger_builder *builder = new logger_builder_concrete();

    logging::logger *logger = builder
        // ->add_stream("log.log", logging::logger::severity::information)
        // ->add_stream("trace.log", logging::logger::severity::trace)
        // ->add_stream("debug.log", logging::logger::severity::debug)
        ->add_stream("tree.log", logging::logger::severity::critical)
        ->construct();

    // allocating::memory *allocator = new allocating::memory_with_list(2048000, nullptr, logger, allocating::memory::fit_type::first);
    allocating::memory *allocator = new allocating::memory_with_descriptors(2048000, nullptr, logger, allocating::memory::fit_type::first);

    associative_container<int, std::string> *tree =
            new splay_tree<int, std::string, integer_comparator>(allocator, logger);



    std::set<int> s;

    srand(time(NULL));

    for (int i = 0; i < 10000; ++i) {

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
    delete allocator;
    delete builder;


}

void my_test() {

    logging::logger_builder *builder = new logger_builder_concrete();

    logging::logger *logger = builder
        ->add_stream("log.log", logging::logger::severity::information)
        ->add_stream("trace.log", logging::logger::severity::trace)
        ->add_stream("debug.log", logging::logger::severity::debug)
        ->construct();


    allocating::memory *allocator = new allocating::memory_with_descriptors(204800, nullptr, logger, allocating::memory::fit_type::first);


    associative_container<int, std::string> *tree =
            new splay_tree<int, std::string, integer_comparator>(allocator, logger);


    // std::set<int> s;
    // srand(time(NULL));
    // for (int i = 0; i < 20000; ++i) {
    //     if (rand() & 1) {
    //         int key = rand() % 30001 - 15000;
    //         tree->insert(key, "kjnf");
    //         s.insert(key);
    //     } else if (!s.empty()) {
    //         size_t item = rand() % s.size();
    //         auto it = s.begin();
    //         for (size_t k = 0; k < item; ++k, ++it);
    //         tree->remove(*it);
    //         s.erase(*it);
    //     }
    // }

    std::cout << "insert ===================\n";
    tree->insert(2, "two");
    tree->print_container();
    std::cout << "insert ===================\n";
    tree->insert(1, "one");
    tree->print_container();
    std::cout << "insert ===================\n";
    tree->insert(1, "one");
    tree->print_container();
    std::cout << "insert ===================\n";
    tree->insert(3, "three");



    tree->print_container();
    
    tree->insert(5, "five");
    tree->print_container();
    
    tree->insert(2, "two");
    tree->print_container();
    
    tree->insert(1, "one");
    tree->print_container();
    
    tree->insert(4, "four");
    tree->print_container();
    
    tree->insert(3, "three");
    tree->print_container();
    
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
    return;
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


    delete tree;
    delete allocator;
    delete logger;
    delete builder;
}