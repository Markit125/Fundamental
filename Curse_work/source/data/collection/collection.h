#include <iostream>
#include <fstream>
#include <string>
#include "../../logger/source/logger/complete/complete_logger.h"
#include "../../memory/2/source/memory/memory.h"
#include "../../../source/tree/11/source/tree/associative_container.h"
#include "../data_type/data_type.h"
#include "../../tree/11/source/allocator/safe_allocator.h"
#include "../../comparer/comparer.h"
#include "../../tree/12/source/avl/avl.h"


class collection : protected allocating::safe_allocator, protected logging::complete_logger {

    friend class database;
    
public:

    explicit collection(allocating::memory *allocator = nullptr, logging::logger *logger = nullptr);

    virtual ~collection();


public:

    int create_note(std::ifstream &file, std::vector<std::string> &query);


public:

    int read_note(std::ifstream &file, std::vector<std::string> &query);

    int read_note_range(std::ifstream &file, std::vector<std::string> &query);


public:

    int delete_note(std::ifstream &file, std::vector<std::string> &query);
    

private:

    void key_filling(std::ifstream &file, type_key &key) const;

    void value_filling(std::ifstream &file, type_value &value) const;


private:

    associative_container<type_key, type_value> *_notes;


private:

    allocating::memory *get_allocator() const;

    logging::logger *get_logger() const;

    allocating::memory *_allocator;

    logging::logger *_logger;

};


int get_word(std::ifstream &stream, std::string &word);

int is_date(std::string &date);

int is_time(std::string &time);

int is_digit(char c);
