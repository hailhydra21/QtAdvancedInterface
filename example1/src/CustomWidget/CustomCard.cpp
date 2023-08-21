/***************************************************************
 * Name:        CustomCard.cpp
 * Author:      WenYi
 * Created:     2023-08-08 11:58
 ***************************************************************/

#include "CustomCard.h"
#include "ui_CustomCard.h"
#include "src/Base/GlobalStatic.h"
#include "src/CustomWidget/CustomUserList.h"

#include <QFile>
#include <QPalette>

CustomCard::CustomCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomCard)
{
    ui->setupUi(this);

    init();
}

CustomCard::CustomCard(Example1::TaskCardData cardData, QWidget *parent)
{
    this->CustomCard::CustomCard(parent);
    setTaskData(cardData);
}

CustomCard::~CustomCard()
{
    delete ui;
}

void CustomCard::init()
{
    //使用本地qss文件对界面进行样式设置
    QFile qssFile(":/QSS/CustomCard.qss");
    qssFile.open(QFile::ReadOnly);
    QString styleSheet = qssFile.readAll();
    this->setStyleSheet(styleSheet);
    qssFile.close();

    m_pCustomUserList = new CustomUserList;
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(10, 5, 10, 5);
    layout->addWidget(m_pCustomUserList);
    ui->w_participants->setLayout(layout);

    createSignalConnect();

    startTimer(11000);
}

void CustomCard::createSignalConnect()
{
    connect(ui->tb_collect, &QToolButton::clicked, [&]{
        m_cardData.collect = !m_cardData.collect;
        setCollect(m_cardData.collect);
    });
}

void CustomCard::setTaskData(Example1::TaskCardData cardData)
{
    m_cardData = cardData;

    refresh();
}

void CustomCard::setTitel(QString str)
{
    ui->label_title->setText(str);
}

void CustomCard::setDescription(QString str)
{
    ui->label_description->setText(str);
}

void CustomCard::setState(Example1::TaskStateType state)
{
    ui->label_task_state->setText(
        GlobalStatic::gs_mapTaskStateNote[state]);

    if(state == Example1::TaskStateType::InProgress)
    {
        ui->w_task_state->setStyleSheet("QWidget#w_task_state{"
                                        "border-radius: 20px;"
                                        "background-color: #eaebf2;}");
        ui->label_task_state->setStyleSheet("QLabel#label_task_state{color: #565a97;}");
    }
    else if(state == Example1::TaskStateType::Completed)
    {
        ui->w_task_state->setStyleSheet("QWidget#w_task_state{"
                                        "border-radius: 20px;"
                                        "background-color: #eaf8f6;}");
        ui->label_task_state->setStyleSheet("QLabel#label_task_state{color: #73cec1;}");
    }
    else if(state == Example1::TaskStateType::OffTrack)
    {
        ui->w_task_state->setStyleSheet("QWidget#w_task_state{"
                                        "border-radius: 20px;"
                                        "background-color: #ffefeb;}"
                                        );
        ui->label_task_state->setStyleSheet("QLabel#label_task_state{color: #ff815f;}");
    }
}

void CustomCard::setPriority(Example1::TaskPriorityType priority)
{
    ui->label_priority->setText(
        GlobalStatic::gs_mapTaskPriorityNote[priority]);
}

void CustomCard::setCreationTime(QDateTime t)
{
    QDateTime t2 = QDateTime::currentDateTime();
    int diff = t.secsTo(t2);
    if(diff < 60)
    {
        ui->label_creation_time->setText(QString("%1 sec ago").arg(diff));
    }
    else if(diff > 60 && diff < 3600)
    {
        ui->label_creation_time->setText(QString("%1 min ago").arg(diff/60));
    }
    else if(diff > 3600 && diff < 3600*24)
    {
        ui->label_creation_time->setText(QString("%1 h ago").arg(diff/3600));
    }
    else
    {
        ui->label_creation_time->setText(t.toString("MM/dd hh:mm"));
    }
}

void CustomCard::setCollect(bool isCollect)
{
    if(isCollect)
    {
        ui->tb_collect->setStyleSheet("QToolButton#tb_collect{"
                                        "border-image: url(:/Images/collect.png);} "
                                      "QToolButton#tb_collect:hover{"
                                          "border-image: url(:/Images/collect.png)2 2 2 2;} "
                                      );
    }
    else
    {
        ui->tb_collect->setStyleSheet("QToolButton#tb_collect{"
                                      "border-image: url(:/Images/no_collect.png);} "
                                      "QToolButton#tb_collect:hover{"
                                      "border-image: url(:/Images/no_collect.png)2 2 2 2;} "
                                      );
    }
}

void CustomCard::setUserList(const QStringList &pathList)
{
    m_pCustomUserList->setUserList(pathList);
}

void CustomCard::setPM(QString path)
{
    m_pCustomUserList->setPM(path);
}

void CustomCard::refresh()
{
    setTitel(m_cardData.title);
    setDescription(m_cardData.description);
    setState(m_cardData.state);
    setPriority(m_cardData.priority);
    setCreationTime(m_cardData.creationTime);
    setCollect(m_cardData.collect);
}

void CustomCard::timerEvent(QTimerEvent *event)
{
    refresh();

    event->accept();
}

