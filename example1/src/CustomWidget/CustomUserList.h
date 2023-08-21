/***************************************************************
 * Name:        CustomUserList.h
 * Author:      WenYi
 * Created:     2023-08-10 16:28
 ***************************************************************/

#ifndef CUSTOMUSERLIST_H
#define CUSTOMUSERLIST_H

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>

class CustomUserList : public QWidget
{
    Q_OBJECT
public:
    explicit CustomUserList(QWidget *parent = nullptr);

    void setUserList(const QStringList &pathList);
    inline void setPM(QString path) { m_pixmap = QPixmap(path); update();}

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QList<QPixmap> m_pixmapList;
    QPixmap m_pixmap;

    int m_crossedDistance;
};

#endif // CUSTOMUSERLIST_H
