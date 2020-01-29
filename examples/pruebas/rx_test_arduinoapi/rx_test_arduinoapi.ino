#include <ESAT_COM.h>
#include <ESAT_COM-hardware/ESAT_COMTransceiverDriver.h>

ESAT_RadioTransceiverClass RXTransceiver=ESAT_RadioTransceiverClass(TRANSCEIVERRX);
uint8_t writebuff[256];


extern "C" 
{
  void debug (const char* text)
  {
    Serial.println(text);
  }
}

extern "C" 
{
  void debug_2 (uint8_t* printbuf, size_t len)
  {   
    for (; len>0; --len, printbuf++)
    {
      Serial.print(*printbuf, HEX);
      Serial.print(' ');
    }
    Serial.println();
  }
}

void setup() 
{
  Serial.begin();
  delay(1000);
  const char msg[]="begin";
  debug(msg);
  uint8_t  index;
  for(index = 0; index<255; index++)
  {
    writebuff[index]=index;
  }
  vSpiInitialize();
  RXTransceiver.begin(ESAT_RadioTransceiverClass::RXMode);
  RXTransceiver.startReception();
}

void loop() 
{
  debug_2(RXTransceiver.read(), 256);
  delay(100);
}
