/*
 * Copyright (C) 2020, 2021 Theia Space, Universidad Politécnica de Madrid
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

#include <Arduino.h>
#include "ESAT_COMRadioStream.h"
#include "ESAT_COMTransceiverDriver.h"

int ESAT_COMRadioStreamClass::available()
{
  // If the reception buffer is empty.
  if (rxBufferAvailableBytes <= 0)
  {
    // Check if the FIFO has new data and retrieve it to
    // the driver buffer.
    if (ESAT_COMReceptionTransceiver.available() > 0)
    {
      // First byte is packet length.
      rxBufferAvailableBytes = (int) *(ESAT_COMReceptionTransceiver.nonBlockingRead());
      // Set the reading pointer to the beginning of the user data.
      lastReadByte = ESAT_COMReceptionTransceiver.nonBlockingRead() + 1;
    }
  }
  // This value is only updated if the reception buffer is empty
  // and the FIFO has new data.
  return rxBufferAvailableBytes;
}

int ESAT_COMRadioStreamClass::availableWrite()
{
  return (int) ESAT_COMTransmissionTransceiver.available();
}

void ESAT_COMRadioStreamClass::begin()
{
  beginReading();
  beginWriting();
}

// Begin reception.
void ESAT_COMRadioStreamClass::beginReading()
{
  rxBufferAvailableBytes=0;
}

// Begin transmission.
void ESAT_COMRadioStreamClass::beginWriting()
{
  initializeTXBuffer(DEFAULT_TX_BUFFER_VALUE);
  flush();
}

// Useless function. All the writings flush the buffer and this buffer
// is not accessible outside.
void ESAT_COMRadioStreamClass::flush()
{
  // May go wrong if transmitter is busy.
  ESAT_COMTransmissionTransceiver.nonBlockingWrite(txBuffer);
}

void ESAT_COMRadioStreamClass::initializeTXBuffer(byte initValue)
{
  for (unsigned int index=1;
       index < ESAT_COMTransceiverDriverClass::RADIO_MAX_PACKET_LENGTH;
       ++index)
  {
    txBuffer[index]=initValue;
  }
}

int ESAT_COMRadioStreamClass::peek ()
{
  // If there are available bytes in either the reception buffer or the FIFO.
  if (available() > 0)
  {
    return (int) *lastReadByte;
  }
  return -1;
}

int ESAT_COMRadioStreamClass::read()
{
  // Peek a single byte and check if it is not the "no available" value.
  int currentByte = peek();
  if (currentByte < 0)
  {
    return -1;
  }
  --rxBufferAvailableBytes; // Decrement unread counter.
  ++lastReadByte; // Increment read pointer.
  // Truncate negative values to -1 to avoid an integer overflow.
  if (rxBufferAvailableBytes < 0)
  {
    rxBufferAvailableBytes = -1;
  }
  return currentByte;
}

size_t ESAT_COMRadioStreamClass::read(ESAT_Buffer& inputBuffer)
{
  unsigned long readCounter;
  // Read and write into the inputBuffer as many received bytes as possible.
  for (readCounter = 0; available() > 0 && inputBuffer.capacity() > inputBuffer.length(); ++readCounter)
  {
    const int receivedData = read();
    if (receivedData < 0)
    {
      return (size_t) readCounter;
    }
    inputBuffer.write((byte) receivedData);
  }
  return (size_t) readCounter;
}

size_t ESAT_COMRadioStreamClass::write (byte datum)
{
  // If a transmission is pending nothing is written.
  if (ESAT_COMTransmissionTransceiver.available() <= 0)
  {
    return 0;
  }
  initializeTXBuffer(DEFAULT_TX_BUFFER_VALUE);
  txBuffer[0]=1; // First byte is length.
  txBuffer[1]=datum;
  // If the transmission goes wrong (because the transceiver
  // is badly configured or shut down).
  if (ESAT_COMTransmissionTransceiver.nonBlockingWrite(txBuffer)!=ESAT_COMTransceiverDriverClass::noError)
  {
    return 0;
  }
  return 1;
}

size_t ESAT_COMRadioStreamClass::write(const byte *buffer, size_t size)
{
  unsigned int index;
  // Copy the data to the transmission buffer.
  for (index=0;
       (size_t) index < size && index < (ESAT_COMTransceiverDriverClass::RADIO_MAX_PACKET_LENGTH-1);
       ++index)
  {
    txBuffer[index + 1] = buffer[index];
  }
  txBuffer[0] = index; // Set the length field.
  if ((ESAT_COMTransmissionTransceiver.available() <= 0) || (index == 0))
  {
    return 0;
  }

  if (ESAT_COMTransmissionTransceiver.nonBlockingWrite(txBuffer)!= ESAT_COMTransceiverDriverClass::noError)
  {
    return 0;
  }
  return index;
}

signed char ESAT_COMRadioStreamClass::write(ESAT_Buffer& outputBuffer)
{
  // Store the source buffer initial position.
  const unsigned long initialPosition = outputBuffer.position();
  unsigned int index;
  // Copy data to txBuffer.
  for (index = 0; outputBuffer.availableBytes() > 0 && index < (ESAT_COMTransceiverDriverClass::RADIO_MAX_PACKET_LENGTH-1); ++index)
  {
    txBuffer[index + 1] = outputBuffer.read();
  }
  // Set length field.
  txBuffer[0] = index;
  signed char availableBuffer = ESAT_COMTransmissionTransceiver.available();
  // If a transmission is pending or no bytes were written abort transmission.
  if (availableBuffer <= 0 || index == 0)
  {
    outputBuffer.seek(initialPosition); // Rewind source buffer.
    return availableBuffer;
  }
  // If the transmission went wrong (because the transceiver
  // is badly configured or shut down) return 0.
  if (ESAT_COMTransmissionTransceiver.nonBlockingWrite(txBuffer) != ESAT_COMTransceiverDriverClass::noError)
  {
    outputBuffer.seek(initialPosition); // Rewind source buffer.
    return 0;
  }
  outputBuffer.seek(initialPosition); // Rewind source buffer.
  return index;
}

ESAT_COMRadioStreamClass ESAT_COMRadioStream;
