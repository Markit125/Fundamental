#ifndef MEMORY_WITH_LIST_H
#define MEMORY_WITH_LIST_H

#include "memory.h"
#include "logger_concrete.h"
#include "logger_builder_concrete.h"
#include "logger_builder.h"
#include "logger.h"
#include <cstddef>



class memory_with_list final : public memory {

public:

    memory_with_list();

    memory_with_list(size_t, memory *, logger *, fit_type);

    ~memory_with_list();

    void *allocate(size_t const) const override;

    void *allocate(size_t, logger *, memory *, fit_type);

    void *allocate_fit(size_t,  fit_type) override;

    void deallocate(void * const) const override;

    size_t get_size(void * const) const override;

    size_t get_size_block(void * const) const;

    void *get_memory_pointer();

    void *allocate(memory *, size_t, fit_type);

    void *memory_with_list_allocate(size_t, fit_type);

    void **find_first_fit(void *, size_t size);

    void **find_best_fit(void *, size_t size);

    void **find_worst_fit(void *, size_t size);

    void *_next_block;

    void **get_pointer_next(void * const);
    
    size_t get_size_service_block() const;

    void insert_allocator_to_pointer_list(void **);



private:

    void set_size_allocator(void *, size_t);

    void *_allocated_memory;

    logger *_logger;

    fit_type _fit;

    std::string get_bytes(void * const) const;

};


#endif