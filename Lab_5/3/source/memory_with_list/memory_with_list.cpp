#include "memory_with_list.h"
#include "logger.h"
#include <cstddef>
#include <stdexcept>
#include <string>
#include <sstream>


template <class T>
std::string cast_to_str(const T& object) {
    std::stringstream ss;
    ss << object;
    return ss.str();
}


void memory_with_list::deallocate(void * const target_to_dealloc) const {
    
    logger *_logger = get_logger();

    size_t size = get_size_block(target_to_dealloc);
    unsigned char *ptr;

    if (target_to_dealloc == trusted_memory_to_block()) {

        ptr = reinterpret_cast<unsigned char *>(reinterpret_cast<void **>(target_to_dealloc) - 4);
        for (size_t i = 0; i < size; ++i) {
            *(ptr++) = 0;
        }

        return;
    }

    void *next = *get_pointer_next(target_to_dealloc);
    void *prev = get_pointer_previous(target_to_dealloc);

    if (nullptr != _logger) {
        _logger->log("Prev " + cast_to_str(prev), logger::severity::trace);
        _logger->log("Next " + cast_to_str(next), logger::severity::trace);

        _logger->log("Outer next " + cast_to_str(*get_pointer_next(trusted_memory_to_block())), logger::severity::trace);
        _logger->log("Outer end  " + cast_to_str(*get_pointer_to_end_pointer_allocator()), logger::severity::trace);
    }

    *(reinterpret_cast<void **>(prev) - 1) = next;

    // prev = *get_pointer_previous(target_to_dealloc);
    // next = *get_pointer_next(prev);

    
    if (nullptr != _logger) {
        _logger->log("Prev " + cast_to_str(prev), logger::severity::trace);
        _logger->log("Curr " + cast_to_str(target_to_dealloc), logger::severity::trace);
        _logger->log("Next " + cast_to_str(next), logger::severity::trace);

        _logger->log("Outer next " + cast_to_str(*get_pointer_next(trusted_memory_to_block())), logger::severity::trace);
        _logger->log("Outer end  " + cast_to_str(*get_pointer_to_end_pointer_allocator()), logger::severity::trace);
    }

    ptr = reinterpret_cast<unsigned char *>(reinterpret_cast<size_t *>(target_to_dealloc) - 2);
    for (size_t i = 0; i < size; ++i) {
        *(ptr++) = 0;
    }

}


logger *memory_with_list::get_logger() const {
    return *reinterpret_cast<logger **>(_trusted_memory);
}


memory_with_list::~memory_with_list() {

    logger *_logger = get_logger();

    if (_logger) {
        _logger->log("Allocator is destroyed", logger::severity::information);
        // delete log;
    }

    if (is_outer_allocator) {
        ::operator delete(_trusted_memory);
    } else {
        deallocate(_trusted_memory);
    }

    
}


std::string memory_with_list::get_bytes(const void * const memory) const {
    
    size_t size = get_size_block(memory) + get_size_service_block_block();
    unsigned char *ptr = reinterpret_cast<unsigned char *>(const_cast<void *>(memory)) - 2;
    
    std::stringstream ss;
    while (size--) {
        ss << static_cast<int>(*(ptr++)) << ' ';
    }

    return ss.str();
}


void *memory_with_list::get_memory_pointer() {
    return _trusted_memory;
}


void *memory_with_list::allocate(size_t const targer_size) const {

    logger *_logger = get_logger();

    if (nullptr != _logger) {
        _logger->log("New memory allocating............................................", logger::severity::trace);
    }

    void *new_memory = allocate_fit(targer_size + get_size_service_block_block(), _fit);

    if (new_memory == nullptr) {

        throw std::runtime_error("There is not enough space for memory allocation!");
        return nullptr;
    }


    if (nullptr != _logger) {
        _logger->log("Allocated block " + std::to_string(targer_size) + " bytes of memory at "
                + cast_to_str(new_memory), logger::severity::information);

        _logger->log("new_memory " + print_memory(new_memory), logger::severity::trace);
        _logger->log("_allocated_memory " + print_allocator(this), logger::severity::trace);

        _logger->log("ALLOCATOR " + cast_to_str(_trusted_memory), logger::severity::trace);
        _logger->log("Starts at     " + cast_to_str(_trusted_memory), logger::severity::trace);
        _logger->log("New memory at " + cast_to_str(new_memory), logger::severity::trace);
        _logger->log("Ends at       " + cast_to_str(*(get_pointer_to_end_pointer_allocator())), logger::severity::trace);
    }

    return new_memory;
}


