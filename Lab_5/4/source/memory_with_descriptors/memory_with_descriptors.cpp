#include "memory_with_descriptors.h"
#include <cstddef>
#include <queue>
#include <stdexcept>
#include <string>
#include <sstream>


template <class T>
std::string cast_to_str(const T& object) {
    std::stringstream ss;
    ss << object;
    return ss.str();
}


void allocating::memory_with_descriptors::deallocate(void * const target_to_dealloc) const {
    
    safe_log("Deallocating...................", logging::logger::severity::trace);

    if (target_to_dealloc == trusted_memory_to_block()) {

        safe_log("Deallocation of inherit allocator", logging::logger::severity::trace);

        memory *outer_allocator = get_outer_allocator();
        outer_allocator->deallocate(target_to_dealloc);

        return;
    }

    safe_log("Deallocation of block", logging::logger::severity::trace);


    void *next = *get_pointer_next(target_to_dealloc);
    void *prev = *get_pointer_previous(target_to_dealloc);


    if (nullptr != next) {
        *(reinterpret_cast<void **>(next) - 2) = prev;
    }
    *(reinterpret_cast<void **>(prev) - 1) = next;

    // size_t size = get_size_block(target_to_dealloc);
    // unsigned char *ptr;    

    // ptr = reinterpret_cast<unsigned char *>(reinterpret_cast<size_t *>(target_to_dealloc) - 2);
    // for (size_t i = 0; i < size; ++i) {
    //     *(ptr++) = 0;
    // }

    safe_log("Deallocation completed!", logging::logger::severity::trace);

}


logging::logger *allocating::memory_with_descriptors::get_logger() const {
    return *reinterpret_cast<logging::logger **>(_trusted_memory);
}

void allocating::memory_with_descriptors::clear_logger() const {
    *reinterpret_cast<logging::logger **>(_trusted_memory) = nullptr;
}


allocating::memory_with_descriptors::~memory_with_descriptors() {


    safe_log("Allocator is destroyed", logging::logger::severity::information);
    clear_logger();

    if (get_outer_allocator() == nullptr) {
        ::operator delete(_trusted_memory);
    } else {
        deallocate(_trusted_memory);
    }

}


std::string allocating::memory_with_descriptors::get_bytes(const void * const memory) {
    
    size_t size = get_size_block(memory) + get_size_service_block_block();
    unsigned char *ptr = reinterpret_cast<unsigned char *>(const_cast<void *>(memory)) - 3;
    
    std::stringstream ss;
    while (size--) {
        ss << static_cast<int>(*(ptr++)) << ' ';
    }

    return ss.str();
}


void *allocating::memory_with_descriptors::get_memory_pointer() {
    return _trusted_memory;
}


void *allocating::memory_with_descriptors::allocate(const size_t target_size) const {


    
    safe_log("New memory allocating............................................", logging::logger::severity::trace);

    void *new_memory = allocate_fit(target_size + get_size_service_block_block(), _fit);

    if (new_memory == nullptr) {

        throw std::runtime_error("There is not enough space for memory allocation!");
    }


    
    safe_log("Allocated block " + std::to_string(target_size) + " bytes of memory at "
                    + cast_to_str(new_memory), logging::logger::severity::information);

    // safe_log("new_memory " + print_memory(new_memory), logging::logger::severity::trace);
    // safe_log("_allocated_memory " + print_allocator(this), logging::logger::severity::trace);

    safe_log("ALLOCATOR " + cast_to_str(_trusted_memory), logging::logger::severity::trace);
    safe_log("Starts at     " + cast_to_str(_trusted_memory), logging::logger::severity::trace);
    safe_log("New memory at " + cast_to_str(new_memory), logging::logger::severity::trace);
    safe_log("Ends at       " + cast_to_str(get_end_allocator()), logging::logger::severity::trace);
    

    return new_memory;
}


