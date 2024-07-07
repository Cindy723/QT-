#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include "DefineDataStruct.h"
#include <QObject>
#include <QSerialPort>
#include <qDebug>
#include <QSerialPortInfo>
#include <QMutex>

#define PLANLENTH 8

class SerialCommunication : public QObject
{
    Q_OBJECT

public:
    explicit SerialCommunication(QObject *parent = nullptr);
    ~SerialCommunication();
    friend class MainWindow;
    QString m_port; // 当前串口
    QStringList SearchCom(void);
    bool openSerialPort(const QString &portName);
    void closeSerialPort();
    bool sendData(QByteArray data);
    QByteArray receiveData() const;

    QSerialPort m_serialPort;
    QByteArray m_receivedData0;
    QByteArray m_receivedData;
    QByteArray m_receivedTotalData; // 大于32字节时QT会分包 返回这个
    void PrintQByteArray(QString msg, QByteArray arry);
    bool m_bENRecev;
signals:
    void dataReceived(QByteArray &data);

private slots:
    void slot_handleReadyRead();
    //void slot_handleError(QSerialPort::SerialPortError error);
private:
    int m_invalidCommunicate = 50;  // 通信间隔
    QMutex mutex;

public:
    QByteArray m_PlanArry = QByteArray::fromHex      ("5aa501a20801011101020300ff22"); // 下发设置计划
    QByteArray m_J1OpenArry = QByteArray::fromHex    ("5AA5001A01010122");             // 锁1 操作 开
    QByteArray m_J1OFFArry = QByteArray::fromHex     ("5AA5001A01010022");             // 锁1 操作 关

    QByteArray m_J2OpenArry = QByteArray::fromHex    ("5AA5001A01020122");             // 锁2 操作 开
    QByteArray m_J2OFFArry = QByteArray::fromHex     ("5AA5001A01020022");             // 锁2 操作 关

    QByteArray m_J3OpenArry = QByteArray::fromHex    ("5AA5001A01030122");             // 锁3 操作 开
    QByteArray m_J3OFFArry = QByteArray::fromHex     ("5AA5001A01030022");             // 锁3 操作 关

    QByteArray m_J4OpenArry = QByteArray::fromHex    ("5AA5001A01040122");             // 锁4 操作 开
    QByteArray m_J4OFFArry = QByteArray::fromHex     ("5AA5001A01040022");             // 锁4 操作 关

};

#endif // SERIALCOMMUNICATION_H

