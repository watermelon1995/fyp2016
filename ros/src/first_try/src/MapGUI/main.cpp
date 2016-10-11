#include "mapgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mapGUI w;
    w.show();

    return a.exec();
}
