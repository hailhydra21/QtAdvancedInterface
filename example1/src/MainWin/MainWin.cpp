/**************************************************
 * Name:        MainWin.cpp
 * Author:      WenYi
 * Created:     2023-08-04 10:41
 **************************************************/

#include "MainWin.h"
#include "ui_MainWin.h"
#include "src/Base/GlobalStatic.h"
#include "src/CustomWidget/MenuItem.h"
#include "src/CustomWidget/CircularState.h"
#include "src/CustomWidget/MenuItemGroup.h"
#include "src/CustomWidget/CustomProgressBar.h"
#include "src/CustomWidget/CustomMessageBox.h"
#include "src/StackedWidget/HomePage.h"
#include "src/StackedWidget/TempPage.h"

#include <QFile>
#include <QDebug>
#include <QVBoxLayout>
#include <QAction>
#include <QListView>
#include <QMenu>
#include <QButtonGroup>
#include <QUdpSocket>

MainWin::MainWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWin)
{
    ui->setupUi(this);

    theNiggleWin();

    m_pAnimation = new QPropertyAnimation(this, "windowOpacity");
    m_pMenuItemGroup = new MenuItemGroup(8, this);
    m_pServicesCntState = new CircularState(Example1::ConnectedState);
    m_cbSwitchLastWith = 135;
    m_pCustomProgressBar = new CustomProgressBar;
    m_pCustomMessageBox = new CustomMessageBox(this);
    m_pHomePage = new HomePage;
    m_pTempPage = new TempPage;
    m_isNotfirstDisplay = true;
    m_workstationId = -1;
    m_taskId = -1;
    m_isOnlyStop = false;

    init();
}

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::init()
{
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowTitle("QtAdvancedInterface");

    //使用本地qss文件对界面进行样式设置
    QFile qssFile(":/QSS/MainWin.qss");
    qssFile.open(QFile::ReadOnly);
    m_styleSheet = qssFile.readAll();
    this->setStyleSheet(m_styleSheet);
    qssFile.close();

    // 阴影
    auto *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor("#959595"));
    shadow->setBlurRadius(30);

    ui->widget_effect->setGraphicsEffect(shadow);

    setMouseTracking(true);

    m_pUserWidgetShadow = new QGraphicsDropShadowEffect();
    m_pUserWidgetShadow->setOffset(-2, 10);
    m_pUserWidgetShadow->setColor(QColor("#c5c5c5"));
    m_pUserWidgetShadow->setBlurRadius(50);

    m_pShadow = new QGraphicsDropShadowEffect();
    m_pShadow->setOffset(10, 10);
    m_pShadow->setColor(QColor("#c5c5c5"));
    m_pShadow->setBlurRadius(50);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->addWidget(m_pMenuItemGroup);
    ui->widget_ItemGroup->setLayout(vLayout);

    QVBoxLayout *vLayout2 = new QVBoxLayout;
    vLayout2->setContentsMargins(0, 0, 0, 0);
    vLayout2->addWidget(m_pServicesCntState);
    ui->w_materialCntState->setLayout(vLayout2);

    m_pMenuItemGroup->getItemList().at(0)->updatePixmap(QPixmap(":/Images/home.png"),
                                                        QPixmap(":/Images/home_hover.png"),
                                                        QPixmap(":/Images/home_activate.png"));
    m_pMenuItemGroup->getItemList().at(1)->updatePixmap(QPixmap(":/Images/menu.png"),
                                                        QPixmap(":/Images/menu_hover.png"),
                                                        QPixmap(":/Images/menu_activate.png"));
    m_pMenuItemGroup->getItemList().at(2)->updatePixmap(QPixmap(":/Images/settings.png"),
                                                        QPixmap(":/Images/settings_hover.png"),
                                                        QPixmap(":/Images/settings_activate.png"));
    m_pMenuItemGroup->getItemList().at(3)->updatePixmap(QPixmap(":/Images/info.png"),
                                                        QPixmap(":/Images/info_hover.png"),
                                                        QPixmap(":/Images/info_activate.png"));

    m_pMenuItemGroup->getItemList().at(0)->setToolTip(tr("Homeage"));
    m_pMenuItemGroup->getItemList().at(1)->setToolTip(tr("Menu"));
    m_pMenuItemGroup->getItemList().at(2)->setToolTip(tr("Settings"));
    m_pMenuItemGroup->getItemList().at(3)->setToolTip(tr("About"));
    m_pMenuItemGroup->getItemList().at(5)->setToolTip(tr("ni gan ma, ai yo~!"));
    m_pMenuItemGroup->getItemList().at(6)->setToolTip(tr("What are you doing, ouch~!"));


    m_pAddFunctionMenu = new QMenu(m_pMenuItemGroup);
    m_pAddFunctionMenu->setAttribute(Qt::WA_TranslucentBackground);
    m_pAddFunctionMenu->setWindowFlags(m_pAddFunctionMenu->windowFlags() | Qt::FramelessWindowHint);
    m_pAddFunctionMenu->setObjectName(tr("AddFunctionMenu"));
    m_pFunctionOne = new QAction(tr("Advanced progress bar(&q)"));
    m_pFunctionTwo = new QAction(tr("Function two(&w)"));
    m_pFunctionThree = new QAction(tr("Function three(&e)"));
    m_pAddFunctionMenu->addAction(m_pFunctionOne);
    m_pAddFunctionMenu->addAction(m_pFunctionTwo);
    m_pAddFunctionMenu->addAction(m_pFunctionThree);
    m_pMenuItemGroup->getItemList().at(1)->setMenu(m_pAddFunctionMenu);

    ui->le_search->setPlaceholderText("Search");

    ui->cb_switch->setView(new QListView());
    ui->cb_switch->setMouseTracking(true);
    ui->cb_switch->view()->parentWidget()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    ui->cb_switch->view()->parentWidget()->setAttribute(Qt::WA_TranslucentBackground);

    ui->cb_switch->addItem(tr("Focusing"), 0);
    ui->cb_switch->addItem(tr("Stare Blankly"), 1);
    ui->cb_switch->addItem(tr("Relaxing"), 2);
    ui->cb_switch->addItem(tr("Busy"), 3);

    ui->w_topLeft->setAttribute(Qt::WA_Hover);
    ui->w_topRight->setAttribute(Qt::WA_Hover);
    ui->w_bottomLeft->setAttribute(Qt::WA_Hover);
    ui->w_bottomRight->setAttribute(Qt::WA_Hover);
    ui->w_user->setAttribute(Qt::WA_Hover);
    ui->w_rb_light->setAttribute(Qt::WA_Hover);
    ui->w_rb_dark->setAttribute(Qt::WA_Hover);
    ui->w_topLeft->installEventFilter(this);
    ui->w_topRight->installEventFilter(this);
    ui->w_bottomLeft->installEventFilter(this);
    ui->w_bottomRight->installEventFilter(this);
    ui->w_user->installEventFilter(this);
    ui->w_rb_light->installEventFilter(this);
    ui->w_rb_dark->installEventFilter(this);

    ui->le_search->setFocusPolicy(Qt::ClickFocus);
    ui->le_search->installEventFilter(this);

    ui->label_logo->setMouseTracking(true);

    QButtonGroup *m_btnGroup = new QButtonGroup(this);
    m_btnGroup->addButton(ui->rb_dark);
    m_btnGroup->addButton(ui->rb_light);

    ui->stackedWidget_midCenter->addWidget(m_pHomePage);
    ui->stackedWidget_midCenter->addWidget(m_pTempPage);
    ui->stackedWidget_midCenter->setMouseTracking(true);

    ui->w_userProfile2->setProFileType(Example1::RoundedRectangle);
    ui->w_userProfile3->setProFileType(Example1::RoundedRectangle);
    ui->w_userProfile4->setProFileType(Example1::RoundedRectangle);

    ui->w_userProfile1->setProfilePreset(Example1::Aatrox);
    ui->w_userProfile2->setProfile("://Images/tempUser/AdaWong.png");
    ui->w_userProfile3->setProfile("://Images/tempUser/Mahone.png");
    ui->w_userProfile4->setProfile("://Images/tempUser/NightKing.png");

    foreach(auto e, this->getAllUIObj(this))
    {
        if(e->metaObject()->className() == QStringLiteral("QWidget"))
        {
            QWidget *w = qobject_cast<QWidget *>(e);
            w->setMouseTracking(true);
        }
        else if(e->metaObject()->className() == QStringLiteral("QFrame"))
        {
            QFrame *w = qobject_cast<QFrame *>(e);
            w->setMouseTracking(true);
        }
    }

    createSignalConnect();
}

