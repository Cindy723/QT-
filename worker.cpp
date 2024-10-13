#include "worker.h"
#include <QString>

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

    float fbase = 1400;
    int vbase = 1;
    int power = -30;

    QString CH3Sta[4] = {"CH3_L", "CH3_H", "CH3_PP", "CH3_P"};
    for (int sta = 0; sta < 4; ++sta) {
       emit sig_sockeSendData(CH3Sta[sta].toUtf8());
       emit sig_updateUI("MCU<- ", CH3Sta[sta].toUtf8());
       QThread::msleep(200);
       for (int fre = 0; fre < 3; ++fre) {
           QString f = QString("FREQUE=%1").arg(fbase+fre*100);
           emit sig_sockeSendData(f.toUtf8());
           emit sig_updateUI("MCU<- ", f.toUtf8());
           QThread::msleep(200);
           for(int tv = 0; tv < 20; ++tv)
           {
               QString P = QString("POWER=%1").arg(power++);
               emit sig_sockeSendData(P.toUtf8());
               emit sig_updateUI("MCU<- ", P);
               QThread::msleep(200);

               QString a = QString("TEST_ADC=%1").arg(tv*vbase+1000);
               emit sig_sockeSendData(a.toUtf8());
               emit sig_updateUI("MCU<- ", a);
               QThread::msleep(200);

               QString v = QString("CH3_V?");
               emit sig_sockeSendData(v.toUtf8());
               QThread::msleep(200);
              if(exit){break;}
           }

           power = -30;
           vbase ++;
           if(exit){break;}
         }
        if(exit){break;}
    }


    emit sig_sockeSendData("CH3_END");
    emit sig_updateUI("MCU<- ", "CH3_END");

    emit sig_workFinished();  // 发出完成信号
}
