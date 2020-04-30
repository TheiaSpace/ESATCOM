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

ESAT_COMTransceiverHALClass::ESAT_COMTransceiverHALClass(SPIClass& spiBus,
                                                         const byte chipSelect,
                                                         const byte interrupt,
                                                         const byte shutdown,
                                                         const byte gpio0,
                                                         const byte gpio1,
                                                         const byte gpio2,
                                                         const byte gpio3)
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

byte ESAT_COMTransceiverHALClass::checkClearToSendPin()
{
  return digitalRead(gpio1Pin);
}

byte ESAT_COMTransceiverHALClass::checkInterruptPin()
{
  return digitalRead(interruptPin);
}

void ESAT_COMTransceiverHALClass::clearChipSelect()
{
  digitalWrite(chipSelectPin, HIGH);
}

void ESAT_COMTransceiverHALClass::clearRTSCounter()
{
  RTSCounter = 0;
}

void ESAT_COMTransceiverHALClass::disable()
{
#if defined(SDN_HAS_HW_PULLUP)
  // Let it be high at least 10 ms.
  pinMode(shutdownPin, INPUT);       
#else
  // We set it high first so we don't get a glitch 
  // after setting it as output (enables the weak pullup).
  digitalWrite(shutdownPin, HIGH);
  // Drive high 10 ms.
  pinMode(shutdownPin, OUTPUT);
#endif
}

byte ESAT_COMTransceiverHALClass::getInterruptPin()
{
  return interruptPin;
}

void ESAT_COMTransceiverHALClass::powerUpTransceiver()
{  
#if defined(SDN_HAS_HW_PULLUP)
  // Enable output driver (disable high impedance input).
  pinMode(shutdownPin, OUTPUT);
  // Drive it low at least 10 ms.
  digitalWrite(shutdownPin, LOW);
#else
  // Drive it low at least 10 ms.
  digitalWrite(shutdownPin, LOW);
#endif
  delay(10);
}

void ESAT_COMTransceiverHALClass::readData(byte command, 
                                           byte dataByteCount, 
                                           byte* data)
{
  if (requestToSend())
  {
    setChipSelect();
    transceiverSPI -> transfer(command);
    SPIBulkRead(dataByteCount, data);
    clearChipSelect();
  }
}

byte ESAT_COMTransceiverHALClass::requestToSend()
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
  // Ensure that reset line is set right before resetting.
  powerUpTransceiver();
  delay(10);
  // Shutdown the radio, wait and power it up.
  disable();
  delay(10); 
  powerUpTransceiver();
  delay(10);
}

byte ESAT_COMTransceiverHALClass::retrieveResponse(byte byteCount, byte* data)
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

void ESAT_COMTransceiverHALClass::setRTSMaximumThreshold(unsigned long threshold)
{
  maximumRTS = threshold;
}

void ESAT_COMTransceiverHALClass::SPIBulkRead(byte numBytes, byte* data)
{
  while (numBytes--)
  {
    *data++ = transceiverSPI -> transfer(0);
  }
}

void ESAT_COMTransceiverHALClass::SPIBulkWrite(byte numBytes, byte* data)
{
  while(numBytes--)
  {
    transceiverSPI -> transfer(*data++);
  }
}

byte ESAT_COMTransceiverHALClass::SPIWriteReadByte(byte toWrite)
{
  return transceiverSPI -> transfer(toWrite);
}

void ESAT_COMTransceiverHALClass::writeCommand(byte byteCount, byte* data)
{
  if (requestToSend())
  {
    setChipSelect();
    SPIBulkWrite(byteCount, data);
    // Required due to a bug in  the transceiver single
    // byte commands. Supposedly fixed in B0 revision.
    if (byteCount == 1)
    {
      SPIWriteReadByte(0);
    }
    clearChipSelect();
  }
} 

byte ESAT_COMTransceiverHALClass::writeCommandAndRetrieveResponse(byte commandByteCount,
                                                                     byte* commandData,
                                                                     byte responseByteCount,
                                                                     byte* responseData)
{
  writeCommand(commandByteCount, commandData);
  return retrieveResponse(responseByteCount, responseData);
}

void ESAT_COMTransceiverHALClass::writeData(byte command, byte dataByteCount, byte* data)
{
  if (requestToSend())
  {
    setChipSelect();
    transceiverSPI -> transfer(command);
    SPIBulkWrite(dataByteCount, data);
    clearChipSelect();
  }
}

void ESAT_COMTransceiverHALClass::writeDataStreamGPIO(byte level)
{
  digitalWrite(gpio2Pin, level);
}

ESAT_COMTransceiverHALClass ReceptionTransceiverLowLevelDriver(SPI, CS_RX, INT_RX, SDN_RX, GPIO0_RX, GPIO1_RX, GPIO2_RX, GPIO3_RX);

ESAT_COMTransceiverHALClass TransmissionTransceiverLowLevelDriver(SPI1, CS_TX, INT_TX, SDN_TX, GPIO0_TX, GPIO1_TX, GPIO2_TX, GPIO3_TX);