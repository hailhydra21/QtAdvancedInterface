/***************************************************************
 * Name:        TempPage.cpp
 * Author:      WenYi
 * Created:     2023-08-10 16:37
 ***************************************************************/

#include "TempPage.h"
#include "ui_TempPage.h"
#include "src/CustomWidget/CustomProgressBar.h"

#include <QLabel>

TempPage::TempPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TempPage)
{
    ui->setupUi(this);

    setMouseTracking(true);
    ui->frame_midCenter2->setMouseTracking(true);

    init();
}

TempPage::~TempPage()
{
    delete ui;
}

void TempPage::init()
{
    //使用本地qss文件对界面进行样式设置
    QFile qssFile(":/QSS/TempPage.qss");
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

    m_listLayout.append(layout1);
    m_listLayout.append(layout2);
    m_listLayout.append(layout3);
    m_listLayout.append(layout4);
    m_listLayout.append(layout5);
    m_listLayout.append(layout6);

    CustomProgressBar *pProgress1 = new CustomProgressBar;
    CustomProgressBar *pProgress2 = new CustomProgressBar;
    CustomProgressBar *pProgress3 = new CustomProgressBar;
    CustomProgressBar *pProgress4 = new CustomProgressBar;
    CustomProgressBar *pProgress5 = new CustomProgressBar;
    CustomProgressBar *pProgress6 = new CustomProgressBar;

    m_listProgress.append(pProgress1);
    m_listProgress.append(pProgress2);
    m_listProgress.append(pProgress3);
    m_listProgress.append(pProgress4);
    m_listProgress.append(pProgress5);
    m_listProgress.append(pProgress6);

    for(auto &e : m_listLayout)
    {
        e->setContentsMargins(0, 0, 0, 0);
    }

    for(auto &e : m_listProgress)
    {
        e->setMinimumSize(QSize(200, 200));
    }

    QLabel *label1 = new QLabel("Progress");
    QLabel *label2 = new QLabel("Progress");
    QLabel *label3 = new QLabel("Progress");
    QLabel *label4 = new QLabel("Progress");
    QLabel *label5 = new QLabel("Progress");
    QLabel *label6 = new QLabel("Progress");

    layout1->addWidget(label1);
    layout2->addWidget(label2);
    layout3->addWidget(label3);
    layout4->addWidget(label4);
    layout5->addWidget(label5);
    layout6->addWidget(label6);

    for(int i = 0; i < m_listLayout.size(); i++)
    {
        m_listLayout.at(i)->addWidget(m_listProgress.at(i));
        m_listLayout.at(i)->setContentsMargins(20, 20, 20, 20);
    }

    ui->card1->setLayout(layout1);
    ui->card2->setLayout(layout2);
    ui->card3->setLayout(layout3);
    ui->card4->setLayout(layout4);
    ui->card5->setLayout(layout5);
    ui->card6->setLayout(layout6);
}

void TempPage::showEvent(QShowEvent *event)
{
    m_listProgress.at(0)->setArcColor(QColor("#0680d7"), QColor("#2ac2d1"), QColor("#4ed066"));
    m_listProgress.at(1)->setArcColor(QColor("#a940a7"), QColor("#c7409e"), QColor("#e63f96"));
    m_listProgress.at(2)->setArcColor(QColor("#f1a581"), QColor("#2ac2d1"), QColor("#f2cd7e"));
    m_listProgress.at(3)->setArcColor(QColor("#888888"), QColor("#b5b5b5"), QColor("#ececec"));
    m_listProgress.at(5)->setArcColor(QColor("#2e4052"), QColor("#606e7b"), QColor("#adb5bb"));
    //    m_listProgress.at(5)->setArcColor(QColor("#ff616f"), QColor("#ff9472"), QColor("#efc9a4"));

    m_listProgress.at(0)->play(100, 80, 40);
    m_listProgress.at(1)->play(16, 16, 16);
    m_listProgress.at(2)->play(35, 45, 80);
    m_listProgress.at(3)->play(45, 60, 30);
    m_listProgress.at(4)->play(80, 70, 50);
    m_listProgress.at(5)->play(40, 90, 70);

    event->accept();
}
