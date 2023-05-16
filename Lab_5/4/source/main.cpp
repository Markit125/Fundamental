#include <iostream>
#include <vector>
#include "allocator.h"
// #include "memory_with_descriptors.h"
#include "logger.h"
#include "memory_with_descriptors/memory_with_descriptors.h"


template <class T>
std::string cast_to_str(const T& object) {
    std::stringstream ss;
    ss << object;
    return ss.str();
}


void testing_allocator()
{
    logging::logger_builder *builder = new logger_builder_concrete();


    logging::logger *logger = builder
            ->add_stream("logs.txt", logging::logger::severity::trace)
            ->add_stream("log.log", logging::logger::severity::information)
            // ->add_stream("console", logging::logger::severity::trace)
            ->construct();

    // memory *allocator1 = new global_heap_allocator(logger);
    allocating::memory *allocator2 = new allocating::memory_with_descriptors(1000000, nullptr, logger, allocating::memory::fit_type::first);
    // memory *allocator2 = new border_descriptors_allocator(1000000, allocating::memory::allocation_mode::first_match, logger, allocator1);
    allocating::memory *allocator3 = new allocating::memory_with_descriptors(999900, allocator2, logger, allocating::memory::fit_type::first);

    std::vector<void*> allocated_blocks;

    srand((unsigned)time(nullptr));

    for (size_t i = 0; i < 10000; ++i)
    {
        void * ptr;

        switch (rand() % 2)
        {
            case 0:
                try
                {
                    ptr = reinterpret_cast<void *>(allocator3->allocate(rand() % 81 + 20)); // разность макс и мин с включенными границами + минимальное
                    allocated_blocks.push_back(ptr);
                }
                catch (std::exception const &ex)
                {
                    std::cout << ex.what() << std::endl;
                }
                break;
            case 1:

                if (allocated_blocks.empty())
                {
                    break;
                }

                try
                {
                    auto iter = allocated_blocks.begin();
                    std::advance(iter, rand() % allocated_blocks.size());
                    allocator3->deallocate(*iter);
                    allocated_blocks.erase(iter);
                }
                catch (std::exception const &ex)
                {
                    std::cout << ex.what() << std::endl;
                }
                break;
        }

        //std::cout << "iter # " << i + 1 << " finish" << std::endl;
    }

    while (!allocated_blocks.empty())
    {
        try
        {
            auto iter = allocated_blocks.begin();
            allocator3->deallocate(*iter);
            allocated_blocks.erase(iter);
        }
        catch (std::exception const &ex)
        {
            std::cout << ex.what() << std::endl;
        }
    }

    delete allocator3;
    delete allocator2;
    // // delete allocator1;
    delete logger;
    delete builder;
}

void my_test();

int main() {

    my_test();

    testing_allocator();

}


void my_test() {

    logging::logger_builder *builder = new logger_builder_concrete();
    
    logging::logger *constructed_logger = builder
        ->add_stream("log.log", logging::logger::severity::information)
        ->add_stream("trace.log", logging::logger::severity::trace)
        ->add_stream("debug.log", logging::logger::severity::debug)
        ->construct();
    
    // constructed_logger = nullptr;

    allocating::memory *allocator = new allocating::memory_with_descriptors(2048, nullptr, constructed_logger, allocating::memory::fit_type::worst);
    allocating::memory *inherit_allocator = new allocating::memory_with_descriptors(1024, allocator, constructed_logger, allocating::memory::fit_type::worst);
    
    size_t array_size = 10;
    int *array = reinterpret_cast<int *>(inherit_allocator->allocate(sizeof(int) * array_size));
    


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

    // constructed_logger->log("HERE 1", logging::logger::severity::trace);

    array = reinterpret_cast<int *>(inherit_allocator->allocate(sizeof(int) * array_size));
    
    std::cout << "after array\n\n";
    
    for (size_t i = 1; i <= array_size; ++i) {
        array[i - 1] = i * i;
    }

    for (size_t i = 0; i < array_size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    inherit_allocator->deallocate(array);


    array = reinterpret_cast<int *>(inherit_allocator->allocate(sizeof(int) * array_size));


    for (size_t i = 1; i <= array_size; ++i) {
        array[i - 1] = i * (i + 1);
    }

    for (size_t i = 0; i < array_size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    // inherit_allocator->deallocate(array);

    int *darray = reinterpret_cast<int *>(inherit_allocator->allocate(sizeof(int) * array_size));


    for (size_t i = 1; i <= array_size; ++i) {
        array[i - 1] = i * (i + 1);
    }

    for (size_t i = 0; i < array_size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    inherit_allocator->deallocate(array);
    inherit_allocator->deallocate(darray);

    delete inherit_allocator;
    delete allocator;

    delete constructed_logger;

}