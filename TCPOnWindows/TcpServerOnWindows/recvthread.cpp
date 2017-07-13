#include "recvthread.h"
#include "tcpserver.h"

RecvThread::RecvThread(SOCKET clientSock, TcpServer *server)
{
    mClientSock = clientSock;
    mTheServer = server;
}

RecvThread::~RecvThread()
{

}

void RecvThread::run()
{
    int len = 1024;
    char *buf = new char[len];
    memset(buf, 0, len);
    int rc;

    while (1) {
        rc = ::recv(mClientSock, buf, len, 0);
        if (rc <= 0) {
            printf("recv() error, %d\n", WSAGetLastError());
            mTheServer->connCountDecrease();
            break;
        } else {
            printf("client %d said: %s\n", mClientSock, buf);
        }
    }

    delete []buf;
}
