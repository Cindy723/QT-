#include "worker.h"

void Worker::doWork()
{
    int method = 0;
    if(m_SerialCom->m_port != "")
    {
        method = 1;
    }

    if(m_SocketClient->m_conncetFlag == 1)
    {
        method = 2;
    }

    // 直通路径数据生成与发送
    if(method == 1){
        m_SerialCom->sendData("CH1_H");
    }else if(method == 2){
        //m_SocketClient->sendData("CH1_H");
        emit sig_sockeSendData("CH1_H");
    }

    QByteArray temp[BUFSIZE][3];
    for (int i = 0; i < BUFSIZE; ++i) {
        temp[i][0] = "FRE_CH1=" + QByteArray::number(2000 + i * 100);       // 频率通道从2000开始，每次增加100
        temp[i][1] = "POWER_CH1=" + QByteArray::number(i);                      // 功率从0开始，每次增加1
        temp[i][2] = "TEST_ADC=" + QByteArray::number(109 + i * 10);        // ADC值从109开始，每次增加10
    }

    QThread::msleep(100);
    QString disp;
    for (uint i = 0; i < BUFSIZE; ++i){
        disp = QString("----------i=%1----------").arg(i);
        emit sig_updateUI("", disp);

        for (uint j = 0; j < 3; ++j){
            if(method == 1){
                m_SerialCom->sendData(temp[i][j]);
            }else if(method == 2){
                emit sig_sockeSendData(temp[i][j]);
            }

            emit sig_updateUI("MCU<- ", temp[i][j]);
            QThread::msleep(50);
        }

        // 通过查询命令为基准 作为一次命令周期结束
        if(method == 1){
            m_SerialCom->sendData("CH1_V?");
        }else if(method == 2){
            //m_SocketClient->sendData("CH1_V?");
            emit sig_sockeSendData("CH1_V?");
        }

        emit sig_updateUI("MCU<- ", "CH1_V?");
        QThread::msleep(50);

        if(exit){
            i = BUFSIZE;
        }
    }


    // 衰减路径数据生成与发送
    QThread::msleep(1000);
    if(method == 1){
        m_SerialCom->sendData("CH1_L");
    }else if(method == 2){
        //m_SocketClient->sendData("CH1_L");
        emit sig_sockeSendData("CH1_L");
    }

    for (int i = 0; i < BUFSIZE; ++i) {
        temp[i][0] = "FRE_CH1=" + QByteArray::number(600 + i * 100);       // 频率通道从2000开始，每次增加100
        temp[i][1] = "POWER_CH1=" + QByteArray::number(i+66);
        temp[i][2] = "TEST_ADC=" + QByteArray::number(34 + i * 10);        // ADC值从109开始，每次增加10
    }
    QThread::msleep(100);
    for (uint i = 0; i < BUFSIZE; ++i){
        disp = QString("----------i=%1----------").arg(i);
        emit sig_updateUI("", disp);

        for (uint j = 0; j < 3; ++j){
            if(method == 1){
                m_SerialCom->sendData(temp[i][j]);
            }else if(method == 2){
                emit sig_sockeSendData(temp[i][j]);
            }

            emit sig_updateUI("MCU<- ", temp[i][j]);
            QThread::msleep(50);
        }

        // 通过查询命令为基准 作为一次命令周期结束
        if(method == 1){
            m_SerialCom->sendData("CH1_V?");
        }else if(method == 2){
            //m_SocketClient->sendData("CH1_V?");
            emit sig_sockeSendData("CH1_V?");
        }

        emit sig_updateUI("MCU<- ", "CH1_V?");
        QThread::msleep(50);

        if(exit){
            i = BUFSIZE;
        }
    }
    emit sig_workFinished();  // 发出完成信号
}
