#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server = new NetworkServer(this);

    ui->ShowClient1->setReadOnly(true);
    ui->ShowClient2->setReadOnly(true);

    connect(ui->PortButton, &QPushButton::clicked, this, &MainWindow::listen_port);
    connect(ui->restart, &QPushButton::clicked, this, &MainWindow::restart_server);
    connect(server, &NetworkServer::receive, this, &MainWindow::receive_from_client);
}

void MainWindow::listen_port() {
    this->port = ui->PortEdit->text().toInt();
    server->listen(QHostAddress::Any, this->port);
    ui->PortButton->setEnabled(false);
    ui->PortEdit->setReadOnly(true);
    ui->PortEdit->setText("Listening...");
}

void MainWindow::remove_client(QTcpSocket* client) {
    if (client == client1) {
        client1 = nullptr;
        ui->ShowClient1->setText("");
    }
    else if (client == client2) {
        client2 = nullptr;
        ui->ShowClient2->setText("");
    }
    clients.remove(client);
}

void MainWindow::receive_from_client(QTcpSocket* client, NetworkData data) {
    if (data.op == OPCODE::LEAVE_OP) {
        remove_client(client);
        return;
    }
    if (!clients.contains(client)) {
        if (clients.size() >= max_clients) {
            QMessageBox::warning(this, "Warning", "The server is full!");
            return;
        }
        clients.insert(client);
        if (!client1)
            client1 = client;
        else if (!client2)
            client2 = client;
    }
    if (client == client1) {
        this->ui->ShowClient1->setText(data.data2);
        if (client2 && data.op == OPCODE::CHAT_OP)
            send_to_another_client(client2, data);
    }
    else if (client == client2) {
        this->ui->ShowClient2->setText(data.data2);
        if (client1 && data.op == OPCODE::CHAT_OP)
            send_to_another_client(client1, data);
    }
    else
        QMessageBox::warning(this, "Warning", "Unknown client!");
}

void MainWindow::send_to_another_client(QTcpSocket* another, NetworkData data) {
    this->server->send(another, data);
}

void MainWindow::restart_server() {
    server->close();
    clients.clear();
    client1 = nullptr;
    client2 = nullptr;
    disconnect(server, &NetworkServer::receive, this, &MainWindow::receive_from_client);
    delete server;
    server = new NetworkServer(this);
    ui->PortButton->setEnabled(true);
    ui->PortEdit->setReadOnly(false);
    ui->PortEdit->setText(QString::number(this->port));
    ui->ShowClient1->setText("");
    ui->ShowClient2->setText("");
    connect(server, &NetworkServer::receive, this, &MainWindow::receive_from_client);
}

MainWindow::~MainWindow() {
    delete ui;
    delete server;
}
