/*
 * Copyright (C) 2019, 2021 Theia Space, Universidad Politécnica de Madrid
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
    // Return the number of available bytes.
    int available();

    // Check if there is possible to write any byte.
    // Return the number of bytes that can be written.
    int availableWrite();

    // Initialize the software.
    void begin();

    // Initialize only the reception software.
    void beginReading();

    // Initialize only the transmission software.
    void beginWriting();

    // Empty the transmission buffer.
    void flush();

    // Retrieve the last received byte without inecreasing
    // the reading position.
    int peek();

    // Read the last received byte and increases the reading
    // position.
    int read();

    // Read as many pending received bytes as possible and store
    // them into an ESAT_Buffer.
    // Return the number of retreived bytes.
    size_t read(ESAT_Buffer& inputBuffer);

    // Required by Stream interface.
    using Print::write;

    // Check if the transmitter is ready and then write a
    // single byte to it to inmediately transmit it.
    // Return the number of successfully written bytes (0 or 1).
    size_t write(byte datum);

    // Check if the transmitter is ready and then write up
    // to size bytes to it to inmediately start their transmission.
    // Return the number of successfully written bytes.
    size_t write(const byte *buffer, size_t size);

    // Check if the transmitter is ready and then write up
    // to ESAT_Buffer::availableBytes to it to inmediately start
    // their transmission. Return the number of successfully
    // written bytes.
    signed char write(ESAT_Buffer& outputBuffer);

  private:
    // Transmission buffer initialization value.
    const byte DEFAULT_TX_BUFFER_VALUE = 0xFF;

    // Pointer to the last read byte.
    byte* lastReadByte;

    // Number of bytes ready to be read.
    int rxBufferAvailableBytes;

    // Transmission buffer.
    byte txBuffer[ESAT_COMTransceiverDriverClass::RADIO_MAX_PACKET_LENGTH];

    // Fill the transmission buffer with the initialization value.
    void initializeTXBuffer(byte initValue);
 };

// Global instance of ESAT_COMRadioStream.
extern ESAT_COMRadioStreamClass ESAT_COMRadioStream;

#endif /* ESAT_COMRadioStream_h */