// ONLY FOR ALLOCATOR
allocating::memory_with_descriptors::memory_with_descriptors(
        size_t size, memory *outer_allocator, logging::logger *memory_logger,
        allocating::memory_with_descriptors::fit_type fit = allocating::memory_with_descriptors::fit_type::first
    ) : _fit { fit } {
    

    _trusted_memory = outer_allocator == nullptr ?
        ::operator new(size + get_size_service_block_allocator()) :
        outer_allocator->allocate(size + get_size_service_block_allocator());


    if (_trusted_memory == nullptr) {

        safe_log("Cannot allocate " + cast_to_str(size) + " bytes of memory", logging::logger::severity::error);

        throw std::runtime_error("There is not enough space for allocator!");
    }


    logging::logger **logger_ptr = reinterpret_cast<logging::logger **>(_trusted_memory);
    *logger_ptr = memory_logger;


    
    safe_log("Allocated allocator with " + cast_to_str(size) + " bytes of memory at " + cast_to_str(_trusted_memory),
                logging::logger::severity::information);


    size_t *pointer_size = reinterpret_cast<size_t *>(_trusted_memory) + 2;
    *pointer_size = size;

    void **previous_block = reinterpret_cast<void **>(_trusted_memory) + 3;
    *previous_block = nullptr;
    void **first_block = reinterpret_cast<void **>(_trusted_memory) + 4;
    *first_block = reinterpret_cast<unsigned char *>(_trusted_memory) + size + get_size_service_block_allocator();
    

    

    safe_log("Memory of new Allocator", logging::logger::severity::trace);
    safe_log("Start at " + cast_to_str(_trusted_memory), logging::logger::severity::trace);
    safe_log("New a at " + cast_to_str(_trusted_memory), logging::logger::severity::trace);
    safe_log("  End at " + cast_to_str(*first_block), logging::logger::severity::trace);




    if (outer_allocator == nullptr) {

        set_outer_allocator(nullptr);

        unsigned char *ptr = reinterpret_cast<unsigned char *>(reinterpret_cast<size_t *>(_trusted_memory) + 5);
        for (size_t i = 0; i < size; ++i) {
            *(ptr++) = 0;
        }
        
    } else {
        set_outer_allocator(outer_allocator);
    }

  
    // safe_log("New allocator _allocated_memory " + print_allocator(this), logging::logger::severity::trace);

}


void *allocating::memory_with_descriptors::allocate_fit(size_t size, allocating::memory_with_descriptors::fit_type fit = allocating::memory_with_descriptors::fit_type::first) const {


    void *fit_memory_block;
    
    
    safe_log("Start finding memory block for allocator with size " + cast_to_str(size) + " bytes",
                logging::logger::severity::information);


    if (fit == allocating::memory_with_descriptors::fit_type::first) {
        fit_memory_block = allocating::memory_with_descriptors::find_first_fit(size);
    } else if (fit == allocating::memory_with_descriptors::fit_type::best) {
        fit_memory_block = allocating::memory_with_descriptors::find_best_fit(size);
    } else {
        fit_memory_block = allocating::memory_with_descriptors::find_worst_fit(size);
    }


    if (fit_memory_block == nullptr) {
     
        safe_log("There is no memory for allocator with size " + cast_to_str(size), logging::logger::severity::error);

        return nullptr;

    } else {
        safe_log(cast_to_str(size) + " bytes of memory is allocated", logging::logger::severity::trace);
    }

    set_size_block(fit_memory_block, size);

    safe_log("Size is sat", logging::logger::severity::trace);

    insert_block_to_pointer_list(fit_memory_block);

    

    safe_log("Block is inserted to the list", logging::logger::severity::trace);

    // safe_log("block fit after " + cast_to_str(fit_memory_block), logging::logger::severity::trace);


    // safe_log("Next block at " + cast_to_str(*get_pointer_next(fit_memory_block)), logging::logger::severity::trace);
    // safe_log("New memory at " + cast_to_str(fit_memory_block), logging::logger::severity::trace);
    // safe_log("Prev block at " + cast_to_str(*get_pointer_previous(fit_memory_block)), logging::logger::severity::trace);

    return fit_memory_block;
}


