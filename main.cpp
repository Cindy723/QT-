#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QListWidget>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QtDebug>
//#include <QQmlApplicationEngine>
#include <QStyleFactory>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 使用 Fusion 风格
    QApplication::setStyle(QStyleFactory::create("fusion"));

    // 设置全局样式表
//    QFile styleFile(":/myStyle.qss");  // 样式表文件路径
//    styleFile.open(QFile::ReadOnly);
//    QString styleSheet = QLatin1String(styleFile.readAll());
//    a.setStyleSheet(styleSheet);
    a.setWindowIcon(QIcon(":/icon.ico"));



    MainWindow w;
    w.setMinimumSize(1024, 640);
    w.setMaximumSize(1024, 640);
    w.show();
    return a.exec();
}
