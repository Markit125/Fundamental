#ifndef MEMORY_H
#define MEMORY_H

#include <cstddef>
#include "../../../../logger/source/logger/prototypes/logger.h"


namespace allocating {

class memory {

public:

    enum fit_type {
        first,
        best,
        worst
    };


    memory() = default;

    virtual ~memory() = default;

    memory(memory const&) = delete;

    void operator=(memory const&) = delete;

    void *operator+=(size_t const &);

    void operator-=(void *);


    virtual void *allocate(size_t) const = 0;

    virtual void deallocate(void *) const = 0;

protected:

    logging::logger *_logger_allocator;

    void *_trusted_memory;

};

}

#endif