#include "../pool/pool.h"
#include <vector>


class database : protected allocating::safe_allocator, protected logging::complete_logger {

public:

    explicit database(allocating::memory *allocator = nullptr, logging::logger *logger = nullptr);

    virtual ~database();


public:

    int create_pool(std::vector<std::string> &query);

    int create_scheme(std::vector<std::string> &query);

    int create_collection(std::vector<std::string> &query);


private:

    associative_container<std::string, pool *> *_data_bases;


private:

    allocating::memory *_allocator;

    logging::logger *_logger;


    allocating::memory *get_allocator() const;

    logging::logger *get_logger() const;

};