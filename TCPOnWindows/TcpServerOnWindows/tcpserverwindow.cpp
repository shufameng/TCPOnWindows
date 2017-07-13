#include "tcpserverwindow.h"
#include "ui_tcpserverwindow.h"
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QDebug>

#include "tcpserver.h"

TcpServer gTheServer;

TcpServerWindow::TcpServerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpServerWindow)
{
    ui->setupUi(this);


}

TcpServerWindow::~TcpServerWindow()
{
    delete ui;
}

void TcpServerWindow::on_pushButton_openCurrentDir_clicked()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::currentPath()));
}

void TcpServerWindow::on_pushButton_start_clicked()
{
    gTheServer.start();
}

void TcpServerWindow::on_pushButton_stop_clicked()
{
    gTheServer.stop();
}

void TcpServerWindow::setIpLabel(const QString &ip)
{
    ui->label_ip->setText(ip);
}

void TcpServerWindow::setPortLabel(const int port)
{
    ui->label_port->setText(QString::number(port));
}

void TcpServerWindow::setConnCountLabel(const int count)
{
    ui->label_connCount->setText(QString::number(count));
}

void TcpServerWindow::setStatus(const QString &status)
{
    ui->label_status->setText(status);
}
