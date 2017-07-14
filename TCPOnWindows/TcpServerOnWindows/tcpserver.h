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

    // ��ʼ��windows�������,
    // ����0,�ɹ�;��������ֵ,ʧ��.
    static int initWSA();
    // ��ȡ����������ip��ַ
    static std::vector<std::string> getLocalHosts();
    // �����־
    static void addLog(const char *log);
    // ��ȡ������־�ļ�������
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
    int                 mConnCount;     /* ������ */
    std::string     mSerHost;           /* ����������ip */
    USHORT      mSerPort;           /* �������˿� */
    SOCKET      mSerSock;           /* �������׽��� */

    ServerStatus mSerStatus;    /* ������״̬ */
};

#endif // TCPSERVER_H
