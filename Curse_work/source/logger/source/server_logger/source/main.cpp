#include "logger/server_logger.h"



const int MSG_Q_KEY_FLAG_LOGGER = 0600;
const int MSG_Q_CHANNEL_RECEIVE_LOG = 36;


int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cout << "You should enter the configuration file name" << std::endl;
        return 1;
    }

    std::string filename(argv[1]);

    logging::logger_builder *builder = new logger_server_builder_concrete();

    if (nullptr == builder) {
        std::cout << "Cannot allocate memory for builder" << std::endl;
        return -1;
    }


    logging::logger *logger;

    try {
        logger = builder->construct_configuration(filename);
    } catch (std::runtime_error &ex) {
        std::cout << ex.what() << std::endl;
        return -2;
    }



    if (nullptr == logger) {
        std::cout << "Logger doesn't exist" << std::endl;
        return -3;
    }

    delete builder;

    key_t key = -1;
    int msqid = -1;
    MsgQueue msg;

    key = ftok("/bin/ls", 'E');
    if (key < 0) {

        perror("ftok");
        return -1;
    }

    msqid = msgget(key, MSG_Q_KEY_FLAG_LOGGER | IPC_CREAT);
    if (msqid < 0) {

        perror("msgget");
        return -2;
    }

    while (1) {

        if (msgrcv(msqid, &msg, sizeof(msg) - sizeof(long), MSG_Q_CHANNEL_RECEIVE_LOG, 0) < 0)
        {
            perror("msgrcv");
            return -3;
        }

        std::string message(msg.buff);

        logger->log(message, msg.severity);
    }


    delete logger;

    if (msgctl(msqid, IPC_RMID, NULL) < 0) {
        
        perror("msgctl");
        return -4;
    }

    std::cout << "\nServer is now shutting down!\n";

    return 0;
}