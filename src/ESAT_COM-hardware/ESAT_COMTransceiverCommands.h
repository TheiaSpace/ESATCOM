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

// List of the Si44463 transceiver SPI commands.
class ESAT_COMTransceiverCommandsClass
{
  public:
  
    // Arguments for the different configurations of each
    // GPIO pin.
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
    
    // Arguments for adjusting the drive strength of all
    // the GPIO.
    enum GPIODriveStrength
    {
      RADIO_HIGH = 0,
      RADIO_MED_HIGH = 1,
      RADIO_MED_LOW = 2,
      RADIO_LOW = 3
    };
  
    // Data structure for handling the reply of the ADC
    // reading command.
    struct ADCReadingsReply 
    {
      word  GPIOAnalogRawValue;
      word  voltageRawValue;
      word  temperatureRawValue;
    };
    
    // Data structure for handling the reply of the chip
    // status command.
    struct ChipStatusReply 
    {
      byte  chipPending;
      byte  chipStatus;
      byte  lastCommandErrorStatus;
      byte  lastCommandErrorCommand;
    };
    
    // Generic command reply handler.
    // Can hold up to 16 bytes.
    struct CommandReply
    {
      byte buffer[16];
    };
    
    // Data structure for handling the reply of the device
    // state command.
    struct DeviceStateReply
    {
      byte   currentState;
      byte   currentChannel;
    };
    
    // Data structure for handling the reply of the fast
    // response register A reading command.
    struct FastResponseRegisterAReply
    {
      byte   fastResponseRegisterA;
      byte   fastResponseRegisterB;
      byte   fastResponseRegisterC;
      byte   fastResponseRegisterD;
    };

    // Data structure for handling the reply of the fast
    // response register B reading command.
    struct FastResponseRegisterBReply
    {
      byte   fastResponseRegisterB;
      byte   fastResponseRegisterC;
      byte   fastResponseRegisterD;
      byte   fastResponseRegisterA;
    };

    // Data structure for handling the reply of the fast
    // response register C reading command.
    struct FastResponseRegisterCReply
    {
      byte   fastResponseRegisterC;
      byte   fastResponseRegisterD;
      byte   fastResponseRegisterA;
      byte   fastResponseRegisterB;
    };

    // Data structure for handling the reply of the fast
    // response register D reading command.
    struct FastResponseRegisterDReply
    {
      byte   fastResponseRegisterD;
      byte   fastResponseRegisterA;
      byte   fastResponseRegisterB;
      byte   fastResponseRegisterC;
    };
    
    // Data structure for handling the reply of the FIFO
    // status command.
    struct FIFOStatusReply
    {
      byte   receptionFIFOCount;
      byte   transmissionFIFOSpace;
    };
    
    // Data structure for handling the reply of the function
    // info command.
    struct FunctionInfoReply 
    {
      byte   externalRevision;
      byte   branchRevision;
      byte   internalRevision;
      // Added patch support.
      word  appliedPatchID;
      byte   currentFunctionalMode;
    };

    // Generic reply handler.
    // Can hold up to 16 bytes.
    struct GenericReply 
    {
      byte reply[16];
    };
    
    // Data structure for handling the reply of the GPIO
    // configuration command.
    struct GPIOConfigurationReply
    {
      byte   GPIO[4];
      byte   NIRQ;
      byte   SDO;
      byte   generalConfiguration;
    };

    // Data structure for handling the reply of the
    // interrupt status command.
    struct InterruptStatusReply
    {
      byte   interruptPending;
      byte   interruptStatus;
      byte   packetHandlerPending;
      byte   packetHandlerStatus;
      byte   modemPending;
      byte   modemStatus;
      byte   chipPending;
      byte   chipStatus;
    };
    
    // Data structure for handling the reply of the
    // manual image rejection calibation command.
    struct ManualImageRejectionCalibrationReply
    {
      byte   imageRejectionCalibrationAppliedAmplitude;
      byte   imageRejectionCalibrationAppliedPhase;
    };    
    
