#include <QApplication>
#include <QObject>
#include "ColorGrid.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ColorGrid w;
    w.show();

    return a.exec();
}
