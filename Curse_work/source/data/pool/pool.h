#include "../scheme/scheme.h"


class pool : protected allocating::safe_allocator, protected logging::complete_logger {

    friend class database;

public:

    explicit pool(allocating::memory *allocator = nullptr, logging::logger *logger = nullptr);

    virtual ~pool();


private:

    associative_container<std::string, scheme *> *_schemes;


private:

    allocating::memory *get_allocator() const;

    logging::logger *get_logger() const;


    allocating::memory *_allocator;

    logging::logger *_logger;

};