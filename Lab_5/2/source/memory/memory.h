#ifndef MEMORY_H
#define MEMORY_H

#include <cstddef>



class memory {

public:

    memory();

    virtual ~memory();

    void *operator+=(size_t const &);

    void operator-=(void *);


    virtual void *allocate(size_t) const = 0;

    virtual void deallocate(void * const) const = 0;

    virtual size_t get_size(void * const) const = 0;

};

#endif