void allocating::memory_with_descriptors::insert_block_to_pointer_list(void *block) const {
    
    void *previous = *get_pointer_previous(block);
    void *next = *get_pointer_next(block);

    


    // while (block > ptr_current) {
    //     previous = ptr_current;
    //     ptr_current = *get_pointer_next(ptr_current);

    //     safe_log("cur " + cast_to_str(ptr_current) + " prev " + cast_to_str(previous) + " block " + cast_to_str(block),
    //             logging::logger::severity::trace);
    // }


    safe_log("prev  " + cast_to_str(previous) + " next " + cast_to_str(next), logging::logger::severity::trace);

    *(reinterpret_cast<void **>(previous) - 1) = block;
    *(reinterpret_cast<void **>(next) - 2) = block;
    // set_pointer_to_next_block(previous, &block);
    
    // set_pointer_to_previous_block(next, &block);


    safe_log("prev  " + cast_to_str(previous) + " next " + cast_to_str(*get_pointer_next(previous)), logging::logger::severity::trace);
    safe_log("block " + cast_to_str(block) + " next " + cast_to_str(*get_pointer_next(block)), logging::logger::severity::trace);
    
}


void allocating::memory_with_descriptors::set_pointer_to_next_block(void *block, void **pointer) {
    *(reinterpret_cast<void **>(block) - 1) = *pointer;
}

void allocating::memory_with_descriptors::set_pointer_to_previous_block(void *block, void **pointer) {
    *(reinterpret_cast<void **>(block) - 2) = *pointer;
}


// Allocator
//      0                 1                     2           3             4                      5
// | logger | pointer to outer allocator | size of all | nullptr | pointer to next | allocated memory for use | *end |
//                                                  ^                          ^
//                        pointer to next points to |           or          to | 

void *allocating::memory_with_descriptors::find_first_fit(size_t size) const {
    //                          size of block plus service block


    void **ptr_next = get_pointer_next(trusted_memory_to_block());

    void *current_memory = trusted_memory_to_block();
    void **ptr_current = &current_memory;
    void **ptr_prev = &current_memory;
    
    void *ptr_end = get_end_allocator();

    void **fit = nullptr;
    size_t free_space;

    
    safe_log("Start jumping between memory blocks", logging::logger::severity::trace);
    
    if (*ptr_next == ptr_end) {

        free_space = get_space_between(*ptr_current, *ptr_next) + get_size_block(*ptr_current);

        
        safe_log("First block! Space for data between " + cast_to_str(*ptr_current) + " and " + cast_to_str(ptr_end) +
                    " is " + cast_to_str(free_space), logging::logger::severity::trace);

        if (free_space >= size) {
            current_memory = reinterpret_cast<void *>(reinterpret_cast<size_t *>(*ptr_current) + 3);
            fit = &current_memory;

            *(reinterpret_cast<void **>(current_memory) - 1) = ptr_end;
            *(reinterpret_cast<void **>(current_memory) - 2) = trusted_memory_to_block();

        } else {
            ptr_current = get_pointer_next(*ptr_current);
        }

    } else {

        while (*ptr_current < ptr_end) {

            
            free_space = get_space_between(*ptr_current, *ptr_next);

            
            safe_log("Space for data between " + cast_to_str(*ptr_current) + " and " + cast_to_str(*ptr_next) +
                        " is " + cast_to_str(free_space),
                        logging::logger::severity::trace);
            safe_log("Size need " + cast_to_str(size), logging::logger::severity::trace);



            if (free_space >= size) {
                
                current_memory = reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(*ptr_current) + get_size_block(*ptr_current) + sizeof(size_t *) * 3);
                fit = &current_memory;

                *(reinterpret_cast<void **>(current_memory) - 1) = get_pointer_next(*ptr_current);
                *(reinterpret_cast<void **>(current_memory) - 2) = ptr_prev;
                break;
            }

            ptr_prev = ptr_current;
            ptr_current = get_pointer_next(*ptr_current);
            ptr_next = get_pointer_next(*ptr_current);
                        
        }
    }



    if (fit == nullptr) {
        
        
        safe_log("Cannot find memory block with " + cast_to_str(size) + " bytes of memory (first fit)",
                    logging::logger::severity::error);

        return nullptr;

    } else {
        safe_log("Found first fit block with size " + cast_to_str(size) + " at " + cast_to_str(*fit), logging::logger::severity::information);
    }

    
    safe_log("_allocated_memory " + cast_to_str(_trusted_memory), logging::logger::severity::trace);
    safe_log("block fit " + cast_to_str(*fit), logging::logger::severity::trace);
    

    return *fit;
}


