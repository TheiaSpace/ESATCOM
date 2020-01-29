#include <ESAT_COM.h>
#include <ESAT_COM-hardware/ESAT_COMTransceiverDriver.h>

ESAT_RadioTransceiverClass TXTransceiver=ESAT_RadioTransceiverClass(TRANSCEIVERTX);
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
  TXTransceiver.begin(ESAT_RadioTransceiverClass::TXMode);

}

void loop() 
{
  TXTransceiver.write(writebuff);
  delay(1000);
}
