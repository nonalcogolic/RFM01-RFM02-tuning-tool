
#include <qapplication.h>
#include "mainwindow.h"


int main(int argn, char ** argv)
{
   QApplication application(argn, argv);

   MainWindow mainWindow;
   mainWindow.show();

   return application.exec();
}
