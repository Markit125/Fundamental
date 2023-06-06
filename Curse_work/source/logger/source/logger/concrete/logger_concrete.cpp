#include "logger_concrete.h"


std::map<std::string, std::pair<std::ofstream *, size_t>> logging::logger_concrete::_streams =
    std::map<std::string, std::pair<std::ofstream *, size_t>>();

logging::logger_concrete::logger_concrete(
    std::map<std::string, logging::logger::severity> const & targets) {
    for (auto & target : targets) {
        auto global_stream = _streams.find(target.first);
        std::ofstream *stream = nullptr;

        if (global_stream == _streams.end()) {
            if (target.first != "console") {
                stream = new std::ofstream;
                stream->open(target.first);
            }

            _streams.insert(std::make_pair(target.first, std::make_pair(stream, 1)));
        }
        else {
            stream = global_stream->second.first;
            global_stream->second.second++;
        }

        _logger_streams.insert(std::make_pair(target.first, std::make_pair(stream, target.second)));
    }
}

logging::logger_concrete::~logger_concrete() {
    for (auto & logger_stream : _logger_streams) {
        auto global_stream = _streams.find(logger_stream.first);
        
        if (global_stream == _streams.end()) {
            continue;
        }

        if (--(global_stream->second.second) == 0) {
            if (global_stream->second.first != nullptr) {
                global_stream->second.first->flush();
                global_stream->second.first->close();
                delete global_stream->second.first;
            }

            _streams.erase(global_stream);
        }
    }
}

std::string get_severity(logging::logger::severity severity) {
    switch (severity) {
        case logging::logger::severity::trace:
            return "[TRACE]";
        case logging::logger::severity::debug:
            return "[DEBUG]";
        case logging::logger::severity::information:
            return "[INFO]";
        case logging::logger::severity::warning:
            return "[WARNING]";
        case logging::logger::severity::error:
            return "[ERROR]";
        case logging::logger::severity::critical:
            return "[CRITICAL]";
        default:
            return "[UNDEFINED]";
    }
}


logging::logger const *logging::logger_concrete::log(
    const std::string &to_log,
    logging::logger::severity severity) const {

    key_t key = -1;
    int msqid = -1;
    MsgQueue msg;

    key = ftok("/bin/ls", 'E');
    if (key < 0) {

        perror("ftok");
        exit(1);
    }

    msqid = msgget(key, MSG_Q_KEY_FLAG_LOGGER | IPC_CREAT);
    if (msqid < 0) {

        perror("msgget");
        exit(1);	
    }

    char *ptr = const_cast<char *>(to_log.c_str());
    int count = 0;

    while (*ptr != '\0' && count < MSG_SIZE) {
        msg.buff[count++] = *(ptr++);
    }
    msg.buff[count] = '\0';
    msg.messageType = MSG_Q_CHANNEL_SEND_LOG;
    msg.severity = severity;


    if (msgsnd(msqid, &msg, sizeof(msg) - sizeof(long), 0) < 0) {
        perror("msgsnd");
        exit(1);
    }

    return this;
}