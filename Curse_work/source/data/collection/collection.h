#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "../../logger/source/logger/complete/complete_logger.h"
#include "../../memory/2/source/memory/memory.h"
#include "../../../source/tree/11/source/tree/associative_container.h"
#include "../../tree/11/source/allocator/safe_allocator.h"
#include "../../comparer/comparer.h"
#include "../../tree/12/source/avl/avl.h"
#include "../../memory/3/source/memory_with_list/memory_with_list.h"
#include "../../memory/4/source/memory_with_descriptors/memory_with_descriptors.h"


class collection : protected allocating::safe_allocator, protected logging::complete_logger {

    friend class database;
    
public:

    explicit collection(allocating::memory *allocator = nullptr, logging::logger *logger = nullptr);

    ~collection();


public:

    int create_note(std::stringstream &file, std::vector<std::string> &query);


public:

    int read_note(std::stringstream &file, std::stringstream &out_stream, std::vector<std::string> &query);

    int read_note_range(std::stringstream &file, std::stringstream &out_stream, std::vector<std::string> &query);


public:

    int delete_note(std::stringstream &file, std::vector<std::string> &query);
    

private:

    void key_filling(std::stringstream &file, type_key &key) const;

    void value_filling(std::stringstream &file, type_value &value) const;


private:

    associative_container<type_key, type_value> *_notes;


private:

    allocating::memory *get_allocator() const override;

    logging::logger *get_logger() const override;

    allocating::memory *_allocator;

    logging::logger *_logger;

};


inline std::ostream &operator<<(std::ostream &stream, collection const &key) { 
    return stream << "[ object collection ]";
}

int get_word(std::stringstream &stream, std::string &word);

int is_date(std::string &date);

int is_time(std::string &time);

int is_digit(char c);

bool is_email_valid(const std::string& email);