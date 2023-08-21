/***************************************************************
 * Name:        MenuItem.h
 * Author:      WenYi
 * Created:     2023-08-04 11:08
 ***************************************************************/

#include "MenuItem.h"
#include "ui_MenuItem.h"

#include <QDebug>
#include <QPainter>
#include <QBitmap>
#include <QMenu>
#include <QPoint>

MenuItem::MenuItem(QWidget *parent) :
    QPushButton(parent),
    ui(new Ui::MenuItem)
{
    ui->setupUi(this);

    m_id = 0;
    m_isActive = false;
    m_isHover = false;
    m_imageWidth = 30;

    m_pixmapNormal = QPixmap(":/Images/nothing2.png");
    m_pixmapHover = QPixmap(":/Images/nothing_hover2.png");
    m_pixmapActivate = QPixmap(":/Images/nothing_activate2.png");

    init();
}

MenuItem::MenuItem(qint8 id, QWidget *parent)
{
    this->MenuItem::MenuItem(parent);
    m_id = id;
}

MenuItem::~MenuItem()
{
    delete ui;
}

void MenuItem::init()
{
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover, true);
    setMinimumSize(60, 45);

    setToolTip(QStringLiteral("你干嘛，唉哟~！"));
}

void MenuItem::updatePixmap(const QPixmap &pixmap1,
                            const QPixmap &pixmap2,
                            const QPixmap &pixmap3)
{
    m_pixmapNormal = pixmap1;
    m_pixmapHover = pixmap2;
    m_pixmapActivate = pixmap3;
    update();
}

void MenuItem::deActivate(const qint8 &id)
{
    if(m_id != id && m_isActive)
    {
        m_isActive = false;
        update();
    }
}

void MenuItem::activate()
{
    m_isActive = true;
    emit signalActivate(m_id, this->pos());
    update();
}

void MenuItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    if(!m_pixmapNormal.isNull() && !m_pixmapHover.isNull() && !m_pixmapActivate.isNull())
    {
        QPixmap pixmap = m_pixmapNormal.scaled(QSize(m_imageWidth, m_imageWidth),
                                               Qt::KeepAspectRatio,
                                               Qt::SmoothTransformation);

        if(m_isActive)
        {
            // 弃用 setMask不抗锯齿
//            QPixmap pxr(pixmap.size());
//            pxr.fill(QColor(86, 90, 151));
//            pxr.setMask(pixmap.createMaskFromColor(Qt::transparent));
//            pixmap = pxr;

            pixmap = m_pixmapActivate.scaled(QSize(m_imageWidth, m_imageWidth),
                                             Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation);

//            // 画矩形
//            QPen pen;
//            pen.setWidth(1);
//            pen.setColor(QColor(86, 90, 151));
//            pen.setStyle(Qt::SolidLine);

//            QBrush brush;
//            brush.setColor(QColor(86, 90, 151));
//            brush.setStyle(Qt::SolidPattern);
//            painter.setPen(pen);
//            painter.setBrush(brush);

//            painter.drawRoundRect(1, 3, 3, 38, 5, 5);
            //ui->label->setVisible(true);
        }
        else if(m_isHover)
        {
            pixmap = m_pixmapHover.scaled(QSize(m_imageWidth, m_imageWidth),
                                          Qt::KeepAspectRatio,
                                          Qt::SmoothTransformation);
        }
//        else
//            ui->label->setVisible(false);

        int x = (this->width() - pixmap.width()) / 2;
        int y = (this->height() - pixmap.height()) / 2;
        painter.drawPixmap(x, y, pixmap);
    }
    //QPushButton::paintEvent(event);
    QWidget::paintEvent(event);
}

void MenuItem::mousePressEvent(QMouseEvent *event)
{
    activate();

    if(event->button() == Qt::LeftButton)
    {
        QMenu *pMenu = this->menu();
        if(pMenu)
        {
            //        QPoint pos;
            //        pos.setX(mapToGlobal(this->geometry().topRight()).x());
            //        pos.setY(QCursor::pos().y());
            //        qDebug() << __FUNCTION__ << __LINE__ << this->geometry().topRight();
            //        qDebug() << __FUNCTION__ << __LINE__ << mapToGlobal(this->geometry().topRight());
            //        qDebug() << __FUNCTION__ << __LINE__ << QCursor::pos();

            pMenu->exec(QCursor::pos());
        }
    }
    //QPushButton::mousePressEvent(event);
}

void MenuItem::leaveEvent(QEvent *event)
{
    m_isHover = false;
    update();
    //QWidget::event(event);
}

bool MenuItem::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::HoverEnter:
        hoverEnterEvent(static_cast<QHoverEvent *>(event));
        return true;
        break;
    case QEvent::HoverLeave:
        hoverLeaveEvent(static_cast<QHoverEvent *>(event));
        return true;
        break;
    case QEvent::HoverMove:
        break;
    }

    return QPushButton::event(event);
}

void MenuItem::hoverEnterEvent(QHoverEvent *event)
{
    //qDebug() << __FUNCTION__ << "Item HoverEnterEvent";
    m_isHover = true;
    update();
}

void MenuItem::hoverLeaveEvent(QHoverEvent *event)
{
    //qDebug() << __FUNCTION__ << "Item HoverEnterEvent";
    m_isHover = false;
    update();
}

