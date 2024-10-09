#include "setting.h"
#include "qdebug.h"
#include "qmessagebox.h"
#include "ui_setting.h"
#include <QFile>
#include <QStyleFactory>
#include <QClipboard>
#include <QVBoxLayout>

// 计算累加和
quint8 calculateChecksum(const QByteArray &data) {
    quint8 sum = 0;
    for (int i = 0; i < data.size(); ++i) {
        sum += static_cast<quint8>(data.at(i)); // 将字节转换为无符号整数后相加
    }
    return sum;
}

void ShowMsgBox(QString cont)
{
    qDebug() << cont;
    QMessageBox msgBox;  // 创建警告对话框
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText(cont);
    msgBox.setWindowTitle("警告");
    msgBox.setWindowFlags(msgBox.windowFlags() | Qt::WindowStaysOnTopHint);
    msgBox.exec();
}


Setting::Setting(SerialCommunication* pSerialCom, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    // 使用 Fusion 风格
    QApplication::setStyle(QStyleFactory::create("fusion"));
    // 设置全局样式表
    QFile styleFile(":/myStyleRepte.qss");  // 样式表文件路径
    styleFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleFile.readAll());
    this->setStyleSheet(styleSheet);
    this->setWindowFlags(Qt::FramelessWindowHint);  // 禁用标题栏
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    m_pSerialCom = pSerialCom;

    addAboutInfoToTab();

    // 连接标签按钮切换事件
    QObject::connect(ui->tabWidget, &QTabWidget::currentChanged, this, [&](int index){
        if(index ==1) { // 来到网络设置
            qDebug() << "Tab2 clicked";
        }
        else if(index ==2) { // 来到附加项
            qDebug() << "Tab3 clicked";
        }
    });


    // 关闭按钮事件
    ui->PBclose->setIcon(QIcon(":/image/Close2.png"));
    ui->PBclose->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    connect(ui->PBclose, &QPushButton::clicked, this, [&](){
       ui->tabWidget->setCurrentIndex(0);
       closeWidget();
    });


}

Setting::~Setting()
{
    delete ui;
}


void Setting::addAboutInfoToTab()
{
    // 创建一个新的 QWidget 作为标签页内容
    QWidget *aboutTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(aboutTab);

    // 添加软件信息文本
    QLabel *aboutLabel = new QLabel(tr(
                                    "<h2>测试工具</h2>"
                                    "<p>软件描述: 本软件主要用于Uart和Socket通信</p>"
                                    "<p>开发者: 北京德辰科技股份有限公司 https://www.decentest.com/ </p>"
<<<<<<< HEAD
                                    "<p>部门: 监测系统部 任春东</p>"
=======
                                    "<p>部门: 监测系统部 </p>"
>>>>>>> 29b14e86ad0e60f0a95aa1e23589d5665c5307e2
                                    "<p>版权所有 © 2024</p>"
                                    ), aboutTab); // 指定 aboutTab 作为父对象
    aboutLabel->setAlignment(Qt::AlignCenter);
    aboutLabel->setWordWrap(true);  // 允许文本自动换行
    layout->addWidget(aboutLabel);  // 将文本标签添加到布局中

    // 添加外部图片
    QLabel *imageLabel = new QLabel(aboutTab); // 明确指定 aboutTab 作为父对象
    QPixmap pixmap(":/image/logo.png"); // 使用资源文件中的图片路径

    // 检查图片是否成功加载
    if(pixmap.isNull()) {
    qDebug() << "Failed to load image!";
    } else {
    imageLabel->setPixmap(pixmap);
    }

    imageLabel->setAlignment(Qt::AlignCenter); // 设置图片为居中对齐
    layout->addWidget(imageLabel);  // 将图片标签添加到布局中

    // 设置标签页内容
    ui->tabWidget->insertTab(0, aboutTab, tr("关于"));
}
