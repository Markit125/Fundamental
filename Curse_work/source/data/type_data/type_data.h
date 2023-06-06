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

inline std::ostream &operator<<(std::ostream &stream, type_key const &key) { 
    return stream << "{ " << key._user_id << ", " << key._delivery_id << " }";
}

inline std::ostream &operator<<(std::ostream &stream, type_value const &value) { 
    return stream << "{\n\t" << value.description << ",\n\t"
                             << value.name << ",\n\t"
                             << value.second_name << ",\n\t"
                             << value.last_name << ",\n\t"
                             << value.email << ",\n\t"
                             << value.phone_number << ",\n\t"
                             << value.address << ",\n\t"
                             << value.comment << ",\n\t"
                             << value.date_time << "\n}";
}

#endif