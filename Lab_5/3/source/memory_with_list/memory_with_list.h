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

    void *allocate_fit(size_t,  fit_type) const;

    void deallocate(void * const) const override;

    size_t get_size_block(const void * const) const;

    void *get_memory_pointer();

    void *allocate(memory *, size_t, fit_type);

    void *memory_with_list_allocate(size_t, fit_type);

    void *find_first_fit(size_t size) const;

    void *find_best_fit(size_t size) const;

    void *find_worst_fit(size_t size) const;

    void **get_pointer_next(const void * const) const;

    void *get_pointer_previous(const void * const) const;
    
    size_t get_size_service_block_allocator() const;

    size_t get_size_service_block_block() const;

    void insert_block_to_pointer_list(void *) const;

    logger *get_logger() const;


    std::string print_memory(const void * const) const;

    std::string print_allocator(const memory * const) const;

    std::string print_allocator_data(const memory * const) const;

private:

    void clear_logger() const;

    void *trusted_memory_to_block() const;

    void set_pointer_to_next_block(void *, void *) const;

    void **get_pointer_to_end_pointer_allocator() const;

    size_t get_space_beetween(void *, void *) const;

    void set_size_block(void *, size_t) const;

    void *_trusted_memory;

    fit_type _fit;

    bool is_outer_allocator {};

    std::string get_bytes(const void * const) const;

};


#endif