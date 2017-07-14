#ifndef TCPCLIENTWINDOW_H
#define TCPCLIENTWINDOW_H

#include <QMainWindow>
#include <WinSock2.h>

namespace Ui {
class TcpClientWindow;
}

class TcpClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TcpClientWindow(QWidget *parent = 0);
    ~TcpClientWindow();

    static int initWSA();
    static int connToSer(SOCKET *s, const QString &ip, ushort port);

    void addLog(const QString &log);

private slots:
    void on_pushButton_newConn_clicked();

    void socketList_add(SOCKET s);
    void socketList_remove(SOCKET s);


    void on_listWidget_socketList_customContextMenuRequested(const QPoint &pos);

    void onCloseSocket();
    void onSendHelloWorld();
    void onSendText();

protected:
    void sendText(SOCKET s, const QString &text);
    void closeSocket(SOCKET s);

private:
    Ui::TcpClientWindow *ui;
};

#endif // TCPCLIENTWINDOW_H