void *allocating::memory_with_descriptors::find_best_fit(size_t size) const {
    //                          size of block plus service block


    void **ptr_next = get_pointer_next(trusted_memory_to_block());
    void *current_memory = trusted_memory_to_block();
    void **ptr_current = &current_memory;
    void **ptr_prev = &current_memory;
    
    void *ptr_end = get_end_allocator();

    void **fit = nullptr;
    size_t free_space;

    
    safe_log("Start jumping between memory blocks", logging::logger::severity::trace);
   
    if (*ptr_next == ptr_end) {

        free_space = get_space_between(*ptr_current, *ptr_next) + get_size_block(*ptr_current);

        safe_log("Space " + cast_to_str(get_space_between(*ptr_current, *ptr_next)), logging::logger::severity::trace);
        safe_log("Size " + cast_to_str(get_size_block(*ptr_current)), logging::logger::severity::trace);
        
        safe_log("First block! Space for data between " + cast_to_str(*ptr_current) + " and " + cast_to_str(ptr_end) +
                    " is " + cast_to_str(free_space), logging::logger::severity::trace);
        

        if (free_space >= size) {
            current_memory = reinterpret_cast<void *>(reinterpret_cast<size_t *>(*ptr_current) + 3);
            fit = &current_memory;

            *(reinterpret_cast<void **>(current_memory) - 1) = ptr_end;
            *(reinterpret_cast<void **>(current_memory) - 2) = trusted_memory_to_block();

        } else {
            ptr_current = get_pointer_next(*ptr_current);
        }

    } else {

        size_t best_size = -1;

        while (*ptr_current < ptr_end) {
            
            free_space = get_space_between(*ptr_current, *ptr_next);

            
            safe_log("Space for data between " + cast_to_str(*ptr_current) + " and " + cast_to_str(*ptr_next) +
                        " is " + cast_to_str(free_space),
                        logging::logger::severity::trace);
            safe_log("Size need " + cast_to_str(size), logging::logger::severity::trace);
            


            if (free_space >= size) {

                if (best_size > free_space) {

                    current_memory = reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(*ptr_current) + get_size_block(*ptr_current) + sizeof(size_t *) * 3);
                    fit = &current_memory;

                    *(reinterpret_cast<void **>(current_memory) - 1) = get_pointer_next(*ptr_current);
                    *(reinterpret_cast<void **>(current_memory) - 2) = ptr_prev;

                    best_size = free_space;
                }

            }

            ptr_prev = ptr_current;
            ptr_current = get_pointer_next(*ptr_current);
            ptr_next = get_pointer_next(*ptr_current);
            
        }
    }



    if (fit == nullptr) {
        
        
        safe_log("Cannot find memory block with " + cast_to_str(size) + " bytes of memory (best fit)",
                    logging::logger::severity::error);
        

        return nullptr;

    } else {
        safe_log("Found first fit block with size " + cast_to_str(size) + " at " + cast_to_str(*fit), logging::logger::severity::information);
    }

    
    safe_log("_allocated_memory " + cast_to_str(_trusted_memory), logging::logger::severity::trace);
    safe_log("block fit " + cast_to_str(*fit), logging::logger::severity::trace);
    

    return *fit;
}


