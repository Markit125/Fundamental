#include "../pool/pool.h"
#include <vector>


class database : protected logging::complete_logger {

public:

    explicit database(logging::logger *logger = nullptr);

    ~database() override;


public:

    int create_pool(std::vector<std::string> &query);

    int create_scheme(std::vector<std::string> &query);

    int create_collection(std::vector<std::string> &query);

    int create_note(std::stringstream &file, std::vector<std::string> &query);


public:

    int delete_pool(std::vector<std::string> &query);

    int delete_scheme(std::vector<std::string> &query);

    int delete_collection(std::vector<std::string> &query);

    int delete_note(std::stringstream &file, std::vector<std::string> &query);


public:

    int read_note(std::stringstream &file, std::vector<std::string> &query);

    int read_note_range(std::stringstream &file, std::vector<std::string> &query);


private:

    void key_filling(std::stringstream &file, type_key &key) const;

    void value_filling(std::stringstream &file, type_value &value) const;


private:

    associative_container<std::string, pool> *_pools;


private:

    logging::logger *_logger;

    logging::logger *get_logger() const override;

};


// int get_word(std::stringstream &stream, std::string &word);

// int is_date(std::string &date);

// int is_time(std::string &time);

// int is_digit(char c);
