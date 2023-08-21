/***************************************************************
 * Name:        HomePage.h
 * Author:      WenYi
 * Created:     2023-08-10 16:37
 ***************************************************************/

#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QList>
#include <QVBoxLayout>

class CustomCard;

namespace Ui {
class HomePage;
}

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

private:
    void init();
    void createSignalConnect();
    void tempTest();

private:
    Ui::HomePage *ui;

    QList<QVBoxLayout *> m_listVBLayout;
    QList<CustomCard *> m_listCard;
};

#endif // HOMEPAGE_H
