#ifndef RECVTHREAD_H
#define RECVTHREAD_H

#include <WinSock2.h>
#include "basethread.h"

class TcpServer;

class RecvThread : public BaseThread
{
public:
    RecvThread(SOCKET clientSock, TcpServer *server);
    ~RecvThread();

protected:
    void run();

private:
    SOCKET mClientSock;
    TcpServer *mTheServer;
};

#endif // RECVTHREAD_H
