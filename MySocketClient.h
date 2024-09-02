#ifndef MYSOCKETCLIENT_H
#define MYSOCKETCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>

class MainWindow;  // 前向声明 防止递归 在CPP包含.h
class MySocketClient : public QObject
{
    Q_OBJECT

public:
    explicit MySocketClient(QObject *parent = nullptr);
    void setMainInstan(MainWindow *p);
    void connectToHost(const QString &host, quint16 port);
    int m_conncetFlag = 0;
private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);

public Q_SLOTS:
    void sendData(QByteArray data);
private:
    QTcpSocket *m_socket;
    MainWindow *m_main;
};

#endif // MYSOCKETCLIENT_H
