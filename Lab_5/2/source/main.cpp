#include <iostream>
#include <string>
#include "allocator/allocator.h"
#include "memory/memory.h"


int main() {

    memory *alloc = ::new allocator();

    double *constants = reinterpret_cast<double *>(alloc->allocate(sizeof(double) * 2));

    std::cout << alloc->get_size(constants) << '\n';

    *(constants + 0) = 3.14159;
    *(constants + 1) = 2.71828;

    std::cout << *constants << '\n' << *(constants + 1) << std::endl;
    
    alloc->deallocate(constants);

    // std::cout << '\n' << *constants << '\n' << *(constants + 1) << std::endl;

    delete alloc;
}