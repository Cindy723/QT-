#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidget>
#include <QMessageBox>
#include <QLineEdit>
#include <qDebug>
#include <QProcess>
#include <QThread>
#include <QRandomGenerator>
#include <QCloseEvent>
#include <QSettings>

#define APPVERSION " Version 0.1 "

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);  // 禁用标题栏
    setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    ui->PBmini->setIcon(QIcon(":/mini.png"));
    ui->PBmini->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    ui->PBSet->setIcon(QIcon(":/Set.png"));
    ui->PBSet->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    ui->PBClose->setIcon(QIcon(":/Close.png"));
    ui->PBClose->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    // 创建系统托盘图标
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/icon.ico"));
    trayIcon->setVisible(true);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::trayIconActivated);
    trayIconMenu = new QMenu(this);
    restoreAction = new QAction("Restore", this);
    quitAction = new QAction("Quit", this);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addAction(quitAction);
    connect(restoreAction, &QAction::triggered, this, &MainWindow::restoreWindow);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    trayIcon->setContextMenu(trayIconMenu);

    // 设置按钮
    ui->PBmini->setIcon(QIcon(":/mini2.png"));
    ui->PBmini->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    ui->PBmini->setStyleSheet("QPushButton { background-color: white; color: black; }");

    ui->PBSet->setIcon(QIcon(":/Set2.png"));
    ui->PBSet->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    ui->PBSet->setStyleSheet("QPushButton { background-color: white; color: black; }");

    ui->PBClose->setIcon(QIcon(":/Close2.png"));
    ui->PBClose->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    ui->PBClose->setStyleSheet("QPushButton { background-color: white; color: black; }");

    ui->PB_J1ON->setIcon(QIcon(":/UNLOCK.png"));
    //ui->PB_J1ON->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    ui->PB_J2ON->setIcon(QIcon(":/UNLOCK.png"));
    //ui->PB_J2ON->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    ui->PB_J3ON->setIcon(QIcon(":/UNLOCK.png"));
    //ui->PB_J3ON->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    ui->PB_J4ON->setIcon(QIcon(":/UNLOCK.png"));
    //ui->PB_J4ON->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    ui->PB_J1OFF->setIcon(QIcon(":/LOCK.png"));
    //ui->PB_J1OFF->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    ui->PB_J2OFF->setIcon(QIcon(":/LOCK.png"));
    //ui->PB_J2OFF->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    ui->PB_J3OFF->setIcon(QIcon(":/LOCK.png"));
    //ui->PB_J3OFF->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    ui->PB_J4OFF->setIcon(QIcon(":/LOCK.png"));
    //ui->PB_J4OFF->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    // 状态栏信息
    statusBar = new QStatusBar(this); // Step 1: Create the QStatusBar object
    setStatusBar(statusBar);           // Step 2: Set the status bar for the main window
    Lable_softwareVersion = new QLabel(this);
    statusBar->addWidget(Lable_softwareVersion);
    Lable_OperationrResult = new QLabel(this);
    statusBar->addWidget(Lable_OperationrResult);

    Lable_softwareVersion->setText(APPVERSION);  //  Lable_softwareVersion->setText(QString(APPVERSION) +" / "+strVer);
    updateOperationResult("初始化");

    // 扫描一次端口
    m_Portlist = m_SerialCom.SearchCom();
    ui->comboBox->addItems(m_Portlist);

    // 选择了下拉框  连接 comboBox 的 activated 信号到槽函数
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::activated),
            this, [&](){
        qDebug() << "comboBox activated " ;
        m_Portlist = m_SerialCom.SearchCom();
        ui->comboBox->clear();
        ui->comboBox->addItems(m_Portlist);
    });

    // 打开端口按钮事件
    connect(ui->PB_OpenPort, &QPushButton::clicked, this, [&](){
        if(m_SerialCom.m_port != "")
        {
          updateOperationResult(ui->comboBox->currentText() + " 已经打开!");
        }
        else if(m_SerialCom.openSerialPort(ui->comboBox->currentText()))
        {
            updateOperationResult(ui->comboBox->currentText() + " 打开成功");
        }else
            updateOperationResult(ui->comboBox->currentText() + " 打开失败! 可能端口被占用或硬件错误");
    });

    // 关闭端口按钮事件
    connect(ui->PB_ClosePort, &QPushButton::clicked, this, [&](){
         m_SerialCom.closeSerialPort();
         updateOperationResult(ui->comboBox->currentText() + " 关闭成功");
    });

    // 锁操作
    connect(ui->PB_J1ON, &QPushButton::clicked, this, [&](){
        m_SerialCom.sendData(m_SerialCom.m_J1OpenArry);
        updateOperationResult(ui->comboBox->currentText() + " 发送锁1打开指令");
    });
    connect(ui->PB_J2ON, &QPushButton::clicked, this, [&](){
        m_SerialCom.sendData(m_SerialCom.m_J2OpenArry);
        updateOperationResult(ui->comboBox->currentText() + " 发送锁2打开指令");
    });
    connect(ui->PB_J3ON, &QPushButton::clicked, this, [&](){
        m_SerialCom.sendData(m_SerialCom.m_J3OpenArry);
        updateOperationResult(ui->comboBox->currentText() + " 发送锁3打开指令");
    });
    connect(ui->PB_J4ON, &QPushButton::clicked, this, [&](){
        m_SerialCom.sendData(m_SerialCom.m_J4OpenArry);
        updateOperationResult(ui->comboBox->currentText() + " 发送锁4打开指令");
    });
    connect(ui->PB_J1OFF, &QPushButton::clicked, this, [&](){
        m_SerialCom.sendData(m_SerialCom.m_J1OFFArry);
        updateOperationResult(ui->comboBox->currentText() + " 发送锁1关闭指令");
    });
    connect(ui->PB_J2OFF, &QPushButton::clicked, this, [&](){
        m_SerialCom.sendData(m_SerialCom.m_J2OFFArry);
        updateOperationResult(ui->comboBox->currentText() + " 发送锁2关闭指令");
    });
    connect(ui->PB_J3OFF, &QPushButton::clicked, this, [&](){
        m_SerialCom.sendData(m_SerialCom.m_J3OFFArry);
        updateOperationResult(ui->comboBox->currentText() + " 发送锁3关闭指令");
    });
    connect(ui->PB_J4OFF, &QPushButton::clicked, this, [&](){
        m_SerialCom.sendData(m_SerialCom.m_J4OFFArry);
        updateOperationResult(ui->comboBox->currentText() + " 发送锁4关闭指令");
    });


    // 最小化按钮事件
    connect(ui->PBmini, &QPushButton::clicked, this, [&](){
       this->hide();
    });

    // 设置按钮事件
    connect(ui->PBSet, &QPushButton::clicked, this, [&](){

    });

    // 关闭按钮事件
    connect(ui->PBClose, &QPushButton::clicked, qApp, &QApplication::quit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::restoreWindow() {
    // 恢复窗口显示
    this->show();
    this->setWindowState(Qt::WindowActive);
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            // 处理单击或双击事件，例如恢复窗口
            restoreWindow();
            break;
        default:
            break;
    }
}


