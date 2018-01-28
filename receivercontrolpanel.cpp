#include "receivercontrolpanel.h"
#include "ui_receivercontrolpanel.h"

#include "CBroadcomPinout.h"
#include "cgpioevent.h"
#include "helper.h"

#include <list>

#include <qmessagebox.h>
#include <qdebug.h>

#include "Commands/ACommands.h"

#include "Commands/Receiver/configurationsetting.h"
#include "Commands/Receiver/frequencysetting.h"
#include "Commands/Receiver/receiversetting.h"
#include "Commands/Receiver/wakeuptimer.h"
#include "Commands/Receiver/lowdutycycle.h"
#include "Commands/Receiver/lowbatterydetectorandclockdivider.h"
#include "Commands/Receiver/afccontrol.h"
#include "Commands/Receiver/datafilter.h"
#include "Commands/Receiver/datarate.h"
#include "Commands/Receiver/outputandfifo.h"
#include "Commands/Receiver/resetmode.h"
#include "Commands/Receiver/hwreset.h"
#include "Commands/Receiver/statusread.h"


namespace {
   void checkAndSend(const QCheckBox * checkbox, const std::function<void()> & fn)
   {
      if (checkbox->isChecked())
      {
         fn();
      }
   }
}


ReceiverControlPanel::ReceiverControlPanel(CBroadcomPinout & pinout, CGPIOEvent & events, QWidget *parent)
   : QWidget(parent)
   , ui(new Ui::ReceiverControlPanel)
   , mPinout(pinout)
   , mEvents(events)
   , mReceiver(pinout)
{
   ui->setupUi(this);

   mEvents.listenPin(ePin::nIRQ, [this](const bool state) { emit nIRQSignal(state); }, eEventType::rise);
   mEvents.listenPin(ePin::FFIT, [this](const bool state) { emit FIFO_interupt(state); }, eEventType::rise);
   mEvents.listenPin(ePin::VDI, [this](const bool state) { emit VDI_interupt(state); }, eEventType::rise);

   connect(this, SIGNAL(nIRQSignal(const bool)), this, SLOT(receiver_nIRQ(const bool)), Qt::ConnectionType::QueuedConnection);
   connect(this, SIGNAL(FIFO_interupt(const bool)), this, SLOT(receiver_FIFO_interupt(const bool)), Qt::ConnectionType::QueuedConnection);
   connect(this, SIGNAL(VDI_interupt(const bool)), this, SLOT(receiver_VDI_interupt(const bool)), Qt::ConnectionType::QueuedConnection);


   connect(ui->pushButton_send_all , SIGNAL(clicked()), this, SLOT(sendAll()));
   connect(ui->pushButton_Configuration , SIGNAL(clicked()), this, SLOT(sendConfiguration()));
   connect(ui->pushButton_frequency , SIGNAL(clicked()), this, SLOT(sendFrequency()));
   connect(ui->pushButton_receiver_settings , SIGNAL(clicked()), this, SLOT(sendReceiverSettings()));
   connect(ui->pushButton_wakeUp , SIGNAL(clicked()), this, SLOT(sendWakeUpTimer()));
   connect(ui->pushButton_low_duty , SIGNAL(clicked()), this, SLOT(sendLowDutyCycle()));
   connect(ui->pushButton_bat_and_clk_rate , SIGNAL(clicked()), this, SLOT(sendLowBattery()));
   connect(ui->pushButton_AFC , SIGNAL(clicked()), this, SLOT(sendAFC()));
   connect(ui->pushButton_data_filter , SIGNAL(clicked()), this, SLOT(sendDataFilter()));
   connect(ui->pushButton_data_rate , SIGNAL(clicked()), this, SLOT(sendDataRate()));
   connect(ui->pushButton_fifo , SIGNAL(clicked()), this, SLOT(sendFIFO()));
   connect(ui->pushButton_reset_mode , SIGNAL(clicked()), this, SLOT(sendResetMode()));
   connect(ui->pushButton_SW_reset , SIGNAL(clicked()), this, SLOT(sendReset()));
   connect(ui->pushButton_read_status, SIGNAL(clicked()), this, SLOT(sendReadstatus()));


   //ui->edit_multple_comand_rec->setText("0000 898A A7D0 C847 C69B C42A C200 C080 CE84 CE87 C081");

}

