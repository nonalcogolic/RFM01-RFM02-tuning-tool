# RFM-01 and RFM-02 Tuning tool for raspberry pi

### Very-very important details:

Events like level detect and edge detection status freeze the raspberry. To resolve it you would need to put next line into /boot/config.txt :

dtoverlay=gpio-no-irq

### HOW to make sure both (receiver and transmitter) are working and successfully receives the command, and status has been read correctly?

Idea is to use wake up command : set wake up period, enable timer, wait for reaction, check the status.
Timer both: E000
12:8 R
0:7 M
M*2^R ms

Enable wake in tr PWMN | 2
Enable wake in rc PWMN | 0x0200  //beaware: value of register are always overriden, it's need to set it again every SW restart

E0FF

FF00 - reset chip (RFM-01)


RFM-02:
DisableWakeUpSync - if 1, multyple sleep cycle on 10. 
Example DisableWakeUpSync = 1; M=250, R=3  WakeUp period will be equal 0,25 * 8 * 10 = 20 sec
        DisableWakeUpSync = 0; M=250, R=3  WakeUp period will be equal 0,25 * 8 * 10 = 20 sec


// ~70/110 bps
Read status
Send Sleep (wakeUp disabled  earlier: E000) ,
Send enable a1 and a0 (instead +-Send all )
Send data
On oscilator


// ~70 bps

Read status
Send Sleep (wakeUp disabled  earlier: E000) ,
Send enable a1 and a0 (instead +-Send all )
On oscilator
Send data


### TX should be stoped with sleep or PWMN, could be not stoped at all (90% sure)
should be handled manualy


### FULL TRANSMITTION CYCLE:

1) Send default settings with "send all" to transmitter and mentioned bellow order for the receiver:
- Config
- Frequency
- Datarate
- AFC
- Data filter
- Receiver settings (off receiver)
- Fifo disable (both checkboxes)
- Fifo enable (both checkboxes)
- Receiver settings (on receiver)

For the transmitter enable all oscil, synth and ampl and enable FSK
Send transmit.
In case of success - FIFO IT checkbox will become checked.

To read out message press "Read status". Text edit will show current state of RFM-01 with 8 bits transmitted data in the end of sequence.
2) restart: SW restart for the receiver, sleep for transmitter
Other option to is to allow RFM-01 to get a new messages is to repeat the steps bellow:
- Receiver settings (off receiver)
- Fifo disable (both checkboxes)
- Fifo enable (both checkboxes)
- Receiver settings (on receiver)

//Transmiter stable rate:
Used params 4800, SDI source selected, internal caps 15,5, Data transmit command modified with the data size (!)
1) Disable a1, a0, ex, es, ea
2) Send
3) To reload: set ex=0, then ex=1
4) again posible to get stable bitrate

### Quick config of RFM-01 (receiver): 
Just press the "Send all selected (auto config)". 
This button will send all necessary for default configuration messages to your RFM-01 module and uncheck "auto read when received" flag. 
This is required to avoid infinite loop when  very first FIFO IT will be rised. 
Once FIFO IT will be shown checked you can enable this flag if it's needed for the session. 


Say me thanks: 
ETH: 
0x4a5734a52fe9fabcd370651de5d418e22342ff59

