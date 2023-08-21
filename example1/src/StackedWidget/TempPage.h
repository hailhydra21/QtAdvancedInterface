/***************************************************************
 * Name:        TempPage.h
 * Author:      WenYi
 * Created:     2023-08-10 16:37
 ***************************************************************/

#ifndef TEMPPAGE_H
#define TEMPPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QList>

class CustomProgressBar;

namespace Ui {
class TempPage;
}

class TempPage : public QWidget
{
    Q_OBJECT

public:
    explicit TempPage(QWidget *parent = nullptr);
    ~TempPage();

protected:
    void showEvent(QShowEvent *event);

private:
    void init();

private:
    Ui::TempPage *ui;

    QList<CustomProgressBar *> m_listProgress;
    QList<QVBoxLayout *> m_listLayout;
};

#endif // TEMPPAGE_H
