
#include <qapplication.h>
#include "receivercontrolpanel.h"
#include "applicationcontroller.h"


int main(int argn, char ** argv)
{
   QApplication application(argn, argv);

   ApplicationController controller;

   return application.exec();
}
