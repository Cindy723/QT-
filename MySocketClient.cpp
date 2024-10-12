#include "MySocketClient.h"

#include <QCoreApplication>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include "mainwindow.h"
#include <QNetworkProxy>

MySocketClient::MySocketClient(QObject *parent)
    : QObject(parent),
    m_socket(new QTcpSocket(this))
{
    // 连接信号和槽，处理连接成功和数据读取
    connect(m_socket, &QTcpSocket::connected, this, &MySocketClient::onConnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &MySocketClient::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &MySocketClient::onDisconnected);
    connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &MySocketClient::onError);

}

void MySocketClient::setMainInstan(MainWindow *p)
{
    m_main = p;
}

void MySocketClient::connectToHost(const QString &host, quint16 port)
{
    // 连接到目标IP和端口
    if(m_conncetFlag == 1){
        qDebug() << "Socket已经连接!";
        m_main->updateOperationResult("Socket已经连接!");
        return;
    }

    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::NoProxy); // 不使用代理
    m_socket->setProxy(proxy);
    m_socket->connectToHost(host, port);
}

void MySocketClient::onConnected()
{
    qDebug() << "Connected to server.";
    m_main->updateOperationResult("Socket连接成功!");
    m_conncetFlag = 1;
    // 连接成功后可以发送数据
    QByteArray data = "Hello, Server!";
    m_socket->write(data);
}

void MySocketClient::onReadyRead()
{
    // 读取服务器发送的数据
    QByteArray data = m_socket->readAll();
    qDebug() << "Received from server:" << data;
    m_main->setHistoryTextInfo("MCU-> ", data.toStdString().c_str());
}

void MySocketClient::onDisconnected()
{
    qDebug() << "Disconnected from server.";
    m_main->updateOperationResult("Disconnected from server.");
    m_conncetFlag = 0;
}

void MySocketClient::onError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Socket error:" << socketError << m_socket->errorString();
    m_main->updateOperationResult(m_socket->errorString());
    m_conncetFlag = 0;
}

void MySocketClient::sendData(QByteArray data)
{
    m_socket->write(data);
}
