#include <QtGui/QApplication>
#include "mainwindow.h"
#include "translater.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
	Translater t;
//  w.show();
  
  return a.exec();
}
