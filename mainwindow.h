#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QRegion>
#include <QPainter>
#include <QSystemTrayIcon>
#include "SerialCommunication.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QThread>
#include <qDebug>
#include "MySocketClient.h"
#include "Worker.h"
#include "setting.h"

#include "drag.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QPushButton>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define APPVERSION " Version 0.2 "

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 串口通信对象
    SerialCommunication m_SerialCom;
    MySocketClient m_SocketClient;
    void setupConnections();
    void updateOperationResult(QString content);

    // 重写关闭事件处理函数
    void closeEvent(QCloseEvent *event) override;
    void ConnectRecev();

    void setHistoryTextInfo(QString head, QString info);

    /* 界面拖动与圆角实现 */
protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            // 保存当前鼠标位置和窗口位置的差值
            dragStartPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }
    void mouseMoveEvent(QMouseEvent *event) override {
        if (event->buttons() & Qt::LeftButton) {
            // 移动窗口到新位置
            move(event->globalPos() - dragStartPosition);
            event->accept();
        }

    }
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);

        // 设置抗锯齿
        painter.setRenderHint(QPainter::Antialiasing);

        // 背景颜色
        QColor fillColor("#f9f9f9");
        painter.setBrush(fillColor);
        painter.setPen(Qt::transparent);

        // 绘制圆角矩形
        QRect rect = this->rect();
        rect.setWidth(rect.width() - 1);
        rect.setHeight(rect.height() - 1);
        painter.drawRoundedRect(rect, 15, 15);

        // 绘制边界线
        QColor borderColor("#E94560"); // 边界线颜色
        painter.setPen(QPen(borderColor, 1)); // 设置边界线颜色和宽度
        painter.drawRoundedRect(rect, 15, 15);

        // 添加标题横线
        QColor penColor("#E94560");
        painter.setPen(QPen(penColor, 1));
        painter.drawLine(0, 45, width()-2, 43);

        QWidget::paintEvent(event);
    }
    // 排序拖动事件
    void dragEnterEvent(QDragEnterEvent *event) override {
        qDebug() << "->main dragEnterEvent";
        if (event->mimeData()->hasText()) { // 只接受带有文本的拖动操作
            event->acceptProposedAction();
        }
    }
    void dragMoveEvent(QDragMoveEvent *event) override {
        qDebug() << "main dragMove";
        event->accept();

    }

    void slot_drag(QDropEvent *event) {
        qDebug() << "main dropEvent1";
        if (event->mimeData()->hasFormat("application/x-button-pointer"))
        {
            qDebug() << "main dropEvent2";
            // 获取按钮指针
            quintptr ptrValue = event->mimeData()->data("application/x-button-pointer").toULongLong();
            DraggableButton *button = reinterpret_cast<DraggableButton *>(ptrValue);

            if (!button) return;

            // 从旧位置移除按钮
            ui->verticalLayout->removeWidget(button);

            QWidget *widgetUnderMouse = childAt(event->pos());
            if (!widgetUnderMouse) {
                return; // 鼠标未指向任何子控件
            }

            quint16 insertIndex = 0;
            // 遍历布局中的所有子控件，找到对应的索引
            for (int i = 0; i < ui->verticalLayout->count(); ++i) {
                QWidget *itemWidget = ui->verticalLayout->itemAt(i)->widget();
                if (itemWidget == widgetUnderMouse) {
                    insertIndex = i;
                }
            }

            // 插入到目标位置
            qDebug() << "main insertIndex " << insertIndex;
            ui->verticalLayout->insertWidget(insertIndex, button);
            button->show();
            event->acceptProposedAction();
        }
    }

private:
    QRegion createRoundedMask(const QSize &size, int radius) {
        QRegion maskRegion;
        QRect outerRect(QPoint(0, 0), size);
        maskRegion += outerRect;

        // 创建一个椭圆形状，作为窗口的圆角
        QRect innerRect(QPoint(radius, radius), size - QSize(radius * 2, radius * 2));
        maskRegion -= innerRect;
        return maskRegion;
    }

    QPoint dragStartPosition;

    // 托盘
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QAction *restoreAction;
    QAction *quitAction;

    // 恢复窗口
    void restoreWindow();
    // 处理托盘图标点击事件
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
private:
    Ui::MainWindow *ui = nullptr;
    QStringList m_Portlist;
    QString m_CurretProt;
    Setting *m_setWidget;
    int m_totalFastContrl;
    QLabel *m_floatingLabel = nullptr;
    DraggableButton *m_draggedButton = nullptr;
    int m_insertIndex = -1;
    QVector<QPushButton *>  m_vPbSend;
    QVector<DraggableButton *>  m_vPbdrp;
    QVector<QLineEdit *>  m_linedit;

    // 串口循环发送线程
    Worker *worker = nullptr;
    QThread *thread = nullptr;

    QStatusBar *statusBar = nullptr;
    QLabel *Lable_currentOperation = nullptr; // Label for current operation
    QLabel *Lable_OperationrResult = nullptr; // Label for operation result
    QLabel *Lable_softwareVersion = nullptr; // Label for software version
    void checkMethodAndSendFun(QByteArray byteArray);
    void loadSettings();
    void saveSettings();
};


#endif
