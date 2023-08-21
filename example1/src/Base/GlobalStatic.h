/***************************************************************
 * Name:        GlobalStatic.h
 * Author:      WenYi
 * Created:     2023-05-06 14:42
 ***************************************************************/

#ifndef GLOBALSTATIC_H
#define GLOBALSTATIC_H

#include "src/Base/DataType.h"

#include <QMap>
#include <QStringList>

class GlobalStatic
{
public:
    static QMap<int, QString> gs_mapTaskStateNote;
    static QMap<int, QString> gs_mapTaskPriorityNote;
};

#endif // GLOBALSTATIC_H
