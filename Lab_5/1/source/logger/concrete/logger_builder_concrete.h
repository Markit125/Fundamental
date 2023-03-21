#ifndef SANDBOX_CPP_LOGGER_BUILDER_CONCRETE_H
#define SANDBOX_CPP_LOGGER_BUILDER_CONCRETE_H

#include <map>
#include "../prototypes/logger_builder.h"
#include "json.hpp"
#include <fstream>


class logger_builder_concrete final : public logger_builder {

private:

    std::map<std::string, logger::severity> _construction_info;

    logger::severity str_to_severity(std::string const);

public:

    logger_builder_concrete();

    ~logger_builder_concrete();

    logger_builder *add_stream(std::string const &, logger::severity) override;

    logger *construct_configuration(std::string const &) override;

    logger *construct() const override;

};


#endif //SANDBOX_CPP_LOGGER_BUILDER_CONCRETE_H
