/***************************************************************
 * Name:        HomePage.cpp
 * Author:      WenYi
 * Created:     2023-08-08 11:57
 ***************************************************************/

#include "HomePage.h"
#include "ui_HomePage.h"
#include "src/Base/DataType.h"
#include "src/CustomWidget/CustomCard.h"

#include <QFile>

HomePage::HomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);

    setMouseTracking(true);
    ui->frame_midCenter2->setMouseTracking(true);

    init();
}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::init()
{
    //使用本地qss文件对界面进行样式设置
    QFile qssFile(":/QSS/HomePage.qss");
    qssFile.open(QFile::ReadOnly);
    QString styleSheet = qssFile.readAll();
    this->setStyleSheet(styleSheet);
    qssFile.close();

    QVBoxLayout *layout1 = new QVBoxLayout;
    QVBoxLayout *layout2 = new QVBoxLayout;
    QVBoxLayout *layout3 = new QVBoxLayout;
    QVBoxLayout *layout4 = new QVBoxLayout;
    QVBoxLayout *layout5 = new QVBoxLayout;
    QVBoxLayout *layout6 = new QVBoxLayout;
    layout1->setContentsMargins(0, 0, 0, 0);
    layout2->setContentsMargins(0, 0, 0, 0);
    layout3->setContentsMargins(0, 0, 0, 0);
    layout4->setContentsMargins(0, 0, 0, 0);
    layout5->setContentsMargins(0, 0, 0, 0);
    layout6->setContentsMargins(0, 0, 0, 0);

    m_listVBLayout.append(layout1);
    m_listVBLayout.append(layout2);
    m_listVBLayout.append(layout3);
    m_listVBLayout.append(layout4);
    m_listVBLayout.append(layout5);
    m_listVBLayout.append(layout6);

    createSignalConnect();
    tempTest();
}

void HomePage::createSignalConnect()
{

}

void HomePage::tempTest()
{
    CustomCard *pCard1 = new CustomCard;
    CustomCard *pCard2 = new CustomCard;
    CustomCard *pCard3 = new CustomCard;
    CustomCard *pCard4 = new CustomCard;
    CustomCard *pCard5 = new CustomCard;
    CustomCard *pCard6 = new CustomCard;

    m_listVBLayout.at(0)->addWidget(pCard1);
    m_listVBLayout.at(1)->addWidget(pCard2);
    m_listVBLayout.at(2)->addWidget(pCard3);
    m_listVBLayout.at(3)->addWidget(pCard4);
    m_listVBLayout.at(4)->addWidget(pCard5);
    m_listVBLayout.at(5)->addWidget(pCard6);

    m_listCard.append(pCard1);
    m_listCard.append(pCard2);
    m_listCard.append(pCard3);
    m_listCard.append(pCard4);
    m_listCard.append(pCard5);
    m_listCard.append(pCard6);

    ui->card1->setLayout(m_listVBLayout.at(0));
    ui->card2->setLayout(m_listVBLayout.at(1));
    ui->card3->setLayout(m_listVBLayout.at(2));
    ui->card4->setLayout(m_listVBLayout.at(3));
    ui->card5->setLayout(m_listVBLayout.at(4));
    ui->card6->setLayout(m_listVBLayout.at(5));

    Example1::TaskCardData cardData1("Berkshire Hathaway",
                                     "Project management web app",
                                     Example1::Completed,
                                     Example1::HighPriority,
                                     QDateTime::currentDateTime(),
                                     true);
    Example1::TaskCardData cardData2("United Health Group",
                                     "Company branding",
                                     Example1::Completed,
                                     Example1::NormalPriority,
                                     QDateTime::currentDateTime(),
                                     true);
    Example1::TaskCardData cardData3("JP Morgan Chase",
                                     "Ecommerce website redesign",
                                     Example1::InProgress,
                                     Example1::HighPriority,
                                     QDateTime::currentDateTime(),
                                     false);
    Example1::TaskCardData cardData4("CVS Health",
                                     "Alleviation Appliance",
                                     Example1::OffTrack,
                                     Example1::NormalPriority,
                                     QDateTime::currentDateTime(),
                                     false);
    Example1::TaskCardData cardData5("Ping An Insurance",
                                     "Project management app",
                                     Example1::Completed,
                                     Example1::LowPriority,
                                     QDateTime::currentDateTime(),
                                     true);
    Example1::TaskCardData cardData6("Amerisource Bergen",
                                     "Dashing Development",
                                     Example1::OffTrack,
                                     Example1::NormalPriority,
                                     QDateTime::currentDateTime(),
                                     true);

    m_listCard.at(0)->setTaskData(cardData1);
    m_listCard.at(1)->setTaskData(cardData2);
    m_listCard.at(2)->setTaskData(cardData3);
    m_listCard.at(3)->setTaskData(cardData4);
    m_listCard.at(4)->setTaskData(cardData5);
    m_listCard.at(5)->setTaskData(cardData6);

    QStringList list1, list2, list3, list4, list5;
    list1.append(":/Images/tempUser/tempUser5.png");
    list1.append(":/Images/tempUser/tempUser8.png");
    list1.append(":/Images/tempUser/tempUser9.png");
    m_listCard.at(1)->setUserList(list1);
    m_listCard.at(1)->setPM(":/Images/tempUser/Heisenberg.png");

    list2.append(":/Images/tempUser/tempUser10.png");
    list2.append(":/Images/tempUser/tempUser12.png");
    list2.append(":/Images/tempUser/tempUser13.png");
    list2.append(":/Images/tempUser/tempUser14.png");
    m_listCard.at(2)->setUserList(list2);
    m_listCard.at(2)->setPM(":/Images/tempUser/Mahone.png");

    list3.append(":/Images/tempUser/tempUser17.png");
    list3.append(":/Images/tempUser/tempUser15.png");
    list3.append(":/Images/tempUser/JonSnow.png");
    list3.append(":/Images/tempUser/tempUser16.png");
    m_listCard.at(3)->setUserList(list3);
    m_listCard.at(3)->setPM(":/Images/tempUser/NightKing.png");

    list4.append(":/Images/tempUser/tempUser14.png");
    list4.append(":/Images/tempUser/Aatrox.png");
    list4.append(":/Images/tempUser/tempUser10.png");
    list4.append(":/Images/tempUser/Mahone.png");
    list4.append(":/Images/tempUser/tempUser15.png");
    list4.append(":/Images/tempUser/tempUser4.png");
    m_listCard.at(4)->setUserList(list4);
    m_listCard.at(4)->setPM(":/Images/tempUser/AdaWong.png");

    list5.append(":/Images/tempUser/tempUser7.png");
    list5.append(":/Images/tempUser/AudreyHepburn.png");
    list5.append(":/Images/tempUser/tempUser12.png");
    m_listCard.at(5)->setUserList(list5);
    m_listCard.at(5)->setPM(":/Images/tempUser/JonSnow.png");
}
