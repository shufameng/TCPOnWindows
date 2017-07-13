#ifndef TCPSERVERWINDOW_H
#define TCPSERVERWINDOW_H

#include <QMainWindow>

namespace Ui {
class TcpServerWindow;
}



class TcpServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TcpServerWindow(QWidget *parent = 0);
    ~TcpServerWindow();

private slots:
    void on_pushButton_openCurrentDir_clicked();
    void on_pushButton_start_clicked();
    void on_pushButton_stop_clicked();

    void setIpLabel(const QString &ip);
    void setPortLabel(const int port);
    void setConnCountLabel(const int count);
    void setStatus(const QString &status);

private:
    Ui::TcpServerWindow *ui;


};


#endif // TCPSERVERWINDOW_H
