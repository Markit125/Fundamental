#include "my_time.h"
#include <ostream>

#define DATE_LEN 19


std::string get_time() {
    time_t rawtime;
    time(&rawtime);

    struct tm *timeinfo = localtime(&rawtime);
    char buffer[DATE_LEN];

    strftime(buffer,DATE_LEN,"%m/%d/%y %H:%M:%S",timeinfo);

    return buffer;
}