#ifndef ACCEPTTHREAD_H
#define ACCEPTTHREAD_H

#include "basethread.h"

class TcpServer;

class AcceptThread : public BaseThread
{
public:
    AcceptThread(TcpServer *server);
    ~AcceptThread();

protected:
    void run();

private:
    TcpServer *mTheServer;
};

#endif // ACCEPTTHREAD_H
