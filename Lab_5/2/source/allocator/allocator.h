#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "../memory/memory.h"
#include "../../../1/source/logger/concrete/logger_concrete.h"
#include "../../../1/source/logger/concrete/logger_builder_concrete.h"
#include "../../../1/source/logger/prototypes/logger_builder.h"
#include "../../../1/source/logger/prototypes/logger.h"
#include <cstddef>



class allocator : public memory {

public:

    allocator();

    ~allocator();

    void *allocate(size_t const) const override;

    void deallocate(void * const) const override;

    size_t get_size_block(const void * const) const override;

private:

    void *allocated_memory;

    std::string get_bytes(void * const) const;

};


#endif