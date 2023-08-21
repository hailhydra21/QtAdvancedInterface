/***************************************************************
 * Name:        CustomMessageBox.h
 * Author:      WenYi
 * Created:     2023-05-29 22:04
 ***************************************************************/

#ifndef CUSTOMMESSAGEBOX_H
#define CUSTOMMESSAGEBOX_H

#include <QDialog>
#include <QWidget>
#include <QMouseEvent>

class QGraphicsDropShadowEffect;
class QPropertyAnimation;

namespace Ui {
class CustomMessageBox;
}

class CustomMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit CustomMessageBox(QWidget *parent = nullptr);
    ~CustomMessageBox();

    void setWindowTitle(const QString &title);
    void setIconPixmap(const QPixmap &pixmap);
    void setText(const QString &text);

    using QDialog::exec;
    int exec(const QPoint &pos);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void init();
    void createSignalConnect();

private:
    Ui::CustomMessageBox *ui;

    QGraphicsDropShadowEffect *m_pShadow;
    QPropertyAnimation *m_animation;

    bool m_isLeftButtonPress;
    QPoint m_dragStartPoint;
    QString m_styleSheet;
};

#endif // CUSTOMMESSAGEBOX_H
