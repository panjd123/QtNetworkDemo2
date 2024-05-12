#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ip_edit->setText(ip);
    ui->port_edit->setText(QString::number(port));
    ui->send_button->setEnabled(false);
    ui->disconnect_button->setEnabled(false);
    ui->receive_edit->setReadOnly(true);

    socket = new NetworkSocket(new QTcpSocket(this), this); // 创建一个客户端对象，其父对象为当前窗口

    connect(socket->base(), &QTcpSocket::connected, this, &MainWindow::connected_successfully);  // connected 是客户端连接成功后发出的信号
    connect(ui->connect_button, &QPushButton::clicked, this, &MainWindow::connectToServer); // 连接服务器
    connect(ui->disconnect_button, &QPushButton::clicked, this, &MainWindow::disconnectFromServer); // 断开连接
    connect(ui->send_button, &QPushButton::clicked, this, &MainWindow::sendMessage); // 发送消息
    connect(socket, &NetworkSocket::receive, this, &MainWindow::receiveMessage);
    // receive 是客户端收到消息后发出的信号，receiveMessage 是处理这个信号的槽函数
}

void MainWindow::connectToServer() {
    this->ip = ui->ip_edit->text();
    this->port = ui->port_edit->text().toInt();
    socket->hello(ip, port);                       // 连接服务器 ip:port
    this->socket->base()->waitForConnected(2000);  // 等待连接，2s 后超时
    // 你可以不阻塞（或者说连接在后台做），但这意味着你可以在连接成功前操作你的界面，比如发生消息，但此时还没建立连接，所以会出错
    // 建议懒人总是阻塞等待，写起来省事
}

void MainWindow::connected_successfully() {
    // 连接成功后，设置界面的状态
    ui->connect_button->setEnabled(false);
    ui->disconnect_button->setEnabled(true);
    ui->send_button->setEnabled(true);
    ui->port_edit->setReadOnly(true);
    ui->ip_edit->setText("Connected");
    ui->ip_edit->setReadOnly(true);
    socket->send(NetworkData(OPCODE::READY_OP, "", "", ""));
    // 这个程序中，连接成功后，发送一个消息给服务器，告诉服务器我已经准备好了,这不是网络中必须的操作，但是在游戏中，我们可能会规定这样的行为
}

void MainWindow::disconnectFromServer() {
    socket->send(NetworkData(OPCODE::LEAVE_OP, "", "", ""));
    // 这个程序中，客户端断开连接时要发送一个消息给服务器，这不是网络中必须的操作，这只是方便服务端知道客户端正常离开了（而不是异常断开）
    // 否则其实 tcp 连接中，服务端怎么检测客户端是否异常断开连接是一个有点烦人的问题，你可以搜索“qt tcp 怎么监测客户端有没有断开”
    socket->bye();
    // 在这个网络包里，断开只要调用 bye 就行了，但是在游戏的联机协议里，我们可能会规定其他行为，比如上面说的发送一个消息
    ui->connect_button->setEnabled(true);
    ui->disconnect_button->setEnabled(false);
    ui->send_button->setEnabled(false);
    ui->port_edit->setReadOnly(false);
    ui->ip_edit->setReadOnly(false);
    ui->ip_edit->setText(ip);
}

void MainWindow::sendMessage() {
    QString message = ui->send_edit->text();
    socket->send(NetworkData(OPCODE::CHAT_OP, "", message, "")); // 发送消息给服务端，是不是很简单
    ui->send_edit->clear();
}

void MainWindow::receiveMessage(NetworkData data) {
    ui->receive_edit->setText(data.data2); // data 是收到的消息，我们显示出来
}

MainWindow::~MainWindow() {
    delete ui;
    delete socket;
}
