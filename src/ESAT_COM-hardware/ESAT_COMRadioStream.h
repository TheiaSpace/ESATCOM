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
  
 #ifndef ESAT_COMRadioStream_h
 #define ESAT_COMRadioStream_h
  
 #include <Arduino.h>
 #include <ESAT_Buffer.h>
 #include "ESAT_COMTransceiverDriver.h"
 
  // Stream interface for radio communication. 
  // Provides an abstraction layer from the radio drivers, 
  // allowing to use any other Stream interface compliant class.  
  // Transsmision and reception functionalities are grouped together.
class ESAT_COMRadioStreamClass: public Stream
 {
  
  public:  
  
  // Check if there are any bytes available to be read.
  int available();
  
  // Check if there is possible to write bytes.
  int availableWrite();
  
  // Initialize transceivers and transmission buffer.
  void begin();
  
  // Initialize only reception transceiver and buffer.
  void beginReading();
  
  // Initialize only transmission transceiver and buffer.
  void beginWriting();
  
  // Empty the transmission buffer.
  void flush();  
  
  // Retrieve last received byte without wasting it.
  int peek();
  
  // Read last received byte.
  int read();   
  
  // Read as pending received bytes as possible and store 
  // them into an ESAT_Buffer.
  // Return the number of retreived bytes.
  size_t read(ESAT_Buffer& inputBuffer);
  
  using Print::write;
  
  // Check if transmitter is ready and then write a
    // single byte to the radio and starts its transmission.
  // Return the number of successfully written bytes (0 or 1).
  size_t write(uint8_t datum);
  
  // Check if transmitter is ready and then write up 
  // to size bytes to the radio and starts its transmission.
  // Return the number of successfully written bytes.
  size_t write(const uint8_t *buffer, size_t size);

    // Check if transmitter is ready and then write up 
  // to ESAT_Buffer::availableBytes the radio and starts its transmission.
  // Return the number of successfully written bytes.
  int8_t write(ESAT_Buffer& outputBuffer);
    
  private:
  
  // Transmission buffer initialization value.
  const uint8_t DEFAULT_TX_BUFFER_VALUE = 0xFF;

  // Pointer to the last read byte.
  uint8_t* lastReadByte;
  
  // Number of bytes ready to be read.
  int rxBufferAvailableBytes;
  
  // Transmission buffer.
  uint8_t txBuffer[ESAT_COMTransceiverDriverClass::RADIO_MAX_PACKET_LENGTH];  
  
  // Fills the transmission buffer with the initialization value.
  void initializeTXBuffer(uint8_t initValue);  
  
 };
 
 //Global instance of ESATRadioStream.
 extern ESAT_COMRadioStreamClass ESAT_COMRadioStream;
 
 #endif /* ESAT_COMRadioStream_h */
 