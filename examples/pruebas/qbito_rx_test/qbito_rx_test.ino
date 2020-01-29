
#include <ESAT_COMTransceiverDriver.h>
#include <SPI.h> //required to allow Arduino to find the path of the low level driver for MSP430. Should be fixed.

uint8_t data_array[256];


void setup() 
{
 
  delay(500);
  Serial.begin();
  vSpiInitialize();    
  vRadio_Init_rx();
  vRadio_StartRX(0);

  
}
void loop() 
{
  unsigned char index;
  while (!gRadio_CheckReceived(&index));
  for(index=0; index<RADIO_MAX_LONG_PACKET_LENGTH_RX_BS-1; index++)
  {
    Serial.print((char)fixRadioPacket[index], DEC);
    Serial.print(", ");
  }
  Serial.println();
  Serial.println("-----------------------------------------------------------");    
  vRadio_StartRX(0);
  delay(50);

}
