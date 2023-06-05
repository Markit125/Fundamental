#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
 
// Compile & Run
// g++ Client.cpp -o Client
// ./Client
 
// the structure representing the message queue
// & must match the same layout as in the server.cpp
struct MsgQueue {
    // IMPORTANT: every message structure must start with this
    long messageType;
 
    // these variables are optional & you can add 
    // more or less if you wish
    int someNumber;
    char buff[5000];	
 
};
 
// message queue flag
const int MSG_Q_KEY_FLAG = 0664;
 
// message queue type
const int MSG_Q_CHANNEL = 26;
 
int main() {
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

        perror("ftok");
        exit(1);
    }	
 
    // connect to the message queue; fail if the	
    // there is no message queue associated with
    // this key. This function returns the id of 
    // the queue.
    msqid = msgget(key, MSG_Q_KEY_FLAG);	
 
    // was the allocation a success ?
    if (msqid < 0) {

        perror("msgget");
        exit(1);	
    }
 
    // display info to the screen
    std::cout << "\nSuccessfully connected to server id #" << msqid << " with "
        << "the key " << key
        << "\n\nNow sending messages....";
                
    // send 10 messages to the server
    for (int x = 0; x < 10; ++x) {
        // set the message type - this must match
        // the 4th parameter of msgrcv() in the server.cpp code
        msg.messageType = MSG_Q_CHANNEL;
        
        // place data into the message queue structure to send to the server
        msg.someNumber = x;
        strncpy(msg.buff, "Message queues are awesome!", sizeof(msg.buff));
        
        // this is where we send messages:
        // @param: msqid - the id of the message queue
        // @param: msg - the message structure which stores the
        //   message to send
        // @param: sizeof(msg) - sizeof(long) - size of the message
        //   excluding the required first member (messageType) which is
        //   required.
        // @param: 0 - flag values (not useful for this example).
        if (msgsnd(msqid, &msg, sizeof(msg) - sizeof(long), 0) < 0) {
            perror("msgsnd");
            exit(1);
        }
    }
    
    std::cout << "Sending complete!\n";
 
    return 0;
}// http://programmingnotes.org/