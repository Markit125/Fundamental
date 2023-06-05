#include "../collection/collection.h"


class scheme : protected allocating::safe_allocator, protected logging::complete_logger {

    friend class database;

public:

    explicit scheme(allocating::memory *allocator = nullptr, logging::logger *logger = nullptr);

    ~scheme();


public:

    int create_collection(std::vector<std::string> &query);

    int create_note(std::stringstream &file, std::vector<std::string> &query);


public:

    int read_note(std::stringstream &file, std::vector<std::string> &query);

    int read_note_range(std::stringstream &file, std::vector<std::string> &query);


public:

    int delete_collection(std::vector<std::string> &query);

    int delete_note(std::stringstream &file, std::vector<std::string> &query);


private:

    associative_container<std::string, collection> *_collections;


private:

    allocating::memory *get_allocator() const override;

    logging::logger *get_logger() const override;


    allocating::memory *_allocator;

    logging::logger *_logger;

};


inline std::ostream &operator<<(std::ostream &stream, scheme const &key) { 
    return stream << "[ object scheme ]";
}