/***************************************************************
 * Name:        CustomUserProfile.cpp
 * Author:      WenYi
 * Created:     2023-08-10 16:29
 ***************************************************************/

#include "CustomUserProfile.h"

#include <QPainter>
#include <QPainterPath>
#include <QMediaPlayer>
#include <QUrl>
#include <QRandomGenerator>

CustomUserProfile::CustomUserProfile(QWidget *parent)
    : QWidget{parent}
{
    setMinimumSize(QSize(30, 30));

    m_pixmap = QPixmap(":/Images/user_profile.png");
    m_profileType = Example1::Circular;
    m_rectangleRadius = 12;

    m_pMediaPlayer = new QMediaPlayer(this);
    m_clickedSoundEffects = "";

    m_index = -1;
}

void CustomUserProfile::setProfilePreset(Example1::UserProfilePresetType presetType)
{
    if(presetType == Example1::Aatrox)
        useAatroxPreset();
}

void CustomUserProfile::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    painter.setRenderHint(QPainter::Antialiasing);

    int side = qMin(width(), height());
    QPixmap pix;
    pix = m_pixmap.scaled(side, side, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPainterPath path;

    switch(m_profileType)
    {
    case Example1::Circular:
        path.addEllipse(0, 0, side, side);
        break;
    case Example1::Rectangle:
        path.addRect(0, 0, side, side);
        break;
    case Example1::RoundedRectangle:
        path.addRoundedRect(0, 0, side, side, m_rectangleRadius, m_rectangleRadius);
        break;
    default:
        break;
    }

    painter.setClipPath(path);
    painter.drawPixmap(QRect(0, 0, side, side), pix);
    painter.end();

    event->accept();
}

void CustomUserProfile::mousePressEvent(QMouseEvent *event)
{
    if(!m_clickedSoundPath.isEmpty())
    {
        m_pMediaPlayer->setMedia(QUrl(m_clickedSoundPath));
        m_pMediaPlayer->play();
    }

    event->accept();
}

void CustomUserProfile::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(!m_dClickedSoundPath.isEmpty())
    {
        m_index = (m_index + 1) % m_dClickedSoundPath.size();
        //int number = QRandomGenerator::global()->bounded(m_dClickedSoundPath.size());
        m_pMediaPlayer->setMedia(QUrl(m_dClickedSoundPath.at(m_index)));
        m_pMediaPlayer->play();
    }
}

void CustomUserProfile::useAatroxPreset()
{
    m_pixmap = QPixmap("://Images/tempUser/Aatrox.png");

    setClickedSoundEffects("qrc:/SoundEffects/Aatrox/Aatrox_R_skill.wav");

    QStringList strList;
    strList.append(QStringLiteral("qrc:/SoundEffects/Aatrox/fight.wav"));
    strList.append(QStringLiteral("qrc:/SoundEffects/Aatrox/hahahahaa.wav"));
    strList.append(QStringLiteral("qrc:/SoundEffects/Aatrox/Do_you_think_you_can_kill_me.wav"));
    strList.append(QStringLiteral("qrc:/SoundEffects/Aatrox/cut.wav"));
    strList.append(QStringLiteral("qrc:/SoundEffects/Aatrox/I_am_Aatrox.wav"));
    strList.append(QStringLiteral("qrc:/SoundEffects/Aatrox/Kill_a_thousand_times.wav"));

    setDoubleClickedSoundEffects(strList);
}
