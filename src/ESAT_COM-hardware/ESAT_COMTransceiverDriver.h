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
#ifndef ESAT_COMTransceiverDriver_h
#define ESAT_COMTransceiverDriver_h

#include <Arduino.h>
#include <SPI.h>
#include "ESAT_COMTransceiverHAL.h"
#include "configurations/ESAT_COMTransceiverConfiguration.h"

// Radio communications devices driver class.
// All interactions with Si4463 rev C2A transceivers
// (either transmission or reception) are done through
// this class.
class ESAT_COMTransceiverDriverClass
{    
  public:  
    
    // Data type for the different radio data sinks and sources.
    enum ModulationSource
    {
      fifo = 0,
      randomGenerator     = 1,
      gpio0_synchronous   = 2,
      gpio0_asynchronous  = 3,  
      gpio1_synchronous   = 4,
      gpio1_asynchronous  = 5,
      gpio2_synchronous   = 6,
      gpio2_asynchronous  = 7,       
      gpio3_synchronous   = 8,
      gpio3_asynchronous  = 9, 
    };
    
    // Data type for the different modulation schemas.
    enum ModulationType
    {
      OOK = 0,
      twoFSK = 1,
      twoGaussianFSK = 2,
      fourFSK = 3,
      fourGaussianFSK = 4,
      continuousWave = 5,
    };
    
    // Data  type for possible errors returned by the driver.
    enum TransceiverErrorCode
    {
      noError = 0,
      // High level errors
      notInitializedError = 1,
      wrongModeError = 2,
      wrongFrequencyError = 3,
      wrongPowerError = 4,
      // Low level errors
      CTSError = 5,
      commandError = 6,
      chipError = 7, // Fired if the interrupt line changes unexpectedly.
      // GenericError
      error = 8,
    };
    
    // Data type for the different radio working modes.
    enum TransceiverMode
    {
      notInitializedMode = 0,
      TXMode = 1,
      RXMode = 2,
    };
  
    // Highest reserved channel for reception.
    const uint8_t HIGHEST_RECEPTION_CHANNEL = 31;
    
    // Highest allowed frequency (in MHz) for reception.
    const float HIGHEST_RECEPTION_FREQUENCY = 1050.0;
    
    // Highest reserved channel for transmission.
    const uint8_t HIGHEST_TRANSMISSION_CHANNEL = 15;
    
    // Highest allowed frequency (in MHz) for transmission.
    const float HIGHEST_TRANSMISSION_FREQUENCY = 1050.0;
    
    // Lowest reserved channel for reception.
    const uint8_t LOWEST_RECEPTION_CHANNEL = 16;
    
    // Lowest allowed frequency (in MHz) for reception.
    const float LOWEST_RECEPTION_FREQUENCY = 142.0;
    
    // Lowest reserved channel for transmission.
    const uint8_t LOWEST_TRANSMISSION_CHANNEL = 0;
    
    // Lowest allowed frequency (in MHz) for transmission.
    const float LOWEST_TRANSMISSION_FREQUENCY = 142.0;
    
    // Maximum packet length supported by radio transceiver.
    static const uint8_t RADIO_MAX_PACKET_LENGTH = 129;
    
    // Maximum value for transmission power rate.
    const float MAXIMUM_TRANSMISSION_POWER_RATE = 100.0;
    
    // Minimum value for transmission power rate.
    const float MINIMUM_TRANSMISSION_POWER_RATE = 0.0;
    
    // Reception transceiver device.
    static const uint8_t RECEPTION_TRANSCEIVER = 0;
    
    // Transmission transceiver device.
    static const uint8_t TRANSMISSION_TRANSCEIVER = 1;
    
    // Constructor. Initializes the transceiver API software
    // and attaches it to a physical interface.    
    ESAT_COMTransceiverDriverClass(ESAT_COMTransceiverHALClass& hardwareTransceiver);
    
    // Process the transmission (keeps filling the fifo 
    // until packet is over); and the reception (if a 
    // packet has been received, retrieves it from fifo).
    int8_t available();
    
    // Initialize transceiver according to the selected 
    // mode (transmission or reception).
    // Return if the initialization went wrong or not.      
    TransceiverErrorCode begin(TransceiverMode mode);
    
    // Changes modulation source.
    // Return if the process is wrong.      
    TransceiverErrorCode configureModulationSource(ModulationSource modulationSource);
    
    // Changes modulation type by reconfiguring the chip.
    // Return if the process is wrong.
    TransceiverErrorCode configureModulationType(ModulationType modulationType);
    
    // Disable and hold the transceiver in reset state.
    void disable();
       
    // Return the channel configured for the current transceiver.
    uint8_t getChannel();
    
    // Return the center frequency configured for the current transceiver.
    float getFrequency();
    
    // Return the current set modulation.
    uint8_t getModulation();
    
    // Read last received signal strength indicator value.
    float getReceivedSignalStrengthIndicator();
      
    // Read the transceiver temperature.
    float getTransceiverTemperature();
    
    // Read the transceiver suplly voltage.
    float getTransceiverVoltage();
    
    // Return the transmisssion power (0.0 if it is a receiver).
    float getTransmissionPowerRate();
    
    // Retrieve the reception pointer buffer without
    // polling before wheter a packet has been received
    // or not, thus not holding the process.    
    uint8_t* nonBlockingRead();  
    
    // Send a packets but not wait for it to be sent, 
    // not holding the execution.
    // Return if the process is wrong.
    TransceiverErrorCode nonBlockingWrite(uint8_t* msgBuf);     
    
