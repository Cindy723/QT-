#ifndef SETTING_H
#define SETTING_H

#include "SerialCommunication.h"
#include "qstatusbar.h"
#include <QWidget>
#include <QMouseEvent>
#include <QRegion>
#include <QPainter>
#include <QPoint>
#include <QLabel>

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(SerialCommunication *pSerialCom, QWidget *parent = nullptr);
   ~Setting();

    Ui::Setting *ui;

/*界面拖动与圆角实现*/
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
            painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
            QColor fillColor("#f9f9f9");
            painter.setBrush(fillColor);
            painter.setPen(Qt::transparent);

            // 绘制边界线
            QRect rect = this->rect();
            QColor borderColor("#E94560"); // 边界线颜色
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

private:
    SerialCommunication *m_pSerialCom;
    void addAboutInfoToTab();
private slots:
    void closeWidget() {
        close();  // 关闭当前的 QWidget
    }
};
quint8 calculateChecksum(const QByteArray &data);
#endif // SETTING_H
