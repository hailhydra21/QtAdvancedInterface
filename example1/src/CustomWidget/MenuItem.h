/***************************************************************
 * Name:        MenuItem.h
 * Author:      WenYi
 * Created:     2023-08-04 11:08
 ***************************************************************/

#ifndef MENUITEM_H
#define MENUITEM_H

#include <QWidget>
#include <QPushButton>
#include <QPixmap>
#include <QHoverEvent>

namespace Ui {
class MenuItem;
}

class MenuItem : public QPushButton
{
    Q_OBJECT

public:
    explicit MenuItem(QWidget *parent = nullptr);
    MenuItem(qint8 id, QWidget *parent = nullptr);
    ~MenuItem();

    void updatePixmap(const QPixmap &pixmap1, const QPixmap &pixmap2, const QPixmap &pixmap3);
    void deActivate(const qint8 &id);
    void activate();
    inline void setId(const qint8 &id){ m_id = id; }

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
    bool event(QEvent *event) override;

private:
    void init();
    void hoverEnterEvent(QHoverEvent *event);
    void hoverLeaveEvent(QHoverEvent *event);

signals:
    void signalActivate(qint8 id, QPoint pos);

private:
    qint8 m_id;
    int m_imageWidth;
    QPixmap m_pixmapNormal;
    QPixmap m_pixmapHover;
    QPixmap m_pixmapActivate;
    bool m_isActive;
    bool m_isHover;
    Ui::MenuItem *ui;
};

#endif // MENUITEM_H
