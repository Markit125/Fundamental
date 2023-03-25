#include "memory_with_list.h"
#include "logger.h"
#include <cstddef>
#include <string>
#include <sstream>


// memory_with_list::memory_with_list() {

//     logger_builder *builder = new logger_builder_concrete();

//     _logger_allocator = builder
//             ->add_stream("log_warning.log", logger::severity::warning)
//             ->add_stream("log_trace.log", logger::severity::trace)
//             ->add_stream("log_info.log", logger::severity::information)
//             ->construct();

//     _logger_allocator
//             ->log("Logger is built", logger::severity::information)
//             ->log("Memory with list is instantiated", logger::severity::information);

//     delete builder;
// }


template <class T>
std::string cast_to_str(const T& object) {
    std::stringstream ss;
    ss << object;
    return ss.str();
}


// void *memory_with_list::allocate(size_t count, size_t size_of_element) const {
//     return allocate(count * size_of_element);
// }


void memory_with_list::deallocate(void * const target_to_dealloc) const {

    size_t *target_size = reinterpret_cast<size_t *>(target_to_dealloc) - 1;
    void *v_ptr = reinterpret_cast<void *>(target_size);

    _logger->log("Deallocated " + cast_to_str(*target_size) + " bytes of memory from "
            + cast_to_str(target_size) + " that contained bytes: [ "
            + get_bytes(target_to_dealloc) + "]",
            logger::severity::information);

    ::operator delete(v_ptr);

    // memory_with_list::operator delete(v_ptr, *target_size + sizeof(size_t));
    // ::operator delete(reinterpret_cast<void *>(target_size)); //, target_size + sizeof(size_t));
}


memory_with_list::~memory_with_list() {

    _logger->log("Allocator is destroyed", logger::severity::information);

    delete _logger;
}


size_t memory_with_list::get_size(void * const object) const {
    return *(reinterpret_cast<size_t *>(object) - 1);
}


std::string memory_with_list::get_bytes(void * const memory) const {
    
    size_t size = memory_with_list::get_size(memory);
    unsigned char *ptr = reinterpret_cast<unsigned char *>(memory);
    std::stringstream ss;
    while (size-- > 0) {
        ss << static_cast<int>(*(ptr++)) << ' ';
    }

    return ss.str();
}


void *memory_with_list::get_memory_pointer() {
    return _allocated_memory;
}


void *memory_with_list::allocate(size_t const targer_size) const {

    _logger->log("New memory allocating............................................", logger::severity::trace);

    void **new_memory = allocate_fit(targer_size + get_size_service_block_block(), _fit);


    _logger->log("Allocated block " + std::to_string(targer_size) + " bytes of memory at "
            + cast_to_str(*new_memory), logger::severity::information);

    _logger->log("Start at " + cast_to_str(_allocated_memory), logger::severity::trace);
    _logger->log("New m at " + cast_to_str(*new_memory), logger::severity::trace);
    _logger->log("  End at " + cast_to_str(*(get_pointer_to_end_pointer_allocator())), logger::severity::trace);

    return *new_memory;
}


