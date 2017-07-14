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
    int bufLen = 1024;
    char *buf = new char[bufLen];
    memset(buf, 0, bufLen);

    int logLen = 1024;
    char *log = new char[logLen];
    memset(log, 0, logLen);

    int rc;

    while (1) {
        rc = ::recv(mClientSock, buf, bufLen, 0);
        if (rc <= 0) {
            sprintf(log, "recv() error, %d\n", WSAGetLastError());
            mTheServer->connCountDecrease();
            TcpServer::addLog(log);
            break;
        } else {
            sprintf(log, "client %d said: %s\n", mClientSock, buf);
            TcpServer::addLog(log);
        }
    }

    delete []buf;
    delete []log;
}