ReceiverControlPanel::~ReceiverControlPanel()
{
   delete ui;
}

void ReceiverControlPanel::sendComand(const ACommands & cmd)
{
   const auto bytes = cmd();
   QString string;
   for (auto bit : bytes)
      string += bit ? "1" : "0";

   qDebug() << "Receiver: " << string;

   mReceiver.sendComand(bytes);
}

void ReceiverControlPanel::receiver_nIRQ(const bool state)
{
   static int value= 0;
   value = (++value) % 100;
   ui->progressBar->setValue(value);
}

void ReceiverControlPanel::receiver_FIFO_interupt(const bool state)
{
   ui->checkBox_FIFO_IT->setChecked(state);
}

void ReceiverControlPanel::receiver_VDI_interupt(const bool state)
{
   ui->checkBox_VDI_IT->setChecked(state);
}

void ReceiverControlPanel::sendAll()
{
   checkAndSend(ui->checkBox_a_Configuration, std::bind(&ReceiverControlPanel::sendConfiguration, this));
   checkAndSend(ui->checkBox_a_frequency, std::bind(&ReceiverControlPanel::sendFrequency, this));
   checkAndSend(ui->checkBox_a_Receiver_setings, std::bind(&ReceiverControlPanel::sendReceiverSettings, this));
   checkAndSend(ui->checkBox_a_wakeUp, std::bind(&ReceiverControlPanel::sendWakeUpTimer, this));
   checkAndSend(ui->checkBox_a_LowDuty, std::bind(&ReceiverControlPanel::sendLowDutyCycle, this));
   checkAndSend(ui->checkBox_a_low_bat_clk_rate, std::bind(&ReceiverControlPanel::sendLowBattery, this));
   checkAndSend(ui->checkBox_a_AFC, std::bind(&ReceiverControlPanel::sendAFC, this));
   checkAndSend(ui->checkBox_a_data_filter, std::bind(&ReceiverControlPanel::sendDataFilter, this));
   checkAndSend(ui->checkBox_a_data_rate, std::bind(&ReceiverControlPanel::sendDataRate, this));
   checkAndSend(ui->checkBox_a_fifo, std::bind(&ReceiverControlPanel::sendFIFO, this));
   //checkAndSend(ui->checkBox_a_, std::bind(&ReceiverControlPanel::sendResetMode, this));
   //checkAndSend(ui->checkBox_a_, std::bind(&ReceiverControlPanel::sendReset, this));
   //checkAndSend(ui->checkBox_a_, std::bind(&ReceiverControlPanel::sendReadstatus, this));
}

void ReceiverControlPanel::sendConfiguration()
{
   auto msg = Receiver::ConfigurationSetting();
   msg.setBaseBandWidth(Receiver::baseband(ui->comboBox_bandwidth->currentText()));
   msg.setCrystalLoadCapasitance(ui->double_capacitance->value());
   msg.setFrequencyBand(Receiver::frequency(ui->comboBox_frequency_band->currentText()));
   msg.disableCLKOutput(ui->checkBox_disable_CLK->isChecked());
   msg.enableLowBatteryDetector(ui->checkBox_en_low_bat->isChecked());
   msg.enableWakeUpTimerDetector(ui->checkBox_en_wakeUp->isChecked());
   msg.enableOscilator(ui->checkBox_en_active_sleep->isChecked());


   sendComand(msg);
}

void ReceiverControlPanel::sendFrequency()
{
   auto msg = Receiver::FrequencySetting();
   msg.setFrequency(ui->lineEdit_frequency->text().toInt());
   sendComand(msg);
}

