#ifndef QTCUSTOMTOASTWIDGET_H
#define QTCUSTOMTOASTWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QtMath>
#include <QPropertyAnimation>
#include <QAbstractAnimation>
#include <QDesktopWidget>
#include <QApplication>
#include "CustomShadowEffect.h"

#define DEF_HOLD_TIME    1200
#define DEF_FADE_TIME     500
#define MARGIN             13

class QtCustomToastWidget : public QWidget
{
    Q_OBJECT
public:
    static QtCustomToastWidget* instance();
    static void destroyInstance();

    void setBackColor(QColor& color);
    void setFontColor(QColor& color);
    void setHoldTime(int msecs);
    void setFadeTime(int msecs);
    void toast(QString& msg, QWidget* wdg = nullptr);

protected:
    void paintEvent(QPaintEvent*);

private slots:
    void onStartToHide();

private:
    explicit QtCustomToastWidget(QWidget *parent = 0);
    void updateUi();
    void moveToCenter(QWidget* wdg = nullptr);

private:
    static QtCustomToastWidget* m_instance;

private:
    QColor               m_fontColor;
    QColor               m_backColor;
    QString              m_toast;
    QTimer               m_timer;
    QPropertyAnimation*  m_hideAni;
    int                  m_holdTime;   // 显示时间
    int                  m_fadeTime;   // 消失动画时间
};

#endif // QTCUSTOMTOASTWIDGET_H
