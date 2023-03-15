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


    void *allocate(size_t targer_size) const override;

    void deallocate(void * const target_to_dealloc) const override;

    size_t get_size(void * const object) const;
    
private:

    logger *_logger_allocator;


};


#endif