void ReceiverControlPanel::sendReceiverSettings()
{
   auto msg = Receiver::ReceiverSetting();
   msg.setLNAgain(Receiver::lnaGain(ui->comboBox_LNA_gain->currentText()));
   msg.setRSSI(Receiver::rssi(ui->comboBox_RSSI_threshold->currentText()));
   msg.setVDIsignal(Receiver::vdiSignal(ui->comboBox_VDI_cond->currentText()));
   msg.enableReceiver(ui->checkBox_en_receiver->isChecked());
   sendComand(msg);
}

void ReceiverControlPanel::sendWakeUpTimer()
{
   auto msg = Receiver::WakeUpTimer();
   msg.setPeriod(ui->lineEdit_wakeUp_M->text().toInt(), ui->lineEdit_wakeUp_R->text().toInt());
   sendComand(msg);
}

void ReceiverControlPanel::sendLowDutyCycle()
{
   auto msg = Receiver::LowDutyCycle();
   msg.setDutyCycle(ui->lineEdit_lowDutyCycle->text().toInt());
   msg.enableLowDutyCycle(ui->checkBox_en_lowDuty->isChecked());
   sendComand(msg);
}

void ReceiverControlPanel::sendLowBattery()
{
   auto msg = Receiver::LowBatteryDetectorAndClockDivider();
   msg.setOutputCLKFrequency(Receiver::clk(ui->comboBox_CLK_out->currentText()));
   msg.setTresholdValue(ui->double_battery_threshold->value());
   sendComand(msg);
}

void ReceiverControlPanel::sendAFC()
{
   auto msg = Receiver::AFCControl();
   msg.enableAFCCalculations(ui->checkBox_calculation_offset->isChecked());
   msg.enableFrequencyOffsetRegister(ui->checkBox_output_reg->isChecked());
   msg.enableHighAccuracyMode(ui->checkBox_fine_mode->isChecked());
   msg.enableStrobeEdge(ui->checkBox_strobe_edge->isChecked());
   msg.setAutomaticOperationMode(Receiver::automaticOperations(ui->comboBox_afc_mode->currentText()));
   msg.setRangeLimit(Receiver::rangeLimit(ui->comboBox_afc_range_lim->currentText()));
   sendComand(msg);
}

void ReceiverControlPanel::sendDataFilter()
{
   auto msg = Receiver::DataFilter();
   msg.enableAutoClockRecovery(ui->checkBox_clock_recovery_auto_lock->isChecked()); //todo
   msg.onClockRecovery(ui->checkBox_fast_mode->isChecked()); //todo: check
   msg.setDataFilterType(Receiver::filterType(ui->comboBox_filter_type->currentText()));
   msg.setDQDparams(ui->int_dqd_treshold->value());
   sendComand(msg);
}

void ReceiverControlPanel::sendDataRate()
{
   auto msg = Receiver::DataRate();
   msg.setDataRate(ui->lineEdit_data_rate->text().toInt());
   sendComand(msg);
}

void ReceiverControlPanel::sendFIFO()
{
   auto msg = Receiver::OutputAndFIFO();
   msg.enableFIFO(ui->checkBox_fifo_16->isChecked());
   msg.enableFifoFill(ui->checkBox_fifo_fill->isChecked());
   msg.setFIFOFillCondition(Receiver::fifoCondition(ui->comboBox_fill_condition->currentText()));
   msg.setFIFOitLevel(ui->int_fifo_IT_level->value());
   sendComand(msg);
}

void ReceiverControlPanel::sendResetMode()
{
   auto msg = Receiver::ResetMode();
   msg.disableHighlySensetiveResetMode(ui->checkBox_dis_sensetive_reset->isChecked());
   sendComand(msg);
}

void ReceiverControlPanel::sendReset()
{
   auto msg = Receiver::HWReset();
   sendComand(msg);
}

void ReceiverControlPanel::sendReadstatus()
{
   auto word = mReceiver.readStatus();

   QString result;

   for (auto symb : word)
   {
      result += (symb) ? "1" : "0";
   }

   ui->lineEdit_status->setText(result);
}




