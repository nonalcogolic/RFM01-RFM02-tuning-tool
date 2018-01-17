
#include <qapplication.h>
#include "receivercontrolpanel.h"


int main(int argn, char ** argv)
{
   QApplication application(argn, argv);

   ReceiverControlPanel receiverControlPanel;
   receiverControlPanel.show();

   return application.exec();
}
