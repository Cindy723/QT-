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
#include <QTextCodec>
#include <QScrollBar>
#include "drag.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_totalFastContrl(100)
{
    ui->setupUi(this);
    m_SocketClient.setMainInstan(this);
    m_SerialCom.setMainInstan(this);
    m_setWidget = new Setting(&m_SerialCom);
    setAcceptDrops(true);  // 接受拖放操作

    setWindowFlags(Qt::FramelessWindowHint);    // 禁用标题栏
    setAttribute(Qt::WA_TranslucentBackground); //设置窗口背景透明
    ui->PBmini->setIcon(QIcon(":/image/mini.png"));
    ui->PBmini->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    ui->PBSet->setIcon(QIcon(":/image/Set.png"));
    ui->PBSet->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    ui->PBClose->setIcon(QIcon(":/image/Close.png"));
    ui->PBClose->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    // 创建系统托盘图标
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/image/icon.ico"));
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
    ui->PBmini->setIcon(QIcon(":/image/mini2.png"));
    ui->PBmini->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    ui->PBmini->setStyleSheet("QPushButton { background-color: white; color: black; }");

    ui->PBSet->setIcon(QIcon(":/image/Set2.png"));
    ui->PBSet->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    ui->PBSet->setStyleSheet("QPushButton { background-color: white; color: black; }");

    ui->PBClose->setIcon(QIcon(":/image/Close2.png"));
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
        if(worker != nullptr)
        {
         worker->exit = 1;
        }
        if(m_SerialCom.m_port != "")
        {
            m_SerialCom.closeSerialPort();
            updateOperationResult(ui->comboBox->currentText() + " 关闭成功");
        }else updateOperationResult(ui->comboBox->currentText() + " 还未打开");

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
        m_setWidget->show();
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
        checkMethodAndSendFun(byteArray);
    });

    // 连接按钮
    connect(ui->PB_Connect, &QPushButton::clicked, this, [&](){
        updateOperationResult("连接到 "+ ui->lineEdit_ip->text());
        m_SocketClient.connectToHost(ui->lineEdit_ip->text(), ui->lineEdit_port->text().toInt());
    });

    //动态添加上更多的快捷指令
    for (int i = 0; i < m_totalFastContrl; ++i) {
        QLineEdit *newLineEdit = new QLineEdit(this);   // 创建一个新的 QLineEdit 对象
        //newLineEdit->setPlaceholderText(QString("lineEdit_s%1").arg(i + 0));
        newLineEdit->setObjectName(QString("lineEdit_s%1").arg(i + 0));
        ui->verticalLayout_7->addWidget(newLineEdit);
        qDebug() << "newObj" << newLineEdit->objectName() << "-";
    }
    for (int i = 0; i < m_totalFastContrl; ++i) {
        QPushButton *newButton = new QPushButton(this);  // 创建一个新的 QPushButton 对象
        newButton->setText(QString("发送"));
        newButton->setObjectName(QString("PB_send_%1").arg(i + 0));
        newButton->setFixedHeight(22);

        // 可以为按钮绑定一个信号槽，例如点击按钮后执行某些操作
        connect(newButton, &QPushButton::clicked, this, [i]() {
            qDebug() << "Button PB_send_" << (i + 0) << " clicked!";
        });

        ui->verticalLayout_8->addWidget(newButton);
        qDebug() << "newObj" << newButton->objectName() << "-";
    }
    for (int i = 0; i < m_totalFastContrl; ++i) {
        QLineEdit *newLineEdit = new QLineEdit(this);  // 创建一个新的 QLineEdit 对象
        //newLineEdit->setPlaceholderText(QString("lineEdit_tips_%1").arg(i + 0));
        newLineEdit->setObjectName(QString("lineEdit_tips_%1").arg(i + 0));

        // 设置其他属性，如大小、样式等（可选）
        //newLineEdit->setFixedSize(200, 30);  // 设置固定大小
        //newLineEdit->setStyleSheet("background-color: lightyellow;");
        ui->verticalLayout_9->addWidget(newLineEdit);
        qDebug() << "newObj" << newLineEdit->objectName() << "-";
    }

    // 连接快捷指令发送按钮
    for (int i = 0; i < m_totalFastContrl; ++i) {
        QPushButton *button = findChild<QPushButton *>(QString("PB_send_%1").arg(i));
        m_vPbSend.push_back(button);
        QLineEdit *lineEdit = findChild<QLineEdit *>(QString("lineEdit_s%1").arg(i));
        m_linedit.push_back(lineEdit);

        if (button && lineEdit) {
            connect(button, &QPushButton::clicked, this, [this, lineEdit]() {
                QByteArray byteArray = lineEdit->text().toUtf8();
                checkMethodAndSendFun(byteArray);
                //ui->textEdit_send->append(byteArray);
                ui->textEdit_send->setText(byteArray);
            });
        }
    }

    // 添加排序按钮
    for (int i = 0; i < m_totalFastContrl; ++i) {
        DraggableButton* button = new DraggableButton(QString("按钮 %1").arg(i), this);
        m_vPbdrp.push_back(button);
        button->setFixedSize(55, 22);
        ui->verticalLayout->addWidget(button);
        connect(button, &DraggableButton::sig_drag, this, &MainWindow::slot_drag);
    }


    // 消息自动滚动
    ui->checkBox_auto->setCheckState(Qt::Checked);

    // 连接串口数据
    ConnectRecev();

    // 模拟校准数据输入
    setupConnections();

    // 读取配置文件
    loadSettings();
}

