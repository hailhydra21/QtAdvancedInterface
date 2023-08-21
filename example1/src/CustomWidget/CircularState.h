/***************************************************************
 * Name:        CircularState.h
 * Author:      WenYi
 * Created:     2023-08-04 11:09
 ***************************************************************/

#ifndef CIRCULARSTATE_H
#define CIRCULARSTATE_H

#include "src/Base/DataType.h"

#include <QWidget>

class QPropertyAnimation;
class QTimer;

namespace Ui {
class CircularState;
}

class CircularState : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double opacity READ getOpacity WRITE setOpacity)
public:
    explicit CircularState(QWidget *parent = nullptr);
    CircularState(Example1::ConnectStateType type, QWidget *parent = nullptr);
    ~CircularState();

    void setConnectState(Example1::ConnectStateType type);
    inline void setOpacity(double opacity){ m_opacity = opacity; update(); }
    inline double getOpacity(){ return m_opacity; }

protected:
    void paintEvent(QPaintEvent *event) override;
    bool event(QEvent *e) override;

private:
    void init();
    void createSignalConnect();

private:
    Ui::CircularState *ui;

    QPropertyAnimation *m_pBlinkAnimation;
    QPropertyAnimation *m_pBlinkAnimation2;
    QPropertyAnimation *m_pBlinkAnimation3;

    Example1::ConnectStateType m_connectState;

    double m_opacity;
    bool m_isHover;
    QTimer *m_timer;
    QTimer *m_timer2;
    QTimer *m_timer3;
};

#endif // CIRCULARSTATE_H
