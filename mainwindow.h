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
#include <SerialCommunication.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 串口通信对象
    SerialCommunication m_SerialCom;
    void updateOperationResult(QString content);

    // 重写关闭事件处理函数
    void closeEvent(QCloseEvent *event) override;
    void ConnectRecev();
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

            // 添加标题横线
            QColor penColor("#E94560");
            painter.setPen(QPen(penColor, 1));
            painter.drawLine(0, 45, width()-2, 43);

            // 绘制边界线
            QColor borderColor("#333333"); // 边界线颜色
            painter.setPen(QPen(borderColor, 1)); // 设置边界线颜色和宽度
            painter.drawRoundedRect(rect, 15, 15);

            QWidget::paintEvent(event);
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
    Ui::MainWindow *ui;
    QStringList m_Portlist;
    QString m_CurretProt;

    QStatusBar *statusBar;
    QLabel *Lable_currentOperation; // Label for current operation
    QLabel *Lable_OperationrResult; // Label for operation result
    QLabel *Lable_softwareVersion; // Label for software version
//signals:
public slots:
};

#endif