    // Data structure for handling the reply of the modem
    // status reading command.
    struct ModemStatusReply 
    {
      byte  modemPending;
      byte  modemStatus;
      byte  currentReceivedSignalStregnthIndicator;
      byte  latchedReceivedSignalStrengthIndicator;
      byte  antenna1ReceivedSignalStrengthIndicator;
      byte  antenna2ReceivedSignalStrengthIndicator;
      word automaticFrequencyControlFrequencyOffset;
    };
    
    // Data structure for handling the reply of the packet
    // handler status reading command.
    struct PacketHandlerStatusReply 
    {
      byte  packetHandlerPending;
      byte  packetHandlerStatus;
    };

    // Data structure for handling the reply of the packet
    // info command.
    struct PacketInfoReply 
    {
      word  length;
    };
    
    // Data structure for handling the reply of the part
    // info command.
    struct PartInfoReply 
    {
      byte   chipRevision;
      word  partNumber;
      byte   partBuild;
      word  ID;
      byte   customerID;
      byte   ROMID;
    };
    
    // Generic properties reply handler.
    // Can hold up to 16 bytes.
    struct PropertiesReply
    {
      byte   buffer[16];   
    };
    
  
  // Command for issuing a NOP to the transceiver.
  static const byte COMMAND_NOP = 0x0;
  
  // Command arguments count for issuing a NOP to 
  // the transceiver.
  static const byte COMMAND_NOP_ARGUMENTS_COUNT = 1;

  // Command for checking the transceiver part number.
  static const byte COMMAND_PART_INFO = 0x1;
  
  // Command arguments count for checking the transceiver 
  // part number.
  static const byte COMMAND_PART_INFO_ARGUMENTS_COUNT = 1;
  
  // Command reply count for checking the transceiver 
  // part number.
  static const byte COMMAND_PART_INFO_REPLY_COUNT = 8;

  // Command for initializing the transceiver.
  static const byte COMMAND_POWER_UP = 0x2;
  
  // Command arguments count for initializing the transceiver.
  static const byte COMMAND_POWER_UP_ARGUMENTS_COUNT = 7;

  // Command for configuring an specific property to the transceiver.
  static const byte COMMAND_SET_PROPERTY = 0x11;
  
  // Command arguments count for configuring an specific property 
  // to the transceiver.
  static const byte COMMAND_SET_PROPERTY_ARGUMENTS_COUNT = 16;

  // Command for retrieving an specific property from the transceiver.
  static const byte COMMAND_GET_PROPERTY = 0x12;
  
  // Command arguments count for retrieving an specific property 
  // from the transceiver.
  static const byte COMMAND_GET_PROPERTY_ARGUMENTS_COUNT = 4;
  
  // Command reply count for retrieving an specific property 
  // from the transceiver.
  static const byte COMMAND_GET_PROPERTY_REPLY_COUNT = 16;

  // Command for configuring the transciver GPIOs.
  static const byte COMMAND_CONFIGURE_GPIO = 0x13;
  
  // Command arguments count for configuring the transciver GPIOs.
  static const byte COMMAND_CONFIGURE_GPIO_ARGUMENTS_COUNT = 8;
  
  // Command reply count for configuring the transciver GPIOs.
  static const byte COMMAND_CONFIGURE_GPIO_REPLY_COUNT = 7;

  // Command for reading the transceiver analog lines.
  static const byte COMMAND_ADC_READ = 0x14;
  
  // Command arguments count for reading the transceiver analog
  // lines.
  static const byte COMMAND_ADC_READ_ARGUMENTS_COUNT = 3;
  
  // Command reply count for  reading the transceiver analog
  // lines.
  static const byte COMMAND_ADC_READ_REPLY_COUNT = 6;

  // Command for checking the transceiver FIFOs statuses.
  static const byte COMMAND_GET_FIFO_STATUS = 0x15;
  
