#include "../collection/collection.h"


class scheme {

public:

    explicit scheme(allocating::memory *allocator = nullptr, logging::logger *logger = nullptr);

    virtual ~scheme();



public:

    associative_container<std::string, collection *> *_schemes;

    friend class pool;


private:

    allocating::memory *get_allocator() const;

    logging::logger *get_logger() const;


    allocating::memory *_allocator;

    logging::logger *_logger;

};