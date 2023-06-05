#include <iostream>
#include <cstdlib>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "processing/processing.h"
#include "logger/source/logger/concrete/logger_builder_concrete.h"

#define MSG_SIZE 5000
 
// the structure representing the message queue
// & must match the same layout as in the client.cpp
struct MsgQueue {
    // IMPORTANT: every message structure must start with this
    long messageType;
 
    // these variables are optional & you can add 
    // more or less if you wish
    int someNumber;
    char buff[MSG_SIZE];
 
};
 
// message queue flag
const int MSG_Q_KEY_FLAG = 0664;
 
// message queue data transfer channel
const int MSG_Q_CHANNEL = 26;
 
int main(int argc, char *argv[]) {

    logging::logger_builder *builder = new logger_builder_concrete();

    if (nullptr == builder) {
        std::cout << "Cannot allocate memory for builder" << std::endl;
        return -1;
    }


    logging::logger *logger;

    try {
        logger = builder->construct_configuration("../source/configuration/conf.json");
    } catch (std::runtime_error &ex) {
        std::cout << ex.what() << std::endl;
        return -2;
    }


    database *db = new database(logger);

    if (nullptr == db) {
        std::cout << "Cannot allocate memory for database" << std::endl;
        return -4;
    }


    // declare variables
    key_t key = -1;
    int msqid = -1;
    MsgQueue msg;
 
    // use a random file and a random character to generate
    // a unique key. The same parameters to this function will 
    // always generate the same value. This is how multiple
    // processes can connect to the same queue.
    key = ftok("/bin/ls", 'K');
 
    // was the key allocation successful ?
    if (key < 0) {
        
        perror("ftok error");
        exit(1);
    }	
 
    // allocate the message queue if it does not already exist.
    // this function returns the id of the queue.
    msqid = msgget(key, MSG_Q_KEY_FLAG | IPC_CREAT);
 
    // was the allocation a success ?
    if (msqid < 0) {
        
        perror("msgget");
        exit(1);
    }
 
    // display info to the screen
    std::cout << "\nThe server has started!\n"
        << "\nWaiting for someone to connect to server id #" << msqid << " with "
        << "the key " << key << std::endl;


    while (1) {

        if (msgrcv(msqid, &msg, sizeof(msg) - sizeof(long), MSG_Q_CHANNEL, 0) < 0)
        {
            perror("msgrcv");
            exit(1);
        }


        std::stringstream ss;
        ss << msg.buff;
        
        
        process_file(db, ss, logger);
    }
 
    // finally, deallocate the message queue
    if (msgctl(msqid, IPC_RMID, NULL) < 0) {
        
        perror("msgctl");
        exit(1);
    }

    delete db;
    
    std::cout << "\nServer is now shutting down!\n";
 
    return 0;
}