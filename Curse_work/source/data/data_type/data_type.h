#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#define MAX_SIZE_T_LEN 15

#include <iostream>
#include <sstream>

struct type_key {

    size_t _user_id;
    size_t _delivery_id;

};

struct type_value {

    std::string description;
    std::string name;
    std::string second_name;
    std::string last_name;
    std::string email;
    size_t phone_number;
    std::string address;
    std::string comment;
    std::string date_time;

};


#endif