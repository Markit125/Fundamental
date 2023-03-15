#ifndef MEMORY_H
#define MEMORY_H

#include <cstddef>



class memory {

public:

    memory();

    virtual ~memory();

    void *operator+=(size_t const &size);

    void operator-=(void *memory_object);


    virtual void *allocate(size_t targer_size) const = 0;

    virtual void deallocate(void * const target_to_dealloc) const = 0;

    virtual size_t get_size(void * const object) const = 0;

};

#endif