#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <WinSock2.h>
#include <string>
#include <vector>

class TcpServer
{
public:
    enum ServerStatus {
        SS_Started,
        SS_Stopped,
        SS_Starting,
        SS_Stopping
    };

public:
    TcpServer();
    virtual ~TcpServer();

    // 初始化windows网络组件,
    // 返回0,成功;返回其它值,失败.
    static int initWSA();
    // 获取本机的所有ip地址
    static std::vector<std::string> getLocalHosts();
    // 添加日志
    static void addLog(const char *log);
    // 读取当天日志文件的内容
    static std::string readLog();

    int start();
    int stop();

    void connCountIncrease()
    { ++ mConnCount; }

    void connCountDecrease()
    { -- mConnCount; }

    int connCount() const
    { return mConnCount; }

    void setServerHost(std::string host)
    { mSerHost = host; }

    std::string serverHost() const
    { return mSerHost; }

    void setServerPort(USHORT port)
    { mSerPort = port; }

    USHORT serverPort() const
    { return mSerPort; }

    SOCKET serverSocket() const
    { return mSerSock; }

    ServerStatus serverStatus() const
    { return mSerStatus; }

private:
    int                 mConnCount;     /* 连接数 */
    std::string     mSerHost;           /* 服务器主机ip */
    USHORT      mSerPort;           /* 服务器端口 */
    SOCKET      mSerSock;           /* 服务器套接字 */

    ServerStatus mSerStatus;    /* 服务器状态 */
};

#endif // TCPSERVER_H