  // Command arguments count for checking the transceiver FIFOs
  // statuses.
  static const byte COMMAND_GET_FIFO_STATUS_ARGUMENTS_COUNT = 2;
  
  // Command reply count for checking the transceiver FIFOs
  // statuses.
  static const byte COMMAND_GET_FIFO_STATUS_REPLY_COUNT = 2;

  // Command for getting information about the packet settings.
  static const byte COMMAND_GET_PACKET_INFO = 0x16;
  
  // Command arguments count for getting information about the
  // packet settings.
  static const byte COMMAND_GET_PACKET_INFO_ARGUMENTS_COUNT = 6;
  
  // Command reply count for getting information about the packet
  // settings.
  static const byte COMMAND_GET_PACKET_INFO_REPLY_COUNT = 2;

  // Command for checking the transceiver interrupt flags.
  static const byte COMMAND_GET_INTERRUPTS_STATUS = 0x20;
  
  // Command arguments count for checking the transceiver interrupt
  // flags.
  static const byte COMMAND_GET_INTERRUPTS_STATUS_ARGUMENTS_COUNT = 4;
  
  // Command reply count for checking the transceiver interrupt flags.
  static const byte COMMAND_GET_INTERRUPTS_STATUS_REPLY_COUNT = 8;

  // Command for checking the packet handler status.
  static const byte COMMAND_GET_PACKET_HANDLER_STATUS = 0x21;
  
  // Command arguments count for checking the packet handler status.
  static const byte COMMAND_GET_PACKET_HANDLER_STATUS_ARGUMENTS_COUNT = 2;
  
  // Command reply count for checking the packet handler status.
  static const byte COMMAND_GET_PACKET_HANDLER_STATUS_REPLY_COUNT = 2;

  // Command for checking the modem status.
  static const byte COMMAND_GET_MODEM_STATUS = 0x22;
  
  // Command arguments count forchecking the modem status.
  static const byte COMMAND_GET_MODEM_STATUS_ARGUMENTS_COUNT = 2;
  
  // Command reply count for checking the modem status.
  static const byte COMMAND_GET_MODEM_STATUS_REPLY_COUNT = 8;

  // Command for checking the chip global status.
  static const byte COMMAND_GET_CHIP_STATUS = 0x23;
  
  // Command arguments count for checking the chip global status.
  static const byte COMMAND_GET_CHIP_STATUS_ARGUMENTS_COUNT = 2;
  
  // Command reply count for checking the chip global status.
  static const byte COMMAND_GET_CHIP_STATUS_REPLY_COUNT = 4;

  // Command for starting the transmission of the stored data.
  static const byte COMMAND_START_TRANSMISSION = 0x31;
  
  // Command arguments count for starting the transmission of 
  // the stored data.
  static const byte COMMAND_START_TRANSMISSION_ARGUMENTS_COUNT = 7;

  // Command for starting the reception mode.
  static const byte COMMAND_START_RECEPTION = 0x32;
  
  // Command arguments count for starting the reception mode.
  static const byte COMMAND_START_RECEPTION_ARGUMENTS_COUNT = 8;

  // Command for changing the state machine state.
  static const byte COMMAND_CHANGE_STATE = 0x34;
  
  // Command arguments count for changing the state machine state.
  static const byte COMMAND_CHANGE_STATE_ARGUMENTS_COUNT = 2;

  // Command for reading the fast response register A.
  static const byte COMMAND_GET_FAST_RESPONSE_REGISTER_A = 0x50;
  
  // Command arguments count for reading the fast response register A.
  static const byte COMMAND_GET_FAST_RESPONSE_REGISTER_A_ARGUMENTS_COUNT = 1;
  
  // Command reply count for reading the fast response register A.
  static const byte COMMAND_GET_FAST_RESPONSE_REGISTER_A_REPLY_COUNT = 4;

