/***************************************************************
 * Name:        CustomTreeWidget.h
 * Author:      WenYi
 * Created:     2023-05-26 16:41
 ***************************************************************/

#ifndef CUSTOMTREEWIDGET_H
#define CUSTOMTREEWIDGET_H

#include <QTreeWidget>
#include <QFont>

class CustomTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit CustomTreeWidget(QWidget *parent = nullptr);
    ~CustomTreeWidget();

    void clear();
//    void activatedItem();

private:
    void init();
    void createSignalConnect();

private:
    QTreeWidgetItem *m_pLastHoverItem;
    QFont m_fontTreeWidgetItem;
};

#endif // CUSTOMTREEWIDGET_H
