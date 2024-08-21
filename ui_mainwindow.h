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
        MainWindow->resize(675, 436);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(260, 10, 171, 31));
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
        comboBox->setGeometry(QRect(80, 58, 101, 28));
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(20, 60, 41, 31));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);
        PBmini = new QPushButton(centralwidget);
        PBmini->setObjectName(QString::fromUtf8("PBmini"));
        PBmini->setGeometry(QRect(560, 10, 31, 24));
        PBSet = new QPushButton(centralwidget);
        PBSet->setObjectName(QString::fromUtf8("PBSet"));
        PBSet->setGeometry(QRect(590, 10, 31, 24));
        PBClose = new QPushButton(centralwidget);
        PBClose->setObjectName(QString::fromUtf8("PBClose"));
        PBClose->setGeometry(QRect(620, 10, 31, 24));
        PB_OpenPort = new QPushButton(centralwidget);
        PB_OpenPort->setObjectName(QString::fromUtf8("PB_OpenPort"));
        PB_OpenPort->setGeometry(QRect(190, 58, 81, 30));
        PB_ClosePort = new QPushButton(centralwidget);
        PB_ClosePort->setObjectName(QString::fromUtf8("PB_ClosePort"));
        PB_ClosePort->setGeometry(QRect(280, 58, 91, 30));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 675, 21));
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
        label_11->setText(QCoreApplication::translate("MainWindow", "\345\212\237\347\216\207\350\256\241\346\265\213\350\257\225\345\267\245\345\205\267", nullptr));
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
