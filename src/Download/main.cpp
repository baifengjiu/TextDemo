#include "Download.h"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
	QString qss;
	QFile file(":/Download/Resources/css.css");
	if (file.open(QIODevice::ReadOnly))
	{
		qss = file.readAll();
	}
	file.close();

	QApplication a(argc, argv);
	a.setStyleSheet(qss);
	Download w;
	w.show();
	return a.exec();
}
