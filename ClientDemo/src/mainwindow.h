#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../NetworkLibrary/networkdata.h"
#include "../../NetworkLibrary/networksocket.h"

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
    QString ip = "127.0.0.1";
    NetworkSocket *socket;
    Ui::MainWindow *ui;

private slots:
    void connected_successfully();
    void connectToServer();
    void disconnectFromServer();
    void sendMessage();
    void receiveMessage(NetworkData);
};
#endif // MAINWINDOW_H
