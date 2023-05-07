#ifndef COMPLETE_LOGGER
#define COMPLETE_LOGGER

#include "logger.h"

class complete_logger
{

public:

    virtual ~complete_logger() = default;

    logging::logger const *safe_log(const std::string &, logging::logger::severity) const;

    virtual logging::logger *get_logger() const = 0;

};


#endif