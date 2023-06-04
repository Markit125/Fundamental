#include "database.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// creating

int database::create_pool(std::vector<std::string> &query) {

    pool *new_pool = reinterpret_cast<pool *>(safe_allocate(sizeof(pool)));
    new (new_pool) pool(_allocator, _logger);
    safe_log("Memory for pool is allocated", logging::logger::severity::information);

    _pools->insert(query[0], std::move(new_pool));

    safe_log("Pool created", logging::logger::severity::information);

    return 0;
}


int database::create_scheme(std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    if (!(_pools->find(query[0], &pool_found))) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }


    scheme *new_scheme = reinterpret_cast<scheme *>(safe_allocate(sizeof(scheme)));
    new (new_scheme) scheme(_allocator, _logger);
    safe_log("Memory for scheme is allocated", logging::logger::severity::information);

    (*pool_found.second)->_schemes->insert(query[1], std::move(new_scheme));
    safe_log("Scheme created", logging::logger::severity::information);

    return 0;
}


int database::create_collection(std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    if (!(_pools->find(query[0], &pool_found))) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    std::pair<std::string, scheme **> scheme_found;

    if (!((*pool_found.second)->_schemes->find(query[1], &scheme_found))) {
        throw std::runtime_error("Scheme " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + " doesn't exists!\n");
    }

    collection *new_collection = reinterpret_cast<collection *>(safe_allocate(sizeof(collection)));
    new (new_collection) collection(_allocator, _logger);
    safe_log("Memory for collection is allocated", logging::logger::severity::information);

    (*scheme_found.second)->_collections->insert(query[2], std::move(new_collection));

    safe_log("Collection created", logging::logger::severity::information);
    
    return 0;
}


int database::create_note(std::ifstream &file, std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    if (!(_pools->find(query[0], &pool_found))) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    std::pair<std::string, scheme **> scheme_found;

    if (!((*pool_found.second)->_schemes->find(query[1], &scheme_found))) {
        throw std::runtime_error("Scheme " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + " doesn't exists!\n");
    }

    std::pair<std::string, collection **> collection_found;

    if (!((*scheme_found.second)->_collections->find(query[2], &collection_found))) {
        throw std::runtime_error("Collection " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + "/" + cast_to_str(query[2]) + " doesn't exists!\n");
    }

    type_key key;

    key_filling(file, key);


    type_value value;

    value_filling(file, value);



    (*collection_found.second)->_notes->insert(key, std::move(value));

    safe_log("Note created", logging::logger::severity::information);

    // (*collection_found.second)->_notes->print_container();
    
    // (*collection_found.second)->_notes->print_notes_between(type_key {1, 2}, type_key{ 10, 4 });
    
    
    return 0;
}


//reading

int database::read_note(std::ifstream &file, std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    if (!(_pools->find(query[0], &pool_found))) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    std::pair<std::string, scheme **> scheme_found;

    if (!((*pool_found.second)->_schemes->find(query[1], &scheme_found))) {
        throw std::runtime_error("Scheme " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + " doesn't exists!\n");
    }

    std::pair<std::string, collection **> collection_found;

    if (!((*scheme_found.second)->_collections->find(query[2], &collection_found))) {
        throw std::runtime_error("Collection " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + "/" + cast_to_str(query[2]) + " doesn't exists!\n");
    }

    // (*collection_found.second)->_notes->print_container();

    type_key key;

    key_filling(file, key);


    type_value value;

    try {
        value = (*collection_found.second)->_notes->get(key);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error(cast_to_str(ex.what()) + " " +
            "{ " + cast_to_str(key._user_id) + ", " + cast_to_str(key._delivery_id) + " }");
    }
    
    std::cout << key << std::endl << value << std::endl;

    return 0;
}


int database::read_note_range(std::ifstream &file, std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    if (!(_pools->find(query[0], &pool_found))) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    std::pair<std::string, scheme **> scheme_found;

    if (!((*pool_found.second)->_schemes->find(query[1], &scheme_found))) {
        throw std::runtime_error("Scheme " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + " doesn't exists!\n");
    }

    std::pair<std::string, collection **> collection_found;

    if (!((*scheme_found.second)->_collections->find(query[2], &collection_found))) {
        throw std::runtime_error("Collection " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + "/" + cast_to_str(query[2]) + " doesn't exists!\n");
    }

    // (*collection_found.second)->_notes->print_container();

    type_key key_left;
    type_key key_right;

    key_filling(file, key_left);
    key_filling(file, key_right);

    (*collection_found.second)->_notes->print_notes_between(key_left, key_right);

    return 0;
}

