#include "memory.h"


void *memory::operator+=(size_t const &size) {
    return allocate(size);
}


void memory::operator-=(void *memory_object) {
    deallocate(memory_object);
}


memory::memory() {
    
}


memory::~memory() {

}