#ifndef SAFE_ALLOCATOR_H
#define SAFE_ALLOCATOR_H

#include "../../../2/source/memory/memory.h"
#include <cstddef>


namespace allocating {

class safe_allocator
{
    
public:

    virtual ~safe_allocator() = default;

    void *safe_allocate(size_t) const;

    void safe_deallocate(void *) const;

    virtual allocating::memory *get_allocator() const = 0;

};

}

#endif
