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
#ifndef ESAT_COMTransceiverHAL_h
#define ESAT_COMTransceiverHAL_h

#include <Arduino.h>
#include <SPI.h>

#define SDN_HAS_HW_PULLUP

class ESAT_COMTransceiverHALClass
{    
  public:
  
  // HAL module error.
  enum TransceiverLowLevelDriverError
  {
      TRANSCEIVER_SUCCESS, // No error.
      TRANSCEIVER_CTS_TIMEOUT, // Transceiver unavailable.
      TRANSCEIVER_CHIP_ERROR, // Hardware error.
      TRANSCEIVER_COMMAND_ERROR // Wrong command format.
  };
  
  // Default constructor.
  ESAT_COMTransceiverHALClass();
  
  // Constructor of the class. Configures the interface pins
  // required to communicate to the transceiver.
  // Requires the SPI module and the pins numbers.
  ESAT_COMTransceiverHALClass(SPIClass& spiBus, 
                              byte chipSelect,
                              byte interrupt,
                              byte shutdown,
                              byte gpio0,
                              byte gpio1,
                              byte gpio2,
                              byte gpio3);
  
  // Initializes the transceiver required software and hardware.
  // This function should be called before.
  void begin();
  
  // Clears the transceiver chip select line.
  void clearChipSelect();
  
  // Clears the unsuccessful request to send counter.
  void clearRTSCounter();
  
   // Tests if the clear to send line is high (1) or low (0).
  byte checkClearToSendPin(); 
    
  // Tests if the interrupt line is high (1) or low (0).
  byte checkInterruptPin(); 
  
  // Turns the radio chip off by holding the SDN pin high.
  void disable();
  
  // Gets the interrupt pin number.
  byte getInterruptPin(); 
  
  // Dessaserts the transceiver shutdown line.
  void powerUpTransceiver();

  // Retrieves data from the transceiver. Requires the
  // command for accessing to the data, the number of bytes
  // to retreive and the data storage pointer.
  void readData(byte command, byte dataByteCount, byte* data);
  
  // Checks if transceiver is ready to accept commands.
  // Return if the transceiver is ready or not.
  byte requestToSend();
  
  // Resets the transceiver by asserting and desasserting shutdown.
  void reset();
  
  // Polls for CTS and reads the last command response.
  // Requires the response expecte length and the storage pointer.
  byte retrieveResponse(byte byteCount, byte* data);  
  
  // Sets the transceiver chip select line.
  void setChipSelect();  
  
  // Sets the maximum failed RTS threshold.
  void setRTSMaximumThreshold(unsigned long threshold);
  
  // Writes a bunch of bytes via SPI.
  // Requires the number of bytes to write and their
  // pointer location.
  void SPIBulkWrite(byte numBytes, byte* data);
  
  // Reads a bunch of bytes via SPI.
  // Requires the number of bytes to read and their
  // storaging buffer.
  void SPIBulkRead(byte numBytes, byte* data);
  
  // Writes and reads a byte to the SPI bus simultaneously.
  // Requires the byte to write and returns the read one.
  byte SPIWriteReadByte(byte toWrite);
  
  // Polls for CTS and issues a command if the transceiver
  // is ready. Requires the command length and a pointer to it.
  // WARNING, IF NO CTS EXECUTION IS HOLD IN AN INFINITE LOOP.
  void writeCommand(byte byteCount, byte* data);  
   
  // Polls for CTS, issues a command if the transceiver
  // is ready and polls for its response. Requires both the command
  // and the response expected lengths and a pointer to them.
  byte writeCommandAndRetrieveResponse(byte commandByteCount, byte* commandData,
                                          byte responseByteCount, byte* responseData);  
                                          
  // Writes data to the transceiver. Requires the
  // command for loading the data, the
  // number of bytes to write and the pointer for
  // reading the data.
  void writeData(byte command, byte dataByteCount, byte* data);
  
  // Writes a bit from a data stream to the manual transmission GPIO2.
  void writeDataStreamGPIO(byte level);
         
  private:
  
  // Delay (in us) between requests to send chekings.
  const word DELAY_BETWEEN_RTS_US = 20;
  
  // SPI clock divider value.
  // TODO
  // Test with 10
  const byte SPI_CLOCK_DIVIDER_FOR_STM32L4 = 20;
  
  // Transceiver chip select pin.
  byte chipSelectPin;
 
  // Transceiver interrupt pin.
  byte interruptPin;
  
  // Transceiver shutdown pin.
  byte shutdownPin;      
  
  // Transceiver GPIO 0 pin.
  byte gpio0Pin;
  
  // Transceiver GPIO 1 pin.
  byte gpio1Pin;
  
  // Transceiver GPIO 2 pin.
  byte gpio2Pin;
  
  // Transceiver GPIO 3 pin.
  byte gpio3Pin;
  
  // Number of requests to send before aborting communications.
  unsigned long maximumRTS = 500;
  
  // Number of RTS performed.
  unsigned long RTSCounter;

  // Pointer to the hardware SPI instance.
  SPIClass* transceiverSPI;
};

// Global instace of the reception transceiver low level driver.
extern ESAT_COMTransceiverHALClass ReceptionTransceiverLowLevelDriver;

// Global instace of the transmission transceiver low level driver.
extern ESAT_COMTransceiverHALClass TransmissionTransceiverLowLevelDriver;

#endif /*ESAT_COMTransceiverHAL_h*/