// ONLY FOR ALLOCATOR
memory_with_list::memory_with_list(
        size_t size, memory_with_list *outer_allocator, logger *memory_logger,
        memory_with_list::fit_type fit = memory_with_list::fit_type::first
    ) : _fit { fit } {
    

    _trusted_memory = outer_allocator == nullptr ?
        ::operator new(size + get_size_service_block_allocator()) :
        outer_allocator->allocate(size + get_size_service_block_allocator());


    logger *_logger = nullptr;
    if (outer_allocator) {
        _logger = get_logger();
    }


    if (_trusted_memory == nullptr) {

        if (_logger != nullptr) {
            _logger->log("Cannot allocate " + cast_to_str(size) + " bytes of memory", logger::severity::error);
        }    

        throw std::runtime_error("There is not enough space for allocator!");
        return;
    }


    logger **logger_ptr = reinterpret_cast<logger **>(_trusted_memory);
    *logger_ptr = memory_logger;

    if (outer_allocator && _logger != nullptr) {

        _logger->log("Memory of new Allocator", logger::severity::trace);
        _logger->log("Start at " + cast_to_str(outer_allocator->_trusted_memory), logger::severity::trace);
        _logger->log("New a at " + cast_to_str(_trusted_memory), logger::severity::trace);
        _logger->log("  End at " + cast_to_str(*(outer_allocator->get_pointer_to_end_pointer_allocator())), logger::severity::trace);
    }


    if (nullptr != _logger) {
        _logger->log("Allocated allocator with " + cast_to_str(size) + " bytes of memory at " + cast_to_str(_trusted_memory),
                    logger::severity::information);
    }


    void **end_ptr = get_pointer_to_end_pointer_allocator();
    *end_ptr = reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(_trusted_memory) + size + get_size_service_block_allocator());

    size_t *pointer_size = reinterpret_cast<size_t *>(_trusted_memory) + 2;
    *pointer_size = size;

    void **first_block = reinterpret_cast<void **>(_trusted_memory) + 3;
    *first_block = *end_ptr;


    if (outer_allocator == nullptr) {

        is_outer_allocator = true;

        unsigned char *ptr = reinterpret_cast<unsigned char *>(reinterpret_cast<size_t *>(_trusted_memory) + 4);
        for (size_t i = 0; i < size; ++i) {
            *(ptr++) = 0;
        }
        
    }

    if (nullptr != _logger) {

        _logger->log("New allocator _allocated_memory " + print_allocator(this), logger::severity::trace);

        if (outer_allocator) {
            _logger->log("_allocated_memory " + print_allocator(outer_allocator), logger::severity::trace);
        }
    }

}


void *memory_with_list::allocate_fit(size_t size, memory_with_list::fit_type fit = memory_with_list::fit_type::first) const {

    logger *_logger = get_logger();

    void *fit_memory_block = nullptr;
    
    if (nullptr != _logger) {
        _logger->log("Start finding memory block for allocator with size " + cast_to_str(size) + " bytes",
                    logger::severity::information);
    }
    

    if (fit == memory_with_list::fit_type::first) {
        fit_memory_block = memory_with_list::find_first_fit(size);
    } else if (memory_with_list::fit_type::best) {
        fit_memory_block = memory_with_list::find_best_fit(size);
    } else {
        fit_memory_block = memory_with_list::find_worst_fit(size);
    }


    if (fit_memory_block == nullptr) {

        if (nullptr != _logger) {
            _logger->log("There is no memory for allocator with size " + cast_to_str(size), logger::severity::error);
        }

        return nullptr;
    } else if (nullptr != _logger) {
        _logger->log(cast_to_str(size) + " bytes of memory is allocated", logger::severity::trace);
    }


    set_size_block(fit_memory_block, size);

    insert_block_to_pointer_list(fit_memory_block);
    

    // _logger->log("Block is inserted to the list", logger::severity::trace);

    // _logger->log("block fit after " + cast_to_str(fit_memory_block), logger::severity::trace);


    // _logger->log("Next block at " + cast_to_str(*get_pointer_next(fit_memory_block)), logger::severity::trace);
    // _logger->log("New memory at " + cast_to_str(fit_memory_block), logger::severity::trace);
    // _logger->log("Prev block at " + cast_to_str(*get_pointer_previous(fit_memory_block)), logger::severity::trace);

    return fit_memory_block;
}


