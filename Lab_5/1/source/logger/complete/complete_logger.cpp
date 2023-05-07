#include "complete_logger.h"
#include "logger.h"

logging::logger const *logging::complete_logger::safe_log(const std::string &message, logging::logger::severity severity) const {
    
    logging::logger *logger = get_logger();
    
    if (nullptr != logger) {
        return logger->log(message, severity);
    }

    return nullptr;
}