  // Command for reading the fast response register B.
  static const byte COMMAND_GET_FAST_RESPONSE_REGISTER_B = 0x51;
  
  // Command arguments count for reading the fast response register B.
  static const byte COMMAND_GET_FAST_RESPONSE_REGISTER_B_ARGUMENTS_COUNT = 1;
  
  // Command reply count for reading the fast response register B.
  static const byte COMMAND_GET_FAST_RESPONSE_REGISTER_B_REPLY_COUNT = 4;

  // Command for reading the fast response register C.
  static const byte COMMAND_GET_FAST_RESPONSE_REGISTER_C = 0x53;
  
  // Command arguments count for reading the fast response register C.
  static const byte COMMAND_GET_FAST_RESPONSE_REGISTER_C_ARGUMENTS_COUNT = 1;
  
  // Command reply count for reading the fast response register C.
  static const byte COMMAND_GET_FAST_RESPONSE_REGISTER_C_REPLY_COUNT = 4;

  // Command for reading the fast response register D.
  static const byte COMMAND_GET_FAST_RESPONSE_REGISTER_D = 0x57;
  
  // Command arguments count for reading the fast response register D.
  static const byte COMMAND_GET_FAST_RESPONSE_REGISTER_D_ARGUMENTS_COUNT = 1;
  
  // Command reply count for reading the fast response register D.
  static const byte COMMAND_GET_FAST_RESPONSE_REGISTER_D_REPLY_COUNT = 4;

  // Command for loading data into the transmission FIFO.
  static const byte COMMAND_WRITE_TRANSMISSION_FIFO = 0x66;
  
  // Command arguments count for loading data into the transmission
  // FIFO.
  static const byte COMMAND_WRITE_TRANSMISSION_FIFO_ARGUMENTS_COUNT = 3;

  // Command for reading data from the reception FIFO.
  static const byte COMMAND_READ_RECEPTION_FIFO = 0x77;
  
  // Command arguments count for reading data from the reception
  // FIFO.
  static const byte COMMAND_READ_RECEPTION_FIFO_ARGUMENTS_COUNT = 1;
  
  // Command reply count for reading data from the reception FIFO.
  static const byte COMMAND_READ_RECEPTION_FIFO_REPLY_COUNT = 2;

  // Transceiver commands argument fields.
  // Format: [COMMAND]_ARGUMENT_[BYTE]_[VALUE].
  // Arguments for COMMAND_START_RECEPTION (0x32).
  static const byte START_RECEPTION_ARGUMENT_NEXT_STATE_1_RECEPTION_TIMEOUT_STATE_NO_CHANGE = 0;
  static const byte START_RECEPTION_ARGUMENT_NEXT_STATE_2_RECEPTION_VALID_STATE_READY = 3;
  static const byte START_RECEPTION_ARGUMENT_NEXT_STATE_3_RECEPTION_INVALID_STATE_RECEPTION = 8;

  // Transceiver commands replies masks.
  // Format: [COMMAND]_REPLY_[BYTE]_[BITFIELD]_BITMASK.
  // Masks for COMMAND_GET_INTERRUPTS_STATUS (0x20) reply.
  static const byte INTERRUPT_STATUS_REPLY_PACKET_HANDLER_PENDING_PACKET_RECEIVED_BITMASK = 0x10;
  static const byte INTERRUPT_STATUS_REPLY_PACKET_HANDLER_PENDING_PACKET_SENT_BITMASK = 0x20;
  static const byte INTERRUPT_STATUS_REPLY_CHIP_PENDING_COMMAND_ERROR_BITMASK = 0x8;
  static const byte INTERRUPT_STATUS_REPLY_CHIP_PENDING_CHIP_READY_BITMASK = 0x4;
  static const byte INTERRUPT_STATUS_REPLY_CHIP_STATUS_CHIP_READY_BITMASK = 0x4;

