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

    // 初始化windows网络组件
    TcpServer::initWSA();

    // 获取本机所有IP地址,并加载到界面
    ui->comboBox_host->clear();
    std::vector<std::string> hosts = TcpServer::getLocalHosts();
    for (uint i = 0; i < hosts.size(); i ++)
        ui->comboBox_host->addItem(QString::fromStdString(hosts.at(i)));

    // 设置默认端口
    setPortLabel(8888);

    // 计时器,用于定时加载服务器的信息到界面
    connect(&mTimer, SIGNAL(timeout()), this, SLOT(updateServerMsg()));
    mTimer.setInterval(1000);
    mTimer.setSingleShot(false);

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
    gTheServer.setServerHost(ui->comboBox_host->currentText().toStdString());
    gTheServer.setServerPort(ui->lineEdit_port->text().toUShort());
    gTheServer.start();
    mTimer.start();
}

void TcpServerWindow::on_pushButton_stop_clicked()
{
    gTheServer.stop();

}

void TcpServerWindow::setIpLabel(const QString &ip)
{
    ui->comboBox_host->setCurrentText(ip);
}

void TcpServerWindow::setPortLabel(const int port)
{
    ui->lineEdit_port->setText(QString::number(port));
}

void TcpServerWindow::setConnCountLabel(const int count)
{
    ui->label_connCount->setText(QString::number(count));
}

void TcpServerWindow::setStatus(const QString &status)
{
    ui->label_status->setText(status);
}

void TcpServerWindow::updateServerMsg()
{
    ui->comboBox_host->setCurrentText(
                QString::fromStdString(gTheServer.serverHost()));
    ui->lineEdit_port->setText(
                QString::number(gTheServer.serverPort()));
    ui->label_connCount->setText(
                QString::number(gTheServer.connCount()));

    if (gTheServer.serverStatus() == TcpServer::SS_Started) {
        ui->label_status->setText(QString::fromLocal8Bit("服务器已经启动"));
        ui->pushButton_start->setDisabled(true);
        ui->pushButton_stop->setDisabled(false);
    }
    else if (gTheServer.serverStatus() == TcpServer::SS_Stopped) {
        ui->label_status->setText(QString::fromLocal8Bit("服务器已经停止"));
        ui->pushButton_start->setDisabled(false);
        ui->pushButton_stop->setDisabled(true);
    }
    else if (gTheServer.serverStatus() == TcpServer::SS_Starting) {
        ui->label_status->setText(QString::fromLocal8Bit("服务器正在启动..."));
        ui->pushButton_start->setDisabled(true);
        ui->pushButton_stop->setDisabled(true);
    }
    else if (gTheServer.serverStatus() == TcpServer::SS_Stopping) {
        ui->label_status->setText(QString::fromLocal8Bit("服务器正在停止..."));
        ui->pushButton_start->setDisabled(true);
        ui->pushButton_stop->setDisabled(true);
    }
}
