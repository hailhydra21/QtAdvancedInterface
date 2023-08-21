/***************************************************************
 * Name:        MenuItemGroup.cpp
 * Author:      WenYi
 * Created:     2023-08-04 11:07
 ***************************************************************/

#include "MenuItemGroup.h"
#include "ui_MenuItemGroup.h"
#include "src/CustomWidget/MenuItem.h"

#include <QDebug>
#include <QSpacerItem>
#include <QPropertyAnimation>
#include <QDateTime>
#include <QFile>

MenuItemGroup::MenuItemGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuItemGroup)
{
    ui->setupUi(this);

    m_isNotfirstDisplay = true;

    init();
}

MenuItemGroup::MenuItemGroup(int itemCount, QWidget *parent)
{
    this->MenuItemGroup::MenuItemGroup(parent);

    for(int i = 0; i < itemCount; i++)
    {
        MenuItem *item = new MenuItem(i);
        m_itemList.append(item);
        m_vLayout->addWidget(item);
    }
    m_vLayout->addSpacerItem(new QSpacerItem(5, 1000, QSizePolicy::Expanding, QSizePolicy::Expanding));

    for(int i = 0; i < m_itemList.size(); i++)
    {
        connect(m_itemList.at(i), &MenuItem::signalActivate, this, [&](qint8 id, QPoint pos){
            for(int j = 0; j < m_itemList.size(); j++)
                m_itemList.at(j)->deActivate(id);

            QPoint newPos;
            newPos.setY(pos.y() - 1);
            moveAnimation(ui->label->pos(), newPos);
            emit signalSendClicked(id);
        });
    }
}

MenuItemGroup::~MenuItemGroup()
{
    delete ui;
}

void MenuItemGroup::showEvent(QShowEvent *event)
{
    if(m_isNotfirstDisplay)
    {
        m_itemList.at(0)->activate();
        m_isNotfirstDisplay = false;
    }
}

void MenuItemGroup::init()
{
    //使用本地qss文件对界面进行样式设置
    QFile qssFile(":/QSS/MenuItemGroup.qss");
    qssFile.open(QFile::ReadOnly);
    m_styleSheet = qssFile.readAll();
    this->setStyleSheet(m_styleSheet);
    qssFile.close();

    m_vLayout = new QVBoxLayout();
    m_vLayout->setSpacing(30);
    m_vLayout->setContentsMargins(0, 10, 0, 0);
    ui->scrollAreaWidgetContents->setLayout(m_vLayout);

    setMouseTracking(true);
    ui->scrollAreaWidgetContents->setMouseTracking(true);
    ui->scrollArea->setMouseTracking(true);
    ui->widget->setMouseTracking(true);
    ui->label->setMouseTracking(true);
}

void MenuItemGroup::moveAnimation(QPoint startPos, QPoint endPos)
{
    QPropertyAnimation *anim = new QPropertyAnimation(ui->label, "pos", this);
    anim->setDuration(500);
    anim->setStartValue(startPos);
    anim->setEndValue(endPos);
    anim->start();
}

//void MenuItemGroup::mouseMoveEvent(QMouseEvent *event)
//{
//    qDebug() << __FUNCTION__ << "sfa" << QDateTime::currentDateTime();
//}













