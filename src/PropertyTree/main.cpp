#include "PropertyTree.h"
#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString qss;
    QFile file(":/PropertyTree/Resources/StyleSheet.css");
    if (file.open(QFile::ReadOnly))
    {
        qss = file.readAll();
    }
    a.setStyleSheet(qss);
    MainWindow w;
    w.show();
    return a.exec();
}
