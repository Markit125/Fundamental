#include "memory_with_list.h"
#include <cstddef>
#include <string>
#include <sstream>


memory_with_list::memory_with_list() {

    logger_builder *builder = new logger_builder_concrete();

    _logger_allocator = builder
            ->add_stream("log_warning.log", logger::severity::warning)
            ->add_stream("log_trace.log", logger::severity::trace)
            ->add_stream("log_info.log", logger::severity::information)
            ->construct();

    _logger_allocator
            ->log("Logger is built", logger::severity::information)
            ->log("Memory with list is instantiated", logger::severity::information);

    delete builder;
}


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

    _logger_allocator
            ->log("Allocated " + std::to_string(*size) + " bytes of memory at "
            + cast_to_str(new_memory), logger::severity::information);


    return reinterpret_cast<void *>(reinterpret_cast<size_t *>(new_memory) + 1);
}


// void *memory_with_list::allocate(size_t count, size_t size_of_element) const {
//     return allocate(count * size_of_element);
// }


// void memory_with_list::deallocate(void * const target_to_dealloc) const {

//     size_t *target_size = reinterpret_cast<size_t *>(target_to_dealloc) - 1;
//     void *v_ptr = reinterpret_cast<void *>(target_size);

//     _logger_allocator
//             ->log("Deallocated " + cast_to_str(*target_size) + " bytes of memory from "
//             + cast_to_str(target_size) + " that contained bytes: [ "
//             + get_bytes(target_to_dealloc) + " ]",
//             logger::severity::information);

//     ::operator delete(v_ptr);

//     // memory_with_list::operator delete(v_ptr, *target_size + sizeof(size_t));
//     // ::operator delete(reinterpret_cast<void *>(target_size)); //, target_size + sizeof(size_t));
// }


memory_with_list::~memory_with_list() {

    _logger_allocator
            ->log("Allocator is destroyed", logger::severity::information);

    delete _logger_allocator;
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
memory_with_list::memory_with_list(size_t size, memory *outer_allocator, logger *memory_logger,
                memory_with_list::fit_type fit = memory_with_list::fit_type::first) :
                _logger { memory_logger }, _fit { fit } {

    _allocated_memory = outer_allocator == nullptr ?
        ::operator new(size + get_size_service_block()) :
        outer_allocator->allocate_fit(size + get_size_service_block(), fit);

    if (_allocated_memory == nullptr) {
        // TODO: logger
    }

    size_t *pointer_size = reinterpret_cast<size_t *>(_allocated_memory);
    *pointer_size = size;
    void **first_block = reinterpret_cast<void **>(_allocated_memory);
    *first_block = nullptr;
}


// void memory_with_list::set_size_allocator(void *allocated_memory, size_t size) {
//     size_t *pointer_size = reinterpret_cast<size_t *>(allocated_memory);
//     *pointer_size = size;
// }


void *memory_with_list::allocate_fit(size_t size, memory_with_list::fit_type fit = memory_with_list::fit_type::first) {

    void **fit_memory_block = nullptr;

    if (fit == memory_with_list::fit_type::first) {
        fit_memory_block = memory_with_list::find_first_fit(this, size);
    } else if (memory_with_list::fit_type::best) {
        fit_memory_block = memory_with_list::find_best_fit(this, size);
    } else {
        fit_memory_block = memory_with_list::find_worst_fit(this, size);
    }

    if (fit_memory_block == nullptr) {
        return nullptr;
    }

    this->insert_allocator_to_pointer_list(fit_memory_block);

    return fit_memory_block;
}


void **memory_with_list::find_first_fit(void *allocator, size_t size) {

    void *next = get_pointer_next(this);
    void *fit = nullptr;
    size_t size_next;

    while (next != nullptr) {

        size_next = get_size_block(next);
        size_next -= get_size_service_block();

        if (size_next >= size) {
            if ()
        }
        
        next = get_pointer_next(next);

    }


    return ;
}


size_t get_size_block(void * const block) {
    return *(reinterpret_cast<size_t *>(block) - 2);
}


void **memory_with_list::get_pointer_next(void * const block) {
    return reinterpret_cast<void **>(block) - 1;
}


size_t memory_with_list::get_size_service_block() const {
    return sizeof(size_t) + sizeof(void **);
}