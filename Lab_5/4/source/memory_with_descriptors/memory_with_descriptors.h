#ifndef MEMORY_WITH_DESCRIPTORS_H
#define MEMORY_WITH_DESCRIPTORS_H

#include "memory.h"
#include "logger_concrete.h"
#include "logger_builder_concrete.h"
#include "logger_builder.h"
#include "logger.h"
#include <cstddef>


class memory_with_descriptors final : public memory {

public:

    memory_with_descriptors(size_t, memory *, logger *, fit_type);

    ~memory_with_descriptors() override;

    void *allocate(size_t) const override;

    void deallocate(void *) const override;

private:

    void *_trusted_memory{};

    static std::string get_bytes(const void *);

};


#endif