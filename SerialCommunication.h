#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include "DefineDataStruct.h"
#include <QObject>
#include <QSerialPort>
#include <qDebug>
#include <QSerialPortInfo>
#include <QMutex>

#define PLANLENTH 8

class MainWindow;
class SerialCommunication : public QObject
{
    Q_OBJECT

public:
    explicit SerialCommunication(QObject *parent = nullptr);
    void setMainInstan(MainWindow *p);
    ~SerialCommunication();
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
    MainWindow *m_main;
    int m_invalidCommunicate = 50;  // 通信间隔
    QMutex mutex;
    QTimer *m_timer;
    int m_timeoutInterval = 10;    // 超时时间（毫秒）
    void onTimeout();
public:
    QByteArray m_PlanArry = QByteArray::fromHex      ("5aa501a20801011101020300ff22"); // 下发设置计划

};

#endif // SERIALCOMMUNICATION_H