// validation

void database::key_filling(std::ifstream &file, type_key &key) const {

    std::string word;

    if (!get_word(file, word)) {
        throw std::runtime_error("Expected key");
    }

    if (word != "{") {
        throw std::runtime_error("Expected '{' after delivery_id" + word);
    }

    if (!get_word(file, word)) {
        throw std::runtime_error("Expected user_id");
    }

    key._user_id = 0;
    for (int i = 0; i < word.size() - 1; ++i) {
        if (word[i] < '0' || '9' < word[i]) {
            throw std::runtime_error("Invalid user_id");
        }
        key._user_id = key._user_id * 10 + word[i] - '0';
    }

    if (word[word.size() - 1] !=  ',') {
        throw std::runtime_error("Expected ',' after user_id");
    }

    if (!get_word(file, word)) {
        throw std::runtime_error("Expected delivery_id");
    }

    key._delivery_id = 0;
    for (int i = 0; i < word.size(); ++i) {
        if (word[i] < '0' || '9' < word[i]) {
            throw std::runtime_error("Invalid delivery_id");
        }
        key._delivery_id = key._delivery_id * 10 + word[i] - '0';
    }

    if (!get_word(file, word)) {
        throw std::runtime_error("Unexpected end of file");
    }
    
    if (word != "}") {
        throw std::runtime_error("Expected '}' after delivery_id");
    }

}


