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
#ifndef ESAT_COMTransceiverInterface_h
#define ESAT_COMTransceiverInterface_h

#include <Arduino.h>
#include <SPI.h>

class ESAT_COMTransceiverInterfaceClass
{    
  public:  
  enum TransceiverLowLevelDriverError
  {
      TRANSCEIVER_SUCCESS,
      TRANSCEIVER_NO_PATCH,
      TRANSCEIVER_CTS_TIMEOUT,
      TRANSCEIVER_PATCH_FAIL,
      TRANSCEIVER_COMMAND_ERROR
  };
  
  // Default constructor.
  ESAT_COMTransceiverInterfaceClass();
  
  // Constructor of the class. Configures the interface pins
  // required to communicate to the transceiver.
  ESAT_COMTransceiverInterfaceClass(SPIClass& spiBus, uint8_t chipSelect, uint8_t interrupt, uint8_t shutdown);
  
  // Initializes the transceiver required software and hardware.
  // This function should be called before anything.
  void begin();
   
  // Tests if the interrupt line is high (1) or low (0).
  uint8_t checkInterruptPin(); 
  
  // Clears the transceiver chip select line.  
  void clearChipSelect();
  
  // Turns the radio chip off by holding the SDN pin high.
  void disable();
  
  // Gets the interrupt pin number.
  uint8_t getInterruptPin(); 
  
  // Dessaserts the transceiver shutdown line.
  void powerUpTransceiver();

  // Retrieves data from the transceiver. Requires the
  // command for accessing the data, the flag for waiting 
  // for a valid CTS before starting the retrival, the
  // number of bytes to retreive and the pointer for 
  // storing the data.
  void readData(uint8_t command, uint8_t pollForCTS, uint8_t dataByteCount, uint8_t* data);
  
  // Checks if transceiver is ready to accept commands.
  // Also updates ctsWentHigh flag.
  // Return if the transceiver is ready or not.
  uint8_t requestToSend();
  
  // Resets the transceiver by asserting and desasserting shutdown.
  void reset();
  
  // Polls for CTS and reads the last command response.
  // Requires the response expecte length and the storage pointer.
  uint8_t retrieveResponse(uint8_t byteCount, uint8_t* data);  
  
  // Sets the transceiver chip select line.
  void setChipSelect();  
  
  // Clears the ctsWentHigh latched value.
  void setBusy();

 // Writes a bunch of bytes via SPI.
  // Requires the number of bytes to write and their
  // location.
  void SPIBulkWrite(uint8_t numBytes, uint8_t* data);
  
  // Reads a bunch of bytes via SPI.
  // Requires the number of bytes to read and their
  // storageing buffer.
  void SPIBulkRead(uint8_t numBytes, uint8_t* data);
  
  // Writes and reads a byte to the SPI bus simultaneously.
  // Requires the byte to write and returns the read one.
  uint8_t SPIWriteReadByte(uint8_t toWrite);
  
  // Polls for CTS and issues a command if the transceiver
  // is ready. Requires the command length and a pointer to it.
  // WARNING, IF NO CTS EXECUTION IS HOLD IN AN INFINITE LOOP.
  void writeCommand(uint8_t byteCount, uint8_t* data);  
   
  // Polls for CTS, issues a command if the transceiver
  // is ready and polls for its response. Requires both the command
  // and the response expected lengths and a pointer to them.
  // WARNING, IF NO CTS EXECUTION IS HOLD IN AN INFINITE LOOP.
  uint8_t writeCommandAndRetrieveResponse(uint8_t commandByteCount, uint8_t* commandData,
                                          uint8_t responseByteCount, uint8_t* responseData);  
                                          
  // Writes data to the transceiver. Requires the
  // command for loading the data, the flag for waiting 
  // for a valid CTS before starting the writing, the
  // number of bytes to write and the pointer for 
  // reading the data.
  void writeData(uint8_t command, uint8_t pollForCTS, uint8_t dataByteCount, uint8_t* data);
         
  private:
  
  // Number of requests to send before aborting communications.
  const uint16_t RADIO_CTS_TIMEOUT = 10000;
  
  // SPI clock divider value.
  const uint8_t SPI_CLOCK_DIVIDER_FOR_STM32L4 = 10;
  
  // Transceiver chip select pin.
  uint8_t chipSelectPin;

  // Used for latching the last CTS.
  uint8_t ctsWentHigh = 0;

  // Pointer to the transceiver SPI instance.
  SPIClass* transceiverSPI;
 
  // Transceiver interrupt pin.
  uint8_t interruptPin;
  
  // Transceiver shutdown pin.
  uint8_t shutdownPin;      
};

// Global instace of the reception transceiver low level driver.
extern ESAT_COMTransceiverInterfaceClass ReceptionTransceiverLowLevelDriver;

// Global instace of the transmission transceiver low level driver.
extern ESAT_COMTransceiverInterfaceClass TransmissionTransceiverLowLevelDriver;

#endif /*ESAT_COMTransceiverInterface_h*/