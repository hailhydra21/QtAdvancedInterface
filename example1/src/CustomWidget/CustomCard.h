/***************************************************************
 * Name:        CustomCard.h
 * Author:      WenYi
 * Created:     2023-08-10 16:27
 ***************************************************************/

#ifndef CUSTOMCARD_H
#define CUSTOMCARD_H

#include "src/Base/DataType.h"

#include <QWidget>

class CustomUserList;

namespace Ui {
class CustomCard;
}

class CustomCard : public QWidget
{
    Q_OBJECT

public:
    explicit CustomCard(QWidget *parent = nullptr);
    CustomCard(Example1::TaskCardData cardData, QWidget *parent = nullptr);
    ~CustomCard();

    void setTaskData(Example1::TaskCardData cardData);
    void setTitel(QString str);
    void setDescription(QString str);
    void setState(Example1::TaskStateType state);
    void setPriority(Example1::TaskPriorityType priority);
    void setCreationTime(QDateTime t);
    void setCollect(bool isCollect);

    void setUserList(const QStringList &pathList);
    void setPM(QString path);

    void refresh();

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    void init();
    void createSignalConnect();

private:
    Ui::CustomCard *ui;
    CustomUserList *m_pCustomUserList;

    Example1::TaskCardData m_cardData;
};

#endif // CUSTOMCARD_H
