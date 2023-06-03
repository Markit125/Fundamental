#ifndef SANDBOX_CPP_LOGGER_CONCRETE_H
#define SANDBOX_CPP_LOGGER_CONCRETE_H

#include "../prototypes/logger.h"
#include "logger_builder_concrete.h"
#include <map>


namespace logging {


class logger_concrete final : public logging::logger {

    // friend class logger_builder_concrete;
    // friend class configurator;

private:

    std::map<std::string, std::pair<std::ofstream *, logger::severity>>  _logger_streams;

private:

    static std::map<std::string, std::pair<std::ofstream *, size_t> > _streams;

public:

    logger_concrete(std::map<std::string, logger::severity> const &);

public:

    logger_concrete(logger_concrete const &) = delete;

    logger_concrete &operator=(logger_concrete const &) = delete;

    ~logger_concrete();

public:

    logger const *log(const std::string &, severity) const override;

};

}

#endif //SANDBOX_CPP_LOGGER_CONCRETE_H