void MainWin::theNiggleWin()
{
    GlobalStatic::gs_mapTaskStateNote.insert(Example1::TaskStateType::InProgress, "In progress");
    GlobalStatic::gs_mapTaskStateNote.insert(Example1::TaskStateType::Completed, "Completed");
    GlobalStatic::gs_mapTaskStateNote.insert(Example1::TaskStateType::OffTrack, "Off track");

    GlobalStatic::gs_mapTaskPriorityNote.insert(Example1::TaskPriorityType::LowPriority, "Low priority");
    GlobalStatic::gs_mapTaskPriorityNote.insert(Example1::TaskPriorityType::NormalPriority, "Normal priority");
    GlobalStatic::gs_mapTaskPriorityNote.insert(Example1::TaskPriorityType::HighPriority, "High priority");
}

void MainWin::createSignalConnect()
{
    connect(ui->tb_minimize, &QToolButton::clicked, this, [&](){
        if(!this->isMinimized())
            this->showMinimized();
    });
    connect(ui->tb_maximize, &QToolButton::clicked, this, &MainWin::winMaximized);
    connect(ui->tb_close, &QToolButton::clicked, this, [&](){
        fadeOut(1000);
    });
    connect(ui->cb_switch, &QComboBox::currentTextChanged, this, [&](QString text){
        m_pCBSwitchAnimation = new QPropertyAnimation(this, "cbSwitchWidth");
        m_pCBSwitchAnimation->setDuration(500);
        switch (ui->cb_switch->currentData().toInt())
        {
        case 0:
            m_pCBSwitchAnimation->setEndValue(140);
            m_cbSwitchLastWith = 140;
            break;
        case 1:
            m_pCBSwitchAnimation->setEndValue(190);
            m_cbSwitchLastWith = 190;
            break;
        case 2:
            m_pCBSwitchAnimation->setEndValue(140);
            m_cbSwitchLastWith = 140;
            break;
        case 3:
            m_pCBSwitchAnimation->setEndValue(100);
            m_cbSwitchLastWith = 100;
            break;
        default:
            return ;
            break;
        }

        m_pCBSwitchAnimation->setEasingCurve(QEasingCurve::InCubic);
        m_pCBSwitchAnimation->start();
    });

    connect(m_pMenuItemGroup, &MenuItemGroup::signalSendClicked, this, [&](quint8 id){
        switch (id)
        {
        case 0:
        {
            ui->stackedWidget_midCenter->setCurrentIndex(0);
            break;
        }
        case 4:
        {
            m_pCustomMessageBox->setWindowTitle("Warning!");
            m_pCustomMessageBox->setText(QStringLiteral("你干嘛，哎哟~!"));
            QPoint pos = mapToGlobal(ui->widget_effect->geometry().topLeft());
            int ret = m_pCustomMessageBox->exec(pos);
            break;
        }
        case 5:
        {
            m_pCustomMessageBox->setWindowTitle("Warning!");
            m_pCustomMessageBox->setText(tr("ni gan ma, ai yo~!"));
            QPoint pos = mapToGlobal(ui->widget_effect->geometry().topLeft());
            int ret = m_pCustomMessageBox->exec(pos);
            break;
        }
        case 6:
        {
            m_pCustomMessageBox->setWindowTitle("Warning!");
            m_pCustomMessageBox->setText(tr("What are you doing, ouch~!"));
            QPoint pos = mapToGlobal(ui->widget_effect->geometry().topLeft());
            int ret = m_pCustomMessageBox->exec(pos);
            break;
        }
        default:
            break;
        }
    });

    connect(m_pAnimation, &QPropertyAnimation::finished, this, [&]{
        QApplication::exit();
    });

    connect(m_pFunctionOne, &QAction::triggered, this, [&]{
        ui->stackedWidget_midCenter->setCurrentIndex(1);
    });
}

