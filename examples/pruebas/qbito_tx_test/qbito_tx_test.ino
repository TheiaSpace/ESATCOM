
#include <ESAT_COMTransceiverDriver.h>
#include <SPI.h> //required to allow Arduino to find the path of the low level driver for MSP430. Should be fixed.

uint8_t data_array[129];
uint8_t i;

void setup() 
{
 for (i=0; i<129; i++)
 {
  data_array[i]=i;
 }
 data_array[i]=i;
  
  delay(500);
  vSpiInitialize();    
  vRadio_Init();
}

void loop() 
{
 uint8_t data_buff=data_array[0];
 for (i=0; i<128; i++)
 {
    data_array[i]=data_array[i+1];
 }
 data_array[128]=data_buff;
 
  vRadio_StartTx(0, data_array);
  delay(1000);

}
