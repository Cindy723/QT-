#include "SerialCommunication.h"
#include <QMessageBox>
#include <QThread>
#include <vector>
#include <Qtimer>
#include "mainwindow.h"

SerialCommunication::SerialCommunication(QObject *parent)
    : QObject(parent)
    ,m_bENRecev(false)
{
    connect(&m_serialPort, &QSerialPort::readyRead, this, &SerialCommunication::slot_handleReadyRead);
    // connect(&m_serialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(slot_handleError(QSerialPort::SerialPortError)));
    m_timer = new QTimer(this);
    m_timer->setSingleShot(true); // 确保定时器只触发一次

    connect(m_timer, &QTimer::timeout, this, &SerialCommunication::onTimeout);
}

void SerialCommunication::setMainInstan(MainWindow *p)
{
    m_main = p;
}

SerialCommunication::~SerialCommunication()
{
    closeSerialPort();
}

// 对串口列表进行排序
bool comparePortNames(const QString &portName1, const QString &portName2) {
    // 提取串口号中的数字部分
    QString number1 = portName1.mid(3); // 假设串口名称格式为"COMx"
    QString number2 = portName2.mid(3);
    return number1.toInt() < number2.toInt();
}

QStringList SerialCommunication::SearchCom(){
    QSerialPortInfo portInfo;
    std::vector<QString> vport;
    foreach(portInfo, QSerialPortInfo::availablePorts())
    {
        // 过滤无关串口号
        if (!portInfo.description().contains("Bluetooth", Qt::CaseInsensitive)
                && !portInfo.description().contains("蓝牙", Qt::CaseInsensitive))
        {
           vport.push_back(portInfo.portName());
        }

    }
    std::sort(vport.begin(), vport.end(), comparePortNames);

    m_serialPort.clear();
    m_receivedData.clear();

    // 将 vector<QString> 转换成 QStringList
    QStringList listprot;
    for (const auto& str : vport) {
        listprot.append(str);
    }

    return listprot;
}


bool SerialCommunication::openSerialPort(const QString &portName)
{
    m_serialPort.setPortName(portName);
    if (!m_serialPort.open(QIODevice::ReadWrite)) {
        m_port = "";
        return false;
    }

    m_serialPort.setBaudRate(QSerialPort::Baud9600);
    m_serialPort.setDataBits(QSerialPort::Data8);
    m_serialPort.setParity(QSerialPort::NoParity);
    m_serialPort.setStopBits(QSerialPort::OneStop);
    m_serialPort.setFlowControl(QSerialPort::NoFlowControl);
    m_serialPort.setReadBufferSize(1); // 缓冲大小1，这样可以每个字节都进入槽函数，否则32字节一组

    m_port = portName;
    m_bENRecev = true;
    return true;
}

void SerialCommunication::closeSerialPort()
{
    m_bENRecev = false;
    m_serialPort.close();
}

bool SerialCommunication::sendData(QByteArray data)
{
    /// 注意 QByteArray byte("\xa1\xa2"); 这种方式初始化 QByteArray 时遇到00 就会认为发送结束
    /// char 数组中间有0x00 也认为发送结束。。
    PrintQByteArray("send(hex):", data);
    data += '\n';
    qint64 bytesWritten = m_serialPort.write(data);
    m_serialPort.waitForReadyRead(m_invalidCommunicate);
    return bytesWritten != -1; //这里即便中途USB脱落也不会发送失败
}

QByteArray SerialCommunication::receiveData() const
{
    return m_receivedData;
}

void SerialCommunication::slot_handleReadyRead()
{
    if(m_bENRecev)
    {
        m_receivedData0 += m_serialPort.readAll();
        m_timer->start(m_timeoutInterval);
    }
}

void  SerialCommunication::onTimeout()
{
    // 超时触发，认为一帧数据接收结束
    m_receivedData = m_receivedData0;
    qDebug() << "Rec:" << m_receivedData;
    m_receivedData0.clear();
    emit dataReceived(m_receivedData);
}

void SerialCommunication::PrintQByteArray(QString msg, QByteArray arry)
{
    QStringList ls;
    for (int i = 0; i < arry.size(); i++) {
        ls << QString::number(static_cast<quint8>(arry.at(i)), 16).rightJustified(2, '0');
    }
     qDebug() << msg << ls;
}
//void SerialCommunication::slot_handleError(QSerialPort::SerialPortError error)
//   {
//       if (error == QSerialPort::ResourceError) {
//           // 串口资源错误，可能是设备被拔掉
//           qDebug() << "Serial port error: " << m_serialPort.errorString();
//           // 在这里可以添加处理设备被拔掉的代码
//       }
//   }
