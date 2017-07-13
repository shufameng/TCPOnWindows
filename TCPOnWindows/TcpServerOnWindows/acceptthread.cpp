#include "acceptthread.h"
#include "tcpserver.h"
#include "recvthread.h"

AcceptThread::AcceptThread(TcpServer *server)
{
    mTheServer = server;
}

AcceptThread::~AcceptThread()
{

}

void AcceptThread::run()
{
    if (!mTheServer)
        return;

    SOCKET clientSock;
    while (1) {
        clientSock = ::accept(mTheServer->serverSocket(), NULL, 0);
        if (-1 == clientSock) {
            printf("accept() error, %d\n", WSAGetLastError());
            continue;
        } else {
            mTheServer->connCountIncrease();

            RecvThread *thread = new RecvThread(clientSock, mTheServer);
            thread->start();
        }
    }
}

