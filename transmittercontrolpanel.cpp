#include "transmittercontrolpanel.h"
#include "ui_transmittercontrolpanel.h"

#include <functional>

#include "Commands/Transmitter/configurationsetting.h"
#include "Commands/Transmitter/powermanagement.h"
#include "Commands/Transmitter/frequencysetting.h"
#include "Commands/Transmitter/datarate.h"
#include "Commands/Transmitter/powersetting.h"
#include "Commands/Transmitter/sleep.h"
#include "Commands/Transmitter/lowbatteryandtxbitsync.h"
#include "Commands/Transmitter/wakeuptimer.h"
#include "Commands/Transmitter/pllsettings.h"
#include "Commands/Transmitter/datatransmit.h"
#include "Commands/Transmitter/readstatus.h"


#include "QDebug"


void checkAndSend(const QCheckBox * checkbox, const std::function<void()> & fn)
{
   if (checkbox->isChecked())
   {
      fn();
   }
}



int convertCLK(const QString clk)
{
   static const std::map<QString, int> CLKValues // RFM-02 spec
   {
      {"1"     , 0  },
      {"1.25"  , 1  },
      {"1.66"  , 2  },
      {"2"     , 3  },
      {"2.5"   , 4  },
      {"3.33"  , 5  },
      {"5"     , 6  },
      {"10"    , 7  }
   };

   const auto value = CLKValues.find(clk);
   if (value != CLKValues.cend())
   {
      return value->second;
   }

   return 1;
}


TransmitterControlPanel::TransmitterControlPanel(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::TransmitterControlPanel)
{
   ui->setupUi(this);

   connect(ui->but_send_all, SIGNAL(clicked()), this, SLOT(sendAll()));
   connect(ui->but_send_conf, SIGNAL(clicked()), this, SLOT(sendConfig()));
   connect(ui->but_send_pow_man, SIGNAL(clicked()), this, SLOT(sendPowerManagment()));
   connect(ui->but_send_work_freq, SIGNAL(clicked()), this, SLOT(sendFrequency()));
   connect(ui->but_send_datarate, SIGNAL(clicked()), this, SLOT(sendDataRate()));
   connect(ui->but_send_pow, SIGNAL(clicked()), this, SLOT(sendPowerSettings()));
   connect(ui->but_send_tx_dwake_treshold, SIGNAL(clicked()), this, SLOT(sendTXandTreshold()));
   connect(ui->but_send_sleep, SIGNAL(clicked()), this, SLOT(sendSleep()));
   connect(ui->but_send_wake, SIGNAL(clicked()), this, SLOT(sendWakeUpTime()));
   connect(ui->but_transmit_data, SIGNAL(clicked()), this, SLOT(sendDataTransmit()));
   connect(ui->but_read_status, SIGNAL(clicked()), this, SLOT(sendReadStatus()));
   connect(ui->but_send_pll, SIGNAL(clicked()), this, SLOT(sendPLLSettings()));
   connect(ui->deviation_value, SIGNAL(valueChanged(int)), ui->label_deviation, SLOT(setNum(int)));
}

TransmitterControlPanel::~TransmitterControlPanel()
{
   delete ui;
}

void TransmitterControlPanel::sendAll()
{
   checkAndSend(ui->checkbox_auto_conf, std::bind(&TransmitterControlPanel::sendConfig, this));
   checkAndSend(ui->checkbox_auto_conf, std::bind(&TransmitterControlPanel::sendPowerManagment, this));
   checkAndSend(ui->checkbox_auto_conf, std::bind(&TransmitterControlPanel::sendFrequency, this));
   checkAndSend(ui->checkbox_auto_conf, std::bind(&TransmitterControlPanel::sendDataRate, this));
   checkAndSend(ui->checkbox_auto_conf, std::bind(&TransmitterControlPanel::sendPowerSettings, this));
   checkAndSend(ui->checkbox_auto_conf, std::bind(&TransmitterControlPanel::sendTXandTreshold, this));
   checkAndSend(ui->checkbox_auto_conf, std::bind(&TransmitterControlPanel::sendSleep, this));
   checkAndSend(ui->checkbox_auto_conf, std::bind(&TransmitterControlPanel::sendWakeUpTime, this));
   checkAndSend(ui->checkbox_auto_conf, std::bind(&TransmitterControlPanel::sendPLLSettings, this));
}

