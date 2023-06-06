#ifndef SANDBOX_CPP_LOGGER_CONCRETE_H
#define SANDBOX_CPP_LOGGER_CONCRETE_H

#include "../prototypes/logger.h"
#include "logger_builder_concrete.h"
#include "../../time/my_time.h"
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cstring>

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>




const int MSG_Q_KEY_FLAG_LOGGER = 0600;

const int MSG_Q_CHANNEL_SEND_LOG = 36;

const int MSG_SIZE = 2000;

struct MsgQueue {

    long messageType;
    logging::logger::severity severity;
    char buff[MSG_SIZE];

};

namespace logging {


class logger_concrete final : public logging::logger {

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
