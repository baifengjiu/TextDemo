#include <QApplication>
#include <QObject>
#include "PaintDemo.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PaintDemo w;
    w.show();

    return a.exec();
}
