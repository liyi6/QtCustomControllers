﻿#include "QtCustomToastWidget.h"

QtCustomToastWidget* QtCustomToastWidget::m_instance = nullptr;

QtCustomToastWidget::QtCustomToastWidget(QWidget *parent)
    : QWidget(parent),
      m_hideAni(nullptr),
      m_holdTime(DEF_HOLD_TIME),
      m_fadeTime(DEF_FADE_TIME),
      m_fontColor(QColor(255, 255, 255)),
      m_backColor(QColor(0, 0, 0))
{
    updateUi();
}

QtCustomToastWidget *QtCustomToastWidget::instance()
{
    if (!m_instance) {
        m_instance = new QtCustomToastWidget;
    }
    return m_instance;
}

void QtCustomToastWidget::destroyInstance()
{
    if (m_instance) {
        delete m_instance;
        m_instance = nullptr;
    }
}

void QtCustomToastWidget::setBackColor(QColor &color)
{
    m_backColor = color;
}

void QtCustomToastWidget::setFontColor(QColor &color)
{
    m_fontColor = color;
}

void QtCustomToastWidget::setHoldTime(int msecs)
{
    m_holdTime = msecs;
}

void QtCustomToastWidget::setFadeTime(int msecs)
{
    m_fadeTime = msecs;
    m_hideAni->setDuration(m_fadeTime);
}


void QtCustomToastWidget::updateUi()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnTopHint);
    setWindowOpacity(0.8);
    setFont(QFont(QStringLiteral("微软雅黑"), 12));

    m_hideAni = new QPropertyAnimation(this, "windowOpacity");
    m_hideAni->setDuration(m_fadeTime);
    m_hideAni->setStartValue(0.8);
    m_hideAni->setEndValue(0);
    connect(m_hideAni, SIGNAL(finished()), this, SLOT(hide()));

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onStartToHide()));
}

void QtCustomToastWidget::toast(QString &msg, QWidget *wdg)
{
    m_toast = msg;

    if (QAbstractAnimation::Stopped != m_hideAni->state()) {
        m_hideAni->stop();
    }

    if (m_timer.isActive()) {
        m_timer.stop();
    }
    m_timer.start(m_holdTime);

    setWindowOpacity(0.8);

    if (wdg) {

        show();
    }

}


void QtCustomToastWidget::paintEvent(QPaintEvent *)
{
    // 计算字体大小以及窗体大小
    if (m_toast.isEmpty()) {
        setFixedSize(145, 45);
    } else {
        // 计算字体的大小以及根据字体大小设置窗体大小
        int margin = 13;
        QFontMetrics fontMetrics(font());
        QSize fontSize = fontMetrics.size(Qt::TextSingleLine, m_toast);
        setFixedSize(fontSize.width()+2*margin, fontSize.height()+2*margin);

        qDebug() << fontSize.width();
        qDebug() << fontSize.height();

        //绘制中心部分
        QPainter painter(this);
        int padding = 4;
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRoundedRect(padding, padding, width()-padding*2, height()-padding*2, padding, padding);
        //path.addRect(padding, padding, width()-padding*2, height()-padding*2);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.fillPath(path, QBrush(m_backColor));

        //绘制边界
        QColor color(209, 209, 209); // 初始化color的R G B通道
        int edgeAlpha = 250;         // 边界最内圈的Alpha通道值
        for(int i=0; i<padding; i++)
        {
            QPainterPath path;
            path.setFillRule(Qt::WindingFill);
            path.addRoundedRect(padding-i, padding-i, this->width()-(padding-i)*2, this->height()-(padding-i)*2, padding, padding);
            int alpha = edgeAlpha - qSqrt(i)*35;
            if(alpha < 0){
                alpha = 1;
            }else if(alpha > 256){
                alpha = 255;
            }
            color.setAlpha(alpha);
            painter.setPen(color);
            painter.drawPath(path);
        }

        //绘制字体
        QPen pen;
        pen.setColor(m_fontColor);
        painter.setPen(pen);
        painter.setFont(font());
        painter.drawText(margin, margin, fontSize.width(), fontSize.height(), Qt::AlignJustify, m_toast);
        painter.end();
    }
}

void QtCustomToastWidget::onStartToHide()
{
    m_timer.stop();
    m_hideAni->start();
}


