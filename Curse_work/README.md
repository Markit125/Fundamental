# Client-server database
A client-server database capable of storing structures of any type in pools, schemas, and collections, which are recursively stored in an "AVL-tree" structure implemented using C++ templates.
It has its own query language. The client and server communicate using IPC Unix message queues. Additionally, a separate server can be used for saving logs from the client and user.
