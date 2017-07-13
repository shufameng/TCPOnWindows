#include "tcpserver.h"
#include "acceptthread.h"

TcpServer::TcpServer()
{
    mConnCount = 0;
    mSerHost = "";
    mSerPort = 8888;
    mSerSock = 0;
    mSerStatus = SS_Stopped;
}

TcpServer::~TcpServer()
{

}

int TcpServer::initWSA()
{
    WSADATA wsa;
    DWORD ver = MAKEWORD(2, 2);
    int rc = WSAStartup(ver, &wsa);
    if (0 != rc)
        return rc;

    if (2 != (HIBYTE(wsa.wVersion)) || (2 != LOBYTE(wsa.wVersion)))
        return -1;

    return rc;
}

int TcpServer::start()
{
    int rc;

    // socket()
    mSerSock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (-1 == mSerSock) {
        printf("socket() error, %d\n", WSAGetLastError());
        return -1;
    }

    // bind()
    sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.S_un.S_addr = inet_addr(mSerHost.data());
    serAddr.sin_port = htons(mSerPort);
    rc = ::bind(mSerSock, (struct sockaddr*)(&serAddr), sizeof(serAddr));
    if (-1 == rc) {
        printf("bind() error, %d\n", WSAGetLastError());
        return -1;
    }

    // listen()
    rc = ::listen(mSerSock, SOMAXCONN);
    if (-1 == rc) {
        printf("listen() error, %d\n", WSAGetLastError());
        return -1;
    }

    // accept()
    AcceptThread *t = new AcceptThread(this);
    t->start();

    mSerStatus = SS_Started;

    return 0;
}

int TcpServer::stop()
{
    return 0;
}

