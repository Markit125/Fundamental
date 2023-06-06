#include "safe_allocator.h"
#include <iostream>


void *allocating::safe_allocator::safe_allocate(size_t size) const {

    allocating::memory *allocator = get_allocator();

    if (nullptr != allocator) {
        return allocator->allocate(size);
    }

    return ::operator new(size);
}


void allocating::safe_allocator::safe_deallocate(void *object) const {

    allocating::memory *allocator = get_allocator();

    if (nullptr != allocator) {
        allocator->deallocate(object);
    } else {
        ::operator delete(object);
    }
}