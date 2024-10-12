#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>
#include "SerialCommunication.h"
#include "MySocketClient.h"

#define BUFSIZE 67

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(SerialCommunication *serialCom, MySocketClient *socketClient):
        m_SerialCom(serialCom)
        ,m_SocketClient(socketClient) {}
    int exit = 0;
public slots:
    void doWork();

signals:
    void sig_updateUI(QString head, QString info);
    void sig_sockeSendData(QByteArray data);
    void sig_workFinished();

private:
    SerialCommunication *m_SerialCom;  // 指向主类中串口对象的指针
    MySocketClient *m_SocketClient;
};

#endif // WORKER_H
