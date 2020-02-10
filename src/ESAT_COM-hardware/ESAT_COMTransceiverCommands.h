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
#ifndef ESAT_COMTransceiverCommands_h
#define ESAT_COMTransceiverCommands_h

#include <Arduino.h>
#include "ESAT_COMTransceiverHAL.h"

// List of Si44463 transceiver SPI commands.

class ESAT_COMTransceiverCommandsClass
{
  public:
  
    enum GPIOConfigurationArguments
    {
      DONOTHING = 0,
      TRISTATE = 1,
      DRIVE0 = 2,
      DRIVE1 = 3,
      INPUT_READ = 4,
      CTS = 8,
      INV_CTS = 9,
      POR = 12,
      TX_DATA_CLK = 16,
      RX_DATA_CLK = 17,
      TX_DATA = 19,
      RX_DATA = 20,
      RX_RAW_DATA = 21,
      RX_FIFO_FULL = 34,
      TX_FIFO_EMPTY = 35
    };
    
    enum GPIODriveStrength
    {
      RADIO_HIGH = 0,
      RADIO_MED_HIGH = 1,
      RADIO_MED_LOW = 2,
      RADIO_LOW = 3
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
    
  
  // Command for issuing a NOP to the transceiver.
  static const uint8_t COMMAND_NOP = 0x0;
  static const uint8_t COMMAND_NOP_ARGUMENTS_COUNT = 1;

  // Command for checking the transceiver part version.
  static const uint8_t COMMAND_PART_INFO = 0x1;
  static const uint8_t COMMAND_PART_INFO_ARGUMENTS_COUNT = 1;
  static const uint8_t COMMAND_PART_INFO_REPLY_COUNT = 8;

  // Command for initializing the transceiver.
  static const uint8_t COMMAND_POWER_UP = 0x2;
  static const uint8_t COMMAND_POWER_UP_ARGUMENTS_COUNT = 7;

  // Command for configuring an specific property to the transceiver.
  static const uint8_t COMMAND_SET_PROPERTY = 0x11;
  static const uint8_t COMMAND_SET_PROPERTY_ARGUMENTS_COUNT = 16;

  // Command for retrieving an specific property from the transceiver.
  static const uint8_t COMMAND_GET_PROPERTY = 0x12;
  static const uint8_t COMMAND_GET_PROPERTY_ARGUMENTS_COUNT = 4;
  static const uint8_t COMMAND_GET_PROPERTY_REPLY_COUNT = 16;

  // Command for configuring the transciver GPIOs.
  static const uint8_t COMMAND_CONFIGURE_GPIO = 0x13;
  static const uint8_t COMMAND_CONFIGURE_GPIO_ARGUMENTS_COUNT = 8;
  static const uint8_t COMMAND_CONFIGURE_GPIO_REPLY_COUNT = 7;

  // Command for reading the trasnceiver analog lines.
  static const uint8_t COMMAND_ADC_READ = 0x14;
  static const uint8_t COMMAND_ADC_READ_ARGUMENTS_COUNT = 3;
  static const uint8_t COMMAND_ADC_READ_REPLY_COUNT = 6;

  // Command for checking the transceiver FIFOs statuses.
  static const uint8_t COMMAND_GET_FIFO_STATUS = 0x15;
  static const uint8_t COMMAND_GET_FIFO_STATUS_ARGUMENTS_COUNT = 2;
  static const uint8_t COMMAND_GET_FIFO_STATUS_REPLY_COUNT = 2;

  // Command for checking information about the last received packet.
  static const uint8_t COMMAND_GET_PACKET_INFO = 0x16;
  static const uint8_t COMMAND_GET_PACKET_INFO_ARGUMENTS_COUNT = 6;
  static const uint8_t COMMAND_GET_PACKET_INFO_REPLY_COUNT = 2;

  // Command for checking the trasnceiver interrupt flags.
  static const uint8_t COMMAND_GET_INTERRUPTS_STATUS = 0x20;
  static const uint8_t COMMAND_GET_INTERRUPTS_STATUS_ARGUMENTS_COUNT = 4;
  static const uint8_t COMMAND_GET_INTERRUPTS_STATUS_REPLY_COUNT = 8;

