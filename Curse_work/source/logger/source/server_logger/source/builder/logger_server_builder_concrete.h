#ifndef SANDBOX_CPP_LOGGER_server_BUILDER_CONCRETE_H
#define SANDBOX_CPP_LOGGER_server_BUILDER_CONCRETE_H

#include <map>
#include "../../../logger/prototypes/logger_builder.h"
#include "json.hpp"
#include <fstream>


class logger_server_builder_concrete final : public logging::logger_builder {

private:

    std::map<std::string, logging::logger::severity> _construction_info;

    logging::logger::severity str_to_severity(std::string const);

public:

    logger_server_builder_concrete();

    ~logger_server_builder_concrete();

    logger_builder *add_stream(std::string const &, logging::logger::severity) override;

    logging::logger *construct_configuration(std::string const &) override;

    logging::logger *construct() const override;

};


#endif //SANDBOX_CPP_LOGGER_server_BUILDER_CONCRETE_H
