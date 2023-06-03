#include <iostream>
#include "../../logger/source/logger/complete/complete_logger.h"
#include "../../memory/2/source/memory/memory.h"
#include "../../../source/tree/11/source/tree/associative_container.h"
#include "../data_type/data_type.h"
#include "../../tree/11/source/allocator/safe_allocator.h"
#include "../../comparer/comparer.h"
#include "../../tree/12/source/avl/avl.h"


class collection {

public:

    explicit collection(allocating::memory *allocator = nullptr, logging::logger *logger = nullptr);

    virtual ~collection();


private:

    associative_container<type_key, type_value> *_collections;

    friend class scheme;


private:

    allocating::memory *get_allocator() const;

    logging::logger *get_logger() const;

    allocating::memory *_allocator;

    logging::logger *_logger;

};