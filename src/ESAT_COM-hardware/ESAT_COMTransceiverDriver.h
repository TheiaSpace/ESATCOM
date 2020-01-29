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
#include "ESAT_COMTransceiverInterface.h"

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
      notAnInterruptPinError = 1,
      notInitializedError = 2,
      wrongModeError = 3,
      wrongFrequencyError = 4,
      wrongPowerError = 5,
      CTSError = 6,      
    };
    
    // Data type for the different radio working modes.
    enum TransceiverMode
    {
      notInitializedMode = 0,
      TXMode = 1,
      TXInterruptsMode = 2,
      RXMode = 3,
      RXInterruptsMode = 4,
    };

    struct ADCReadingsReply 
    {
      uint16_t  GPIOAnalogRawValue;
      uint16_t  voltageRawValue;
      uint16_t  temperatureRawValue;
    };
    
    struct ChipStatusReply 
    {
      uint8_t  chipPending;
      uint8_t  chipStatus;
      uint8_t  lastCommandErrorStatus;
      uint8_t  lastCommandErrorCommand;
    };
    
    struct CommandReply
    {
      uint8_t   buffer[16];
    };

    struct DeviceStateReply
    {
      uint8_t   currentState;
      uint8_t   currentChannel;
    };
    
    struct FastResponseRegisterAReply
    {
      uint8_t   fastResponseRegisterA;
      uint8_t   fastResponseRegisterB;
      uint8_t   fastResponseRegisterC;
      uint8_t   fastResponseRegisterD;
    };

    struct FastResponseRegisterBReply
    {
      uint8_t   fastResponseRegisterB;
      uint8_t   fastResponseRegisterC;
      uint8_t   fastResponseRegisterD;
      uint8_t   fastResponseRegisterA;
    };

    struct FastResponseRegisterCReply
    {
      uint8_t   fastResponseRegisterC;
      uint8_t   fastResponseRegisterD;
      uint8_t   fastResponseRegisterA;
      uint8_t   fastResponseRegisterB;
    };

    struct FastResponseRegisterDReply
    {
      uint8_t   fastResponseRegisterD;
      uint8_t   fastResponseRegisterA;
      uint8_t   fastResponseRegisterB;
      uint8_t   fastResponseRegisterC;
    };
    
    struct FIFOStatusReply
    {
      uint8_t   receptionFIFOCount;
      uint8_t   transmissionFIFOSpace;
    };
    
    struct FunctionInfoReply 
    {
      uint8_t   externalRevision;
      uint8_t   branchRevision;
      uint8_t   internalRevision;
      //added patch support
      uint16_t  appliedPatchID;
      uint8_t   currentFunctionalMode;
    };

    struct GenericReply 
    {
      uint8_t reply[16];
    };
    
    struct GPIOConfigurationReply
    {
      uint8_t   GPIO[4];
      uint8_t   NIRQ;
      uint8_t   SDO;
      uint8_t   generalConfiguration;
    };

    struct InterruptStatusReply
    {
      uint8_t   interruptPending;
      uint8_t   interruptStatus;
      uint8_t   packetHandlerPending;
      uint8_t   packetHandlerStatus;
      uint8_t   modemPending;
      uint8_t   modemStatus;
      uint8_t   chipPending;
      uint8_t   chipStatus;
    };
    
    struct ManualImageRejectionCalibrationReply
    {
      uint8_t   imageRejectionCalibrationAppliedAmplitude;
      uint8_t   imageRejectionCalibrationAppliedPhase;
    };    
    
    struct ModemStatusReply 
    {
      uint8_t  modemPending;
      uint8_t  modemStatus;
      uint8_t  currentReceivedSignalStregnthIndicator;
      uint8_t  latchedReceivedSignalStrengthIndicator;
      uint8_t  antenna1ReceivedSignalStrengthIndicator;
      uint8_t  antenna2ReceivedSignalStrengthIndicator;
      uint16_t automaticFrequencyControlFrequencyOffset;
    };
        
    struct PacketHandlerStatusReply 
    {
      uint8_t  packetHandlerPending;
      uint8_t  packetHandlerStatus;
    };

    struct PacketInfoReply 
    {
      uint16_t  length;
    };
      
    struct PartInfoReply 
    {
      uint8_t   chipRevision;
      uint16_t  partNumber;
      uint8_t   partBuild;
      uint16_t  ID;
      uint8_t   customerID;
      uint8_t   ROMID;
    };
    
    struct PropertiesReply
    {
      uint8_t   buffer[16];
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
    ESAT_COMTransceiverDriverClass(ESAT_COMTransceiverInterfaceClass& hardwareTransceiver);
    
    // Process the transmission (keeps filling the fifo 
    // until packet is over); and the reception (if a 
    // packet has been received, retrieves it from fifo).
    int8_t available();
    
    // Initialize transceiver according to the selected 
    // mode (transmission or reception).
    // Return if the initialization went wrong or not.      
    TransceiverErrorCode begin(TransceiverMode mode);
    
    // Configures the transceiver general purpose input output pins.
    GPIOConfigurationReply configureGPIO(uint8_t GPIO0, uint8_t GPIO1, uint8_t GPIO2, uint8_t GPIO3, uint8_t NIRQ, uint8_t SDO, uint8_t driveStrength);
    
    // Changes modulation source.
    // Return if the process is wrong.      
    TransceiverErrorCode configureModulationSource(ModulationSource modulationSource);
    
    // Changes modulation type by reconfiguring the chip.
    // Return if the process is wrong.
    TransceiverErrorCode configureModulationType(ModulationType modulationType);
    
    // Disable and hold the transceiver in reset state.
    void disable();
    
    // Reads the selected analog values from the transceiver.
    // Use analogChannels to select which channels to read (GPIO, 
    // voltage and/or temperature).
    ADCReadingsReply getADCReading(uint8_t analogChannels);
    
    // Return the channel configured for the current transceiver.
    uint8_t getChannel();
    
    // Return the center frequency configured for the current transceiver.
    float getFrequency();
    
    // Return the current set modulation.
    uint8_t getModulation();
    
    // Returns information about the length of the variable field in the 
    // last packet received, and (optionally) overrides the field length. 
    PacketInfoReply getPacketInfo(uint8_t fieldNumberMask, uint16_t newLength, int16_t differenceLength);
    
    // Read last received signal strength indicator value.
    uint8_t getReceivedSignalStrengthIndicator();
      
    // Read the transceiver temperature.
    uint16_t getTransceiverTemperature();
    
    // Read the transceiver suplly voltage.
    uint16_t getTransceiverVoltage();
    
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

    // Issue a NOP command to the transceiver. Does nothing.
    void nop();   

    // Retrieves the basic information about the transceiver.
    PartInfoReply partInfo();    
    
    // Poll fot a packet to be received, holding the
    // execution loop.
    // Return the reception buffer.
    uint8_t* read();
    
    // Retrieves the current state of the device and lists pending
    // reception and transmission requests.
    DeviceStateReply requestDeviceState();
    
    // Changes TX/RX channel.
    void setChannel(uint8_t channel);
    
    // Changes center frequency.
    // Return if the process is wrong.
    TransceiverErrorCode setFrequency(float frequency);
    
    // Configure the transceiver to use interrupts.
    // Return if the change go wrong or not.
    TransceiverErrorCode setInterruptsMode();
          
    // Configure the transceiver to poll the interrupt line.
    // Return if the change go wrong or not.
    TransceiverErrorCode setPollingMode();
    
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
    
    // Maximum value for mapping the power rate into the transceiver values.
    const float MAXIMUM_POWER_VALUE = 127.0;
    
    // Minimum value for mapping the power rate into the transceiver values.
    const float MINIMUM_POWER_VALUE = 0.0;
    
    // ID of the patch image.
    const uint16_t TRANSCEIVER_PATCH_ID = 0xCA90;

    // ID of the ROM to be patched.
    const uint8_t TRANSCEIVER_PATCH_ROMID = 0x06;
    
    // Low level driver entity.
    ESAT_COMTransceiverInterfaceClass* transceiver;
    
    boolean receptionAvailable;
    
    // Fifo reception buffer.
    uint8_t receptionBuffer[RADIO_MAX_PACKET_LENGTH];
    
    // Reception configuration data pointer.
    uint8_t* receptionConfigurationData;    
    
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
    
    // Transmission configuration data pointer.
    uint8_t* transmissionConfigurationData;    
      
    // Transmission frequency.
    float transmissionFrequency;
    
    // Interrupt flag for transmitting transceiver.
    static volatile uint8_t transmissionInterruptFlag;

    // Indicate if a transmission is going on.
    boolean transmissionInProgress;
    
    // Transmitter power rate.
    float transmissionPowerRate; 

    // Loads the patch image to the transceiver
    // during booting up.
    uint8_t applyPatch();
    
    // Initializes the transceiver according to the working
    // mode and modulation set.
    // Return if the initialization went wrong or not.
    TransceiverErrorCode begin(TransceiverMode mode, ModulationType modulationType);
    
    // Changes the transceiver state to the nextState one.
    void changeState(uint8_t nextState);
      
    // Check if there is a packet ready to be read.
    int8_t checkReceptionAvailability();
    
    // Check if the last packet is already transmitted.
    int8_t checkTransmissionAvailability();
    
    // Configure the transceiver clock generator for the
    // desired frequency.
    // Return the best PLL outdiv value for that frequency.
    uint8_t configureClockGenerator(float frequency);  
             
    // Configures the transmitter.
    boolean initializeTransceiver(const uint8_t* configurationData);
    
    // Gets the chip status flags. Optionally clears them.
    ChipStatusReply getChipStatus(uint8_t clearPendingFlagsMask);
    
    // Reads the Fast Response Registers starting with A register.
    FastResponseRegisterAReply  getFastResponseRegisterA(uint8_t responseByteCount);
    
    // Reads the Fast Response Registers starting with B register.
    FastResponseRegisterBReply  getFastResponseRegisterB(uint8_t responseByteCount);
    
    // Reads the Fast Response Registers starting with C register.
    FastResponseRegisterCReply  getFastResponseRegisterC(uint8_t responseByteCount);
    
    // Reads the Fast Response Registers starting with D register.
    FastResponseRegisterDReply  getFastResponseRegisterD(uint8_t responseByteCount);
    
    // Retrieves the current byte counts in the transmission and
    // reception FIFOs and allows to reset them using FIFOsResetFlags
    // mask.  
    FIFOStatusReply getFIFOStatus(uint8_t FIFOsResetFlags);
    
    // Returns the function revision information of the transceiver.
    FunctionInfoReply getFunctionInfo();    
     
    // Retrieves the interrupt status flags and clears the
    // selected ones from packet handler, modem and chip sources.
    InterruptStatusReply getInterruptStatus(uint8_t packetHandlerClearingPendingInterruptsMask, uint8_t modemClearingPendingInterruptsMask, uint8_t chipClearingPendingInterruptsMask);  
      
    // Gets the modem status flags. Optionally clears them.
    ModemStatusReply getModemStatus(uint8_t clearPendingFlagsMask);
      
    // Gets the packer handler status flags. Optionally clears them.
    PacketHandlerStatusReply getPacketHandlerStatus(uint8_t clearPendingFlagsMask);
    
    // Reads a transceiver property. Requires the property 
    // group number to be retrieved, the number of the property fields 
    // to be read (max. 12) and the initial field offset.
    PropertiesReply getProperty(uint8_t group, uint8_t numProperties, uint8_t startingProperty);
    
    // Loads all inital properties from a null-ended list.
    // Requires the pointer to the list.
    uint8_t initializeConfigurations(const uint8_t* initialConfigurationsList);
    
    // Initializes the transceiver after powering it up.
    // Requires the path boot options, the clock source and the 
    // clock frequency.
    void powerUp(uint8_t bootOptions, uint8_t crystalOptions, uint32_t crystalFrequency);
    
    // Configures a transceiver property. Requires the property 
    // group number to be configured, the number of the property fields 
    // to update (max. 12), the initial field offset and the field's
    // contents buffer.
    void setProperty(uint8_t group, uint8_t numProperties, uint8_t startingProperty, uint8_t* properties);
        
    // Interrupt service routine for the reception transceiver.
    // Set the RX ISR flag when is called.
    static void setReceptionTransceiverInterruptFlag (void);
    
    // Interrupt service routine for the transmission transceiver.
    // Set the TX ISR flag when is called.
    static void setTransmissionTransceiverInterruptFlag (void);    
    
    // Switches the transceiver to reception state, thus being
    // able to receive packets. It needs the reception
    // channel on which to listen, the conditions for starting 
    // and ending the reception, the expected packet length and
    // the states to change after reception timeouts, is over or
    // fails.
    void startReception(uint8_t channel, uint8_t condition, uint16_t receptionLength, uint8_t nextState1, uint8_t nextState2, uint8_t nextState3);  
    
    // Switches the transceiver to transmission state and 
    // starts transmitting a packet. It needs the transmission
    // channel on which to transmit, the conditions for starting 
    // and ending the transmission and the packet length.
    void startTransmission(uint8_t channel, uint8_t condition, uint16_t transmissionLength);
    
    // Select the configuration file acording to the
    // modulation chosen for the reception channel.
    // Return the pointer to the configuration file.
    uint8_t* switchReceptionConfigurationFile(ModulationType modulationType);
    
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
    
    // Select the configuration file acording to the
    // modulation chosen for the transmission channel.
    // Return the pointer to the configuration file.
    uint8_t* switchTransmissionConfigurationFile(ModulationType modulationType);    

};

// Global instace of the reception transceiver.
extern ESAT_COMTransceiverDriverClass ReceptionTransceiver;

// Global instace of the transmission transceiver.
extern ESAT_COMTransceiverDriverClass TransmissionTransceiver;

#endif /*ESAT_COMTransceiverDriver_h*/