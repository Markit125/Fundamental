#include "../scheme/scheme.h"


class pool : protected allocating::safe_allocator, protected logging::complete_logger {

    friend class database;

public:

    explicit pool(allocating::memory *allocator = nullptr, logging::logger *logger = nullptr);

    ~pool();

  public:

    int create_scheme(std::vector<std::string> &query);

    int create_collection(std::vector<std::string> &query);

    int create_note(std::ifstream &file, std::vector<std::string> &query);


public:

    int read_note(std::ifstream &file, std::vector<std::string> &query);

    int read_note_range(std::ifstream &file, std::vector<std::string> &query);


public:

    int delete_scheme(std::vector<std::string> &query);

    int delete_collection(std::vector<std::string> &query);

    int delete_note(std::ifstream &file, std::vector<std::string> &query);
    

private:

    associative_container<std::string, scheme *> *_schemes;


private:

    allocating::memory *get_allocator() const ;

    logging::logger *get_logger() const ;


    allocating::memory *_allocator;

    logging::logger *_logger;

};