int MainWin::getCbSwitchWidth()
{
    return ui->widget_comboBox->width();
}

void MainWin::setCbSwitchWidth(int width)
{
    ui->widget_comboBox->setFixedWidth(width);
}

void MainWin::setCursorType(Example1::RectRegionType type)
{
    if(type == Example1::RectTopLeft || type == Example1::RectBottomRight)
        this->setCursor(Qt::SizeFDiagCursor);
    else if(type == Example1::RectTopRight || type == Example1::RectBottomLeft)
        this->setCursor(Qt::SizeBDiagCursor);
    else if(type == Example1::RectLeft || type == Example1::RectRight)
        this->setCursor(Qt::SizeHorCursor);
    else if(type == Example1::RectTop || type == Example1::RectBottom)
        this->setCursor(Qt::SizeVerCursor);
    else
        this->setCursor(Qt::ArrowCursor);
}

qint8 MainWin::getRectRegion(QPoint p)
{
    qint8 row = p.x() < WINMARGIN ? 1 : (p.x() > width() - WINMARGIN ? 3 : 2);
    if(p.y() < WINMARGIN)
        return 10 + row;
    else if(p.y() < height() - WINMARGIN)
        return 20 + row;
    else
        return 30 + row;
}

void MainWin::winMaximized()
{
    if(!this->isMaximized())
    {
        this->showMaximized();
    }
    else
    {
        this->showNormal();
    }
}

