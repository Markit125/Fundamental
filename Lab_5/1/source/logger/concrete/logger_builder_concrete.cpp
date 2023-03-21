#include "logger_builder_concrete.h"
#include "logger_concrete.h"
#include <fstream>


logger_builder *logger_builder_concrete::add_stream(
    std::string const &path,
    logger::severity severity) {
    _construction_info[path] = severity;

    return this;
}


logger *logger_builder_concrete::construct() const {
    return new logger_concrete(_construction_info);
}

logger *logger_builder_concrete::construct_configuration(const std::string & filename) {

    std::ifstream conf_file(filename);
    std::stringstream buf;
    buf << conf_file.rdbuf();
    auto json = nlohmann::json::parse(buf.str());


    std::stringstream path;
    for (auto &item : json["streams"].items()) {
        this->add_stream(item.key(), str_to_severity(item.value()));

    }

    return this->construct();
}


logger_builder_concrete::logger_builder_concrete() {

}


logger_builder_concrete::~logger_builder_concrete() {

}


logger::severity logger_builder_concrete::str_to_severity(std::string const str) {
    if (str == "trace") {
        return logger::severity::trace;
    } else if (str == "debug") {
        return logger::severity::debug;
    } else if (str == "info") {
        return logger::severity::information;
    } else if (str == "warning") {
        return logger::severity::warning;
    } else if (str == "error") {
        return logger::severity::error;
    } else {
        return logger::severity::critical;
    }
}
