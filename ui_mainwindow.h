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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_11;
    QLabel *label_13;
    QLabel *label_18;
    QPushButton *PB_J2ON;
    QLabel *label_16;
    QPushButton *PB_J1OFF;
    QPushButton *PB_J3OFF;
    QLabel *label_17;
    QPushButton *PB_J4ON;
    QPushButton *PB_J1ON;
    QPushButton *PB_J2OFF;
    QLabel *label_15;
    QPushButton *PB_J4OFF;
    QPushButton *PB_J3ON;
    QComboBox *comboBox;
    QLabel *label_14;
    QPushButton *PBmini;
    QPushButton *PBSet;
    QPushButton *PBClose;
    QPushButton *PB_OpenPort;
    QPushButton *PB_ClosePort;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(420, 10, 171, 31));
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
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(630, 60, 61, 31));
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Parchment"));
        font1.setPointSize(12);
        font1.setKerning(true);
        label_13->setFont(font1);
        label_18 = new QLabel(centralwidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(879, 98, 40, 16));
        sizePolicy.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy);
        label_18->setFont(font1);
        PB_J2ON = new QPushButton(centralwidget);
        PB_J2ON->setObjectName(QString::fromUtf8("PB_J2ON"));
        PB_J2ON->setGeometry(QRect(713, 120, 45, 35));
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(713, 98, 40, 16));
        sizePolicy.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy);
        label_16->setFont(font1);
        PB_J1OFF = new QPushButton(centralwidget);
        PB_J1OFF->setObjectName(QString::fromUtf8("PB_J1OFF"));
        PB_J1OFF->setGeometry(QRect(630, 168, 45, 35));
        PB_J3OFF = new QPushButton(centralwidget);
        PB_J3OFF->setObjectName(QString::fromUtf8("PB_J3OFF"));
        PB_J3OFF->setGeometry(QRect(796, 168, 45, 35));
        label_17 = new QLabel(centralwidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(796, 98, 40, 16));
        sizePolicy.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy);
        label_17->setFont(font1);
        PB_J4ON = new QPushButton(centralwidget);
        PB_J4ON->setObjectName(QString::fromUtf8("PB_J4ON"));
        PB_J4ON->setGeometry(QRect(879, 120, 45, 35));
        PB_J1ON = new QPushButton(centralwidget);
        PB_J1ON->setObjectName(QString::fromUtf8("PB_J1ON"));
        PB_J1ON->setGeometry(QRect(630, 120, 45, 35));
        PB_J2OFF = new QPushButton(centralwidget);
        PB_J2OFF->setObjectName(QString::fromUtf8("PB_J2OFF"));
        PB_J2OFF->setGeometry(QRect(713, 168, 45, 35));
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(630, 98, 40, 16));
        sizePolicy.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy);
        label_15->setFont(font1);
        PB_J4OFF = new QPushButton(centralwidget);
        PB_J4OFF->setObjectName(QString::fromUtf8("PB_J4OFF"));
        PB_J4OFF->setGeometry(QRect(879, 168, 45, 35));
        PB_J3ON = new QPushButton(centralwidget);
        PB_J3ON->setObjectName(QString::fromUtf8("PB_J3ON"));
        PB_J3ON->setGeometry(QRect(796, 120, 45, 35));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(80, 58, 101, 28));
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(20, 60, 41, 31));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);
        PBmini = new QPushButton(centralwidget);
        PBmini->setObjectName(QString::fromUtf8("PBmini"));
        PBmini->setGeometry(QRect(920, 10, 31, 24));
        PBSet = new QPushButton(centralwidget);
        PBSet->setObjectName(QString::fromUtf8("PBSet"));
        PBSet->setGeometry(QRect(950, 10, 31, 24));
        PBClose = new QPushButton(centralwidget);
        PBClose->setObjectName(QString::fromUtf8("PBClose"));
        PBClose->setGeometry(QRect(980, 10, 31, 24));
        PB_OpenPort = new QPushButton(centralwidget);
        PB_OpenPort->setObjectName(QString::fromUtf8("PB_OpenPort"));
        PB_OpenPort->setGeometry(QRect(190, 58, 81, 30));
        PB_ClosePort = new QPushButton(centralwidget);
        PB_ClosePort->setObjectName(QString::fromUtf8("PB_ClosePort"));
        PB_ClosePort->setGeometry(QRect(280, 58, 91, 30));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 22));
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
        label_11->setText(QCoreApplication::translate("MainWindow", "\346\227\213\350\275\254\346\237\234\346\265\213\350\257\225\345\267\245\345\205\267", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\351\224\201\346\265\213\350\257\225", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "\351\224\2014", nullptr));
        PB_J2ON->setText(QString());
        label_16->setText(QCoreApplication::translate("MainWindow", "\351\224\2012", nullptr));
        PB_J1OFF->setText(QString());
        PB_J3OFF->setText(QString());
        label_17->setText(QCoreApplication::translate("MainWindow", "\351\224\2013", nullptr));
        PB_J4ON->setText(QString());
        PB_J1ON->setText(QString());
        PB_J2OFF->setText(QString());
        label_15->setText(QCoreApplication::translate("MainWindow", "\351\224\2011", nullptr));
        PB_J4OFF->setText(QString());
        PB_J3ON->setText(QString());
        label_14->setText(QCoreApplication::translate("MainWindow", "COM\357\274\232", nullptr));
        PBmini->setText(QString());
        PBSet->setText(QString());
        PBClose->setText(QString());
        PB_OpenPort->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\347\253\257\345\217\243", nullptr));
        PB_ClosePort->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\347\253\257\345\217\243", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