void MainWin::tbMaxChangedStyle()
{
    QString style;
    if(this->isMaximized())
    {
        QFile qssFile(":/QSS/tb_squaresStyle.qss");
        qssFile.open(QFile::ReadOnly);
        style = qssFile.readAll();
    }
    else
    {
        QFile qssFile(":/QSS/tb_maximizeStyle.qss");
        qssFile.open(QFile::ReadOnly);
        style = qssFile.readAll();
    }
    ui->tb_maximize->setStyleSheet(style);
}

void MainWin::fadeOut(const int &millisecond)
{
    m_pAnimation->setDuration(millisecond);
    m_pAnimation->setStartValue(1);
    m_pAnimation->setEndValue(0);
    m_pAnimation->start();
}

QObjectList MainWin::getAllUIObj(QObject *parent)
{
    QObjectList listOfChildren, listTemp;
    if(parent)
    {
        listOfChildren = parent->children();
    }
    if(listOfChildren.isEmpty())
        return listOfChildren;

    listTemp = listOfChildren;
    foreach(auto *obj, listTemp)
    {
        if(obj->metaObject()->className() == QStringLiteral("QWidget")
            || obj->metaObject()->className() == QStringLiteral("QFrame"))
        {
            QObjectList list = getAllUIObj(obj);
            if(!list.isEmpty())
            {
                foreach(auto *obj2, list)
                {
                    if(obj2->metaObject()->className() == QStringLiteral("QWidget")
                        || obj2->metaObject()->className() == QStringLiteral("QFrame"))
                            listOfChildren.append(obj2);
                }
            }
        }
    }
    return listOfChildren;
}