void memory_with_list::insert_block_to_pointer_list(void *block) const {
    void *ptr_current = trusted_memory_to_block();
    void *previous = ptr_current;

    // _logger->log("cur " + cast_to_str(ptr_current) + " prev " + cast_to_str(previous) + " block " + cast_to_str(block),
    //             logger::severity::trace);


    while (block > ptr_current) {
        previous = ptr_current;
        ptr_current = *get_pointer_next(ptr_current);

        // _logger->log("cur " + cast_to_str(ptr_current) + " prev " + cast_to_str(previous) + " block " + cast_to_str(block),
                // logger::severity::trace);
    }


    // _logger->log("prev  " + cast_to_str(previous) + " next " + cast_to_str(*get_pointer_next(previous)), logger::severity::trace);

    set_pointer_to_next_block(block, ptr_current);
    
    set_pointer_to_next_block(previous, block);


    // _logger->log("prev  " + cast_to_str(previous) + " next " + cast_to_str(*get_pointer_next(previous)), logger::severity::trace);
    // _logger->log("block " + cast_to_str(block) + " next " + cast_to_str(*get_pointer_next(block)), logger::severity::trace);
    
}


void memory_with_list::set_pointer_to_next_block(void *block, void *pointer) const {
    *(reinterpret_cast<void **>(block) - 1) = pointer;
}


void **memory_with_list::get_pointer_to_end_pointer_allocator() const {
    return reinterpret_cast<void **>(_trusted_memory) + 1;
}

// Allocator
//      0           1              2               3                    4
// | logger | pointer to end | size of all | pointer to next | allocated memory for use | *end |
//                                                  ^                          ^
//                        pointer to next points to |           or          to | 

void *memory_with_list::find_first_fit(size_t size) const {
    //                          size of block plus service block

    logger *_logger = get_logger();

    void **ptr_next = get_pointer_next(trusted_memory_to_block());

    void *current_memory = reinterpret_cast<void *>(reinterpret_cast<void **>(_trusted_memory) + 4);
    void **ptr_current = &current_memory;
    
    void *end = *get_pointer_to_end_pointer_allocator();
    void **fit = nullptr;
    size_t free_space;

    if (nullptr != _logger) {
        _logger->log("Start jumping between memory blocks", logger::severity::trace);

        _logger->log(">>>>>>>ptr_current: " + cast_to_str(*ptr_current), logger::severity::trace);
        _logger->log("prt_next: " + cast_to_str(*ptr_next), logger::severity::trace);
        _logger->log("prt_end: " + cast_to_str(end), logger::severity::trace);
    }
    
    if (*ptr_next == end) {

        free_space = get_space_beetween(*ptr_current, *ptr_next) + get_size_block(*ptr_current);

        if (nullptr != _logger) {
            _logger->log("First block! Space for data between " + cast_to_str(*ptr_current) + " and " + cast_to_str(end) +
                        " is " + cast_to_str(free_space), logger::severity::trace);
        }

        if (free_space >= size) {
            current_memory = reinterpret_cast<void *>(reinterpret_cast<size_t *>(*ptr_current) + 2);
            fit = &current_memory;
        } else {
            ptr_current = get_pointer_next(*ptr_current);
        }

    } else {

        while (*ptr_current < end) {

            
            free_space = get_space_beetween(*ptr_current, *ptr_next);

            if (nullptr != _logger) {
                _logger->log("Space for data between " + cast_to_str(*ptr_current) + " and " + cast_to_str(*ptr_next) +
                            " is " + cast_to_str(free_space),
                            logger::severity::trace);
            }


            if (free_space >= size) {
                
                // current_memory = reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(*ptr_current) + get_size_block(*ptr_current) + 2);
                current_memory = reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(*ptr_current) + get_size_block(*ptr_current) + sizeof(size_t *) * 2);
                fit = &current_memory;
                break;
            }

            // _logger->log("----->>>ptr_current: " + cast_to_str(*ptr_current), logger::severity::trace);
            // _logger->log("prt_next: " + cast_to_str(*ptr_next), logger::severity::trace);

            ptr_current = get_pointer_next(*ptr_current);
            ptr_next = get_pointer_next(*ptr_current);

            // _logger->log("----->>>ptr_current: " + cast_to_str(*ptr_current), logger::severity::trace);

            if (nullptr != _logger) {
                _logger->log("prt_next: " + cast_to_str(*ptr_next), logger::severity::trace);
                _logger->log("ptr_current: " + cast_to_str(*ptr_current), logger::severity::trace);
                _logger->log("prt_end: " + cast_to_str(end), logger::severity::trace);
            }
        }
    }



    if (*ptr_current == end) {
        
        if (nullptr != _logger) {
            _logger->log("Cannot find memory block with " + cast_to_str(size) + " bytes of memory (first fit)",
                        logger::severity::error);
        }
        return nullptr;

    } else if (nullptr != _logger) {
        _logger->log("Found first fit block with size " + cast_to_str(size) + " at " + cast_to_str(*fit), logger::severity::information);
    }

    if (nullptr != _logger) {
        _logger->log("_allocated_memory " + cast_to_str(_trusted_memory), logger::severity::trace);
        _logger->log("block fit " + cast_to_str(*fit), logger::severity::trace);
    }

    return *fit;
}


