/***************************************************************
 * Name:        MenuItemGroup.h
 * Author:      WenYi
 * Created:     2023-08-04 11:07
 ***************************************************************/

#ifndef MENUITEMGROUP_H
#define MENUITEMGROUP_H

#include <QWidget>
#include <QVBoxLayout>

class MenuItem;

namespace Ui {
class MenuItemGroup;
}

class MenuItemGroup : public QWidget
{
    Q_OBJECT

public:
    explicit MenuItemGroup(QWidget *parent = nullptr);
    MenuItemGroup(int itemCount, QWidget *parent = nullptr);
    ~MenuItemGroup();

    inline QList<MenuItem*> &getItemList() { return m_itemList; }

protected:
    void showEvent(QShowEvent *event);

signals:
    void signalSendClicked(qint8 id);

private:
    void init();
    void moveAnimation(QPoint startPos, QPoint endPos);
    //void mouseMoveEvent(QMouseEvent *event);

private:
    QString m_styleSheet;
    QList<MenuItem*> m_itemList;
    QVBoxLayout *m_vLayout;
    Ui::MenuItemGroup *ui;

    bool m_isNotfirstDisplay;
};

#endif // MENUITEMGROUP_H