  // Command for checking the packet handler status.
  static const uint8_t COMMAND_GET_PACKET_HANDLER_STATUS = 0x21;
  static const uint8_t COMMAND_GET_PACKET_HANDLER_STATUS_ARGUMENTS_COUNT = 2;
  static const uint8_t COMMAND_GET_PACKET_HANDLER_STATUS_REPLY_COUNT = 2;

  // Command for checking the modem status.
  static const uint8_t COMMAND_GET_MODEM_STATUS = 0x22;
  static const uint8_t COMMAND_GET_MODEM_STATUS_ARGUMENTS_COUNT = 2;
  static const uint8_t COMMAND_GET_MODEM_STATUS_REPLY_COUNT = 8;

  // Command for checking the chip global status.
  static const uint8_t COMMAND_GET_CHIP_STATUS = 0x23;
  static const uint8_t COMMAND_GET_CHIP_STATUS_ARGUMENTS_COUNT = 2;
  static const uint8_t COMMAND_GET_CHIP_STATUS_REPLY_COUNT = 4;

  // Command for starting the transmission of the stored data.
  static const uint8_t COMMAND_START_TRANSMISSION = 0x31;
  static const uint8_t COMMAND_START_TRANSMISSION_ARGUMENTS_COUNT = 7;

  // Command for starting the reception mode.
  static const uint8_t COMMAND_START_RECEPTION = 0x32;
  static const uint8_t COMMAND_START_RECEPTION_ARGUMENTS_COUNT = 8;

  // Command for changing the state machine state.
  static const uint8_t COMMAND_CHANGE_STATE = 0x34;
  static const uint8_t COMMAND_CHANGE_STATE_ARGUMENTS_COUNT = 2;

  // Command for reading the fast response register A.
  static const uint8_t COMMAND_GET_FAST_RESPONSE_REGISTER_A = 0x50;
  static const uint8_t COMMAND_GET_FAST_RESPONSE_REGISTER_A_ARGUMENTS_COUNT = 1;
  static const uint8_t COMMAND_GET_FAST_RESPONSE_REGISTER_A_REPLY_COUNT = 4;

  // Command for reading the fast response register B.
  static const uint8_t COMMAND_GET_FAST_RESPONSE_REGISTER_B = 0x51;
  static const uint8_t COMMAND_GET_FAST_RESPONSE_REGISTER_B_ARGUMENTS_COUNT = 1;
  static const uint8_t COMMAND_GET_FAST_RESPONSE_REGISTER_B_REPLY_COUNT = 4;

  // Command for reading the fast response register C.
  static const uint8_t COMMAND_GET_FAST_RESPONSE_REGISTER_C = 0x53;
  static const uint8_t COMMAND_GET_FAST_RESPONSE_REGISTER_C_ARGUMENTS_COUNT = 1;
  static const uint8_t COMMAND_GET_FAST_RESPONSE_REGISTER_C_REPLY_COUNT = 4;

  // Command for reading the fast response register D.
  static const uint8_t COMMAND_GET_FAST_RESPONSE_REGISTER_D = 0x57;
  static const uint8_t COMMAND_GET_FAST_RESPONSE_REGISTER_D_ARGUMENTS_COUNT = 1;
  static const uint8_t COMMAND_GET_FAST_RESPONSE_REGISTER_D_REPLY_COUNT = 4;

  // Command for loading data into the transmission FIFO.
  static const uint8_t COMMAND_WRITE_TRANSMISSION_FIFO = 0x66;
  static const uint8_t COMMAND_WRITE_TRANSMISSION_FIFO_ARGUMENTS_COUNT = 3;

  // Command for reading data from the reception FIFO.
  static const uint8_t COMMAND_READ_RECEPTION_FIFO = 0x77;
  static const uint8_t COMMAND_READ_RECEPTION_FIFO_ARGUMENTS_COUNT = 1;
  static const uint8_t COMMAND_READ_RECEPTION_FIFO_REPLY_COUNT = 2;

