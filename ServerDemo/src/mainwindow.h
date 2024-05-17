#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>
#include <QMessageBox>
#include "../../NetworkLibrary/networkdata.h"
#include "../../NetworkLibrary/networkserver.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    int port = 10086;
    const int max_clients = 2;
    Ui::MainWindow *ui;
    QSet<QTcpSocket*> clients;
    NetworkServer* server = nullptr;
    QTcpSocket* client1 = nullptr;
    QTcpSocket* client2 = nullptr;
    void send_to_another_client(QTcpSocket* another, NetworkData data);
    void remove_client(QTcpSocket* client);
    void remove_all_clients();

private slots:
    void listen_port();
    void restart_server();
    void receive_from_client(QTcpSocket* client, NetworkData data);
};
#endif // MAINWINDOW_H
