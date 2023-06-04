#include "../collection/collection.h"


class scheme : protected allocating::safe_allocator, protected logging::complete_logger {

    friend class database;

public:

    explicit scheme(allocating::memory *allocator = nullptr, logging::logger *logger = nullptr);

    virtual ~scheme();


private:

    associative_container<std::string, collection *> *_collections;


private:

    allocating::memory *get_allocator() const;

    logging::logger *get_logger() const;


    allocating::memory *_allocator;

    logging::logger *_logger;

};