#ifndef MEMORY_H
#define MEMORY_H

#include <cstddef>
#include "../../../1/source/logger/prototypes/logger.h"


namespace allocating {

class memory {

public:

    enum fit_type {
        first,
        best,
        worst
    };


    memory();

    virtual ~memory();

    void *operator+=(size_t const &);

    void operator-=(void *);


    virtual void *allocate(size_t) const = 0;

    virtual void deallocate(void *) const = 0;

    // virtual size_t get_size_block(const void * const) const;

protected:

    logging::logger *_logger_allocator;

    void *_trusted_memory;

};

}

#endif