  // Transceiver commands argument fields.
  // Format: [COMMAND]_ARGUMENT_[BYTE]_[VALUE].
  // Arguments for COMMAND_START_RECEPTION (0x32).
  static const uint8_t START_RECEPTION_ARGUMENT_NEXT_STATE_1_RECEPTION_TIMEOUT_STATE_NO_CHANGE = 0;
  static const uint8_t START_RECEPTION_ARGUMENT_NEXT_STATE_2_RECEPTION_VALID_STATE_READY = 3;
  static const uint8_t START_RECEPTION_ARGUMENT_NEXT_STATE_3_RECEPTION_INVALID_STATE_RECEPTION = 8;

  // Transceiver commands replies masks.
  // Format: [COMMAND]_REPLY_[BYTE]_[BITFIELD]_BITMASK.
  // Masks for COMMAND_GET_INTERRUPTS_STATUS (0x20) reply.
  static const uint8_t INTERRUPT_STATUS_REPLY_PACKET_HANDLER_PENDING_PACKET_RECEIVED_BITMASK = 0x10;
  static const uint8_t INTERRUPT_STATUS_REPLY_PACKET_HANDLER_PENDING_PACKET_SENT_BITMASK = 0x20;
  static const uint8_t INTERRUPT_STATUS_REPLY_CHIP_PENDING_COMMAND_ERROR_BITMASK = 0x8;
  static const uint8_t INTERRUPT_STATUS_REPLY_CHIP_PENDING_CHIP_READY_BITMASK = 0x4;
  static const uint8_t INTERRUPT_STATUS_REPLY_CHIP_STATUS_CHIP_READY_BITMASK = 0x4;

  // Transceiver commands arguments masks
  // Format: [COMMAND]_ARGUMENT_[BYTE]_[BITFIELD]_BITMASK.
  // Masks for COMMAND_ADC_READ (0x14) arguments.
  static const uint8_t ADC_READ_ARGUMENT_READ_VOLTAGE_BITMASK = 0x8;
  static const uint8_t ADC_READ_ARGUMENT_READ_TEMPERATURE_BITMASK = 0x10;
  // Masks for COMMAND_GET_FIFO_STATUS (0x15) arguments.
  static const uint8_t FIFO_STATUS_ARGUMENT_TRANSMISSION_FIFO_BITMASK = 0x1;
  static const uint8_t FIFO_STATUS_ARGUMENT_RECEPTION_FIFO_BITMASK = 0x2;
  
  // Default constructor.
  //ESAT_COMTransceiverCommandsClass(){};
  
  // Loads the patch image into the transceiver.
  ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError applyPatch(ESAT_COMTransceiverHALClass& transceiver);
  
  // Configures all the GPIOs for any specific usage.
  // Requires the desired configuration, the pull-up setting
  // and the drive strength.
  GPIOConfigurationReply configureGPIO(ESAT_COMTransceiverHALClass& transceiver, 
                                        GPIOConfigurationArguments GPIO0Config, boolean enableGPIO0PullUp,
                                        GPIOConfigurationArguments GPIO1Config, boolean enableGPIO1PullUp,
                                        GPIOConfigurationArguments GPIO2Config, boolean enableGPIO2PullUp,
                                        GPIOConfigurationArguments GPIO3Config, boolean enableGPIO3PullUp,
                                        GPIODriveStrength driveStrength);
                                        
  // Initializes the GPIOs to their default settings.
  GPIOConfigurationReply configureGPIODefault(ESAT_COMTransceiverHALClass& transceiver);
  
  // Reads the selected analog values from the transceiver.
  // Use analogChannels to select which channels to read (GPIO, 
  // voltage and/or temperature).
  ADCReadingsReply getADCReading(ESAT_COMTransceiverHALClass& transceiver, uint8_t analogChannels);
  
  // Reads the Fast Response Registers starting with A register.
  FastResponseRegisterAReply getFastResponseRegisterA(ESAT_COMTransceiverHALClass& transceiver, uint8_t responseByteCount);
  
  // Reads the Fast Response Registers starting with B register.
  FastResponseRegisterBReply getFastResponseRegisterB(ESAT_COMTransceiverHALClass& transceiver, uint8_t responseByteCount);
  
  // Reads the Fast Response Registers starting with C register.
  FastResponseRegisterCReply getFastResponseRegisterC(ESAT_COMTransceiverHALClass& transceiver, uint8_t responseByteCount);
  