  // Transceiver commands arguments masks
  // Format: [COMMAND]_ARGUMENT_[BYTE]_[BITFIELD]_BITMASK.
  // Masks for COMMAND_ADC_READ (0x14) arguments.
  static const byte ADC_READ_ARGUMENT_READ_VOLTAGE_BITMASK = 0x8;
  static const byte ADC_READ_ARGUMENT_READ_TEMPERATURE_BITMASK = 0x10;
  // Masks for COMMAND_GET_FIFO_STATUS (0x15) arguments.
  static const byte FIFO_STATUS_ARGUMENT_TRANSMISSION_FIFO_BITMASK = 0x1;
  static const byte FIFO_STATUS_ARGUMENT_RECEPTION_FIFO_BITMASK = 0x2;
   
  // Loads the patch image into the transceiver.
  // Requires the HAL reference of the transceiver to be issued
  // and returns any HAL error that may happen.
  ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError applyPatch(ESAT_COMTransceiverHALClass& transceiver);
  
  // Configures all the GPIOs for any specific usage.
  // Requires the desired configuration, the pull-up setting,
  // the drive strength and the HAL reference of the transceiver
  // to be issued. returns the GPIO configuration reply.
  GPIOConfigurationReply configureGPIO(ESAT_COMTransceiverHALClass& transceiver, 
                                        GPIOConfigurationArguments GPIO0Config, boolean enableGPIO0PullUp,
                                        GPIOConfigurationArguments GPIO1Config, boolean enableGPIO1PullUp,
                                        GPIOConfigurationArguments GPIO2Config, boolean enableGPIO2PullUp,
                                        GPIOConfigurationArguments GPIO3Config, boolean enableGPIO3PullUp,
                                        GPIODriveStrength driveStrength);
                                        
  // Initializes the GPIOs to their default settings.
  // Requires the HAL reference of the transceiver to be issued
  // and returns the GPIO configuration reply.
  GPIOConfigurationReply configureGPIODefault(ESAT_COMTransceiverHALClass& transceiver);
  
  // Reads the selected analog values from the transceiver.
  // Use analogChannels to select which channels to read (GPIO, 
  // voltage and/or temperature). Also requires the HAL 
  // reference of the transceiver to be issued and returns the
  // ADC read value reply.
  ADCReadingsReply getADCReading(ESAT_COMTransceiverHALClass& transceiver, byte analogChannels);
  
  // Reads the Fast Response Registers starting with A register.
  // Requires the HAL reference of the transceiver to be issued
  // and returns the register content as a reply struct.
  FastResponseRegisterAReply getFastResponseRegisterA(ESAT_COMTransceiverHALClass& transceiver, byte responseByteCount);
  
  // Reads the Fast Response Registers starting with B register.
  // Requires the HAL reference of the transceiver to be issued
  // and returns the register content as a reply struct.
  FastResponseRegisterBReply getFastResponseRegisterB(ESAT_COMTransceiverHALClass& transceiver, byte responseByteCount);
  
  // Reads the Fast Response Registers starting with C register.
  // Requires the HAL reference of the transceiver to be issued
  // and returns the register content as a reply struct.
  FastResponseRegisterCReply getFastResponseRegisterC(ESAT_COMTransceiverHALClass& transceiver, byte responseByteCount);
  
  // Reads the Fast Response Registers starting with D register.
  // Requires the HAL reference of the transceiver to be issued
  // and returns the register content as a reply struct.
  FastResponseRegisterDReply getFastResponseRegisterD(ESAT_COMTransceiverHALClass& transceiver, byte responseByteCount);
  
  // Retrieves the current byte counts in the transmission and
  // reception FIFOs and resets them if desired.  Requires the
  // HAL reference of the transceiver to be issued and returns
  // and returns the FIFO status reply.
  FIFOStatusReply getFIFOStatus(ESAT_COMTransceiverHALClass& transceiver, boolean resetTransmissionFIFO, boolean resetReceptionFIFO);
  
