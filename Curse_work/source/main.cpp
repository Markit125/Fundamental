#include <iostream>
#include <cstdlib>
#include <ostream>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "processing/processing.h"
#include "logger/source/logger/concrete/logger_builder_concrete.h"

#define MSG_SIZE 5000
 
struct MsgQueue {

    long messageType;
    char buff[MSG_SIZE];
 
};

const int MSG_Q_KEY_FLAG_SERVER = 0664;
const int MSG_Q_KEY_FLAG_CLIENT = 0700;

const int MSG_Q_CHANNEL_RECEIVE = 26;
const int MSG_Q_CHANNEL_SEND = 16;

 
int main(int argc, char *argv[]) {

    logging::logger *logger;
    logging::logger_builder *builder = new logger_builder_concrete();
    
    if (nullptr == builder) {
        std::cout << "Cannot allocate memory for builder" << std::endl;
        return -1;
    }
    
    if (argc == 2) {
    
        std::string filename(argv[1]);

        logger = builder->construct_configuration(filename);

    } else if (argc == 1) {

        logger = builder
        ->add_stream("info.log", logging::logger::severity::information)
        ->add_stream("debug.log", logging::logger::severity::debug)
        ->add_stream("trace.log", logging::logger::severity::trace)
        ->construct();
    }

    delete builder;


    database *db = new database(logger);

    if (nullptr == db) {
        std::cout << "Cannot allocate memory for database" << std::endl;
        return -4;
    }


    // declare variables
    key_t key_receive = -1;
    key_t key_send = -1;
    int msqid_receive = -1;
    int msqid_send = -1;
    MsgQueue msg_receive;
    MsgQueue msg_send;
 

    key_receive = ftok("/bin/ls", 'P');
    
    if (key_receive < 0) {
        perror("ftok error");
        exit(1);
    }	
 

    msqid_receive = msgget(key_receive, MSG_Q_KEY_FLAG_SERVER | IPC_CREAT);

    if (msqid_receive < 0) {
        perror("msgget");
        exit(1);
    }
 
 
    std::cout << "\nThe server has started!\n" << "\nWaiting for someone to connect to server #" << msqid_receive
              << " with the key " << key_receive << std::endl;


    // while (1) {
    for (int i = 0; i < 3; ++i) {

        if (msgrcv(msqid_receive, &msg_receive, sizeof(msg_receive) - sizeof(long), MSG_Q_CHANNEL_RECEIVE, 0) < 0)
        {
            perror("msgrcv");
            return -3;
        }

        std::stringstream ss;
        std::stringstream out;
        ss << msg_receive.buff;

        process_file(db, ss, out, logger);

        std::cout << "processed\n";

        std::string str = out.str();
        char *ptr = const_cast<char *>(str.c_str());
        int count = 0;

        while (*ptr != '\0' && count < MSG_SIZE) {
            msg_send.buff[count++] = *(ptr++);
        }
        msg_send.buff[count] = '\0';
        
        msg_send.messageType = MSG_Q_CHANNEL_SEND;
        

        key_send = ftok("/bin/ls", 'X');

        if (key_send < 0) {
            perror("ftok");
            return -1;
        }


        msqid_send = -1;
        msqid_send = msgget(key_send, MSG_Q_KEY_FLAG_CLIENT | IPC_CREAT);

        if (msqid_send < 0) {
            perror("msgget");
            return -2;
        }


        if (msgsnd(msqid_send, &msg_send, sizeof(msg_send) - sizeof(long), 0) < 0) {

            perror("msgsnd");
            return -4;
        }

        if (logger) logger->log("Message processed", logging::logger::severity::information);
        sleep(1);

    }
 
    if (msgctl(msqid_receive, IPC_RMID, NULL) < 0) {
        
        perror("msgctl");
        return -5;
    }

    delete db;
    
    std::cout << "\nServer is now shutting down!\n";
 
    return 0;
}