MainWindow::~MainWindow()
{
    saveSettings();
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
            setHistoryTextInfo("MCU-> ", Data);

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
        connect(worker, &Worker::sig_updateUI, this, &MainWindow::setHistoryTextInfo);
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

void MainWindow::setHistoryTextInfo(QString head, QString info)
{
    if(ui)
    {
        QString timestamp = QDateTime::currentDateTime().toString("[HH:mm:ss.zzz] ");
        if(ui->checkBox_auto->checkState() == Qt::Checked){ // 自动滚动
            ui->textEdit_rec->append(timestamp + head + info);
            ui->textEdit_rec->moveCursor(QTextCursor::End);
        }
        else {
            // 保存当前的光标位置和滚动条位置
            QTextCursor cursor = ui->textEdit_rec->textCursor();
            int scrollPosition = ui->textEdit_rec->verticalScrollBar()->value();  // 获取当前滚动条位置
            ui->textEdit_rec->append(timestamp + head + info);
            // 恢复光标和滚动条的位置
            ui->textEdit_rec->setTextCursor(cursor);
            ui->textEdit_rec->verticalScrollBar()->setValue(scrollPosition);  // 还原滚动条位置

        }
    }
}

void  MainWindow::checkMethodAndSendFun(QByteArray byteArray)
{
    int method = 0;
    if(m_SerialCom.m_port != "")
    {
        method = 1;
    }

    if(m_SocketClient.m_conncetFlag != 0)
    {
        method = 2;
    }

    if(method == 0)
    {
        updateOperationResult("COM和Socket均未连接!");
    }

    if(method == 1)
    {
        m_SerialCom.sendData(byteArray);
        setHistoryTextInfo("MCU<- ", byteArray);
    }
    else if(method == 2)
    {
        m_SocketClient.sendData(byteArray);
        setHistoryTextInfo("MCU<- ", byteArray);
    }
};

// 注册表方案
// void MainWindow::loadSettings() {
//     QSettings settings("cdcdcdcdcd", "GeneralTestApp");

//     // 加载lineEdit_s1到lineEdit_s11
//     for (int i = 1; i <= 16; ++i) {
//         findChild<QLineEdit *>(QString("lineEdit_s%1").arg(i))->setText(settings.value(QString("lineEdit_s%1").arg(i), "").toString());
//     }

//     // 加载lineEdit_tips_1到lineEdit_tips_11
//     for (int i = 1; i <= 16; ++i) {
//         findChild<QLineEdit *>(QString("lineEdit_tips_%1").arg(i))->setText(settings.value(QString("lineEdit_tips_%1").arg(i), "").toString());
//     }

//     ui->lineEdit_ip->setText(settings.value("lineEdit_ip", "").toString());
//     ui->lineEdit_port->setText(settings.value("lineEdit_port", "").toString());
// }

// void MainWindow::saveSettings() {
//     QSettings settings("cdcdcdcdcd", "GeneralTestApp");

//     // 保存lineEdit_s1到lineEdit_s11
//     for (int i = 1; i <= 16; ++i) {
//         settings.setValue(QString("lineEdit_s%1").arg(i), findChild<QLineEdit *>(QString("lineEdit_s%1").arg(i))->text());
//     }

//     // 保存lineEdit_tips_1到lineEdit_tips_11
//     for (int i = 1; i <= 16; ++i) {
//         settings.setValue(QString("lineEdit_tips_%1").arg(i), findChild<QLineEdit *>(QString("lineEdit_tips_%1").arg(i))->text());
//     }

//     settings.setValue("lineEdit_ip", ui->lineEdit_ip->text());
//     settings.setValue("lineEdit_port", ui->lineEdit_port->text());
// }


void MainWindow::loadSettings() {
    // 获取可执行文件所在目录
    QString filePath = QCoreApplication::applicationDirPath() + "/settings.ini";
    QSettings settings(filePath, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("utf-8"));

    ui->lineEdit_ip->setText(settings.value("lineEdit_ip", "").toString());
    ui->lineEdit_port->setText(settings.value("lineEdit_port", "").toString());

    for (int i = 0; i < m_totalFastContrl; ++i) {
        findChild<QLineEdit *>(QString("lineEdit_s%1").arg(i))->setText(settings.value(QString("lineEdit_s%1").arg(i), "").toString());
        findChild<QLineEdit *>(QString("lineEdit_tips_%1").arg(i))->setText(settings.value(QString("lineEdit_tips_%1").arg(i), "").toString());
    }

}

void MainWindow::saveSettings() {
    // 获取可执行文件所在目录
    QString filePath = QCoreApplication::applicationDirPath() + "/settings.ini";
    QSettings settings(filePath, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("utf-8"));

    settings.setValue("lineEdit_ip", ui->lineEdit_ip->text());
    settings.setValue("lineEdit_port", ui->lineEdit_port->text());

    for (int i = 0; i < m_totalFastContrl; ++i) {
        settings.setValue(QString("lineEdit_s%1").arg(i), findChild<QLineEdit *>(QString("lineEdit_s%1").arg(i))->text());
        settings.setValue(QString("lineEdit_tips_%1").arg(i), findChild<QLineEdit *>(QString("lineEdit_tips_%1").arg(i))->text());
    }
}
