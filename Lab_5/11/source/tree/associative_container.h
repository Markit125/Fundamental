#ifndef SANDBOX_CPP_ASSOCIATIVE_CONTAINER_H
#define SANDBOX_CPP_ASSOCIATIVE_CONTAINER_H

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

    virtual tvalue &&remove(
        tkey const &key) = 0;
    

    virtual void print_prefix() const = 0;

    virtual void print_infix() const = 0;

    virtual void print_postfix() const = 0;

    virtual void print_container() const = 0;

};

#endif //SANDBOX_CPP_ASSOCIATIVE_CONTAINER_H