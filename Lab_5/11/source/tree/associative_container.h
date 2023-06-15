#ifndef SANDBOX_CPP_ASSOCIATIVE_CONTAINER_H
#define SANDBOX_CPP_ASSOCIATIVE_CONTAINER_H

#include <sstream>
#include <utility>


template<
    typename tkey,
    typename tvalue>
class associative_container
{

public:

    virtual ~associative_container() = default;


public:

    virtual void insert(
        tkey const &key,
        tvalue &&value) = 0;

    virtual tvalue const &get(
        tkey const &key) = 0;

    virtual tvalue&& remove(
        tkey const &key) = 0;

    virtual bool find(
        tkey const &key,
        std::pair<tkey, tvalue *> *) = 0;
    

    virtual void print_notes_between(std::stringstream &out_stream, tkey left_bound, tkey right_bound) = 0;

    virtual void print_container() const = 0;

    virtual void print_container_logger() const = 0;

};

#endif //SANDBOX_CPP_ASSOCIATIVE_CONTAINER_H