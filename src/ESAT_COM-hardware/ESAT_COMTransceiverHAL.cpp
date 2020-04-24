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
 
#include "ESAT_COMTransceiverHAL.h"

ESAT_COMTransceiverHALClass::ESAT_COMTransceiverHALClass()
{  
}

ESAT_COMTransceiverHALClass::ESAT_COMTransceiverHALClass(SPIClass& spiBus, uint8_t chipSelect, uint8_t interrupt, uint8_t shutdown, uint8_t gpio0, uint8_t gpio1, uint8_t gpio2, uint8_t gpio3)
{
  transceiverSPI = &spiBus;
  chipSelectPin = chipSelect;
  interruptPin = interrupt;
  shutdownPin = shutdown;
  gpio0Pin = gpio0;
  gpio1Pin = gpio1;
  gpio2Pin = gpio2;
  gpio3Pin = gpio3;
}

void ESAT_COMTransceiverHALClass::begin()
{
  pinMode(interruptPin, INPUT);
  pinMode(chipSelectPin, OUTPUT);
  digitalWrite(chipSelectPin, HIGH);
  pinMode(gpio1Pin, INPUT);
  pinMode(gpio2Pin, OUTPUT);
  transceiverSPI -> begin();
  transceiverSPI -> setClockDivider(SPI_CLOCK_DIVIDER_FOR_STM32L4);
}

void ESAT_COMTransceiverHALClass::clearChipSelect()
{
  digitalWrite(chipSelectPin, HIGH);
}

void ESAT_COMTransceiverHALClass::clearRTSCounter()
{
  RTSCounter = 0;
}

uint8_t ESAT_COMTransceiverHALClass::checkClearToSendPin()
{
  return digitalRead(gpio1Pin);
}

uint8_t ESAT_COMTransceiverHALClass::checkInterruptPin()
{
  return digitalRead(interruptPin);
}

void ESAT_COMTransceiverHALClass::disable()
{
#if defined(SDN_HAS_HW_PULLUP)
      pinMode(shutdownPin, INPUT); //Let it be high at least 10 ms
#else
      digitalWrite(shutdownPin, HIGH); // So we don't get a glitch after setting pinMode OUTPUT
      pinMode(shutdownPin, OUTPUT); //Drive high 10 ms
#endif
}

uint8_t ESAT_COMTransceiverHALClass::getInterruptPin()
{
  return interruptPin;
}

void ESAT_COMTransceiverHALClass::powerUpTransceiver()
{  
#if defined(SDN_HAS_HW_PULLUP)
  pinMode(shutdownPin, OUTPUT); //Pull it down
  digitalWrite(shutdownPin, LOW); //Drive low least 10 ms
#else
  digitalWrite(shutdownPin, LOW); // Let it be low at leat 10 ms
#endif
  delay(10);
}

void ESAT_COMTransceiverHALClass::readData(uint8_t command, uint8_t dataByteCount, uint8_t* data)
{
  if (requestToSend())
  {
    setChipSelect();
    transceiverSPI -> transfer(command);
    SPIBulkRead(dataByteCount, data);
    clearChipSelect();
  }
}

uint8_t ESAT_COMTransceiverHALClass::requestToSend()
{  
  do
  {    
    if (checkClearToSendPin())
    {
      RTSCounter = 0;
      return 1;
    }
    delayMicroseconds(DELAY_BETWEEN_RTS_US);
  }
  while (++RTSCounter < maximumRTS);
  return 0;
}

void ESAT_COMTransceiverHALClass::reset()
{
  powerUpTransceiver();
  delay(10);
  // Shutdown the radio, wait and power up.
  disable();
  delay(10); 
  powerUpTransceiver();
  delay(10);
}

uint8_t ESAT_COMTransceiverHALClass::retrieveResponse(uint8_t byteCount, uint8_t* data)
{
  if (requestToSend())
  {
    setChipSelect();
    transceiverSPI -> transfer(0x44);
    transceiverSPI -> transfer(0);
    if (byteCount)
    {
      SPIBulkRead(byteCount, data);
    }
    clearChipSelect();
    return 0xFF;
  }
  return 0;
}

void ESAT_COMTransceiverHALClass::setChipSelect()
{
  digitalWrite(chipSelectPin, LOW);
}

void ESAT_COMTransceiverHALClass::setRTSMaximumThreshold(uint32_t threshold)
{
  maximumRTS = threshold;
}

void ESAT_COMTransceiverHALClass::SPIBulkRead(uint8_t numBytes, uint8_t* data)
{
  while (numBytes--)
  {
    *data++ = transceiverSPI -> transfer(0);
  }
}

void ESAT_COMTransceiverHALClass::SPIBulkWrite(uint8_t numBytes, uint8_t* data)
{
  while(numBytes--)
  {
    transceiverSPI -> transfer(*data++);
  }
}

uint8_t ESAT_COMTransceiverHALClass::SPIWriteReadByte(uint8_t toWrite)
{
  return transceiverSPI -> transfer(toWrite);
}

void ESAT_COMTransceiverHALClass::writeCommand(uint8_t byteCount, uint8_t* data)
{
  if (requestToSend())
  {
    setChipSelect();
    SPIBulkWrite(byteCount, data);
    // Required due to a bug in transceiver single 
    // byte commands. Supposedly fixed in B0. 
    if (byteCount == 1)
    {
      SPIWriteReadByte(0);
    }
    clearChipSelect();
  }
} 

uint8_t ESAT_COMTransceiverHALClass::writeCommandAndRetrieveResponse(uint8_t commandByteCount, uint8_t* commandData,
                                                                        uint8_t responseByteCount, uint8_t* responseData)
{
  writeCommand(commandByteCount, commandData);
  return retrieveResponse(responseByteCount, responseData);
}

void ESAT_COMTransceiverHALClass::writeData(uint8_t command, uint8_t dataByteCount, uint8_t* data)
{
 if (requestToSend())
 {
  setChipSelect();
  transceiverSPI -> transfer(command);
  SPIBulkWrite(dataByteCount, data);
  clearChipSelect();
 }
}

void ESAT_COMTransceiverHALClass::writeDataStreamGPIO(uint8_t level)
{
  digitalWrite(gpio2Pin, level);
}

ESAT_COMTransceiverHALClass ReceptionTransceiverLowLevelDriver(SPI, CS_RX, INT_RX, SDN_RX, GPIO0_RX, GPIO1_RX, GPIO2_RX, GPIO3_RX);

ESAT_COMTransceiverHALClass TransmissionTransceiverLowLevelDriver(SPI1, CS_TX, INT_TX, SDN_TX, GPIO0_TX, GPIO1_TX, GPIO2_TX, GPIO3_TX);