  // Retrieves the interrupt status flags from the transceiver and
  // clears the selected ones by the mask (0 means "clear").
  // Also requires the HAL reference of the transceiver to be issued
  // and returns the interrupt status reply.
  InterruptStatusReply getInterruptStatus(ESAT_COMTransceiverHALClass&, 
                                          byte packetHandlerClearingPendingInterruptsMask, 
                                          byte modemClearingPendingInterruptsMask, 
                                          byte chipClearingPendingInterruptsMask);
 
  // Retrieves the modem status and clears its pending
  // interrupts. Requires the HAL reference of the transceiver 
  // to be issued and returns the modem status reply.
  ModemStatusReply getModemStatus(ESAT_COMTransceiverHALClass&, byte clearPendingFlagsMask);
  
  // Reads a transceiver property. Requires the transceiver where to
  // reas, the property group number to be retrieved, the number of 
  // the property fields to be read (max. 12) and the initial field offset.
  // Requires the HAL reference of the transceiver to be issued
  // and returns the properties reply.
  PropertiesReply getProperty(ESAT_COMTransceiverHALClass& transceiver, byte group, byte numProperties, byte startingProperty);  
  
  // Retrieves the basic information about the transceiver.
  // Requires the HAL reference of the transceiver to be issued
  // and returs the part info reply.
  PartInfoReply partInfo(ESAT_COMTransceiverHALClass& transceiver);
  
  // Initializes the transceiver after powering it up.
  // Requires the HAL reference of the transceiver to be issued.
  void powerUp(ESAT_COMTransceiverHALClass& transceiver);
  
  // Reads data from the reception buffer. Requires the data length and
  // its storing buffer and the HAL reference of the transceiver to be issued.
  void readReceptionFIFOBuffer(ESAT_COMTransceiverHALClass& transceiver, byte length, byte* dataReadBuffer);
  
  // Configures a transceiver property. Requires the transceiver HAL to be
  // configured, the property group number, the number of the property 
  // fields to update (max. 12), the initial field offset and the field's
  // contents buffer.    
  ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError setProperty(ESAT_COMTransceiverHALClass& transceiver, byte group, byte numProperties, byte startingProperty, byte* properties);
  
  // Switches the transceiver to the reception state, thus being
  // able to receive packets. It needs the reception
  // channel on which to listen, the expected packet length,
  // and the HAL reference of the transceiver to be issued.
  void startReception(ESAT_COMTransceiverHALClass& transceiver, byte channel, word receptionLength);
  
  // Switches the transceiver to the transmission state and 
  // starts transmitting a packet. It needs the transmission
  // channel on which to transmit, the packet length and the 
  // HAL reference of the transceiver to be issued.
  void startTransmission(ESAT_COMTransceiverHALClass& transceiver, byte channel, word transmissionLength);
  
  // Loads data into the trasmission FIFO buffer.
  // Requires the transmission hardware transceiver,
  // the data length and the data buffer.
  void writeTransmissionFIFOBuffer(ESAT_COMTransceiverHALClass& transceiver, byte length, byte* dataToBeWritten);
   
  private:
  
  // ID of the patch image.
  const word TRANSCEIVER_PATCH_ID = 0xCA90;

  // ID of the ROM to be patched.
  const byte TRANSCEIVER_PATCH_ROMID = 0x06;

  // Sets the GPIO mode mask for the selected configuration.
  byte getGPIOConfigurationMask(ESAT_COMTransceiverCommandsClass::GPIOConfigurationArguments arguments);

  // Sets the GPIO drive strength mask for the selected configuration.
  byte getGPIODriveStrengthMask(GPIODriveStrength strength);

  // Sets the GPIO pull-up mask for the selected configuration.
  byte getGPIOPullUpMask(boolean pullUpEnabled);  
};

// Global instance of the ESAT_COMTransceiverCommandsClass.
extern ESAT_COMTransceiverCommandsClass ESAT_COMTransceiverCommands;

#endif /*ESAT_COMTransceiverCommands_h*/