    // Poll fot a packet to be received, holding the
    // execution loop.
    // Return the reception buffer.
    uint8_t* read();
       
    // Changes TX/RX channel.
    void setChannel(uint8_t channel);
    
    // Changes center frequency.
    // Return if the process is wrong.
    TransceiverErrorCode setFrequency(float frequency);
          
    // Disable the interrupts
    // Return if the change go wrong or not.
    TransceiverErrorCode disableInterrupts();
    
    // Changes TX power.
    // Return if the process is wrong.
    TransceiverErrorCode setTransmissionPower(float transmissionPowerRateToBeSet);  

    // Enable the reception (only in RX mode).
    // Return if the process is wrong.
    TransceiverErrorCode startReception();      
    
    // Write a packet and wait for it to be sent, 
    // either by ISR or by polling checking methods.
    // Return if the process is wrong.
    TransceiverErrorCode write(uint8_t* msgBuf);
  
  private:
  
    // Clock frequency for computing the radio frequency.
    const uint32_t CRYSTAL_FOR_FREQUENCY_COMPUTING = 30000000;
    
    // Default modulation schema.
    const enum ModulationType DEFAULT_MODULATION_TYPE = OOK;
    
    // Default frequency for reception.
    const float DEFAULT_RECEPTION_FREQUENCY = 433.0; // In MHz.
    
    // Default frequency for transmission.
    const float DEFAULT_TRANSMISSION_FREQUENCY = 433.0; // In MHz.    
    
    // Default transmission power rate.
    const float DEFAULT_TRANSMISSION_POWER_RATE = 100.0;
    
    // Maximum failed initialization sequences allowed.
    const uint8_t MAXIMUM_FAILED_INITIALIZATIONS = 25;
    
    // Maximum value for mapping the power rate into the transceiver values.
    const float MAXIMUM_POWER_VALUE = 127.0;
    
    // Minimum value for mapping the power rate into the transceiver values.
    const float MINIMUM_POWER_VALUE = 0.0;  

    // Reception chain losses for RSSI calculation.
    const float RECEPTION_LOSSES_dB = 130.0;
       
    // Low level driver entity.
    ESAT_COMTransceiverHALClass* transceiver;
    
    boolean receptionAvailable;
    
    // Fifo reception buffer.
    uint8_t receptionBuffer[RADIO_MAX_PACKET_LENGTH];
    
    // Reception configuration object pointer.
    ESAT_COMTransceiverConfigurationClass* receptionConfigurationData;    
    
    // Reception frequency.
    float receptionFrequency;
    
    // Interrupt flag for receiving transceiver.
    static volatile uint8_t receptionInterruptFlag;
    
    // Modulation used by the transceiver.
    ModulationType transceiverModulationType;
    
    // Current transceiver configuration mode (TX/RX).
    TransceiverMode transceiverOperationMode;
    
    // Transceiver radio channel.
    uint8_t transceiverRadioChannel;
    
    // Transmission configuration object pointer.
    ESAT_COMTransceiverConfigurationClass* transmissionConfigurationData;    
      
    // Transmission frequency.
    float transmissionFrequency;
    
    // Interrupt flag for transmitting transceiver.
    static volatile uint8_t transmissionInterruptFlag;

    // Indicate if a transmission is going on.
    boolean transmissionInProgress;
    
    // Transmitter power rate.
    float transmissionPowerRate; 
    
    // Initializes the transceiver according to the working
    // mode and modulation set.
    // Return if the initialization went wrong or not.
    TransceiverErrorCode begin(TransceiverMode mode, ModulationType modulationType);
      
    // Check if there is a packet ready to be read.
    int8_t checkReceptionAvailability();
    
    // Check if the last packet is already transmitted.
    int8_t checkTransmissionAvailability();
               
    // Configures the transceiver.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError initializeTransceiver(ESAT_COMTransceiverConfigurationClass* transceiverConfiguration);
             
    // Interrupt service routine for the reception transceiver.
    // Set the RX ISR flag when is called.
    static void setReceptionTransceiverInterruptFlag (void);
    
    // Interrupt service routine for the transmission transceiver.
    // Set the TX ISR flag when is called.
    static void setTransmissionTransceiverInterruptFlag (void);    
    
    // Select the configuration file acording to the
    // modulation chosen for the reception channel.
    // Return the pointer to the configuration file.
    ESAT_COMTransceiverConfigurationClass* switchReceptionConfiguration(ModulationType modulationType);
    
    // Select the modulation source configuration
    // command according to the modulation source chosen.
    // Return the modulation source command.
    uint8_t  switchModulationSource(ModulationSource source);
    
    // Select the modulation source configuration type 
    // according to the modulation type chosen. However
    // this function doesn't change the modulation at all. 
    // Only set the command bits according to the modulation.
    // Return the modulation source command.
    uint8_t  switchModulationType(ModulationType type);  
    
    // Select the configuration class acording to the
    // modulation chosen for the transmission channel.
    // Return the pointer to the configuration class.
    ESAT_COMTransceiverConfigurationClass* switchTransmissionConfiguration(ModulationType modulationType); 

    // Casts from HAL error to device driver error.
    TransceiverErrorCode translateLowLevelDriverError(ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError);

};

// Global instace of the reception transceiver.
extern ESAT_COMTransceiverDriverClass ReceptionTransceiver;

// Global instace of the transmission transceiver.
extern ESAT_COMTransceiverDriverClass TransmissionTransceiver;

#endif /*ESAT_COMTransceiverDriver_h*/