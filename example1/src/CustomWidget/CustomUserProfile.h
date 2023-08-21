/***************************************************************
 * Name:        CustomUserProfile.h
 * Author:      WenYi
 * Created:     2023-08-10 16:29
 ***************************************************************/

#ifndef CUSTOMUSERPROFILE_H
#define CUSTOMUSERPROFILE_H

#include "src/Base/DataType.h"

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>
#include <QMediaPlayer>

class CustomUserProfile : public QWidget
{
    Q_OBJECT
public:
    explicit CustomUserProfile(QWidget *parent = nullptr);

    inline void setProfile(QPixmap pix) { m_pixmap = pix; update(); }
    inline void setProfile(QString path) { m_pixmap = QPixmap(path); update(); }
    inline void setProFileType(Example1::UserProfileType type) { m_profileType = type; update(); }
    inline void setRadius(int radius) { m_rectangleRadius = radius; update(); }
    inline void setClickedSoundEffects(const QString filePath) { m_clickedSoundPath = filePath; }
    inline void setDoubleClickedSoundEffects(const QStringList filePaths) { m_dClickedSoundPath = filePaths; }
    void setProfilePreset(Example1::UserProfilePresetType presetType);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    void useAatroxPreset();

private:
    QPixmap m_pixmap;
    QMediaPlayer *m_pMediaPlayer;

    Example1::UserProfileType m_profileType;
    QString m_clickedSoundEffects;

    QString m_clickedSoundPath;
    QStringList m_dClickedSoundPath;

    int m_rectangleRadius;
    int m_index;
};

#endif // CUSTOMUSERPROFILE_H
