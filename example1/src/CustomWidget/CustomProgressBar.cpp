/***************************************************************
 * Name:        CustomProgressBar.cpp
 * Author:      WenYi
 * Created:     2023-08-04 11:09
 ***************************************************************/

#include "CustomProgressBar.h"
#include "ui_CustomProgressBar.h"

#include <QPainter>
#include <qDebug>

CustomProgressBar::CustomProgressBar(QWidget *parent) :
    QProgressBar(parent),
    ui(new Ui::CustomProgressBar)
{
    ui->setupUi(this);

    m_persent = 0;
    m_persent2 = 0;
    m_persent3 = 0;
    m_pAnimation = new QPropertyAnimation(this, "value");
    m_pAnimation2 = new QPropertyAnimation(this, "value2");
    m_pAnimation3 = new QPropertyAnimation(this, "value3");

    m_arcColor1 = QColor(117, 196, 245);
    m_arcColor2 = QColor(179, 120, 239);
    m_arcColor3 = QColor(131, 245, 216);

    setProgressValue(80);
    setProgressValue2(70);
    setProgressValue3(50);
}

CustomProgressBar::~CustomProgressBar()
{
    delete ui;
}

void CustomProgressBar::setProgressValue(int value)
{
    m_pAnimation->setDuration(1000);
    m_pAnimation->setStartValue(m_persent);
    m_pAnimation->setEndValue(value);
    m_pAnimation->start();
}

void CustomProgressBar::setProgressValue2(int value)
{
    m_pAnimation2->setDuration(1000);
    m_pAnimation2->setStartValue(m_persent2);
    m_pAnimation2->setEndValue(value);
    m_pAnimation2->start();
}

void CustomProgressBar::setProgressValue3(int value)
{
    m_pAnimation3->setDuration(1000);
    m_pAnimation3->setStartValue(m_persent3);
    m_pAnimation3->setEndValue(value);
    m_pAnimation3->start();
}

void CustomProgressBar::setPersent(int v)
{
    m_persent = v;
    update();
}

void CustomProgressBar::setPersent2(int v)
{
    m_persent2 = v;
    update();
}

void CustomProgressBar::setPersent3(int v)
{
    m_persent3 = v;
    update();
}

void CustomProgressBar::setArcColor(const QColor &c1,
                                    const QColor &c2,
                                    const QColor &c3)
{
    m_arcColor1 = c1;
    m_arcColor2 = c2;
    m_arcColor3 = c3;

    update();
}

void CustomProgressBar::play(int v1, int v2, int v3)
{
    m_persent = 0;
    m_persent2 = 0;
    m_persent3 = 0;

    update();

    setProgressValue(v1);
    setProgressValue2(v2);
    setProgressValue3(v3);
}

void CustomProgressBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int side = qMin(width(), height()) - 20;
    int startX = (width() - side) / 2;
    int startY = (height() - side) / 2;
    QRectF arc(startX, startY, side, side);
    QRectF arc2(startX + 14, startY + 14, side - 28, side - 28);
    QRectF arc3(startX + 28, startY + 28, side - 56, side - 56);

    QRectF mask(startX + 6, startY + 6, side - 12, side - 12);
    QRectF mask2(startX + 20, startY + 20, side - 40, side - 40);
    QRectF mask3(startX + 34, startY + 34, side - 68, side - 68);

    QString valueStr = QString("%1%").arg(QString::number(m_persent));
    QString valueStr2 = QString("%1%").arg(QString::number(m_persent2));
    QString valueStr3 = QString("%1%").arg(QString::number(m_persent3));

    m_rotateAngle = 360 * m_persent * 1.0 / 100;
    m_rotateAngle2 = 360 * m_persent2 * 1.0 / 100;
    m_rotateAngle3 = 360 * m_persent3 * 1.0 / 100;

    //画圆弧
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_arcColor1);
    painter.drawPie(arc, (50-m_rotateAngle)*16, m_rotateAngle*16);
    //画遮罩
    painter.setBrush(QColor(255, 255, 255));
    painter.drawEllipse(mask);

    //画圆弧
    painter.setBrush(m_arcColor2);
    painter.drawPie(arc2, 0*16, m_rotateAngle2*16);
    //画遮罩
    painter.setBrush(QColor(255, 255, 255));
    painter.drawEllipse(mask2);

    //画圆弧
    painter.setBrush(m_arcColor3);
    painter.drawPie(arc3, -m_rotateAngle3*16, m_rotateAngle3*16);
    //画遮罩
    painter.setBrush(QColor(255, 255, 255));
    painter.drawEllipse(mask3);

    // 画小方块
    QRectF rect(startX + 68, startY + 64, 8, 8);
    QRectF rect2(startX + 68, startY + 82, 8, 8);
    QRectF rect3(startX + 68, startY + 100, 8, 8);

    painter.setBrush(m_arcColor1);
    painter.drawEllipse(rect);
    painter.setBrush(m_arcColor2);
    painter.drawEllipse(rect2);
    painter.setBrush(m_arcColor3);
    painter.drawEllipse(rect3);

    QPointF pointF(startX + 86, startY + 73);
    QPointF pointF2(startX + 86, startY + 92);
    QPointF pointF3(startX + 86, startY + 109);

    //画文字
    QFont font = QFont("Microsoft YaHei", 9, QFont::Bold);
    painter.setFont(font);
    painter.setPen(QColor("#555555"));
    painter.drawText(pointF, valueStr);
    painter.drawText(pointF2, valueStr2);
    painter.drawText(pointF3, valueStr3);
}
