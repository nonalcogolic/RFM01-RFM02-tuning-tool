#include "transmittercontrolpanel.h"
#include "ui_transmittercontrolpanel.h"

TransmitterControlPanel::TransmitterControlPanel(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::TransmitterControlPanel)
{
   ui->setupUi(this);
}

TransmitterControlPanel::~TransmitterControlPanel()
{
   delete ui;
}