  // Reads the Fast Response Registers starting with D register.
  FastResponseRegisterDReply getFastResponseRegisterD(ESAT_COMTransceiverHALClass& transceiver, uint8_t responseByteCount);
  
  // Retrieves the current byte counts in the transmission and
  // reception FIFOs and resets them if desired.
  FIFOStatusReply getFIFOStatus(ESAT_COMTransceiverHALClass& transceiver, boolean resetTransmissionFIFO, boolean resetReceptionFIFO);
  
  // Retrieves the interrupt status flags from the transceiver and
  // clears the selected ones by the mask (0 means "clear").
  InterruptStatusReply getInterruptStatus(ESAT_COMTransceiverHALClass&, 
                                          uint8_t packetHandlerClearingPendingInterruptsMask, 
                                          uint8_t modemClearingPendingInterruptsMask, 
                                          uint8_t chipClearingPendingInterruptsMask);
 
  // Retrieves the modem status and clears its pending
  // interrupts.
  ModemStatusReply getModemStatus(ESAT_COMTransceiverHALClass&, uint8_t clearPendingFlagsMask);
  
  // Reads a transceiver property. Requires the transceiver where to
  // reas, the property group number to be retrieved, the number of 
  // the property fields to be read (max. 12) and the initial field offset.
  PropertiesReply getProperty(ESAT_COMTransceiverHALClass& transceiver, uint8_t group, uint8_t numProperties, uint8_t startingProperty);  
  
  // Retrieves the basic information about the transceiver.
  PartInfoReply partInfo(ESAT_COMTransceiverHALClass& transceiver); 
  
  // Initializes the transceiver after powering it up.
  void powerUp(ESAT_COMTransceiverHALClass& transceiver);
  
  // Reads data from the reception buffer. Requires the data length and
  // its storing buffer.
  void readReceptionFIFOBuffer(ESAT_COMTransceiverHALClass& transceiver, uint8_t length, uint8_t* dataReadBuffer);
  
  // Configures a transceiver property. Requires the transceiver to be
  // configured, the property group number, the number of the property 
  // fields to update (max. 12), the initial field offset and the field's
  // contents buffer.    
  ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError setProperty(ESAT_COMTransceiverHALClass& transceiver, uint8_t group, uint8_t numProperties, uint8_t startingProperty, uint8_t* properties);
  
  // Switches the transceiver to reception state, thus being
  // able to receive packets. It needs the reception
  // channel on which to listen, the conditions for starting 
  // and ending the reception, the expected packet length and
  // the states to change after reception timeouts, is over or
  // fails.
  void startReception(ESAT_COMTransceiverHALClass& transceiver, uint8_t channel, uint16_t receptionLength);
  
  // Switches the transceiver to transmission state and 
  // starts transmitting a packet. It needs the transmission
  // channel on which to transmit and the packet length.
  void startTransmission(ESAT_COMTransceiverHALClass& transceiver, uint8_t channel, uint16_t transmissionLength);
  
  // Loads data into the trasmission FIFO buffer.
  // Requires the transmission hardware transceiver,
  // the data length and the data buffer.
  void writeTransmissionFIFOBuffer(ESAT_COMTransceiverHALClass& transceiver, uint8_t length, uint8_t* dataToBeWritten);
   
  private:
  
  // ID of the patch image.
  const uint16_t TRANSCEIVER_PATCH_ID = 0xCA90;

  // ID of the ROM to be patched.
  const uint8_t TRANSCEIVER_PATCH_ROMID = 0x06;

  // Sets the GPIO mode mask for the selected configuration.
  uint8_t getGPIOConfigurationMask(ESAT_COMTransceiverCommandsClass::GPIOConfigurationArguments arguments);

  // Sets the GPIO drive strength mask for the selected configuration.
  uint8_t getGPIODriveStrengthMask(GPIODriveStrength strength);

  // Sets the GPIO pull-up mask for the selected configuration.
  uint8_t getGPIOPullUpMask(boolean pullUpEnabled);  
};

extern ESAT_COMTransceiverCommandsClass ESAT_COMTransceiverCommands;

#endif /*ESAT_COMTransceiverCommands_h*/