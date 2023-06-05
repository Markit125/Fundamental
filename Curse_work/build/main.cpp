#include <cstring>
#include <iostream>
#include <string>
#include <sstream>

struct MsgQueue {
    // IMPORTANT: every message structure must start with this
    long messageType;
 
    // these variables are optional & you can add 
    // more or less if you wish
    int someNumber;
    char buff[200];	
 
};
 

int main() {

    std::stringstream ss;

    MsgQueue msg;

    strncpy(msg.buff, "Message queues are awesome!", sizeof(msg.buff));

    ss << msg.buff;

    std::cout << ss.str();
}