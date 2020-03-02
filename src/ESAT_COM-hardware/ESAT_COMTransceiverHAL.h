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
  enum TransceiverLowLevelDriverError
  {
      TRANSCEIVER_SUCCESS,
      TRANSCEIVER_CTS_TIMEOUT,
      TRANSCEIVER_CHIP_ERROR,
      TRANSCEIVER_COMMAND_ERROR
  };
  
  // Default constructor.
  ESAT_COMTransceiverHALClass();
  
  // Constructor of the class. Configures the interface pins
  // required to communicate to the transceiver.
  ESAT_COMTransceiverHALClass(SPIClass& spiBus, uint8_t chipSelect, uint8_t interrupt, uint8_t shutdown, uint8_t gpio0, uint8_t gpio1, uint8_t gpio2, uint8_t gpio3);
  
  // Initializes the transceiver required software and hardware.
  // This function should be called before anything.
  void begin();
  
  // Clears the transceiver chip select line.  
  void clearChipSelect();
  
  // Clears the unsuccessful request to send counter.
  void clearRTSCounter();
  
   // Tests if the clear to send line is high (1) or low (0).
  uint8_t checkClearToSendPin(); 
    
  // Tests if the interrupt line is high (1) or low (0).
  uint8_t checkInterruptPin(); 
  
  // Turns the radio chip off by holding the SDN pin high.
  void disable();
  
  // Gets the interrupt pin number.
  uint8_t getInterruptPin(); 
  
  // Dessaserts the transceiver shutdown line.
  void powerUpTransceiver();

  // Retrieves data from the transceiver. Requires the
  // command for accessing the data, the number of bytes
  // to retreive and the pointer for storing the data.
  void readData(uint8_t command, uint8_t dataByteCount, uint8_t* data);
  
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
  
  // Sets the maximum failed RTS threshold.
  void setRTSMaximumThreshold(uint32_t threshold);
  
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
  uint8_t writeCommandAndRetrieveResponse(uint8_t commandByteCount, uint8_t* commandData,
                                          uint8_t responseByteCount, uint8_t* responseData);  
                                          
  // Writes data to the transceiver. Requires the
  // command for loading the data, the
  // number of bytes to write and the pointer for 
  // reading the data.
  void writeData(uint8_t command, uint8_t dataByteCount, uint8_t* data);
  
  // Writes a bit from a data stream to the manual transmission GPIO.
  void writeDataStreamGPIO(uint8_t level);
         
  private:
  
  // Delay (in us) between requests to send chekings.
  const uint16_t DELAY_BETWEEN_RTS_US = 20;
  
  // SPI clock divider value.
  const uint8_t SPI_CLOCK_DIVIDER_FOR_STM32L4 = 10;
  
  // Transceiver chip select pin.
  uint8_t chipSelectPin;
 
  // Transceiver interrupt pin.
  uint8_t interruptPin;
  
  // Transceiver shutdown pin.
  uint8_t shutdownPin;      
  
  // Transceiver GPIO 0 pin.
  uint8_t gpio0Pin;
  
  // Transceiver GPIO 1 pin.
  uint8_t gpio1Pin;
  
  // Transceiver GPIO 2 pin.
  uint8_t gpio2Pin;
  
  // Transceiver GPIO 3 pin.
  uint8_t gpio3Pin;
  
  // Number of requests to send before aborting communications.
  uint32_t maximumRTS = 500;
  
  // Number of RTS performed.
  uint32_t RTSCounter;

  // Pointer to the hardware SPI instance.
  SPIClass* transceiverSPI;
};

// Global instace of the reception transceiver low level driver.
extern ESAT_COMTransceiverHALClass ReceptionTransceiverLowLevelDriver;

// Global instace of the transmission transceiver low level driver.
extern ESAT_COMTransceiverHALClass TransmissionTransceiverLowLevelDriver;

#endif /*ESAT_COMTransceiverHAL_h*/