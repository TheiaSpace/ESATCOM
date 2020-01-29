/*
 * Copyright (C) 2019 Theia Space, Universidad Politécnica de Madrid
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
  //DEBUG_PRINTLN("Available called");
  // If reception buffer is empty.
  if (rxBufferAvailableBytes <= 0)
  {
    //DEBUG_PRINTLN("Buffer is empty");
    // Check if the fifo has new data and retrieve it to the driver 
    // buffer.
    if (ReceptionTransceiver.available() > 0)
    {
      DEBUG_PRINTLN("........................................");
      DEBUG_PRINT("FIFO with bytes: ");
      // First byte is packet length.
      rxBufferAvailableBytes = (int) *(ReceptionTransceiver.nonBlockingRead());
      DEBUG_PRINTLN((byte) rxBufferAvailableBytes);
      // Set the reading pointer to the beginning of the user data.
      lastReadByte = ReceptionTransceiver.nonBlockingRead() + 1;
    }
  }
  // This value is only updated if reception buffer is empty and fifo
  // has new data.  
  return rxBufferAvailableBytes;
}

int ESAT_COMRadioStreamClass::availableWrite()
{
  return (int) TransmissionTransceiver.available();
}
 
 void ESAT_COMRadioStreamClass::begin()
 {
  DEBUG_PRINTLN("Starting reading");
  beginReading();
  DEBUG_PRINTLN("Starting writing");
  beginWriting();  
 } 
 
 // Begin reception.
 void ESAT_COMRadioStreamClass::beginReading()
 {
   ReceptionTransceiver.begin(ESAT_COMTransceiverDriverClass::RXInterruptsMode);
  // DEBUG_PRINTLN("Starting transceiver");
   ReceptionTransceiver.startReception();
   //DEBUG_PRINTLN("Starting reception");
   rxBufferAvailableBytes=0; 
 } 
 
 // Begin transmission.
 void ESAT_COMRadioStreamClass::beginWriting()
 {
   TransmissionTransceiver.begin(ESAT_COMTransceiverDriverClass::TXInterruptsMode);
   initializeTXBuffer(DEFAULT_TX_BUFFER_VALUE);
   flush();
 }

// Now this is useless because all writings flush the buffer and this buffer is not accessible outside.
void ESAT_COMRadioStreamClass::flush()
{
  TransmissionTransceiver.nonBlockingWrite(txBuffer); // May went wrong if transmitter is busy.
  //DEBUG_PRINTLN("Flushing");
}

void ESAT_COMRadioStreamClass::initializeTXBuffer(uint8_t initValue)
{
  for (unsigned int index=1; index < ESAT_COMTransceiverDriverClass::RADIO_MAX_PACKET_LENGTH; ++index)
  {
    txBuffer[index]=initValue;
  }  
}

int ESAT_COMRadioStreamClass::peek ()
{
  // If there are available bytes in either reception buffer or fifo.
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
  DEBUG_PRINTLN("Size_t read called");
  // Read and write into the inputBuffer as many received bytes as possible.
  for (readCounter = 0; available() > 0 && inputBuffer.capacity() > inputBuffer.length(); ++readCounter)
  {
    const int receivedData = read();
    if (receivedData < 0)
    {
      DEBUG_PRINT("ReadCounter: ");
      DEBUG_PRINTLN(readCounter);
      return (size_t) readCounter;
    }
    inputBuffer.write((uint8_t) receivedData);    
  }
  DEBUG_PRINT("ReadCounter: ");
  DEBUG_PRINTLN(readCounter);
  return (size_t) readCounter;
}

size_t ESAT_COMRadioStreamClass::write (uint8_t datum)
{  
  DEBUG_PRINTLN("Single");
  // If a transmission is pending nothing is written.
  if (TransmissionTransceiver.available() <= 0) 
  {
    return 0;
  }
  initializeTXBuffer(DEFAULT_TX_BUFFER_VALUE);
  txBuffer[0]=1;  // First byte is length.
  txBuffer[1]=datum;
  // If transmission went wrong (because transceiver is bad configured or shutdown).
  if (TransmissionTransceiver.nonBlockingWrite(txBuffer)!=ESAT_COMTransceiverDriverClass::noError) 
  {
    return 0;
  }
  return 1;
}

size_t ESAT_COMRadioStreamClass::write(const uint8_t *buffer, size_t size)
{
  DEBUG_PRINT("Array: ");
  unsigned int index;
  //DEBUG_PRINTLN("Here I am!!");
  // Copy the data to the transmission buffer.
  for (index=0; (size_t) index < size && index < (ESAT_COMTransceiverDriverClass::RADIO_MAX_PACKET_LENGTH-1); ++index)
  {
    txBuffer[index + 1] = buffer[index];
  }
  txBuffer[0] = index; //Set length field.
  DEBUG_PRINTLNFORMAT(index, DEC);
  DEBUG_PRINT("Availability: ");
  DEBUG_PRINTLNFORMAT(TransmissionTransceiver.available(), DEC);
 
  if ((TransmissionTransceiver.available() <= 0) || (index == 0))
  {
    return 0;
  }
  
  if (TransmissionTransceiver.nonBlockingWrite(txBuffer)!= ESAT_COMTransceiverDriverClass::noError)
  {
    return 0;
  }
  return index;  
}

int8_t ESAT_COMRadioStreamClass::write(ESAT_Buffer& outputBuffer)
{
  DEBUG_PRINTLN("ESAT_Buffer");
  // Store source buffer initial position.
  const unsigned long initialPosition = outputBuffer.position();
  unsigned int index;
  // Copy data to txBuffer.
  for (index = 0; outputBuffer.availableBytes() > 0 && index < (ESAT_COMTransceiverDriverClass::RADIO_MAX_PACKET_LENGTH-1); ++index) 
  {    
    txBuffer[index + 1] = outputBuffer.read();
  }
  // Set length field.
  txBuffer[0] = index; 
  int8_t availableBuffer = TransmissionTransceiver.available();  
  // If a transmission is pending or no bytes were written abort transmission.
  if (availableBuffer <= 0 || index == 0)  
  {
    outputBuffer.seek(initialPosition); // Rewind source buffer.
    return availableBuffer;
  }
  // If the transmission went wrong (because transceiver is bad configured or shutdown) return 0.
  if (TransmissionTransceiver.nonBlockingWrite(txBuffer) != ESAT_COMTransceiverDriverClass::noError)
  {
    outputBuffer.seek(initialPosition); // Rewind source buffer.
    return 0;
  }  
  outputBuffer.seek(initialPosition); // Rewind source buffer. 
  return index;  
}

ESAT_COMRadioStreamClass ESAT_COMRadioStream;
