#include "BankApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	BankApp w;
	//QtClientClass clientUI;
	//QObject::connect(&w, SIGNAL(emitUserName(QString)), &clientUI, SLOT(getUserName(QString)));
	w.show();
	return a.exec();
}
