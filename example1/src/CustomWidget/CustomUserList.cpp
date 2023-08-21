/***************************************************************
 * Name:        CustomUserList.cpp
 * Author:      WenYi
 * Created:     2023-08-10 16:29
 ***************************************************************/

#include "CustomUserList.h"

#include <QPixmap>
#include <QPainter>
#include <QPainterPath>

CustomUserList::CustomUserList(QWidget *parent)
    : QWidget{parent}
{
    setMinimumHeight(38);
    m_pixmapList.append(QPixmap(":/Images/tempUser/tempUser1.png"));
    m_pixmapList.append(QPixmap(":/Images/tempUser/tempUser2.png"));
    m_pixmapList.append(QPixmap(":/Images/tempUser/tempUser3.png"));
    m_pixmapList.append(QPixmap(":/Images/tempUser/tempUser6.png"));
    m_pixmapList.append(QPixmap(":/Images/tempUser/tempUser7.png"));

    m_pixmap = QPixmap(":/Images/tempUser/Aatrox.png");

    m_crossedDistance = 5;
}

void CustomUserList::setUserList(const QStringList &pathList)
{
    m_pixmapList.clear();
    for(auto &e : pathList)
    {
        m_pixmapList.append(QPixmap(e));
    }
}

void CustomUserList::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    painter.setRenderHint(QPainter::Antialiasing);

    int side = qMin(width() - 5, height() - 5);
    int n = m_pixmapList.size();
    int startX = side * (n - 1) - (n - 1) * m_crossedDistance;

    for(int i = 0; i < n; i++)
    {
        QPixmap pix = m_pixmapList.at(i).scaled(side, side, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPainterPath painterPath;

        int x = startX - (side - m_crossedDistance) * i;
        QRect rect(x, (height() - side) / 2.0, side, side);

        painterPath.addEllipse(rect);
        painter.setClipPath(painterPath);
        painter.drawPixmap(rect, pix);
    }

    QPixmap pix = m_pixmap.scaled(side, side, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPainterPath painterPath;
    QRect rect(width() - side, (height() - side) / 2.0, side, side);

    painterPath.addEllipse(rect);
    painter.setClipPath(painterPath);
    painter.drawPixmap(rect, pix);

    painter.end();

    event->accept();
}
