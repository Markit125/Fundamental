#ifndef CONFIGURE_FROM_FILE
#define CONFIGURE_FROM_FILE

#include "../concrete/logger_concrete.h"


class configurator
{

public:

    logger *configure_from_file(std::string const);

private:

    logger::severity str_to_severity(std::string const);

};


#endif