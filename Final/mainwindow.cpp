#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer(this);

    // whenever a user connects, it will emit signal
    connect(server, SIGNAL(newConnection()),
            this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 9999))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started!";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), SLOT(receiveMessage()));
    socket->connectToHost("localhost", 9999);
    if(!socket->waitForDisconnected(3000)){
        qDebug() << "Error:" << socket->errorString();
    }
    QJsonObject object
    {
        {"property1", 1},
        {"property2", 2}
    };
    QJsonDocument doc(object);
    QByteArray bytes = doc.toJson();

    qDebug() << bytes;
    ui->textBrowser->append(bytes);

//    QFile file("jsonString.json");
//    if(!file.open(QFile::ReadOnly)){
//        qDebug()<< "Error, Cannot open the file.";
//    }

//    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
//    qDebug()<< jsonDoc.object().value("property1").toString();
}

void MainWindow::newConnection(){
    qDebug() << "Successful Connection!";
    // need to grab the socket
    QTcpSocket *socket = server->nextPendingConnection();

    socket->write("Hello client\r\n");
    socket->flush();

    socket->waitForBytesWritten(3000);

    socket->close();
}

void MainWindow::receiveMessage()
{
    ui->textBrowser->append(socket->readAll());
}