void TransmitterControlPanel::sendConfig()
{
   NTransmitter::ConfigurationSetting msg;
   msg.setFrequency(NTransmitter::ConfigurationSetting::eFrequency::fr_433);
   msg.setClkFrequency(convertCLK(ui->clockOutput->currentText()));
   msg.setCrystalLoadCapasitance(ui->crystalLoadCapasitance->value());
   msg.setBandwidthSign(ui->checkbox_deviation_sign->isChecked());
   msg.setOutputBandwidth(ui->deviation_value->value() / 30 - 1);

   send(msg);
}

void TransmitterControlPanel::sendPowerManagment()
{
   NTransmitter::PowerManagement msg;

   msg.automaticOscilatorAndSynthesizer(ui->checkbox_auto_oscil_synth->isChecked());
   msg.automaticPowerAmplifter(ui->checkbox_auto_power_apl->isChecked());
   msg.activateOscillator(ui->checkBox_on_oscil->isChecked());
   msg.activateSynthesizer(ui->checkBox_on_synth->isChecked());
   msg.activateAmplifter(ui->checkBox_on_amplifter->isChecked());
   msg.activateLowBatteryDetector(ui->checkbox_enLowBtatery->isChecked());
   msg.activateWakeUpTimer(ui->checkbox_en_wakeUp->isChecked());
   msg.disableClockOut(ui->checkBox_disable_clock_output->isChecked());

   send(msg);
}

void TransmitterControlPanel::sendFrequency()
{
   NTransmitter::FrequencySetting msg;
   msg.setFrequency(ui->lineEdit_work_freq->text().toInt());

   send(msg);
}

void TransmitterControlPanel::sendDataRate()
{
   NTransmitter::DataRate msg;
   msg.setDataRate(ui->lineEdit_data_rate->text().toInt());

   send(msg);
}

void TransmitterControlPanel::sendPowerSettings()
{
   NTransmitter::PowerSetting msg;
   msg.setOutputPower(ui->spinBox_power->value() / 3);

   send(msg);
}

void TransmitterControlPanel::sendTXandTreshold()
{
   NTransmitter::LowBatteryAndTXbitSync msg;
   msg.setTresholdValue( ui->treshold->value());
   msg.enableTXSyncr(ui->checkBox_en_tx->isChecked());
   msg.disableWakeTimerColibration(ui->checkBox_disableWakeUpSync->isChecked());

   send(msg);
}

void TransmitterControlPanel::sendSleep()
{
   NTransmitter::Sleep msg;
   msg.setSleepAfter(ui->lineEdit_sleep_periods->text().toInt());

   send(msg);
}

void TransmitterControlPanel::sendWakeUpTime()
{
   NTransmitter::WakeUpTimer msg;
   msg.setPeriod(ui->lineEdit_wakeUp_mantis->text().toInt(), ui->lineEdit_wakeUp_pow->text().toInt());
   send(msg);
}

void TransmitterControlPanel::sendDataTransmit()
{
   if (ui->checkBox_FSK->isChecked())
   {
      ui->checkbox_auto_oscil_synth->setChecked(false);
      ui->checkbox_auto_power_apl->setChecked(false);
      ui->checkBox_on_amplifter->setChecked(true);
      ui->checkBox_on_oscil->setChecked(true);
      ui->checkBox_on_synth->setChecked(true);
      sendPowerManagment();
   }
   else
   {
      NTransmitter::DataTransmit msg;
      send(msg);
   }
}

void TransmitterControlPanel::sendReadStatus()
{
   NTransmitter::ReadStatus msg;
   emit readStatus(msg());
}

void TransmitterControlPanel::sendPLLSettings()
{
   NTransmitter::PLLSettings msg;
   msg.setPllValue(ui->comboBox_PLL->currentText().toDouble() * 1000 - 1);
   send(msg);
}


void TransmitterControlPanel::dataTransmitionFinished(const bool throughTheFSK)
{
   if (throughTheFSK)
   {
      ui->checkbox_auto_oscil_synth->setChecked(false);
      ui->checkbox_auto_power_apl->setChecked(false);
      ui->checkBox_on_amplifter->setChecked(false);
      ui->checkBox_on_oscil->setChecked(false);
      ui->checkBox_on_synth->setChecked(false);
      sendPowerManagment();
      sendReadStatus();
   }
   else
   {
      //TODO: maybe not need
      sendReadStatus();
   }
}

void TransmitterControlPanel::statusReceived(const QString & data)
{
   ui->lineEdit_status->setText(data);
}

void TransmitterControlPanel::send(const ACommands & cmd)
{
   const auto bytes = cmd();
   QString string;
   for (auto bit : bytes)
      string += bit ? "1" : "0";

   qDebug() << string;

   emit sendCommand(bytes);
}
