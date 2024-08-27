#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidget>
#include <QMessageBox>
#include <QLineEdit>
#include <qDebug>
#include <QProcess>
#include <QRandomGenerator>
#include <QCloseEvent>
#include <QSettings>
#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_SocketClient.setMainInstan(this);
    m_SerialCom.setMainInstan(this);

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

    // 默认 IP
    // ui->lineEdit_ip->setText("192.168.0.7");
    // ui->lineEdit_port->setText("20108");
    ui->lineEdit_ip->setText("127.0.0.1");
    ui->lineEdit_port->setText("60000");


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
        // m_Portlist = m_SerialCom.SearchCom();
        // ui->comboBox->clear();
        // ui->comboBox->addItems(m_Portlist);
    });

    // 打开端口按钮
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

    // 关闭端口按钮
    connect(ui->PB_ClosePort, &QPushButton::clicked, this, [&](){
         worker->exit = 1;
         m_SerialCom.closeSerialPort();
         updateOperationResult(ui->comboBox->currentText() + " 关闭成功");
    });

    // 停止发送按钮
    connect(ui->PB_stopSend, &QPushButton::clicked, this, [&](){
        worker->exit = 1;
    });

    // 最小化按钮
    connect(ui->PBmini, &QPushButton::clicked, this, [&](){
       this->hide();
    });

    // 设置按钮
    connect(ui->PBSet, &QPushButton::clicked, this, [&](){

    });

    // 关闭按钮
    connect(ui->PBClose, &QPushButton::clicked, qApp, &QApplication::quit);

    // 清除信息
    connect(ui->PB_clearInfo, &QPushButton::clicked, this, [&](){
        ui->textEdit_rec->clear();
    });

    // 发送按钮
    connect(ui->PB_send, &QPushButton::clicked, this, [&](){
        QByteArray byteArray = ui->textEdit_send->toPlainText().toUtf8();

        int method = 0;
        if(m_SerialCom.m_port == "")
        {
            qDebug() << "端口未打开";
        }else method = 1;

        if(m_SocketClient.m_conncetFlag == 0)
        {
            qDebug() << "网诺未连接";
        }else  method = 2;

        if(method == 1)
        {
            m_SerialCom.sendData(byteArray);
        }
        else if(method == 2)
        {
            m_SocketClient.sendData(byteArray);
        }
        setTextInfo("MCU<- ", byteArray);
    });

    // 连接按钮
    connect(ui->PB_Connect, &QPushButton::clicked, this, [&](){
        updateOperationResult("连接到 "+ ui->lineEdit_ip->text());
        m_SocketClient.connectToHost(ui->lineEdit_ip->text(), ui->lineEdit_port->text().toInt());
    });

    // 连接串口数据
    ConnectRecev();

    // 模拟校准数据输入
    setupConnections();
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
            int byteArrayLength = Data.size();
            unsigned char* ucharArray = new unsigned char[byteArrayLength];
            memset(ucharArray, 0, byteArrayLength);
            for (int i = 0; i < byteArrayLength; ++i) {
                ucharArray[i] = static_cast<unsigned char>(Data.at(i));
            }
            setTextInfo("MCU-> ", Data);

            Data.clear();
            delete []ucharArray;
     });

}

void MainWindow::setupConnections()
{
    connect(ui->PB_testIn, &QPushButton::clicked, this, [=]() {
        // 此处存在内存泄漏
        thread = new QThread;
        worker  = new Worker(&m_SerialCom, &m_SocketClient);
        worker->moveToThread(thread);

        connect(thread, &QThread::started, worker, &Worker::doWork);
        connect(worker, &Worker::sig_updateUI, this, &MainWindow::setTextInfo);
        connect(worker, &Worker::sig_workFinished, thread, &QThread::quit);
        connect(worker, &Worker::sig_workFinished, worker, &Worker::deleteLater);
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        connect(worker, &Worker::sig_sockeSendData, &m_SocketClient, &MySocketClient::sendData);

        qDebug() << "thread start";
        if (thread->isRunning()) {
            qDebug() << "thread isRunning";
            thread->quit();
            thread->wait();
        }
        thread->start();
        qDebug() << "thread end";
    });
}


void MainWindow::updateOperationResult(QString content)
{
    Lable_OperationrResult->setText(QString("操作:  ") + content);
    Lable_OperationrResult->repaint();
}
