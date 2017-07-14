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

std::vector<std::string> TcpServer::getLocalHosts()
{
    std::vector<std::string> hosts;
    char hostName[256];
    int rc = gethostname(hostName, sizeof(hostName));
    if (SOCKET_ERROR == rc)
        return hosts;

    struct hostent *ht = gethostbyname(hostName);
    if (!ht)
        return hosts;

    struct in_addr addr;
    for (int i = 0; i < ht->h_length; i ++) {
        if (ht->h_addr_list[i]) {
            memcpy(&addr, ht->h_addr_list[i], sizeof(addr));
            hosts.push_back(std::string(inet_ntoa(addr)));
        }
    }

    return hosts;
}

void TcpServer::addLog(const char *log)
{
    // 获取程序运行路径
    char path[256];
    GetCurrentDirectoryA(sizeof(path), path);
    char fileName[64];

    // 根据当前日期获取日志文件名
    SYSTEMTIME t;
    GetLocalTime(&t);
    sprintf(fileName, "\\%d-%02d-%02d.txt", t.wYear, t.wMonth, t.wDay);

    // 合成日志文件路径名
    strcat(path, fileName);

    // 打开文件
    FILE *pFile = fopen(path, "a");
    if (!pFile)
        return;

    // 写入内容,关闭文件
    fwrite(log, strlen(log), 1, pFile);
    fflush(pFile);
    fclose(pFile);
}

std::string TcpServer::readLog()
{
    // 获取程序运行路径
    char path[256];
    GetCurrentDirectoryA(sizeof(path), path);
    char fileName[64];

    // 根据当前日期获取日志文件名
    SYSTEMTIME t;
    GetLocalTime(&t);
    sprintf(fileName, "\\%d-%02d-%02d.txt", t.wYear, t.wMonth, t.wDay);

    // 合成日志文件路径名
    strcat(path, fileName);

    // 打开文件
    FILE *pFile = fopen(path, "r");
    if (!pFile)
        return std::string();

    // 获取文件长度
    fseek(pFile, 0, SEEK_END);
    int fileSize = ftell(pFile);

    // 开辟内存,读取文件内容
    char *buf = new char[fileSize];
    memset(buf, 0, fileSize);
    fseek(pFile, 0, SEEK_SET);
    fread(buf, fileSize, 1, pFile);

    std::string str = buf;
    delete []buf;

    return str;
}

int TcpServer::start()
{
    int rc;

    mSerStatus = SS_Starting;

    // socket()
    mSerSock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (-1 == mSerSock) {
        printf("socket() error, %d\n", WSAGetLastError());
        mSerStatus = SS_Stopped;
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
        mSerStatus = SS_Stopped;
        return -1;
    }

    // listen()
    rc = ::listen(mSerSock, SOMAXCONN);
    if (-1 == rc) {
        printf("listen() error, %d\n", WSAGetLastError());
        mSerStatus = SS_Stopped;
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

