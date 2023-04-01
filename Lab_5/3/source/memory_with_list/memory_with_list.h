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

    ~memory_with_list() override;

    void *allocate(size_t) const override;

    void *allocate_fit(size_t,  fit_type) const;

    void deallocate(void *) const override;

    static size_t get_size_block(const void *);

    void *get_memory_pointer();

    void *find_first_fit(size_t) const;

    void *find_best_fit(size_t) const;

    void *find_worst_fit(size_t) const;

    static void **get_pointer_next(const void *);

    void *get_pointer_previous(const void *) const;
    
    static size_t get_size_service_block_allocator();

    static size_t get_size_service_block_block();

    void insert_block_to_pointer_list(void *) const;

    logger *get_logger() const;

    static std::string print_memory(const void *);

    static std::string print_allocator(const memory *);

    static std::string print_allocator_data(const memory *);

private:

    void clear_logger() const;

    void *trusted_memory_to_block() const;

    static void set_pointer_to_next_block(void *, void *);

    void **get_pointer_to_end_pointer_allocator() const;

    static size_t get_space_between(void *, void *);

    static void set_size_block(void *, size_t);

    void *_trusted_memory{};

    fit_type _fit {};

    bool is_outer_allocator {};

    static std::string get_bytes(const void *);

};


#endif