#include <ESAT_COMTransceiverDriver.h>
#include <SPI.h> //required to allow Arduino to find the path of the low level driver for MSP430. Should be fixed.

#define TX_BUFFER_LENGTH 129
#define RX_BUFFER_LENGTH 129

uint8_t tx_data_array[TX_BUFFER_LENGTH];
uint8_t i;

//save test

void setup() 
{
  
 //Prepare tx array 
 for (i=0; i<TX_BUFFER_LENGTH; i++)
 {
  tx_data_array[i]=i;
 }

  delay(1000);
  Serial.begin();
  delay(500);
  //Serial.println("Step 0");  
  vSpiInitialize();
  //Serial.println("Step 1");  
  //Init TX
  vRadio_Init();
  //Serial.println("Step 2"); 
  //Init RX   
  vRadio_Init_rx();
  //Serial.println("Step 3");
  vRadio_StartRX(1);
  //Serial.println("Step 4");
  vRadio_StartTx(0, tx_data_array);
}

void loop() 
{  
uint8_t rx_index;

 //Rotate data
 uint8_t data_buff=tx_data_array[0]; 
 for (i=0; i<TX_BUFFER_LENGTH-1; i++)
 {
    tx_data_array[i]=tx_data_array[i+1];
 }
 tx_data_array[TX_BUFFER_LENGTH-1]=data_buff;

 //TX data
 if (gRadio_CheckTransmitted())
 {
  //Up to 129 bytes
  vRadio_StartTx(0, tx_data_array);
 }
 //RX data
  if (gRadio_CheckReceived(&rx_index))
  {         
    for(rx_index=0; rx_index<RADIO_MAX_LONG_PACKET_LENGTH_RX_BS-1; rx_index++)
    {
      Serial.print((char)fixRadioPacket[rx_index]);      
    }
    Serial.println();    
    Serial.println("......................................................");    
    vRadio_StartRX(1);
  }
  delay(50);
}