void MainWin::mouseMoveEvent(QMouseEvent *event)
{
    // 解决underMouse在拖动的情况下，可能不会更新, 一直为false
    ui->cb_switch->setAttribute(Qt::WA_UnderMouse, qApp->widgetAt(QCursor::pos()) == ui->cb_switch);
    ui->cb_switch->update();

    if(event->buttons() == Qt::LeftButton && m_isLeftButtonPress
        && !ui->widget_ItemGroup->underMouse()
        && !ui->cb_switch->underMouse())
    {
        if(this->isMaximized())
        {
            int w = this->width();
            int h = this->height();
            this->showNormal();
            int w2 = this->width();
            int h2 = this->height();
            this->move(event->globalPos() - QPoint(event->pos().x() * w2*1.0 / w, event->pos().y() * h2*1.0 / h));
        }
        else
        {
            QPoint p = event->globalPos() - m_dragStartPoint;
            if(m_rectRegion == Example1::RectCenter)
            {
                this->move(p + this->pos());
            }
            else
            {
                auto geo = this->geometry();
                if(m_rectRegion == Example1::RectTopLeft)
                    geo.setTopLeft(geo.topLeft() + p);
                else if(m_rectRegion == Example1::RectTopRight)
                    geo.setTopRight(geo.topRight() + p);
                else if(m_rectRegion == Example1::RectBottomLeft)
                    geo.setBottomLeft(geo.bottomLeft() + p);
                else if(m_rectRegion == Example1::RectBottomRight)
                    geo.setBottomRight(geo.bottomRight() + p);
                else if(m_rectRegion == Example1::RectTop)
                    geo.setTop(geo.top() + p.y());
                else if(m_rectRegion == Example1::RectLeft)
                    geo.setLeft(geo.left() + p.x());
                else if(m_rectRegion == Example1::RectRight)
                    geo.setRight(geo.right() + p.x());
                else if(m_rectRegion == Example1::RectBottom)
                    geo.setBottom(geo.bottom() + p.y());

                auto p2 = geo.bottomRight() - geo.topLeft();
                if(p2.x() > minimumWidth() && p2.y() > minimumHeight())
                {
                    this->setGeometry(geo);
                }
            }
            m_dragStartPoint = event->globalPos();
        }
    }
    else
    {
        m_rectRegion = (Example1::RectRegionType)getRectRegion(event->pos());
        setCursorType(m_rectRegion);
    }
    event->accept();
}

void MainWin::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_dragStartPoint = event->globalPos();
        m_isLeftButtonPress = true;
        m_rectRegion = (Example1::RectRegionType)getRectRegion(event->pos());

        if(!ui->le_search->underMouse())
            ui->le_search->clearFocus();

        event->accept();
    }
}

void MainWin::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_isLeftButtonPress = false;
        this->setCursor(Qt::ArrowCursor);
    }
}

void MainWin::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        if(ui->widget_midTop->underMouse())
            winMaximized();
    }
}

void MainWin::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
    {
        QApplication::exit();
    }
}

void MainWin::resizeEvent(QResizeEvent *event)
{
    if(this->isMaximized())
    {
        setContentsMargins(0,0,0,0);
        m_pCustomMessageBox->resize(ui->widget_effect->size());
    }
    else
    {
//        SIMPLEDEBUGTEST2(ui->widget_effect->size());
        setContentsMargins(20,20,20,20);
        if(m_isNotfirstDisplay)
        {
            QSize size(ui->widget_effect->size().width() - 40,
                       ui->widget_effect->size().height() - 40);
            m_pCustomMessageBox->resize(size);
            m_isNotfirstDisplay = false;
        }
        else
        {
            QSize size(ui->widget_effect->size().width(), ui->widget_effect->size().height());
            m_pCustomMessageBox->resize(size);
        }
    }

    tbMaxChangedStyle();

//    QPoint pos = mapToGlobal(ui->widget_effect->geometry().topLeft());
//    m_pCustomMessageBox->move(pos);

    event->accept();
}

void MainWin::showEvent(QShowEvent *event)
{
    ui->widget_comboBox->setFixedWidth(m_cbSwitchLastWith);

    startTimer(1000);

    event->accept();
}

bool MainWin::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->w_topLeft || watched == ui->w_topRight
        || watched == ui->w_bottomLeft || watched == ui->w_bottomRight
        || watched == ui->w_rb_light || watched == ui->w_rb_dark)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            m_pShadow->setEnabled(true);
            QWidget *w = qobject_cast<QWidget *>(watched);
            w->setGraphicsEffect(m_pShadow);
            return true;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            m_pShadow->setEnabled(false);
            return true;
        }
    }
    else if(watched == ui->w_user)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            m_pUserWidgetShadow->setEnabled(true);
            QWidget *w = qobject_cast<QWidget *>(watched);
            w->setGraphicsEffect(m_pUserWidgetShadow);
            return true;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            m_pUserWidgetShadow->setEnabled(false);
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void MainWin::timerEvent(QTimerEvent *event)
{
    QUdpSocket udpSocket;
    udpSocket.connectToHost("time.windows.com", 123);
    if(udpSocket.waitForConnected(3000))
    {
        m_pServicesCntState->setConnectState(Example1::ConnectedState);
    }
    else
    {
        m_pServicesCntState->setConnectState(Example1::UnconnectState);
    }
    event->accept();
}