void *memory_with_list::find_best_fit(size_t size) const {
    //                          size of block plus service block

    logger *_logger = get_logger();

    void **ptr_next = get_pointer_next(trusted_memory_to_block());

    void *current_memory = reinterpret_cast<void *>(reinterpret_cast<void **>(_trusted_memory) + 4);
    void **ptr_current = &current_memory;
    
    void **fit = nullptr;
    size_t free_space;

    if (nullptr != _logger) {
        _logger->log("Start jumping between memory blocks", logger::severity::trace);
    }

    void **ptr_end = get_pointer_to_end_pointer_allocator();


    
    if (*ptr_next == *ptr_end) {

        free_space = get_space_beetween(*ptr_current, *ptr_next) + get_size_block(*ptr_current);

        if (nullptr != _logger) {
            _logger->log("First block! Space for data between " + cast_to_str(*ptr_current) + " and " + cast_to_str(*ptr_end) +
                        " is " + cast_to_str(free_space), logger::severity::trace);
        }

        if (free_space >= size) {
            current_memory = reinterpret_cast<void *>(reinterpret_cast<size_t *>(*ptr_current) + 2);
            fit = &current_memory;
        } else {
            ptr_current = get_pointer_next(*ptr_current);
        }

    } else {

        size_t best_size = -1;

        while (*ptr_current < *ptr_end) {
            
            free_space = get_space_beetween(*ptr_current, *ptr_next);

            if (nullptr != _logger) {
                _logger->log("Space for data between " + cast_to_str(*ptr_current) + " and " + cast_to_str(*ptr_next) +
                            " is " + cast_to_str(free_space),
                            logger::severity::trace);
            }


            if (free_space >= size) {

                if (best_size > free_space) {

                    current_memory = reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(*ptr_current) + get_size_block(*ptr_current) + 2);
                    fit = &current_memory;
                    best_size = free_space;
                }

            }

            ptr_current = get_pointer_next(*ptr_current);
            ptr_next = get_pointer_next(*ptr_current);

            if (nullptr != _logger) {
                _logger->log("ptr_current: " + cast_to_str(*ptr_current), logger::severity::trace);
                _logger->log("prt_end: " + cast_to_str(*ptr_end), logger::severity::trace);
            }
        }
    }



    if (*ptr_current == *ptr_end) {
        
        if (nullptr != _logger) {
            _logger->log("Cannot find memory block with " + cast_to_str(size) + " bytes of memory (first fit)",
                        logger::severity::error);
        }

        return nullptr;

    } else if (nullptr != _logger) {
        _logger->log("Found first fit block with size " + cast_to_str(size) + " at " + cast_to_str(*fit), logger::severity::information);
    }

    if (nullptr != _logger) {
        _logger->log("_allocated_memory " + cast_to_str(_trusted_memory), logger::severity::trace);
        _logger->log("block fit " + cast_to_str(*fit), logger::severity::trace);
    }

    return *fit;
}