void database::value_filling(std::ifstream &file, type_value &value) const {

    std::string word;

    // description

    if (!get_word(file, word)) {
        throw std::runtime_error("Expected value");
    }

    if (word != "==") {
        throw std::runtime_error("Expected '==' before value");
    }

    while (get_word(file, word)) {
        if (word == "==") {
            break;
        }
        value.description += word + " ";
    }
    value.description.pop_back();

    if (word != "==") {
        throw std::runtime_error("Expected '==' after description");
    }

    if (value.description.size() == 0) {
        throw std::runtime_error("Description must not be empty");
    }

    // user's name

    if (!get_word(file, word)) {
        throw std::runtime_error("Expected user's name");
    }

    for (char c : word) {
        if ((c < 'a' || 'z' < c) && (c < 'A' || 'Z' < c)) {
            throw std::runtime_error("Invalid user's name");
        }
    }
    value.name = word;
    

    if (!get_word(file, word)) {
        throw std::runtime_error("Unexpected end of file");
    }

    if (word != "==") {
        throw std::runtime_error("Expected '==' after user's name");
    }
    
    //user's second_name

    if (!get_word(file, word)) {
        throw std::runtime_error("Expected user's second_name");
    }

    for (char c : word) {
        if ((c < 'a' || 'z' < c) && (c < 'A' || 'Z' < c)) {
            throw std::runtime_error("Invalid user's second_name");
        }
    }
    value.second_name = word;
    

    if (!get_word(file, word)) {
        throw std::runtime_error("Unexpected end of file");
    }

    if (word != "==") {
        throw std::runtime_error("Expected '==' after user's second_name");
    }

    // user's last_name
    
    if (!get_word(file, word)) {
        throw std::runtime_error("Expected user's last_name");
    }

    for (char c : word) {
        if ((c < 'a' || 'z' < c) && (c < 'A' || 'Z' < c)) {
            throw std::runtime_error("Invalid user's last_name");
        }
    }
    value.last_name = word;
    

    if (!get_word(file, word)) {
        throw std::runtime_error("Unexpected end of file");
    }

    if (word != "==") {
        throw std::runtime_error("Expected '==' after user's last_name");
    }

    // user's email
    
    if (!get_word(file, word)) {
        throw std::runtime_error("Expected user's email");
    }

    for (char c : word) {
        if ((c < 'a' || 'z' < c) && (c < 'A' || 'Z' < c) && c != '.' && c != '@' && c != '_' && (c < '0' || '9' < c)) {
            throw std::runtime_error("Invalid user's email");
        }
    }
    value.email = word;
    

    if (!get_word(file, word)) {
        throw std::runtime_error("Unexpected end of file");
    }

    if (word != "==") {
        throw std::runtime_error("Expected '==' after user's last_name");
    }

    // user's phone number
    
    if (!get_word(file, word)) {
        throw std::runtime_error("Expected user's phone_number");
    }

    if (word.size() > MAX_SIZE_T_LEN) {
        throw std::runtime_error("Too long user's phone_number");
    }

    value.phone_number = 0;
    for (int i = 0; i < word.size(); ++i) {

        if (word[i] < '0' && '9' < word[i] && word[i] != '+') {
            throw std::runtime_error("Invalid user's phone_number");
        }

        if (word[i] == '+' && i != 0) {
            throw std::runtime_error("Invalid user's phone_number");
        }

        if (word[i] != '+') {
            value.phone_number = value.phone_number * 10 + (word[i] - '0');
        }
    }    

    if (!get_word(file, word)) {
        throw std::runtime_error("Unexpected end of file");
    }

    if (word != "==") {
        throw std::runtime_error("Expected '==' after user's phone_number");
    }

    // address

    while (get_word(file, word)) {
        if (word == "==") {
            break;
        }
        value.address += word + " ";
    }
    value.address.pop_back();

    if (word != "==") {
        throw std::runtime_error("Expected '==' after address");
    }

    if (value.address.size() == 0) {
        throw std::runtime_error("Address must not be empty");
    }
    
    // comment

    while (get_word(file, word)) {
        if (word == "==") {
            break;
        }
        value.comment += word + " ";
    }
    value.comment.pop_back();

    if (word != "==") {
        throw std::runtime_error("Expected '==' after address");
    }

    if (value.comment.size() == 0) {
        throw std::runtime_error("Comment must not be empty");
    }

    // date_time

    if (!get_word(file, word)) {
        throw std::runtime_error("Expected date_time of delivery");
    }

    
    try {
        is_date(word);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error("Invalid date '" + word + "': " + ex.what());
        
    }

    value.date_time += word;
    

    if (!get_word(file, word)) {
        throw std::runtime_error("Expected time of delivery");
    }

    if (!is_time(word)) {
        throw std::runtime_error("Invalid time");
    }
    value.date_time += " " + word;

    if (!get_word(file, word)) {
        throw std::runtime_error("Unexpected end of file");
    }

    if (word != "==") {
        throw std::runtime_error("Expected '==' after date_time of delivery");
    }
}


// deleting


int database::delete_pool(std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    if (!(_pools->find(query[0], &pool_found))) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    _pools->remove(query[0]);

    safe_log("Pool removed", logging::logger::severity::information);

    return 0;
}


int database::delete_scheme(std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    if (!(_pools->find(query[0], &pool_found))) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    std::pair<std::string, scheme **> scheme_found;

    if (!((*pool_found.second)->_schemes->find(query[1], &scheme_found))) {
        throw std::runtime_error("Scheme " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + " doesn't exists!\n");
    }

    (*pool_found.second)->_schemes->remove(query[1]);
    safe_log("Scheme removed", logging::logger::severity::information);

    return 0;
}


int database::delete_collection(std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    if (!(_pools->find(query[0], &pool_found))) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    std::pair<std::string, scheme **> scheme_found;

    if (!((*pool_found.second)->_schemes->find(query[1], &scheme_found))) {
        throw std::runtime_error("Scheme " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + " doesn't exists!\n");
    }

    std::pair<std::string, collection **> collection_found;

    if (!((*scheme_found.second)->_collections->find(query[2], &collection_found))) {
        throw std::runtime_error("Collection " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + "/" + cast_to_str(query[2]) + " doesn't exists!\n");
    }


    (*scheme_found.second)->_collections->remove(query[2]);

    safe_log("Collection removed", logging::logger::severity::information);
    
    return 0;
}


