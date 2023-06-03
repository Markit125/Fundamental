#include "memory.h"


void *allocating::memory::operator+=(size_t const &size) {
    return allocate(size);
}


void allocating::memory::operator-=(void *memory_object) {
    deallocate(memory_object);
}