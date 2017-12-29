#ifndef TRANSMITTERCONTROLPANEL_H
#define TRANSMITTERCONTROLPANEL_H

#include <QWidget>

namespace Ui {
class TransmitterControlPanel;
}

class TransmitterControlPanel : public QWidget
{
   Q_OBJECT

public:
   explicit TransmitterControlPanel(QWidget *parent = 0);
   ~TransmitterControlPanel();

private:
   Ui::TransmitterControlPanel *ui;
};

#endif // TRANSMITTERCONTROLPANEL_H
