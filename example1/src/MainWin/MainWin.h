/***************************************************************
 * Name:        MainWin.h
 * Author:      WenYi
 * Created:     2023-08-04 11:15
 ***************************************************************/

#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPoint>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QFont>

#include "src/Base/DataType.h"

class MenuItemGroup;
class CircularState;
class QMenu;
class QAction;
class QTreeWidgetItem;
class CustomProgressBar;
class CustomMessageBox;
class HomePage;
class TempPage;

namespace Ui {
class MainWin;
}

class MainWin : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int cbSwitchWidth READ getCbSwitchWidth WRITE setCbSwitchWidth)

public:
    explicit MainWin(QWidget *parent = nullptr);
    ~MainWin();

    int getCbSwitchWidth();
    qint8 getRectRegion(QPoint p);

    void setCbSwitchWidth(int width);
    void setCursorType(Example1::RectRegionType type);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    void init();
    void theNiggleWin();
    void createSignalConnect();
    void winMaximized();
    void tbMaxChangedStyle();
    void fadeOut(const int &millisecond);

    QObjectList getAllUIObj(QObject *parent);

private:
    Ui::MainWin *ui;

    QGraphicsDropShadowEffect *m_pShadow;
    QGraphicsDropShadowEffect *m_pUserWidgetShadow;
    QPropertyAnimation *m_pAnimation;
    QPropertyAnimation *m_pCBSwitchAnimation;
    QString m_styleSheet;
    QPoint m_dragStartPoint;

    QMenu *m_pAddFunctionMenu;
    QMenu *m_pExecuteMenu;

    QAction *m_pFunctionOne;
    QAction *m_pFunctionTwo;
    QAction *m_pFunctionThree;

    MenuItemGroup *m_pMenuItemGroup;
    CircularState *m_pServicesCntState;

    CustomProgressBar *m_pCustomProgressBar;
    CustomMessageBox *m_pCustomMessageBox;

    HomePage *m_pHomePage;
    TempPage *m_pTempPage;

    bool m_isLeftButtonPress;
    bool m_isNotfirstDisplay;
    bool m_isOnlyStop;
    Example1::RectRegionType m_rectRegion;

    // 热你个温
    QStringList m_theNiggleWin;

    int m_cbSwitchLastWith;
    int m_workstationId;
    int m_taskId;
};

#endif // MAINWIN_H
