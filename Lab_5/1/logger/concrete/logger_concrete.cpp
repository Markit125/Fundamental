#include "logger_concrete.h"
#include "../../time/my_time.h"
#include <iostream>
#include <fstream>



std::map<std::string, std::pair<std::ofstream *, size_t>> logger_concrete::_streams =
    std::map<std::string, std::pair<std::ofstream *, size_t>>();

logger_concrete::logger_concrete(
    std::map<std::string, logger::severity> const & targets)
{
    for (auto & target : targets)
    {
        auto global_stream = _streams.find(target.first);
        std::ofstream *stream = nullptr;

        if (global_stream == _streams.end())
        {
            if (target.first != "console")
            {
                stream = new std::ofstream;
                stream->open(target.first);
            }

            _streams.insert(std::make_pair(target.first, std::make_pair(stream, 1)));
        }
        else
        {
            stream = global_stream->second.first;
            global_stream->second.second++;
        }

        _logger_streams.insert(std::make_pair(target.first, std::make_pair(stream, target.second)));
    }
}

logger_concrete::~logger_concrete()
{
    for (auto & logger_stream : _logger_streams)
    {
        auto global_stream = _streams.find(logger_stream.first);
        
        if (global_stream == _streams.end())
        {
            continue;
        }

        if (--(global_stream->second.second) == 0)
        {
            if (global_stream->second.first != nullptr)
            {
                global_stream->second.first->flush();
                global_stream->second.first->close();
                delete global_stream->second.first;
            }

            _streams.erase(global_stream);
        }
    }
}

std::string get_severity(logger::severity severity)
{
    switch (severity)
    {
        case logger::severity::trace:
            return "[TRACE]";
        case logger::severity::debug:
            return "[DEBUG]";
        case logger::severity::information:
            return "[INFO]";
        case logger::severity::warning:
            return "[WARNING]";
        case logger::severity::error:
            return "[ERROR]";
        case logger::severity::critical:
            return "[CRITICAL]";
        default:
            return "[UNDEFINED]";
    }
}

logger const *logger_concrete::log(
    const std::string &to_log,
    logger::severity severity) const
{
    for (auto & logger_stream : _logger_streams)
    {
        if (logger_stream.second.second > severity)
        {
            continue;
        }
        
        if (logger_stream.second.first == nullptr)
        {
            std::cout << "[" << get_time() << "]" << get_severity(logger_stream.second.second) << " " << to_log << std::endl;
        }
        else
        {
            (*logger_stream.second.first) << "[" << get_time() << "]" << get_severity(logger_stream.second.second) << " " << to_log << std::endl;
        }
    }

    return this;
}