// 重写关闭事件处理函数
void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "窗口关闭事件";
    QThread::msleep(200);
}

void MainWindow::ConnectRecev()
{

    // 这是第二次connect串口消息
     QObject::connect(&m_SerialCom, &SerialCommunication::dataReceived, this, [&](QByteArray &Data) {

            if (Data.at(3) != (char) 0xb0 && Data.at(3) != (char) 0xe1 && Data.at(3) != (char) 0xe2) // 过滤时间 电能 温湿度打印
            m_SerialCom.PrintQByteArray(QString("Received Size %1: ").arg(Data.size()), Data);
            int byteArrayLength = Data.size();
            unsigned char* ucharArray = new unsigned char[byteArrayLength];
            memset(ucharArray, 0, byteArrayLength);
            for (int i = 0; i < byteArrayLength; ++i) {
                ucharArray[i] = static_cast<unsigned char>(Data.at(i));
            }
            switch (ucharArray[3]) {
            case 0xFF:
               {
                // 请求板子信息
                //m_SerialCom.sendData(m_SerialCom.m_BspinfoArry);
                break;
               }
            default:
                qDebug() << "接受到未知指令 " ;
                break;
            }

            Data.clear();
            delete []ucharArray;
     });// ctodo这行崩溃过

}

void MainWindow::updateOperationResult(QString content)
{
    Lable_OperationrResult->setText(QString("操作:  ") + content);
    Lable_OperationrResult->repaint();
}
