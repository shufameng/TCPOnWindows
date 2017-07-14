#include "tcpclientwindow.h"
#include "ui_tcpclientwindow.h"
#include <QMenu>
#include <QInputDialog>

TcpClientWindow::TcpClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpClientWindow)
{
    ui->setupUi(this);
    initWSA();


}

TcpClientWindow::~TcpClientWindow()
{
    delete ui;
}

int TcpClientWindow::initWSA()
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

int TcpClientWindow::connToSer(SOCKET *s, const QString &ip, ushort port)
{
    *s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (-1 == *s)
        return -1;

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    QByteArray arrayIP = ip.toLocal8Bit();
    addr.sin_addr.S_un.S_addr = inet_addr(arrayIP.data());
    addr.sin_port = htons(port);

    int rc = ::connect(*s, (struct sockaddr*)(&addr), sizeof(addr));
    if (-1 == rc)
        return -1;

    return 0;
}

void TcpClientWindow::addLog(const QString &log)
{
    ui->textEdit_log->append(log);
}

void TcpClientWindow::on_pushButton_newConn_clicked()
{
    SOCKET s;
    if (0 != connToSer(&s, ui->lineEdit_serverIP->text(), ui->lineEdit_serverPort->text().toUShort())) {
        addLog(QString("connect() error, %1").arg(WSAGetLastError()));
        return;
    } else {
        addLog(QString("Socket %1 created").arg(s));
    }

    socketList_add(s);
}

void TcpClientWindow::socketList_add(SOCKET s)
{
    ui->listWidget_socketList->addItem(new QListWidgetItem(QString::number(s)));
}

void TcpClientWindow::socketList_remove(SOCKET s)
{
    for (int i = 0; i < ui->listWidget_socketList->count(); i++) {
        if (ui->listWidget_socketList->item(i)->text().toUInt() == s) {
            QListWidgetItem *item = ui->listWidget_socketList->takeItem(i);
            delete item;
            item = NULL;
        }
    }
}

void TcpClientWindow::on_listWidget_socketList_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);

    if (ui->listWidget_socketList->currentItem()) {
        QMenu m(this);
        m.addAction(QString::fromLocal8Bit("关闭连接"), this, SLOT(onCloseSocket()));
        m.addAction(QString::fromLocal8Bit("发送 Hello World"), this, SLOT(onSendHelloWorld()));
        m.addAction(QString::fromLocal8Bit("发送自定义的字符串"), this, SLOT(onSendText()));
        m.exec(QCursor::pos());
    }
}

void TcpClientWindow::onCloseSocket()
{
    SOCKET s = ui->listWidget_socketList->currentItem()->text().toUInt();
    this->closeSocket(s);
}

void TcpClientWindow::onSendHelloWorld()
{
    SOCKET s = ui->listWidget_socketList->currentItem()->text().toUInt();
    sendText(s, "Hello World");
}

void TcpClientWindow::onSendText()
{
    SOCKET s = ui->listWidget_socketList->currentItem()->text().toUInt();

    QString text = QInputDialog::getText(this,
                          QString::fromLocal8Bit("输入字符串"),
                          QString::fromLocal8Bit("输入你要发送的字符串"));

    if (text.isEmpty())
        return;

    sendText(s, text);
}

void TcpClientWindow::sendText(SOCKET s, const QString &text)
{
    QByteArray arrayText = text.toLocal8Bit();
    int rc = ::send(s, arrayText.data(), strlen(arrayText.data()), 0);
    if (rc <= 0) {
        addLog(QString("send() error, %1").arg(WSAGetLastError()));
        return;
    } else {
        addLog(QString("Socket %1 send '%2'").arg(s).arg(text));
        return;
    }
}

void TcpClientWindow::closeSocket(SOCKET s)
{
    ::closesocket(s);
    socketList_remove(s);
    addLog(QString("Socket %1 closed").arg(s));
}

