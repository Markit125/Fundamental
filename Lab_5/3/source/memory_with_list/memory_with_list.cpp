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


void *memory_with_list::allocate(size_t const targer_size) const {

    void *new_memory = ::operator new(sizeof(size_t) + targer_size);

    size_t *size = reinterpret_cast<size_t *>(new_memory);
    *size = targer_size;

    _logger->log("Allocated " + std::to_string(*size) + " bytes of memory at "
            + cast_to_str(new_memory), logger::severity::information);


    return reinterpret_cast<void *>(reinterpret_cast<size_t *>(new_memory) + 1);
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

// ONLY FOR ALLOCATOR
memory_with_list::memory_with_list(
        size_t size, memory_with_list *outer_allocator, logger *memory_logger,
        memory_with_list::fit_type fit = memory_with_list::fit_type::first
    ) : _logger { memory_logger }, _fit { fit } {

    _allocated_memory = outer_allocator == nullptr ?
        ::operator new(size + get_size_service_block_allocator()) :
        outer_allocator->allocate_fit(size + get_size_service_block_allocator(), fit);

    if (_allocated_memory == nullptr) {
        _logger->log("Cannot allocate " + cast_to_str(size) + " bytes of memory",
                logger::severity::error);
        return;
    }

    _logger->log("Allocated " + cast_to_str(size) + " bytes of memory at " + cast_to_str(_allocated_memory),
                logger::severity::information);

    void **end_ptr = reinterpret_cast<void **>(_allocated_memory);
    *end_ptr = reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(_allocated_memory) + size + get_size_service_block_allocator());;

    size_t *pointer_size = reinterpret_cast<size_t *>(_allocated_memory) + 1;
    *pointer_size = size;

    void **first_block = reinterpret_cast<void **>(_allocated_memory) + 2;
    *first_block = *end_ptr;

}


// void memory_with_list::set_size_allocator(void *allocated_memory, size_t size) {
//     size_t *pointer_size = reinterpret_cast<size_t *>(allocated_memory);
//     *pointer_size = size;
// }


void *memory_with_list::allocate_fit(size_t size, memory_with_list::fit_type fit = memory_with_list::fit_type::first) {

    void **fit_memory_block = nullptr;

    _logger->log("Start finding memory block for allocator with size " + cast_to_str(size) + " bytes",
                logger::severity::information);

    if (fit == memory_with_list::fit_type::first) {
        fit_memory_block = this->memory_with_list::find_first_fit(size);
    } else if (memory_with_list::fit_type::best) {
        // fit_memory_block = this->memory_with_list::find_best_fit(size);
    } else {
        // fit_memory_block = this->memory_with_list::find_worst_fit(size);
    }

    if (fit_memory_block == nullptr) {
        _logger->log("There is no memory for allocator with size " + cast_to_str(size), logger::severity::error);
        return nullptr;
    }

    

    this->insert_allocator_to_pointer_list(fit_memory_block);

    return fit_memory_block;
}


void memory_with_list::insert_allocator_to_pointer_list(void **block) {
    void **current = reinterpret_cast<void **>(reinterpret_cast<size_t>(this->_allocated_memory) + get_size_service_block_allocator());
    void **previous = nullptr;
    
    while (block > current) {
        previous = current;
        current = get_pointer_next(*current);
    }

    set_pointer_to_next_block(*block, current);
    
    set_pointer_to_next_block(*previous, block);
}


void memory_with_list::set_pointer_to_next_block(void *block, void **pointer) {
    *(reinterpret_cast<void **>(reinterpret_cast<size_t *>(block) - 1)) = pointer;
}


void **memory_with_list::get_pointer_to_end_allocator() {
    return reinterpret_cast<void **>(_allocated_memory);
}



// | pointer to end | size of all | pointer to next | allocated memory for use | *end |


void **memory_with_list::find_first_fit(size_t size) {
    //                          size of block plus service block
    void **next = reinterpret_cast<void **>(this->_allocated_memory) + 2;
    // void **next = get_pointer_next(this);
    void **current = reinterpret_cast<void **>(this->_allocated_memory) + 3;
    
    void **fit = nullptr;
    size_t free_space;


    _logger->log("Start jumping between memory blocks", logger::severity::trace);


    void *end = *(this->get_pointer_to_end_allocator());


    _logger->log("end: " + cast_to_str(end) + " next " + cast_to_str(next),
                logger::severity::trace);

    while (next < end) {

        _logger->log("Current: " + cast_to_str(current) + " next: " + cast_to_str(next)
                        + " distance is " + cast_to_str(free_space),
                logger::severity::trace);

        // FIXME: get_space_beetween
        // current < next for some reason
        free_space = get_space_beetween(current, next);
        // size_next = get_size_block(next);

        _logger->log("Space between " + cast_to_str(current) + " and " + cast_to_str(next) + " is " + cast_to_str(free_space),
                logger::severity::trace);

        if (free_space >= size) {
            *fit = reinterpret_cast<void *>(reinterpret_cast<size_t *>(*current) + get_size_block(*current) + 2);
            break;
        }

        next = get_pointer_next(*next);
    }

    if (next == end) {
        _logger->log("Cannot find memory block with " + cast_to_str(size) + " bytes of memory (first fit)",
                    logger::severity::error);
    } else {
        _logger->log("Found first fit block with size " + cast_to_str(size) + " at " + cast_to_str(fit), logger::severity::information);
    }

    return fit;
}


size_t memory_with_list::get_space_beetween(void **ptr_1, void **ptr_2) const {
    size_t size = get_size_block(*ptr_1);

    return ptr_2 - ptr_1 - size;
}


size_t memory_with_list::get_size_block(void * const block) const {
    return *(reinterpret_cast<size_t *>(block) - 2);
}


void memory_with_list::set_size_block(void * block, size_t size) {
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