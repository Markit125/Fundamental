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
#include <map>

#include "../builder/logger_server_builder_concrete.h"
#include "../../../time/my_time.h"
#include "../../../logger/complete/complete_logger.h"


const int MSG_SIZE = 2000;

struct MsgQueue {

    long messageType;
    logging::logger::severity severity;
    char buff[MSG_SIZE];	

};


namespace logging {


class logger_server final : public logging::logger {


private:

    std::map<std::string, std::pair<std::ofstream *, logger::severity>>  _logger_streams;

private:

    static std::map<std::string, std::pair<std::ofstream *, size_t> > _streams;

public:

    logger_server(std::map<std::string, logger::severity> const &);

public:

    logger_server(logger_server const &) = delete;

    logger_server &operator=(logger_server const &) = delete;

    ~logger_server();


public:

    logger const *log(const std::string &, severity) const override;

};

}