int database::delete_note(std::ifstream &file, std::vector<std::string> &query) {

    std::pair<std::string, pool **> pool_found;

    if (!(_pools->find(query[0], &pool_found))) {
        throw std::runtime_error("Pool " + cast_to_str(query[0]) + " doesn't exists!\n");
    }

    std::pair<std::string, scheme **> scheme_found;

    if (!((*pool_found.second)->_schemes->find(query[1], &scheme_found))) {
        throw std::runtime_error("Scheme " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + " doesn't exists!\n");
    }

    std::pair<std::string, collection **> collection_found;

    if (!((*scheme_found.second)->_collections->find(query[2], &collection_found))) {
        throw std::runtime_error("Collection " + cast_to_str(query[0]) + "/"
            + cast_to_str(query[1]) + "/" + cast_to_str(query[2]) + " doesn't exists!\n");
    }

    type_key key;

    key_filling(file, key);


    try {
        (*collection_found.second)->_notes->remove(key);
    } catch (std::runtime_error &ex) {
        throw std::runtime_error(cast_to_str(ex.what()) + " " +
            "{ " + cast_to_str(key._user_id) + ", " + cast_to_str(key._delivery_id) + " }");
    }

    safe_log("Note removed", logging::logger::severity::information);
    
    return 0;
}


// functions

int is_time(std::string &time) {

    if (time.length() != 5) {
        throw std::runtime_error("Wrong count of symbols!");
    }

    int digits[] = { 0, 1, 3, 4 };

    for (int i : digits) {
        if (!is_digit(time[i])) {
            throw std::runtime_error("It does not a digit '" + cast_to_str(time[i]) + "'");
        }
    }

    if (time[2] != ':' && time[2] != '-') {
        throw std::runtime_error("It does not a separator '" + cast_to_str(time[2]) + "'");
    }

    int hours = 10 * (time[0] - '0') + time[1] - '0';
    int minutes = 10 * (time[3] - '0') + time[4] - '0';

    if (hours < 0 || 23 < hours) {
        throw std::runtime_error("Wrong count of hours '" + cast_to_str(hours) + "'");
    }

    if (minutes < 0 || 59 < minutes) {
        throw std::runtime_error("Wrong count of minutes '" + cast_to_str(hours) + "'");
    }

    return 1;
}

int is_date(std::string &date) {
    
    if (date.length() != 10) {
        throw std::runtime_error("Wrong count of symbols!");
    }

    int digits[] = { 0, 1, 3, 4, 6, 7, 8, 9 };

    for (int i : digits) {
        if (!is_digit(date[i])) {
            throw std::runtime_error("It does not a digit '" + cast_to_str(date[i]) + "'");
        }
    }

    int separators[] = { 2,5 };

    for (int i : separators) {
        if (date[i] != '/' && date[i] != '.') {
            throw std::runtime_error("Wrong separator '" + cast_to_str(date[i]) + "'");
        }
    }


    int day = 10 * (date[0] - '0') + date[1] - '0';
    int month = 10 * (date[3] - '0') + date[4] - '0';
    int year = 1000 * (date[6] - '0') + 100 * (date[7] - '0') + 10 * (date[8] - '0') + (date[9] - '0');

    if (day < 1 || day > 31) {
        throw std::runtime_error("Wrong day '" + cast_to_str(day) + "'");
    } else if (month < 1 || month > 12) {
        throw std::runtime_error("Wrong day '" + cast_to_str(month) + "'");
    }

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31) {
        throw std::runtime_error("Wrong count of days in month");
    } else if ((month == 2) && (year % 4 == 0) && day > 29) {
        throw std::runtime_error("Wrong count of days in month");

    } else if ((month == 2) && (year % 4 != 0) && day > 28) {
        throw std::runtime_error("Wrong count of days in month");
    }
    return 1;
}


int is_digit(char c) {
    return '0' <= c && c <= '9';
}


int get_word(std::ifstream &stream, std::string &word) {

    if (stream >> word) {
        return 1;
    }

    return 0;
}

database::database(allocating::memory *allocator, logging::logger *logger)
    : _pools(new avl_tree<std::string, pool *, comparers>(allocator, logger)),
     _allocator(allocator), _logger(logger) {

}

database::~database() {
    delete _pools;
}


allocating::memory *database::get_allocator() const {
    return _allocator;
}


logging::logger *database::get_logger() const {
    return _logger;
}