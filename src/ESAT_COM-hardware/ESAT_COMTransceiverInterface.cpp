/*
 * Copyright (C) 2020 Theia Space, Universidad Politécnica de Madrid
 *
 * This file is part of Theia Space's ESAT COM library.
 *
 * Theia Space's ESAT COM library is free software: you can
 * redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * Theia Space's ESAT COM library is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Theia Space's ESAT COM library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
 
#include "ESAT_COMTransceiverInterface.h"

ESAT_COMTransceiverInterfaceClass::ESAT_COMTransceiverInterfaceClass()
{  
}

ESAT_COMTransceiverInterfaceClass::ESAT_COMTransceiverInterfaceClass(SPIClass& spiBus, uint8_t chipSelect, uint8_t interrupt, uint8_t shutdown)
{
  transceiverSPI = &spiBus;
  chipSelectPin = chipSelect;
  interruptPin = interrupt;
  shutdownPin = shutdown;
}

// SPI public
void ESAT_COMTransceiverInterfaceClass::begin()
{
  pinMode(interruptPin, INPUT);
  pinMode(chipSelectPin, OUTPUT);
  digitalWrite(chipSelectPin, HIGH);
  transceiverSPI -> begin();
  transceiverSPI -> setClockDivider(SPI_CLOCK_DIVIDER_FOR_STM32L4);
  ctsWentHigh = 0;
}

// SPI public
uint8_t ESAT_COMTransceiverInterfaceClass::checkInterruptPin()
{
  return digitalRead(interruptPin);
}

// SPI public
void ESAT_COMTransceiverInterfaceClass::clearChipSelect()
{
  digitalWrite(chipSelectPin, HIGH);
}

// SPI public
void ESAT_COMTransceiverInterfaceClass::disable()
{
#if defined(SDN_HAS_HW_PULLUP)
      pinMode(shutdownPin, INPUT); //Let it be high at least 10 ms
#else
      digitalWrite(shutdownPin, HIGH); // So we don't get a glitch after setting pinMode OUTPUT
      pinMode(shutdownPin, OUTPUT); //Drive high 10 ms
#endif
}

// SPI public
uint8_t ESAT_COMTransceiverInterfaceClass::getInterruptPin()
{
  return interruptPin;
}

// SPI public
void ESAT_COMTransceiverInterfaceClass::powerUpTransceiver()
{  
#if defined(SDN_HAS_HW_PULLUP)
  pinMode(shutdownPin, OUTPUT); //Pull it down
  digitalWrite(shutdownPin, LOW); //Drive low least 10 ms
#else
  digitalWrite(shutdownPin, LOW); // Let it be low at leat 10 ms
#endif
  delay(10);
}

// SPI public
void ESAT_COMTransceiverInterfaceClass::readData(uint8_t command, uint8_t pollForCTS, uint8_t dataByteCount, uint8_t* data)
{
  if(pollForCTS)
  {
    while(ctsWentHigh <= 0)
    {
      requestToSend();
    }
  }
  setChipSelect();
  transceiverSPI -> transfer(command);
  SPIBulkRead(dataByteCount, data);
  DEBUG_PRINT("Low level data: ");
  DEBUG_PRINTLN(*data);
  clearChipSelect();
  setBusy();
}

// SPI public
uint8_t ESAT_COMTransceiverInterfaceClass::requestToSend()
{
  return retrieveResponse(0, 0);
}

// SPI public
void ESAT_COMTransceiverInterfaceClass::reset()
{
  powerUpTransceiver();
  delay(10);
  //. Put radio in shutdown, wait and then release.
  disable();
  delay(10); 
  powerUpTransceiver();
  delay(10);
  setBusy();
}

// SPI public
uint8_t ESAT_COMTransceiverInterfaceClass::retrieveResponse(uint8_t byteCount, uint8_t* data)
{
  uint8_t clearToSend = 0;
  uint16_t errorCounter = RADIO_CTS_TIMEOUT;
  while (errorCounter != 0)      
  {
    setChipSelect();
    transceiverSPI -> transfer(0x44);
    clearToSend = transceiverSPI -> transfer(0);
    if (clearToSend == 0xFF)
    {
      if (byteCount)
      {
        SPIBulkRead(byteCount, data);
      }
      clearChipSelect();
      break;
    }
    clearChipSelect();
    errorCounter--;
  }
  if (errorCounter == 0)
  {
    // CTS Timeout.
  }
  if (clearToSend == 0xFF)
  {    
    ctsWentHigh = 1;
  }
  return clearToSend;
}

// SPI public
void ESAT_COMTransceiverInterfaceClass::setBusy()
{
  ctsWentHigh = 0;
}

// SPI public
void ESAT_COMTransceiverInterfaceClass::setChipSelect()
{
  digitalWrite(chipSelectPin, LOW);
}

// SPI public
void ESAT_COMTransceiverInterfaceClass::SPIBulkRead(uint8_t numBytes, uint8_t* data)
{
  while (numBytes--)
  {
    *data++ = transceiverSPI -> transfer(0);
  }
}

// SPI public
void ESAT_COMTransceiverInterfaceClass::SPIBulkWrite(uint8_t numBytes, uint8_t* data)
{
  while(numBytes--)
  {
    transceiverSPI -> transfer(*data++);
  }
}

// SPI public
uint8_t ESAT_COMTransceiverInterfaceClass::SPIWriteReadByte(uint8_t toWrite)
{
  return transceiverSPI -> transfer(toWrite);
}

// SPI public
void ESAT_COMTransceiverInterfaceClass::writeCommand(uint8_t byteCount, uint8_t* data)
{
  while (ctsWentHigh <= 0)
  {
    requestToSend();
  }
  setChipSelect();
  SPIBulkWrite(byteCount, data);
  // Required due to a bug in transceiver single 
  // byte commands. Supposedly fixed in B0. 
  if (byteCount == 1)
  {
    SPIWriteReadByte(0);
  }
  clearChipSelect();
  setBusy();
}

// SPI public
uint8_t ESAT_COMTransceiverInterfaceClass::writeCommandAndRetrieveResponse(uint8_t commandByteCount, uint8_t* commandData,
                                                                        uint8_t responseByteCount, uint8_t* responseData)
{
  writeCommand(commandByteCount, commandData);
  return retrieveResponse(responseByteCount, responseData);
}

// SPI public
void ESAT_COMTransceiverInterfaceClass::writeData(uint8_t command, uint8_t pollForCTS, uint8_t dataByteCount, uint8_t* data)
{
  if(pollForCTS)
  {
    while(ctsWentHigh <= 0)
    {
        requestToSend();
    }
  }
  setChipSelect();
  transceiverSPI -> transfer(command);
  SPIBulkWrite(dataByteCount, data);
  clearChipSelect();
  setBusy();
}



ESAT_COMTransceiverInterfaceClass ReceptionTransceiverLowLevelDriver(SPI, CS_RX, INT_RX, SDN_RX);

ESAT_COMTransceiverInterfaceClass TransmissionTransceiverLowLevelDriver(SPI1, CS_TX, INT_TX, SDN_TX);