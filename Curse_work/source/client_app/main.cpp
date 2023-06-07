#include "../logger/source/logger/concrete/logger_builder_concrete.h"
#include "../logger/source/logger/prototypes/logger.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdexcept>
#include <fstream>
#include <stdexcept>
#include <string>

#define MSG_SIZE 5000


std::ifstream open_file(std::string &filename) {

    std::ifstream file;
    file.open(filename);

    if (!file.is_open() || !file) {
        throw std::runtime_error("File doesn't exist!");
    }

    return file;
}


struct MsgQueue {

    long messageType;
    
    char buff[MSG_SIZE];	
 
};

const int MSG_Q_KEY_FLAG_SERVER = 0664;
const int MSG_Q_KEY_FLAG_CLIENT = 0700;
 
const int MSG_Q_CHANNEL_SEND = 26;
const int MSG_Q_CHANNEL_RECEIVE = 16;


 
int main(int argc, char *argv[]) {

    logging::logger *logger;
    logging::logger_builder *builder = new logger_builder_concrete();

    if (nullptr == builder) {
        std::cout << "Cannot allocate memory for builder" << std::endl;
        return -1;
    }
    
    if (argc == 3) {

        std::string filename(argv[2]);        
        logger = builder->construct_configuration(filename);

    } else if (argc == 2) {

        logger = builder
        ->add_stream("info.log", logging::logger::severity::information)
        ->add_stream("debug.log", logging::logger::severity::debug)
        ->add_stream("trace.log", logging::logger::severity::trace)
        ->construct();
    }

    if (argc < 2) {
        std::cout << "You should pass filename with commands" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream file;

    try {
        file = open_file(filename);
    } catch (std::runtime_error &ex) {
        std::cout << ex.what() << std::endl;
        return 3;
    }

    if (!file.is_open()) {
        std::cout << "File was not opened" << std::endl;
        return -3;
    }

    
    // declare variables
    key_t key_send = -1;
    key_t key_receive = -1;
    int msqid_send = -1;
    int msqid_receive = -1;
    MsgQueue msg_send;
    MsgQueue msg_receive;


    // message send

    // read file to buffer

    std::string str((std::istreambuf_iterator<char>(file)),
                       (std::istreambuf_iterator<char>()));

    char *ptr = const_cast<char *>(str.c_str());
    int count = 0;

    while (*ptr != '\0' && count < MSG_SIZE) {
        msg_send.buff[count++] = *(ptr++);
    }
    msg_send.buff[count] = '\0';
    msg_send.messageType = MSG_Q_CHANNEL_SEND;


    key_send = ftok("/bin/ls", 'P');

    if (key_send < 0) {
        perror("ftok");
        return -1;
    }
 

    msqid_send = msgget(key_send, MSG_Q_KEY_FLAG_SERVER | IPC_CREAT);

    if (msqid_send < 0) {
        perror("msgget");
        return -2;
    }


    if (logger) logger->log("User connected to server", logging::logger::severity::information);
    std::cout << "\nSuccessfully connected to server #" << msqid_send << " with the key " << key_send << std::endl;

    
    // message receive

    msg_receive.messageType = MSG_Q_CHANNEL_RECEIVE;

    key_receive = ftok("/bin/ls", 'X');

    if (key_receive < 0) {
        perror("ftok");
        return -1;
    }

    msqid_receive = msgget(key_receive, MSG_Q_KEY_FLAG_CLIENT | IPC_CREAT);

    if (msqid_receive < 0) {
        perror("msgget");
        return -3;
    }


    // send message

    if (msgsnd(msqid_send, &msg_send, sizeof(msg_send) - sizeof(long), 0) < 0) {

        perror("msgsnd");
        exit(1);
    }
    
    if (logger) logger->log("Message sent by user", logging::logger::severity::information);
    std::cout << "Sending complete!" << std::endl;
    sleep(1);


    // receive message

    if (msgrcv(msqid_receive, &msg_send, sizeof(msg_send) - sizeof(long), MSG_Q_CHANNEL_RECEIVE, 0) < 0)
    {
        perror("msgrcv");
        exit(1);
    }

    if (logger) logger->log("Message resieved by user", logging::logger::severity::information);
    std::cout << "Recieved message:" << std::endl;
    std::cout << msg_send.buff;
    
    // delete queue

    if (msgctl(msqid_receive, IPC_RMID, NULL) < 0) {
        
        perror("msgctl");
        exit(1);
    }
 
    return 0;
}