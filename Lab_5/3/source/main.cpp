#include <cstddef>
#include <iostream>
#include "allocator.h"
#include "memory_with_list.h"


int main() {
    memory_with_list *allocator = new memory_with_list(1000, nullptr, nullptr, memory::fit_type::worst);
    memory_with_list *inherit_allocator = new memory_with_list(500, allocator, nullptr, memory::fit_type::best);

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

    delete allocator;
}