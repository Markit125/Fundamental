#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
using namespace std;
 
// Compile & Run
// g++ Server.cpp -o Server
// ./Server
 
// the structure representing the message queue
// & must match the same layout as in the client.cpp
struct MsgQueue
{
    // IMPORTANT: every message structure must start with this
    long messageType;
 
    // these variables are optional & you can add 
    // more or less if you wish
    int someNumber;
    char buff[100];	
 
};
 
// message queue flag
const int MSG_Q_KEY_FLAG = 0664;
 
// message queue data transfer channel
const int MSG_Q_CHANNEL = 26;
 
int main()
{
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
    if(key < 0)
    {
        perror("ftok error");
        exit(1);
    }	
 
    // allocate the message queue if it does not already exist.
    // this function returns the id of the queue.
    msqid = msgget(key, MSG_Q_KEY_FLAG | IPC_CREAT);
 
    // was the allocation a success ?
    if(msqid < 0)
    {
        perror("msgget");
        exit(1);
    }
 
    // display info to the screen
    cout <<"\nThe server has started!\n"
        <<"\nWaiting for someone to connect to server id #"<<msqid<<" with "
        <<"the key "<<key<<endl<<endl;
                
    // recieve 10 messages from the client
    for(int x = 0; x < 10; ++x)
    {
        // this is where we receive messages:
        // @param: msqid - the id of the message queue
        // @param: msg - the message structure which stores the
        //   received message
        // @param: sizeof(msg) - sizeof(long) - size of the message
        //   excluding the required first member (messageType) which is
        //   required.
        // @param: MSG_Q_CHANNEL - receive all messages whose type parameter
        //   is set equal to "MSG_Q_CHANNEL"
        // @param: 0 - flag values (not useful for this example).
        if(msgrcv(msqid, &msg, sizeof(msg) - sizeof(long), MSG_Q_CHANNEL, 0) < 0)
        {
            perror("msgrcv");
            exit(1);
        }
        
        // print the received message from the client
        cout << "someNumber = "<<msg.someNumber<<" buff = "<<msg.buff<<endl;
    }
 
    // finally, deallocate the message queue
    if(msgctl(msqid, IPC_RMID, NULL) < 0)
    {
        perror("msgctl");
        exit(1);
    }
    
    cout << "\nServer is now shutting down!\n";
 
    return 0;
}