void *memory_with_list::find_worst_fit(size_t size) const {
    //                          size of block plus service block

    logger *_logger = get_logger();

    void **ptr_next = get_pointer_next(trusted_memory_to_block());

    void *current_memory = reinterpret_cast<void *>(reinterpret_cast<void **>(_trusted_memory) + 4);
    void **ptr_current = &current_memory;
    
    void **fit = nullptr;
    size_t free_space;

    if (nullptr != _logger) {
        _logger->log("Start jumping between memory blocks", logger::severity::trace);
    }

    void **ptr_end = get_pointer_to_end_pointer_allocator();

    
    if (*ptr_next == *ptr_end) {

        free_space = get_space_beetween(*ptr_current, *ptr_next) + get_size_block(*ptr_current);

        if (nullptr != _logger) {
            _logger->log("First block! Space for data between " + cast_to_str(*ptr_current) + " and " + cast_to_str(*ptr_end) +
                        " is " + cast_to_str(free_space), logger::severity::trace);
        }

        if (free_space >= size) {
            current_memory = reinterpret_cast<void *>(reinterpret_cast<size_t *>(*ptr_current) + 2);
            fit = &current_memory;
        } else {
            ptr_current = get_pointer_next(*ptr_current);
        }

    } else {

        size_t worst_size = 0;

        while (*ptr_current < *ptr_end) {
            
            free_space = get_space_beetween(*ptr_current, *ptr_next);

            if (nullptr != _logger) {
                _logger->log("Space for data between " + cast_to_str(*ptr_current) + " and " + cast_to_str(*ptr_next) +
                            " is " + cast_to_str(free_space),
                            logger::severity::trace);
            }

            if (free_space >= size) {

                if (worst_size < free_space) {

                    current_memory = reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(*ptr_current) + get_size_block(*ptr_current) + 2);
                    fit = &current_memory;
                    worst_size = free_space;
                }

            }

            ptr_current = get_pointer_next(*ptr_current);
            ptr_next = get_pointer_next(*ptr_current);

            if (nullptr != _logger) {
                _logger->log("ptr_current: " + cast_to_str(*ptr_current), logger::severity::trace);
                _logger->log("prt_end: " + cast_to_str(*ptr_end), logger::severity::trace);
            }
        }
    }


    if (*ptr_current == *ptr_end) {
        
        if (nullptr != _logger) {
            _logger->log("Cannot find memory block with " + cast_to_str(size) + " bytes of memory (first fit)",
                        logger::severity::error);
        }

        return nullptr;

    } else if (nullptr != _logger) {
        _logger->log("Found first fit block with size " + cast_to_str(size) + " at " + cast_to_str(*fit), logger::severity::information);
    }


    if (nullptr != _logger) {
        _logger->log("_allocated_memory " + cast_to_str(_trusted_memory), logger::severity::trace);
        _logger->log("block fit " + cast_to_str(*fit), logger::severity::trace);
    }

    return *fit;
}



size_t memory_with_list::get_space_beetween(void *ptr_current, void *ptr_next) const {

    unsigned char *ptr_1_casted = reinterpret_cast<unsigned char *>(ptr_current);
    unsigned char *ptr_2_casted = reinterpret_cast<unsigned char *>(ptr_next);

    if (ptr_2_casted - ptr_1_casted - (long) get_size_block(ptr_current) < (long) get_size_service_block_block()) {
        return 0;
    }

    return  ptr_2_casted - ptr_1_casted - get_size_service_block_block() - get_size_block(ptr_current);
}


size_t memory_with_list::get_size_block(const void * const block) const {
    return *(reinterpret_cast<size_t *>(const_cast<void *>(block)) - 2);
}


void memory_with_list::set_size_block(void *block, size_t size) const {
    *(reinterpret_cast<size_t *>(block) - 2) = size;
}


void **memory_with_list::get_pointer_next(const void * const block) const {
    return reinterpret_cast<void **>(const_cast<void *>(block)) - 1;
}


void *memory_with_list::get_pointer_previous(const void * const block) const {
    void *current = trusted_memory_to_block();
    void *previous = current;
    
    while (current < block) {
        previous = current;
        current = *get_pointer_next(current);
    }

    return previous;
}


size_t memory_with_list::get_size_service_block_allocator() const {
    return sizeof(size_t) + sizeof(void *) + sizeof(void *) + sizeof(logger **);
}


size_t memory_with_list::get_size_service_block_block() const {
    return sizeof(size_t) + sizeof(void **);
}


std::string memory_with_list::print_memory(const void *block) const {
    std::string s;
    s = "[ " + get_bytes(block) + "]";
    
    return s;
}


std::string memory_with_list::print_allocator(const memory_with_list * const allocator) const {
    std::stringstream ss;
    ss << "[ ";


    unsigned char *ptr = reinterpret_cast<unsigned char *>(allocator->_trusted_memory);
    void **ptr_end = allocator->get_pointer_to_end_pointer_allocator();

    while (ptr < *ptr_end) {
        ss << static_cast<int>(*(ptr++)) << " ";
    }

    ss << "]";

    return ss.str();
}


std::string memory_with_list::print_allocator_data(const memory_with_list * const allocator) const {
    std::stringstream ss;
    ss << "[ ";


    unsigned char *ptr = reinterpret_cast<unsigned char *>(reinterpret_cast<void **>(allocator->_trusted_memory) + 4);
    void **ptr_end = allocator->get_pointer_to_end_pointer_allocator();

    while (ptr < *ptr_end) {
        ss << static_cast<int>(*(ptr++)) << " ";
    }

    ss << "]";

    return ss.str();
}


void *memory_with_list::trusted_memory_to_block() const {
    return reinterpret_cast<void *>(reinterpret_cast<size_t *>(_trusted_memory) + 4);
}