#include "../collection/collection.h"


class scheme : protected allocating::safe_allocator, protected logging::complete_logger {

    friend class database;

public:

    explicit scheme(allocating::memory *allocator = nullptr, logging::logger *logger = nullptr);

    virtual ~scheme();


public:

    int create_collection(std::vector<std::string> &query);

    int create_note(std::ifstream &file, std::vector<std::string> &query);


public:

    int read_note(std::ifstream &file, std::vector<std::string> &query);

    int read_note_range(std::ifstream &file, std::vector<std::string> &query);


public:

    int delete_collection(std::vector<std::string> &query);

    int delete_note(std::ifstream &file, std::vector<std::string> &query);


private:

    associative_container<std::string, collection *> *_collections;


private:

    allocating::memory *get_allocator() const;

    logging::logger *get_logger() const;


    allocating::memory *_allocator;

    logging::logger *_logger;

};