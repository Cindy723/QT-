/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_11;
    QComboBox *comboBox;
    QLabel *label_14;
    QPushButton *PBmini;
    QPushButton *PBSet;
    QPushButton *PBClose;
    QPushButton *PB_OpenPort;
    QPushButton *PB_ClosePort;
    QTextEdit *textEdit_rec;
    QPushButton *PB_clearInfo;
    QPushButton *PB_read;
    QPushButton *PB_testIn;
    QPushButton *PB_send;
    QLabel *label;
    QTextEdit *textEdit_send;
    QLabel *label_2;
    QLineEdit *lineEdit_ip;
    QLabel *label_15;
    QLineEdit *lineEdit_port;
    QLabel *label_16;
    QPushButton *PB_Connect;
    QPushButton *PB_stopSend;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(784, 547);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(350, 10, 101, 31));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Parchment"));
        font.setPointSize(17);
        font.setKerning(true);
        label_11->setFont(font);
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(80, 58, 101, 23));
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(30, 55, 41, 31));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);
        PBmini = new QPushButton(centralwidget);
        PBmini->setObjectName(QString::fromUtf8("PBmini"));
        PBmini->setGeometry(QRect(670, 10, 31, 24));
        PBSet = new QPushButton(centralwidget);
        PBSet->setObjectName(QString::fromUtf8("PBSet"));
        PBSet->setGeometry(QRect(700, 10, 31, 24));
        PBClose = new QPushButton(centralwidget);
        PBClose->setObjectName(QString::fromUtf8("PBClose"));
        PBClose->setGeometry(QRect(730, 10, 31, 24));
        PB_OpenPort = new QPushButton(centralwidget);
        PB_OpenPort->setObjectName(QString::fromUtf8("PB_OpenPort"));
        PB_OpenPort->setGeometry(QRect(210, 57, 61, 25));
        PB_ClosePort = new QPushButton(centralwidget);
        PB_ClosePort->setObjectName(QString::fromUtf8("PB_ClosePort"));
        PB_ClosePort->setGeometry(QRect(290, 57, 71, 25));
        textEdit_rec = new QTextEdit(centralwidget);
        textEdit_rec->setObjectName(QString::fromUtf8("textEdit_rec"));
        textEdit_rec->setGeometry(QRect(30, 120, 341, 331));
        PB_clearInfo = new QPushButton(centralwidget);
        PB_clearInfo->setObjectName(QString::fromUtf8("PB_clearInfo"));
        PB_clearInfo->setGeometry(QRect(330, 470, 41, 21));
        PB_read = new QPushButton(centralwidget);
        PB_read->setObjectName(QString::fromUtf8("PB_read"));
        PB_read->setGeometry(QRect(510, 465, 81, 30));
        PB_testIn = new QPushButton(centralwidget);
        PB_testIn->setObjectName(QString::fromUtf8("PB_testIn"));
        PB_testIn->setGeometry(QRect(410, 465, 81, 30));
        PB_send = new QPushButton(centralwidget);
        PB_send->setObjectName(QString::fromUtf8("PB_send"));
        PB_send->setGeometry(QRect(710, 470, 41, 21));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 100, 53, 15));
        textEdit_send = new QTextEdit(centralwidget);
        textEdit_send->setObjectName(QString::fromUtf8("textEdit_send"));
        textEdit_send->setGeometry(QRect(410, 120, 341, 331));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(410, 100, 53, 15));
        lineEdit_ip = new QLineEdit(centralwidget);
        lineEdit_ip->setObjectName(QString::fromUtf8("lineEdit_ip"));
        lineEdit_ip->setGeometry(QRect(430, 60, 151, 23));
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(410, 55, 21, 31));
        sizePolicy.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy);
        lineEdit_port = new QLineEdit(centralwidget);
        lineEdit_port->setObjectName(QString::fromUtf8("lineEdit_port"));
        lineEdit_port->setGeometry(QRect(632, 60, 71, 23));
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(600, 55, 31, 31));
        sizePolicy.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy);
        PB_Connect = new QPushButton(centralwidget);
        PB_Connect->setObjectName(QString::fromUtf8("PB_Connect"));
        PB_Connect->setGeometry(QRect(710, 58, 41, 25));
        PB_stopSend = new QPushButton(centralwidget);
        PB_stopSend->setObjectName(QString::fromUtf8("PB_stopSend"));
        PB_stopSend->setGeometry(QRect(610, 465, 81, 30));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 784, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\346\265\213\350\257\225\345\267\245\345\205\267", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "COM\357\274\232", nullptr));
        PBmini->setText(QString());
        PBSet->setText(QString());
        PBClose->setText(QString());
        PB_OpenPort->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\347\253\257\345\217\243", nullptr));
        PB_ClosePort->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\347\253\257\345\217\243", nullptr));
        PB_clearInfo->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        PB_read->setText(QCoreApplication::translate("MainWindow", "\346\240\241\345\207\206\346\225\260\346\215\256\350\257\273\345\207\272", nullptr));
        PB_testIn->setText(QCoreApplication::translate("MainWindow", "\346\240\241\345\207\206\346\225\260\346\215\256\350\276\223\345\205\245", nullptr));
        PB_send->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\350\256\260\345\275\225", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\345\214\272", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "IP:", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        PB_Connect->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        PB_stopSend->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\344\274\240\350\276\223", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
