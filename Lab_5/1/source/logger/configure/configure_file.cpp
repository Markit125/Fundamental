#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#include "configure_file.h"



logger::severity configurator::str_to_severity(std::string const str) {
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


logger *configurator::configure_from_file(std::string const filename) {
    std::map<std::string, logger::severity> construction_info;

    std::ifstream file(filename, std::ios::in);
    if (!file.is_open()) {
        return nullptr;
    }

    std::string severities[] {
        "trace",
        "debug",
        "info",
        "warning",
        "error",
        "critical"
    };

    std::string stream;
    std::string severity;

    while (file >> stream && file >> severity) {
        if (std::find(begin(severities), end(severities), severity) != end(severities)) {
            construction_info[stream] = str_to_severity(severity);
        } else {
            return nullptr;
        }
    }

    return new logger_concrete(construction_info);    
}


configurator::configurator() {

}


configurator::~configurator() {
    
}