void *allocating::memory_with_descriptors::find_worst_fit(size_t size) const {
    //                          size of block plus service block


    void **ptr_next = get_pointer_next(trusted_memory_to_block());

    void *current_memory = trusted_memory_to_block();
    void **ptr_current = &current_memory;
    void **ptr_prev = &current_memory;
    
    void *ptr_end = get_end_allocator();

    void **fit = nullptr;
    size_t free_space;

    
    safe_log("Start jumping between memory blocks", logging::logger::severity::trace);
        
    if (*ptr_next == ptr_end) {

        free_space = get_space_between(*ptr_current, *ptr_next) + get_size_block(*ptr_current);

        
        safe_log("First block! Space for data between " + cast_to_str(*ptr_current) + " and " + cast_to_str(ptr_end) +
                    " is " + cast_to_str(free_space), logging::logger::severity::trace);
        

        if (free_space >= size) {
            current_memory = reinterpret_cast<void *>(reinterpret_cast<size_t *>(*ptr_current) + 3);
            fit = &current_memory;

            *(reinterpret_cast<void **>(current_memory) - 1) = ptr_end;
            *(reinterpret_cast<void **>(current_memory) - 2) = trusted_memory_to_block();

        } else {
            ptr_current = get_pointer_next(*ptr_current);
        }

    } else {

        size_t worst_size = 0;

        while (*ptr_current < ptr_end) {
            
            free_space = get_space_between(*ptr_current, *ptr_next);

            
            safe_log("Space for data between " + cast_to_str(*ptr_current) + " and " + cast_to_str(*ptr_next) +
                        " is " + cast_to_str(free_space),
                        logging::logger::severity::trace);
            safe_log("Size need " + cast_to_str(size), logging::logger::severity::trace);
            
            if (free_space >= size) {

                if (worst_size < free_space) {

                    current_memory = reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(*ptr_current) + get_size_block(*ptr_current) + sizeof(size_t *) * 3);
                    fit = &current_memory;

                    *(reinterpret_cast<void **>(current_memory) - 1) = get_pointer_next(*ptr_current);
                    *(reinterpret_cast<void **>(current_memory) - 2) = ptr_prev;

                    worst_size = free_space;
                }

            }

            ptr_prev = ptr_current;
            ptr_current = get_pointer_next(*ptr_current);
            ptr_next = get_pointer_next(*ptr_current);

            
            safe_log("ptr_current: " + cast_to_str(*ptr_current), logging::logger::severity::trace);
            safe_log("ptr_end: " + cast_to_str(ptr_end), logging::logger::severity::trace);
            
        }
    }


    if (fit == nullptr) {
        
        
        safe_log("Cannot find memory block with " + cast_to_str(size) + " bytes of memory (worst fit)",
                    logging::logger::severity::error);

        return nullptr;

    } else {
        safe_log("Found first fit block with size " + cast_to_str(size) + " at " + cast_to_str(*fit), logging::logger::severity::information);
    }


    safe_log("_allocated_memory " + cast_to_str(_trusted_memory), logging::logger::severity::trace);
    safe_log("block fit " + cast_to_str(*fit), logging::logger::severity::trace);
    

    return *fit;
}



size_t allocating::memory_with_descriptors::get_space_between(void *ptr_current, void *ptr_next) {

    unsigned char *ptr_1_casted = reinterpret_cast<unsigned char *>(ptr_current);
    unsigned char *ptr_2_casted = reinterpret_cast<unsigned char *>(ptr_next);

    if (ptr_2_casted - ptr_1_casted - (long) get_size_block(ptr_current) < (long) get_size_service_block_block()) {
        return 0;
    }

    return  ptr_2_casted - ptr_1_casted - get_size_service_block_block() - get_size_block(ptr_current);
}


