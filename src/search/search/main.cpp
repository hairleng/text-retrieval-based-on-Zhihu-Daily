#include "search.h"
#include <QtWidgets/QApplication>
#include "CharString.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CharString keyWords;
	keyWords = CharString(argv[0]);
	Search w(keyWords);
	w.show();
	return a.exec();
}
