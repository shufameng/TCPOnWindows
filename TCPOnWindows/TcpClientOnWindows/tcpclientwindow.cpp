#include "tcpclientwindow.h"
#include "ui_tcpclientwindow.h"

TcpClientWindow::TcpClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpClientWindow)
{
    ui->setupUi(this);
}

TcpClientWindow::~TcpClientWindow()
{
    delete ui;
}
