#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H


#include <QObject>

#include "receivercontrolpanel.h"
#include "transmittercontrolpanel.h"


class ApplicationController : public QObject
{
   Q_OBJECT
public:
   explicit ApplicationController(QObject *parent = nullptr);

signals:

public slots:


private:
   ReceiverControlPanel mReceiverPanel;
   TransmitterControlPanel mTransmitterPanel;
};

#endif // APPLICATIONCONTROLLER_H