// ONLY FOR ALLOCATOR
memory_with_list::memory_with_list(
        size_t size, memory_with_list *outer_allocator, logger *memory_logger,
        memory_with_list::fit_type fit = memory_with_list::fit_type::first
    ) : _logger { memory_logger }, _fit { fit } {


    _logger->log("New allocator allocating.........................................", logger::severity::trace);

    _allocated_memory = outer_allocator == nullptr ?
        ::operator new(size + get_size_service_block_allocator()) :
        *(outer_allocator->allocate_fit(size + get_size_service_block_allocator() + get_size_service_block_block(), fit));

    if (_allocated_memory == nullptr) {
        
        _logger->log("Cannot allocate " + cast_to_str(size) + " bytes of memory", logger::severity::error);
        return;
    }

    if (outer_allocator) {

        _logger->log("Memory of newAllocator", logger::severity::trace);
        _logger->log("Start at " + cast_to_str(outer_allocator->_allocated_memory), logger::severity::trace);
        _logger->log("New a at " + cast_to_str(_allocated_memory), logger::severity::trace);
        _logger->log("  End at " + cast_to_str(*(outer_allocator->get_pointer_to_end_pointer_allocator())), logger::severity::trace);
    }

    _logger->log("Allocated allocator with " + cast_to_str(size) + " bytes of memory at " + cast_to_str(_allocated_memory),
                logger::severity::information);

    void **end_ptr = get_pointer_to_end_pointer_allocator();
    *end_ptr = reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(_allocated_memory) + size + get_size_service_block_allocator());

    size_t *pointer_size = reinterpret_cast<size_t *>(_allocated_memory) + 1;
    *pointer_size = 0;

    void **first_block = reinterpret_cast<void **>(_allocated_memory) + 2;
    *first_block = *end_ptr;

}


// void memory_with_list::set_size_allocator(void *allocated_memory, size_t size) {
//     size_t *pointer_size = reinterpret_cast<size_t *>(allocated_memory);
//     *pointer_size = size;
// }


void **memory_with_list::allocate_fit(size_t size, memory_with_list::fit_type fit = memory_with_list::fit_type::first) const {

    void **fit_memory_block = nullptr;
    

    _logger->log("Start finding memory block for allocator with size " + cast_to_str(size) + " bytes",
                logger::severity::information);

    if (fit == memory_with_list::fit_type::first) {
        fit_memory_block = memory_with_list::find_first_fit(size);
    } else if (memory_with_list::fit_type::best) {
        // fit_memory_block = this->memory_with_list::find_best_fit(size);
    } else {
        // fit_memory_block = this->memory_with_list::find_worst_fit(size);
    }


    _logger->log("block fit after " + cast_to_str(*fit_memory_block), logger::severity::trace);
    _logger->log("block fit after " + cast_to_str(*fit_memory_block), logger::severity::trace);


    _logger->log("(allocate_fit) block at " + cast_to_str(*fit_memory_block), logger::severity::trace);

    if (fit_memory_block == nullptr) {
        _logger->log("There is no memory for allocator with size " + cast_to_str(size), logger::severity::error);
        return nullptr;
    } else {
        _logger->log(cast_to_str(size) + " bytes of memory is allocated", logger::severity::trace);
    }



    

    insert_allocator_to_pointer_list(*fit_memory_block);

    _logger->log("Block is inserted to the list", logger::severity::trace);

    _logger->log("block fit after " + cast_to_str(*fit_memory_block), logger::severity::trace);

    return fit_memory_block;
}


void memory_with_list::insert_allocator_to_pointer_list(void *block) const {
    void *ptr_current = reinterpret_cast<void *>(reinterpret_cast<size_t *>(_allocated_memory) + 3);
    // void **ptr_current = &current;
    
    void *previous = ptr_current;

    // _logger->log("block " + cast_to_str(block), logger::severity::trace);
    
    // _logger->log("cur " + cast_to_str(ptr_current) + " prev " + cast_to_str(previous) + " block " + cast_to_str(block),
    //             logger::severity::trace);


    while (block > ptr_current) {
        previous = ptr_current;
        ptr_current = get_pointer_next(ptr_current);
    }

    // _logger->log("cur " + cast_to_str(ptr_current) + " prev " + cast_to_str(previous) + " block " + cast_to_str(block),
    //             logger::severity::trace);


    set_pointer_to_next_block(block, &ptr_current);
    
    set_pointer_to_next_block(previous, &block);
}


void memory_with_list::set_pointer_to_next_block(void *block, void **pointer) const {
    *(reinterpret_cast<void **>(reinterpret_cast<size_t *>(block) - 1)) = pointer;
}


void **memory_with_list::get_pointer_to_end_pointer_allocator() const {
    return reinterpret_cast<void **>(_allocated_memory);
}

