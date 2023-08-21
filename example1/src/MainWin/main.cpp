#include "MainWin.h"

#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font = a.font();
    font.setFamily("Bauhaus");
    font.setPointSize(12);
    a.setFont(font);

    MainWin w;
    w.show();

    return a.exec();
}
