#include <ESAT_COM.h>
#include <ESAT_COM-hardware/ESAT_COMTransceiverDriver.h>

ESAT_RadioTransceiverClass TXTransceiver=ESAT_RadioTransceiverClass(TRANSCEIVERTX);
uint8_t writebuff[256];

void setup() 
{
  Serial.begin();
  delay(1000);
  uint8_t  index;
  for(index = 0; index<255; index++)
  {
    writebuff[index]=index;
  }
  vSpiInitialize();
  TXTransceiver.begin(ESAT_RadioTransceiverClass::TXInterruptsMode);
  interrupts();
}

void loop() 
{
  TXTransceiver.write(writebuff);
  delay(1000);
}
