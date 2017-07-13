#ifndef TCPCLIENTWINDOW_H
#define TCPCLIENTWINDOW_H

#include <QMainWindow>

namespace Ui {
class TcpClientWindow;
}

class TcpClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TcpClientWindow(QWidget *parent = 0);
    ~TcpClientWindow();

private:
    Ui::TcpClientWindow *ui;
};

#endif // TCPCLIENTWINDOW_H
