/***************************************************************
 * Name:        CustomProgressBar.h
 * Author:      WenYi
 * Created:     2023-08-04 11:08
 ***************************************************************/

#ifndef CUSTOMPROGRESSBAR_H
#define CUSTOMPROGRESSBAR_H

#include <QWidget>
#include <QProgressBar>
#include <QPaintEvent>
#include <QPropertyAnimation>

namespace Ui {
class CustomProgressBar;
}

class CustomProgressBar : public QProgressBar
{
    Q_OBJECT
    Q_PROPERTY(int value READ getPersent WRITE setPersent)
    Q_PROPERTY(int value2 READ getPersent WRITE setPersent2)
    Q_PROPERTY(int value3 READ getPersent WRITE setPersent3)
public:
    explicit CustomProgressBar(QWidget *parent = nullptr);
    ~CustomProgressBar();

    void setProgressValue(int value);
    void setProgressValue2(int value);
    void setProgressValue3(int value);

    void setPersent(int v);
    void setPersent2(int v);
    void setPersent3(int v);

    void setArcColor(const QColor &c1, const QColor &c2, const QColor &c3);

    inline int getPersent() { return m_persent; }
    inline int getPersent2() { return m_persent2; }
    inline int getPersent3() { return m_persent3; }

    void play(int v1, int v2, int v3);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::CustomProgressBar *ui;

    QPropertyAnimation *m_pAnimation;
    QPropertyAnimation *m_pAnimation2;
    QPropertyAnimation *m_pAnimation3;
    double m_rotateAngle;
    double m_rotateAngle2;
    double m_rotateAngle3;
    int m_persent;
    int m_persent2;
    int m_persent3;

    QColor m_arcColor1;
    QColor m_arcColor2;
    QColor m_arcColor3;
};

#endif // CUSTOMPROGRESSBAR_H
