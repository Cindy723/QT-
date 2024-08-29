/********************************************************************************
** Form generated from reading UI file 'setting.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Setting
{
public:
    QPushButton *PBclose;
    QLabel *label_38;
    QTabWidget *tabWidget;

    void setupUi(QWidget *Setting)
    {
        if (Setting->objectName().isEmpty())
            Setting->setObjectName(QString::fromUtf8("Setting"));
        Setting->resize(498, 415);
        PBclose = new QPushButton(Setting);
        PBclose->setObjectName(QString::fromUtf8("PBclose"));
        PBclose->setGeometry(QRect(450, 10, 41, 24));
        label_38 = new QLabel(Setting);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setGeometry(QRect(20, 20, 51, 21));
        QFont font;
        font.setPointSize(14);
        font.setKerning(true);
        label_38->setFont(font);
        tabWidget = new QTabWidget(Setting);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 60, 461, 331));
        tabWidget->setTabBarAutoHide(false);

        retranslateUi(Setting);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(Setting);
    } // setupUi

    void retranslateUi(QWidget *Setting)
    {
        Setting->setWindowTitle(QCoreApplication::translate("Setting", "Form", nullptr));
        PBclose->setText(QString());
        label_38->setText(QCoreApplication::translate("Setting", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Setting: public Ui_Setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
