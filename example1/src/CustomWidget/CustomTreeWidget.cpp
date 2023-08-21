/***************************************************************
 * Name:        CustomTreeWidget.cpp
 * Author:      WenYi
 * Created:     2023-05-26 16:41
 ***************************************************************/

#include "CustomTreeWidget.h"

CustomTreeWidget::CustomTreeWidget(QWidget *parent)
    : QTreeWidget{parent}
{
    m_pLastHoverItem = nullptr;

    init();
}

CustomTreeWidget::~CustomTreeWidget()
{

}

void CustomTreeWidget::clear()
{
    m_pLastHoverItem = nullptr;
    QTreeWidget::clear();
}

void CustomTreeWidget::init()
{
    createSignalConnect();
}

void CustomTreeWidget::createSignalConnect()
{
    connect(this, &CustomTreeWidget::itemEntered, this, [&](QTreeWidgetItem *item, int column){
        QFont font;
        if(m_pLastHoverItem != nullptr)
        {
            m_pLastHoverItem->setFont(0, m_fontTreeWidgetItem);
        }
        else
        {
            m_fontTreeWidgetItem = item->font(0);
        }
        font = m_fontTreeWidgetItem;
        font.setBold(true);
        font.setPointSize(font.pointSize()+2);
        item->setFont(0, font);
        m_pLastHoverItem = item;
    });
}

