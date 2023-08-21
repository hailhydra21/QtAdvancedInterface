/***************************************************************
 * Name:        CircularState.cpp
 * Author:      WenYi
 * Created:     2023-08-04 11:09
 ***************************************************************/

#include "CircularState.h"
#include "ui_CircularState.h"

#include <QPainter>
#include <QDebug>
#include <QPropertyAnimation>
#include <QTimer>

CircularState::CircularState(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CircularState)
{
    ui->setupUi(this);

    m_connectState = Example1::UnconnectState;
    m_isHover = false;
    m_opacity = 1.0;

    init();
}

CircularState::CircularState(Example1::ConnectStateType type, QWidget *parent)
{
    this->CircularState::CircularState(parent);
    setConnectState(type);
}

CircularState::~CircularState()
{
    delete ui;
}

void CircularState::init()
{
    setAttribute(Qt::WA_Hover, true);

    m_pBlinkAnimation = new QPropertyAnimation(this, "opacity", this);
    m_pBlinkAnimation->setStartValue(1);
    m_pBlinkAnimation->setKeyValueAt(0.5, 0);
    m_pBlinkAnimation->setEndValue(1);
    m_pBlinkAnimation->setDuration(1500);
//    m_pBlinkAnimation->setLoopCount(-1);

    m_pBlinkAnimation2 = new QPropertyAnimation(this, "opacity", this);
    m_pBlinkAnimation2->setStartValue(1);
    m_pBlinkAnimation2->setKeyValueAt(0.5, 0);
    m_pBlinkAnimation2->setEndValue(1);
    m_pBlinkAnimation2->setDuration(1200);

    m_pBlinkAnimation3 = new QPropertyAnimation(this, "opacity", this);
    m_pBlinkAnimation3->setStartValue(1);
    m_pBlinkAnimation3->setKeyValueAt(0.3, 0);
    m_pBlinkAnimation3->setKeyValueAt(0.5, 1);
    m_pBlinkAnimation3->setKeyValueAt(0.8, 0);
    m_pBlinkAnimation3->setEndValue(1);
    m_pBlinkAnimation3->setDuration(1000);

    m_timer = new QTimer();
    m_timer2 = new QTimer();
    m_timer3 = new QTimer();
    m_timer->setInterval(500);
    m_timer2->setInterval(3000);
    m_timer3->setInterval(2000);
    createSignalConnect();
}

void CircularState::createSignalConnect()
{
    connect(m_pBlinkAnimation, &QPropertyAnimation::finished, this, [&]{
        m_timer->start();
    });

    connect(m_pBlinkAnimation2, &QPropertyAnimation::finished, this, [&]{
        m_timer2->start();
    });

    connect(m_pBlinkAnimation3, &QPropertyAnimation::finished, this, [&]{
        m_timer3->start();
    });

    connect(m_timer, &QTimer::timeout, this, [&]{
        m_pBlinkAnimation->start();
        m_timer->stop();
    });

    connect(m_timer2, &QTimer::timeout, this, [&]{
        m_pBlinkAnimation2->start();
        m_timer2->stop();
    });

    connect(m_timer3, &QTimer::timeout, this, [&]{
        m_pBlinkAnimation3->start();
        m_timer3->stop();
    });
}

void CircularState::setConnectState(Example1::ConnectStateType type)
{
    if(m_connectState == type)
        return ;
    m_connectState = type;
    if(type == Example1::ErrorState)
    {
        setOpacity(1.0);
        m_timer->stop();
        m_timer2->stop();
        m_timer3->stop();
        m_pBlinkAnimation->start();
        m_pBlinkAnimation2->stop();
        m_pBlinkAnimation3->stop();
        setToolTip(tr("NetWork Error!"));
    }
    else if(type == Example1::ConnectedState)
    {
        setOpacity(1.0);
        m_timer->stop();
        m_timer2->start();
        m_timer3->stop();
        m_pBlinkAnimation->stop();
        m_pBlinkAnimation2->stop();
        m_pBlinkAnimation3->stop();
        setToolTip(tr("NetWork Connected!"));
    }
    else if(type == Example1::UnconnectState)
    {
        setOpacity(1.0);
        m_timer->stop();
        m_timer2->stop();
        m_timer3->stop();
        m_pBlinkAnimation->stop();
        m_pBlinkAnimation2->stop();
        m_pBlinkAnimation3->stop();
        setToolTip(tr("NetWork UnconnectState!"));
    }
}

void CircularState::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int dif = 10;

    if(!m_isHover)
        dif = 14;

    int side = qMin(width(), height()) - dif;
    int startX = (width() - side) / 2;
    int startY = (height() - side) / 2;
    QRectF outRect(startX, startY, side, side);

    QColor color;

    switch (m_connectState)
    {
    case Example1::ConnectedState:
        color.setRgba(qRgba(0, 205, 102, 255));
//        setToolTip(QStringLiteral("已连接"));
        break;
    case Example1::ErrorState:
        color.setRgba(qRgba(255, 215, 0, 255));
//        setToolTip(QStringLiteral("连接异常"));
        break;
    case Example1::UnconnectState:
        color.setRgba(qRgba(255, 117, 117, 255));
//        setToolTip(QStringLiteral("未连接"));
        break;
    default:
        break;
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(color));
    painter.setOpacity(m_opacity);
    painter.drawEllipse(outRect);
}

bool CircularState::event(QEvent *e)
{
    switch(e->type())
    {
    case QEvent::HoverEnter:
        m_isHover = true;
        update();
        return true;
        break;
    case QEvent::HoverLeave:
        m_isHover = false;
        update();
        return true;
        break;
    case QEvent::HoverMove:
        break;
    }

    return QWidget::event(e);
}
