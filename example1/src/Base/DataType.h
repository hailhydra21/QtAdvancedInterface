/***************************************************************
 * Name:        DataType.h
 * Author:      WenYi
 * Created:     2023-08-04 10:58
 ***************************************************************/

#ifndef DATATYPE_H
#define DATATYPE_H

#include <QString>
#include <QDebug>
#include <QDateTime>

#define WINMARGIN 20
#define SIMPLEDEBUGTEST qDebug() << __FUNCTION__ << __LINE__
#define SIMPLEDEBUGTEST2(s) qDebug() << __FUNCTION__ << __LINE__ << s
#define SIMPLEDEBUGTEST3(s, ss) qDebug() << __FUNCTION__ << __LINE__ << s << ss
#define SIMPLEDEBUGTEST4(s, ss, sss) qDebug() << __FUNCTION__ << s << ss << sss

namespace Example1 {

enum RectRegionType
{
    RectTopLeft = 11,
    RectTop = 12,
    RectTopRight = 13,
    RectLeft = 21,
    RectCenter = 22,
    RectRight = 23,
    RectBottomLeft = 31,
    RectBottom = 32,
    RectBottomRight = 33
};

enum MsgType
{
    Normal = 40,
    Right,
    Error,
    Warning
};

enum ConnectStateType
{
    ConnectedState = 50,
    ErrorState,
    UnconnectState
};

enum TaskStateType
{
    InProgress = 60,
    Completed,
    OffTrack
};

enum TaskPriorityType
{
    LowPriority = 70,
    NormalPriority,
    HighPriority
};

enum UserProfileType
{
    Circular = 80,
    Rectangle,
    RoundedRectangle
};

enum UserProfilePresetType
{
    Nothing = 90,
    Aatrox,
    AdaWong,
    Heisenberg,
    JonSnow,
    Mahone,
    NightKing
};

struct TaskCardData
{
    TaskCardData()
    {
        title = "Title";
        description = "description";
        state = TaskStateType::InProgress;
        priority = TaskPriorityType::NormalPriority;
        creationTime = QDateTime::currentDateTime();
        collect = false;
    }

    TaskCardData(QString t, QString d)
    {
        this->TaskCardData::TaskCardData();
        title = t;
        description = d;
    }

    TaskCardData(QString t, QString d,
                 TaskStateType state,
                 TaskPriorityType priority,
                 QDateTime creationTime = QDateTime::currentDateTime(),
                 bool collect = false)
    {
        this->TaskCardData::TaskCardData();
        title = t;
        description = d;
        this->state = state;
        this->priority = priority;
        this->creationTime = creationTime;
        this->collect = collect;
    }

    QString title;
    QString description;
    QStringList Participants;
    TaskStateType state;
    TaskPriorityType priority;
    QDateTime creationTime;
    bool collect;
    QString other;
};

}
// namespace Example1

#endif // DATATYPE_H
