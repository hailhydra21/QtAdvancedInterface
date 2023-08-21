/***************************************************************
 * Name:        CustomMessageBox.cpp
 * Author:      WenYi
 * Created:     2023-05-29 22:04
 ***************************************************************/

#include "CustomMessageBox.h"
#include "ui_CustomMessageBox.h"

#include <QFile>
#include <QImage>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>

CustomMessageBox::CustomMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomMessageBox)
{
    ui->setupUi(this);

    m_animation = new QPropertyAnimation(this, "geometry");
    m_animation->setEasingCurve(QEasingCurve::InOutSine);

    init();
}

CustomMessageBox::~CustomMessageBox()
{
    delete ui;
}

void CustomMessageBox::init()
{
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    //使用本地qss文件对界面进行样式设置
    QFile qssFile(":/QSS/CustomMessageBoxWarning.qss");
    qssFile.open(QFile::ReadOnly);
    m_styleSheet = qssFile.readAll();
    this->setStyleSheet(m_styleSheet);
    qssFile.close();

    QImage image(":/Images/warning.png");
    setIconPixmap(QPixmap::fromImage(image));

    setWindowTitle("Warning!");
    setText(QStringLiteral("用心灵才能洞察一切!"));

    createSignalConnect();
}

void CustomMessageBox::createSignalConnect()
{
    connect(ui->tb_accept, &QToolButton::clicked, this, &CustomMessageBox::accept);
    connect(ui->tb_cancel, &QToolButton::clicked, this, &CustomMessageBox::close);
}

void CustomMessageBox::setWindowTitle(const QString &title)
{
    ui->label_title->setText(title);
}

void CustomMessageBox::setIconPixmap(const QPixmap &pixmap)
{
    ui->label_ico->setPixmap(pixmap.scaled(ui->label_ico->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void CustomMessageBox::setText(const QString &text)
{
    ui->label_content->setText(text);
}

int CustomMessageBox::exec(const QPoint &pos)
{
    move(pos);

    return exec();
}

void CustomMessageBox::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton && m_isLeftButtonPress)
    {
        QPoint p = event->globalPos() - m_dragStartPoint;
#ifdef DevelopAndTest
        this->move(p + this->pos());
#endif
        m_dragStartPoint = event->globalPos();
    }
}

void CustomMessageBox::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_dragStartPoint = event->globalPos();
        m_isLeftButtonPress = true;

        event->accept();
    }
}

void CustomMessageBox::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_isLeftButtonPress = false;
        this->setCursor(Qt::ArrowCursor);
    }
}

void CustomMessageBox::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        if(ui->tb_accept->hasFocus())
            accept();
        else if(ui->tb_cancel->hasFocus())
            close();
    }
    QDialog::keyPressEvent(event);
}


