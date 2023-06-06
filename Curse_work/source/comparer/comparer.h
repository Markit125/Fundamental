#ifndef COMPARER_H
#define COMPARER_H

#include "../data/type_data/type_data.h"

class comparers {

public:

    int operator()(type_key lhs, type_key rhs) {

        if (lhs._user_id < rhs._user_id) {
            return 1;
        } else if (lhs._user_id > rhs._user_id) {
            return -1;
        }

        if (lhs._delivery_id < rhs._delivery_id) {
            return 1;
        } else if (lhs._delivery_id > rhs._delivery_id) {
            return -1;
        }

        return 0;
    }


    int operator()(std::string lhs, std::string rhs) {

        if (lhs < rhs) {
            return 1;
        } else if (lhs > rhs) {
            return -1;
        }

        return 0;
    }

};


#endif