size_t allocating::memory_with_descriptors::get_size_block(const void * const block) {
    return *(reinterpret_cast<size_t *>(const_cast<void *>(block)) - 3);
}


void allocating::memory_with_descriptors::set_size_block(void *block, size_t size) {
    *(reinterpret_cast<size_t *>(block) - 3) = size;
}


void **allocating::memory_with_descriptors::get_pointer_next(const void * const block) const {
    return reinterpret_cast<void **>(const_cast<void *>(block)) - 1;
}


void **allocating::memory_with_descriptors::get_pointer_previous(const void * const block) const {
    return reinterpret_cast<void **>(const_cast<void *>(block)) - 2;

    // if (nullptr == previous) {
    //     void *trusted = trusted_memory_to_block();
    //     void **ptr_trusted = &trusted;
    //     return ptr_trusted;
    // }
}


size_t allocating::memory_with_descriptors::get_size_service_block_allocator() {
    return sizeof(size_t) + sizeof(void *) + sizeof(void *) + sizeof(void *) + sizeof(logging::logger **);
}


size_t allocating::memory_with_descriptors::get_size_service_block_block() {
    return sizeof(size_t) + sizeof(void **) + sizeof(void **);
}


std::string allocating::memory_with_descriptors::print_memory(const void *block) {
    std::string s;
    s = "[ " + get_bytes(block) + "]";
    
    return s;
}


std::string allocating::memory_with_descriptors::print_allocator(const memory * const allocator) {
    memory_with_descriptors *allocator_memory = reinterpret_cast<memory_with_descriptors *>(const_cast<memory *>(allocator));
    std::stringstream ss;
    ss << "[ ";


    unsigned char *ptr = reinterpret_cast<unsigned char *>(allocator_memory->_trusted_memory);
    void *ptr_end = allocator_memory->get_end_allocator();

    while (ptr < ptr_end) {
        ss << static_cast<int>(*(ptr++)) << " ";
    }

    ss << "]";

    return ss.str();
}


std::string allocating::memory_with_descriptors::print_allocator_data(const memory * const allocator) {
    memory_with_descriptors *allocator_memory = reinterpret_cast<memory_with_descriptors *>(const_cast<memory *>(allocator));
    std::stringstream ss;
    ss << "[ ";


    unsigned char *ptr = reinterpret_cast<unsigned char *>(reinterpret_cast<void **>(allocator_memory->_trusted_memory) + 5);
    void *ptr_end = allocator_memory->get_end_allocator();

    while (ptr < ptr_end) {
        ss << static_cast<int>(*(ptr++)) << " ";
    }

    ss << "]";

    return ss.str();
}


void *allocating::memory_with_descriptors::trusted_memory_to_block() const {
    return reinterpret_cast<void *>(reinterpret_cast<size_t *>(_trusted_memory) + 5);
}


void **allocating::memory_with_descriptors::pointer_to_trusted_memory_to_block() const {
    void *trusted = reinterpret_cast<void **>(reinterpret_cast<size_t *>(_trusted_memory) + 5);
    void **trusted_ptr = &trusted;
    return trusted_ptr;
}


void *allocating::memory_with_descriptors::get_end_allocator() const {
    return reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(_trusted_memory) +
        *(reinterpret_cast<size_t *>(_trusted_memory) + 2) + get_size_service_block_allocator());
}


allocating::memory *allocating::memory_with_descriptors::get_outer_allocator() const {
    return *(reinterpret_cast<allocating::memory **>(_trusted_memory) + 1);
}

void allocating::memory_with_descriptors::set_outer_allocator(memory *allocator) {
    *(reinterpret_cast<memory **>(_trusted_memory) + 1) = allocator;
}