// Allocator
//          0              1               2                    3
// | pointer to end | size of all | pointer to next | allocated memory for use | *end |
//                                                  ^                          ^
//                        pointer to next points to |           or          to | 

void **memory_with_list::find_first_fit(size_t size) const {
    //                          size of block plus service block
    void **ptr_next = reinterpret_cast<void **>(_allocated_memory) + 2;

    void *current_memory = reinterpret_cast<void *>(reinterpret_cast<void **>(_allocated_memory) + 3);
    void **ptr_current = &current_memory;
    
    void **fit = nullptr;
    size_t free_space;


    _logger->log("Start jumping between memory blocks", logger::severity::trace);


    void **ptr_end = get_pointer_to_end_pointer_allocator();



    _logger->log(">>>>>>>ptr_current: " + cast_to_str(*ptr_current), logger::severity::trace);
        _logger->log("prt_end: " + cast_to_str(*ptr_end), logger::severity::trace);

    while (*ptr_current < *ptr_end) {

        
        free_space = get_space_beetween(*ptr_current, *ptr_next);
    
        _logger->log("Space for data between " + cast_to_str(*ptr_current) + " and " + cast_to_str(*ptr_next) +
                     " is " + cast_to_str(free_space),
                    logger::severity::trace);


        if (free_space >= size) {
            current_memory = reinterpret_cast<void *>(reinterpret_cast<size_t *>(*ptr_current) + 2);
            fit = &current_memory;
            break;
        }

        // _logger->log("----->>>ptr_current: " + cast_to_str(*ptr_current), logger::severity::trace);
        // _logger->log("prt_next: " + cast_to_str(*ptr_next), logger::severity::trace);

        ptr_current = get_pointer_next(*ptr_current);
        ptr_next = get_pointer_next(*ptr_current);

        // _logger->log("----->>>ptr_current: " + cast_to_str(*ptr_current), logger::severity::trace);
        // _logger->log("prt_next: " + cast_to_str(*ptr_next), logger::severity::trace);

        _logger->log("ptr_current: " + cast_to_str(*ptr_current), logger::severity::trace);
        _logger->log("prt_end: " + cast_to_str(*ptr_end), logger::severity::trace);
    }


    if (*ptr_current == *ptr_end) {
        _logger->log("Cannot find memory block with " + cast_to_str(size) + " bytes of memory (first fit)",
                    logger::severity::error);
    } else {
        _logger->log("Found first fit block with size " + cast_to_str(size) + " at " + cast_to_str(*fit), logger::severity::information);
    }

    _logger->log("_allocated_memory " + cast_to_str(_allocated_memory), logger::severity::trace);

    _logger->log("block fit " + cast_to_str(*fit), logger::severity::trace);

    return fit;
}


size_t memory_with_list::get_space_beetween(void *ptr_current, void *ptr_next) const {

    unsigned char *ptr_1_casted = reinterpret_cast<unsigned char *>(ptr_current);
    unsigned char *ptr_2_casted = reinterpret_cast<unsigned char *>(ptr_next);

    if (ptr_2_casted - ptr_1_casted < (long) get_size_service_block_block()) {
        return 0;
    }

    return  ptr_2_casted - ptr_1_casted - get_size_service_block_block() - get_size_block(ptr_current);
}




size_t memory_with_list::get_size_block(void * const block) const {
    return *(reinterpret_cast<size_t *>(block) - 2);
}


void memory_with_list::set_size_block(void *block, size_t size) const {
    *(reinterpret_cast<size_t *>(block) - 2) = size;
}


void **memory_with_list::get_pointer_next(void * const block) const {
    return reinterpret_cast<void **>(block) - 1;
}


size_t memory_with_list::get_size_service_block_allocator() const {
    return sizeof(size_t) + sizeof(void *) + sizeof(void *);
}


size_t memory_with_list::get_size_service_block_block() const {
    return sizeof(size_t) + sizeof(void **);
}