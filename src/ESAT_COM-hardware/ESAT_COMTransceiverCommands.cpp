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

#include <Arduino.h>
#include "ESAT_COMTransceiverCommands.h"

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COMTransceiverCommandsClass::applyPatch(ESAT_COMTransceiverHALClass& transceiver)
{  
  volatile uint16_t line = 0;
  volatile uint8_t row = 0;
  const byte TRANSCEIVER_PATCH[] = {
    8, 4, 33, 113, 75, 0, 0, 220, 149, 8, 5, 166, 34, 33, 240, 65, 91, 38, \
    8, 226, 47, 28, 187, 10, 168, 148, 40, 8, 5, 135, 103, 226, 88, 26, \
    7, 91, 8, 225, 208, 114, 216, 138, 184, 91, 125, 8, 5, 17, 236, 158, \
    40, 35, 27, 109, 8, 226, 79, 138, 178, 169, 41, 20, 19, 8, 5, 209, \
    46, 113, 106, 81, 76, 44, 8, 229, 128, 39, 66, 164, 105, 176, 127, 8, \
    5, 170, 129, 42, 189, 69, 232, 168, 8, 234, 228, 240, 36, 201, 159, \
    204, 60, 8, 5, 8, 245, 5, 4, 39, 98, 152, 8, 234, 107, 98, 132, 161, \
    249, 74, 226, 8, 5, 233, 119, 5, 79, 132, 238, 53, 8, 226, 67, 195, \
    141, 251, 173, 84, 37, 8, 5, 20, 6, 94, 57, 54, 47, 69, 8, 234, 12, \
    28, 116, 208, 17, 252, 50, 8, 5, 218, 56, 186, 14, 60, 231, 139, 8, \
    234, 176, 9, 230, 255, 148, 187, 169, 8, 5, 215, 17, 41, 254, 220, \
    113, 213, 8, 234, 127, 131, 167, 96, 144, 98, 24, 8, 5, 132, 127, \
    106, 209, 145, 198, 82, 8, 234, 42, 216, 123, 142, 74, 159, 145, 8, \
    5, 189, 170, 157, 22, 24, 6, 21, 8, 226, 85, 173, 45, 10, 20, 31, 93, \
    8, 5, 211, 224, 124, 57, 207, 1, 240, 8, 239, 58, 145, 114, 106, 3, \
    187, 150, 8, 231, 131, 109, 164, 146, 252, 19, 167, 8, 239, 248, 253, \
    207, 98, 7, 111, 30, 8, 231, 76, 234, 74, 117, 79, 214, 207, 8, 226, \
    246, 17, 228, 38, 13, 77, 198, 8, 5, 251, 191, 232, 7, 137, 195, 81, \
    8, 239, 130, 39, 4, 63, 150, 168, 88, 8, 231, 65, 41, 60, 117, 42, \
    3, 28, 8, 239, 175, 89, 152, 54, 170, 15, 6, 8, 230, 246, 147, 65, \
    45, 236, 14, 153, 8, 5, 41, 25, 144, 229, 170, 54, 64, 8, 231, 251, \
    104, 16, 125, 119, 93, 192, 8, 231, 203, 180, 221, 206, 144, 84, 190, \
    8, 231, 114, 138, 214, 2, 244, 221, 204, 8, 231, 106, 33, 11, 2, 134, \
    236, 21, 8, 231, 123, 124, 61, 107, 129, 3, 208, 8, 239, 125, 97, 54, \
    148, 124, 160, 223, 8, 239, 204, 133, 59, 218, 224, 92, 28, 8, 231, \
    227, 117, 187, 57, 34, 75, 168, 8, 239, 249, 206, 224, 94, 235, 29, \
    203, 8, 231, 189, 226, 112, 213, 171, 78, 63, 8, 231, 183, 141, 32, \
    104, 107, 9, 82, 8, 239, 161, 27, 144, 205, 152, 0, 99, 8, 239, 84, \
    103, 93, 156, 17, 252, 69, 8, 231, 212, 155, 200, 151, 190, 138, 7, \
    8, 239, 82, 141, 144, 99, 115, 213, 42, 8, 239, 3, 188, 110, 28, 118, \
    190, 74, 8, 231, 194, 237, 103, 186, 94, 102, 33, 8, 239, 231, 63, \
    135, 190, 224, 122, 109, 8, 231, 201, 112, 147, 29, 100, 245, 108, \
    8, 239, 245, 40, 8, 52, 179, 182, 44, 8, 239, 58, 10, 236, 15, 219, \
    86, 202, 8, 239, 57, 160, 110, 237, 121, 208, 36, 8, 231, 108, 11, \
    175, 169, 78, 64, 181, 8, 233, 185, 175, 191, 37, 80, 209, 55, 8, 5, \
    158, 219, 222, 63, 148, 233, 107, 8, 236, 197, 5, 170, 87, 220, 138, \
    94, 8, 5, 112, 218, 132, 132, 221, 202, 144
  };
  uint8_t cmdBuff[8];
  // Check if patch is needed.
  const PartInfoReply partInfoReply = partInfo(transceiver);       
  if ((partInfoReply.ROMID == TRANSCEIVER_PATCH_ROMID) && ((partInfoReply.ID >> 8) <= TRANSCEIVER_PATCH_ID))
  {       
    for (line = 0; line < (sizeof(TRANSCEIVER_PATCH) / 9); line++)
    {             
      for (row = 0; row < 8; row++)
      {    
        cmdBuff[row] = TRANSCEIVER_PATCH[(line * 9) + row + 1];
      }
      if (transceiver.writeCommandAndRetrieveResponse(8, cmdBuff, 0, 0) != 0xFF)
      {
        return ESAT_COMTransceiverHALClass::TRANSCEIVER_CTS_TIMEOUT;
      }
      // Check if error has occured.
      if (transceiver.checkInterruptPin() == 0)
      {        
        getInterruptStatus(transceiver, 0, 0, 0);
        //No return values are necessary.
        return ESAT_COMTransceiverHALClass::TRANSCEIVER_CHIP_ERROR;
      }
    }
  }
  return ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS;
}

ESAT_COMTransceiverCommandsClass::GPIOConfigurationReply ESAT_COMTransceiverCommandsClass::configureGPIO(ESAT_COMTransceiverHALClass& transceiver, 
                                                                                                          ESAT_COMTransceiverCommandsClass::GPIOConfigurationArguments GPIO0Config, 
                                                                                                          boolean enableGPIO0PullUp,
                                                                                                          ESAT_COMTransceiverCommandsClass::GPIOConfigurationArguments GPIO1Config, 
                                                                                                          boolean enableGPIO1PullUp,
                                                                                                          ESAT_COMTransceiverCommandsClass::GPIOConfigurationArguments GPIO2Config, 
                                                                                                          boolean enableGPIO2PullUp,
                                                                                                          ESAT_COMTransceiverCommandsClass::GPIOConfigurationArguments GPIO3Config,
                                                                                                          boolean enableGPIO3PullUp,
                                                                                                          ESAT_COMTransceiverCommandsClass::GPIODriveStrength driveStrength)
{
  uint8_t cmdBuff[8];
  GPIOConfigurationReply GPIOConfigurationReply;  
  cmdBuff[0] = COMMAND_CONFIGURE_GPIO;
  cmdBuff[1] = getGPIOPullUpMask(enableGPIO0PullUp) | getGPIOConfigurationMask(GPIO0Config);
  cmdBuff[2] = getGPIOPullUpMask(enableGPIO1PullUp) | getGPIOConfigurationMask(GPIO1Config);
  cmdBuff[3] = getGPIOPullUpMask(enableGPIO2PullUp) | getGPIOConfigurationMask(GPIO2Config);
  cmdBuff[4] = getGPIOPullUpMask(enableGPIO3PullUp) | getGPIOConfigurationMask(GPIO3Config);
  cmdBuff[5] = 0x00; // Nirq
  cmdBuff[6] = 0x00; // SDO
  cmdBuff[7] = getGPIODriveStrengthMask(driveStrength);
  transceiver.writeCommandAndRetrieveResponse(COMMAND_CONFIGURE_GPIO_ARGUMENTS_COUNT,
                                  cmdBuff,
                                  COMMAND_CONFIGURE_GPIO_REPLY_COUNT,
                                  cmdBuff);
  GPIOConfigurationReply.GPIO[0]        = cmdBuff[0];
  GPIOConfigurationReply.GPIO[1]        = cmdBuff[1];
  GPIOConfigurationReply.GPIO[2]        = cmdBuff[2];
  GPIOConfigurationReply.GPIO[3]        = cmdBuff[3];
  GPIOConfigurationReply.NIRQ           = cmdBuff[4];
  GPIOConfigurationReply.SDO            = cmdBuff[5];
  GPIOConfigurationReply.generalConfiguration   = cmdBuff[6];  
  return GPIOConfigurationReply;
}

ESAT_COMTransceiverCommandsClass::GPIOConfigurationReply ESAT_COMTransceiverCommandsClass::configureGPIODefault(ESAT_COMTransceiverHALClass& transceiver)
{
  return configureGPIO(transceiver, 
                      ESAT_COMTransceiverCommandsClass::DONOTHING, false,
                      ESAT_COMTransceiverCommandsClass::DONOTHING, false, 
                      ESAT_COMTransceiverCommandsClass::DONOTHING, false,
                      ESAT_COMTransceiverCommandsClass::DONOTHING, false,
                      ESAT_COMTransceiverCommandsClass::RADIO_LOW);
}

ESAT_COMTransceiverCommandsClass::ADCReadingsReply ESAT_COMTransceiverCommandsClass::getADCReading(ESAT_COMTransceiverHALClass& transceiver, uint8_t analogChannels)
{
  uint8_t cmdBuff[8];
  ADCReadingsReply ADCReadingsReply;  
  cmdBuff[0] = COMMAND_ADC_READ;
  cmdBuff[1] = analogChannels;
  transceiver.writeCommandAndRetrieveResponse(COMMAND_ADC_READ_ARGUMENTS_COUNT,
                                  cmdBuff,
                                  COMMAND_ADC_READ_REPLY_COUNT,
                                  cmdBuff);
  ADCReadingsReply.GPIOAnalogRawValue   = ((uint16_t)cmdBuff[0] << 8) & 0xFF00;
  ADCReadingsReply.GPIOAnalogRawValue  |= (uint16_t)cmdBuff[1] & 0x00FF;
  ADCReadingsReply.voltageRawValue      = ((uint16_t)cmdBuff[2] << 8) & 0xFF00;
  ADCReadingsReply.voltageRawValue     |= (uint16_t)cmdBuff[3] & 0x00FF;
  ADCReadingsReply.temperatureRawValue  = ((uint16_t)cmdBuff[4] << 8) & 0xFF00;
  ADCReadingsReply.temperatureRawValue |= (uint16_t)cmdBuff[5] & 0x00FF;
  return ADCReadingsReply;
}

ESAT_COMTransceiverCommandsClass::FastResponseRegisterAReply  ESAT_COMTransceiverCommandsClass::getFastResponseRegisterA(ESAT_COMTransceiverHALClass& transceiver, uint8_t responseByteCount)
{
  uint8_t cmdBuff[4];
  FastResponseRegisterAReply fastResponseRegisterAReply;  
  transceiver.readData(COMMAND_GET_FAST_RESPONSE_REGISTER_A,
            responseByteCount,
            cmdBuff);
  fastResponseRegisterAReply.fastResponseRegisterA = cmdBuff[0];
  fastResponseRegisterAReply.fastResponseRegisterB = cmdBuff[1];
  fastResponseRegisterAReply.fastResponseRegisterC = cmdBuff[2];
  fastResponseRegisterAReply.fastResponseRegisterD = cmdBuff[3];  
  return fastResponseRegisterAReply;
}
  
ESAT_COMTransceiverCommandsClass::FastResponseRegisterBReply  ESAT_COMTransceiverCommandsClass::getFastResponseRegisterB(ESAT_COMTransceiverHALClass& transceiver, uint8_t responseByteCount)
{
  uint8_t cmdBuff[4];
  FastResponseRegisterBReply fastResponseRegisterBReply;  
  transceiver.readData(COMMAND_GET_FAST_RESPONSE_REGISTER_B,
            responseByteCount,
            cmdBuff);
  fastResponseRegisterBReply.fastResponseRegisterB = cmdBuff[0];
  fastResponseRegisterBReply.fastResponseRegisterC = cmdBuff[1];
  fastResponseRegisterBReply.fastResponseRegisterD = cmdBuff[2];
  fastResponseRegisterBReply.fastResponseRegisterA = cmdBuff[3];  
  return fastResponseRegisterBReply;
}
  
ESAT_COMTransceiverCommandsClass::FastResponseRegisterCReply  ESAT_COMTransceiverCommandsClass::getFastResponseRegisterC(ESAT_COMTransceiverHALClass& transceiver, uint8_t responseByteCount)
{
  uint8_t cmdBuff[4];
  FastResponseRegisterCReply fastResponseRegisterCReply;  
  transceiver.readData(COMMAND_GET_FAST_RESPONSE_REGISTER_C,
            responseByteCount,
            cmdBuff);
  fastResponseRegisterCReply.fastResponseRegisterC = cmdBuff[0];
  fastResponseRegisterCReply.fastResponseRegisterD = cmdBuff[1];
  fastResponseRegisterCReply.fastResponseRegisterA = cmdBuff[2];
  fastResponseRegisterCReply.fastResponseRegisterB = cmdBuff[3];  
  return fastResponseRegisterCReply;
}
  
ESAT_COMTransceiverCommandsClass::FastResponseRegisterDReply  ESAT_COMTransceiverCommandsClass::getFastResponseRegisterD(ESAT_COMTransceiverHALClass& transceiver, uint8_t responseByteCount)
{
  uint8_t cmdBuff[4];
  FastResponseRegisterDReply fastResponseRegisterDReply;  
  transceiver.readData(COMMAND_GET_FAST_RESPONSE_REGISTER_D,
            responseByteCount,
            cmdBuff);
  fastResponseRegisterDReply.fastResponseRegisterD = cmdBuff[0];
  fastResponseRegisterDReply.fastResponseRegisterA = cmdBuff[1];
  fastResponseRegisterDReply.fastResponseRegisterB = cmdBuff[2];
  fastResponseRegisterDReply.fastResponseRegisterC = cmdBuff[3];  
  return fastResponseRegisterDReply;
}

ESAT_COMTransceiverCommandsClass::FIFOStatusReply ESAT_COMTransceiverCommandsClass::getFIFOStatus(ESAT_COMTransceiverHALClass& transceiver, boolean resetTransmissionFIFO, boolean resetReceptionFIFO)
{
  uint8_t cmdBuff[2];
  FIFOStatusReply fifoStatusReply;  
  cmdBuff[0] = COMMAND_GET_FIFO_STATUS;
  cmdBuff[1] = 0;
  if (resetTransmissionFIFO)
  {
    cmdBuff[1] |= FIFO_STATUS_ARGUMENT_TRANSMISSION_FIFO_BITMASK;
  }
  if (resetReceptionFIFO)
  {
    cmdBuff[1] |= FIFO_STATUS_ARGUMENT_RECEPTION_FIFO_BITMASK;
  }
  transceiver.writeCommandAndRetrieveResponse(COMMAND_GET_FIFO_STATUS_ARGUMENTS_COUNT,
                                  cmdBuff,
                                  COMMAND_GET_FIFO_STATUS_REPLY_COUNT,
                                  cmdBuff);
  fifoStatusReply.receptionFIFOCount     = cmdBuff[0];
  fifoStatusReply.transmissionFIFOSpace  = cmdBuff[1];  
  return fifoStatusReply;
}

uint8_t ESAT_COMTransceiverCommandsClass::getGPIOConfigurationMask(ESAT_COMTransceiverCommandsClass::GPIOConfigurationArguments arguments)
{
  switch(arguments)
  {
      default:
      case DONOTHING:
        return 0;
      case TRISTATE:
        return 1;
      case DRIVE0:
        return 2;
      case DRIVE1:
        return 3;
      case INPUT_READ:
        return 4;
      case CTS:
        return 8;
      case INV_CTS:
        return 9;
      case POR:
        return 12;
      case TX_DATA_CLK:
        return 16;
      case RX_DATA_CLK:
        return 17;
      case TX_DATA:
        return 19;
      case RX_DATA:
        return 20;
      case RX_RAW_DATA:
        return 21;
      case RX_FIFO_FULL:
        return 34;
      case TX_FIFO_EMPTY:
        return 35;
  }
}

uint8_t ESAT_COMTransceiverCommandsClass::getGPIODriveStrengthMask(GPIODriveStrength strength)
{
  switch (strength)
  {    
    case RADIO_HIGH:
      return (0 << 5);
    case RADIO_MED_HIGH:
      return (1 << 5);
    case RADIO_MED_LOW:
      return (2 << 5);
    default:
    case RADIO_LOW:
      return (3 << 5);
  }
}

uint8_t ESAT_COMTransceiverCommandsClass::getGPIOPullUpMask(boolean pullUpEnabled)
{
  if (pullUpEnabled)
  {
    return (1 << 6);    
  }
  return 0;
}

ESAT_COMTransceiverCommandsClass::InterruptStatusReply ESAT_COMTransceiverCommandsClass::getInterruptStatus(ESAT_COMTransceiverHALClass& transceiver, uint8_t packetHandlerClearingPendingInterruptsMask, uint8_t modemClearingPendingInterruptsMask, uint8_t chipClearingPendingInterruptsMask)
{
  uint8_t cmdBuff[8];
  InterruptStatusReply interruptStatusReply;
  cmdBuff[0] = COMMAND_GET_INTERRUPTS_STATUS;
  cmdBuff[1] = packetHandlerClearingPendingInterruptsMask;
  cmdBuff[2] = modemClearingPendingInterruptsMask;
  cmdBuff[3] = chipClearingPendingInterruptsMask;    
  transceiver.writeCommandAndRetrieveResponse(COMMAND_GET_INTERRUPTS_STATUS_ARGUMENTS_COUNT,
                                  cmdBuff,
                                  COMMAND_GET_INTERRUPTS_STATUS_REPLY_COUNT,
                                  cmdBuff);
  interruptStatusReply.interruptPending     = cmdBuff[0];
  interruptStatusReply.interruptStatus      = cmdBuff[1];
  interruptStatusReply.packetHandlerPending = cmdBuff[2];
  interruptStatusReply.packetHandlerStatus  = cmdBuff[3];
  interruptStatusReply.modemPending         = cmdBuff[4];
  interruptStatusReply.modemStatus          = cmdBuff[5];
  interruptStatusReply.chipPending          = cmdBuff[6];
  interruptStatusReply.chipStatus           = cmdBuff[7];  
  return interruptStatusReply;
}

ESAT_COMTransceiverCommandsClass::ModemStatusReply ESAT_COMTransceiverCommandsClass::getModemStatus(ESAT_COMTransceiverHALClass& transceiver, uint8_t clearPendingFlagsMask)
{
  uint8_t cmdBuff[8];
  ModemStatusReply modemStatusReply;  
  cmdBuff[0] = COMMAND_GET_MODEM_STATUS;
  cmdBuff[1] = clearPendingFlagsMask;
  transceiver.writeCommandAndRetrieveResponse(COMMAND_GET_MODEM_STATUS_ARGUMENTS_COUNT,
                                  cmdBuff,
                                  COMMAND_GET_MODEM_STATUS_REPLY_COUNT,
                                  cmdBuff);
  modemStatusReply.modemPending                               = cmdBuff[0];
  modemStatusReply.modemStatus                                = cmdBuff[1];
  modemStatusReply.currentReceivedSignalStregnthIndicator     = cmdBuff[2];
  modemStatusReply.latchedReceivedSignalStrengthIndicator     = cmdBuff[3];
  modemStatusReply.antenna1ReceivedSignalStrengthIndicator    = cmdBuff[4];
  modemStatusReply.antenna2ReceivedSignalStrengthIndicator    = cmdBuff[5];  
  modemStatusReply.automaticFrequencyControlFrequencyOffset   = ((uint16_t)cmdBuff[6] << 8) & 0xFF00;
  modemStatusReply.automaticFrequencyControlFrequencyOffset  |= (uint16_t)cmdBuff[7] & 0x00FF;    
  return modemStatusReply;
}

ESAT_COMTransceiverCommandsClass::PropertiesReply ESAT_COMTransceiverCommandsClass::getProperty(ESAT_COMTransceiverHALClass& transceiver, uint8_t group, uint8_t numProperties, uint8_t startingProperty)
{
  uint8_t cmdBuff[16];
  PropertiesReply propertyReply;  
  cmdBuff[0] = COMMAND_GET_PROPERTY;
  cmdBuff[1] = group;
  cmdBuff[2] = numProperties;
  cmdBuff[3] = startingProperty;
  transceiver.writeCommandAndRetrieveResponse(COMMAND_GET_PROPERTY_ARGUMENTS_COUNT,
                                  cmdBuff,
                                  numProperties,
                                  cmdBuff);
  propertyReply.buffer[0]    = cmdBuff[0];
  propertyReply.buffer[1]    = cmdBuff[1];
  propertyReply.buffer[2]    = cmdBuff[2];
  propertyReply.buffer[3]    = cmdBuff[3];
  propertyReply.buffer[4]    = cmdBuff[4];
  propertyReply.buffer[5]    = cmdBuff[5];
  propertyReply.buffer[6]    = cmdBuff[6];
  propertyReply.buffer[7]    = cmdBuff[7];
  propertyReply.buffer[8]    = cmdBuff[8];
  propertyReply.buffer[9]    = cmdBuff[9];
  propertyReply.buffer[10]   = cmdBuff[10];
  propertyReply.buffer[11]   = cmdBuff[11];
  propertyReply.buffer[12]   = cmdBuff[12];
  propertyReply.buffer[13]   = cmdBuff[13];
  propertyReply.buffer[14]   = cmdBuff[14];
  propertyReply.buffer[15]   = cmdBuff[15];  
  return propertyReply;
}

ESAT_COMTransceiverCommandsClass::PartInfoReply ESAT_COMTransceiverCommandsClass::partInfo(ESAT_COMTransceiverHALClass& transceiver)
{
    uint8_t cmdBuff[8];
    ESAT_COMTransceiverCommandsClass::PartInfoReply partInfoReply;  
    cmdBuff[0] = COMMAND_PART_INFO;
    transceiver.writeCommandAndRetrieveResponse(COMMAND_PART_INFO_ARGUMENTS_COUNT,
                                    cmdBuff,
                                    COMMAND_PART_INFO_REPLY_COUNT,
                                    cmdBuff);
    partInfoReply.chipRevision  = cmdBuff[0];
    partInfoReply.partNumber    = ((uint16_t)cmdBuff[1] << 8) & 0xFF00;
    partInfoReply.partNumber   |= (uint16_t)cmdBuff[2] & 0x00FF;
    partInfoReply.partBuild     = cmdBuff[3];
    partInfoReply.ID            = ((uint16_t)cmdBuff[4] << 8) & 0xFF00;
    partInfoReply.ID           |= (uint16_t)cmdBuff[5] & 0x00FF;
    partInfoReply.customerID    = cmdBuff[6];
    partInfoReply.ROMID         = cmdBuff[7];  
  return partInfoReply;
}

void ESAT_COMTransceiverCommandsClass::powerUp(ESAT_COMTransceiverHALClass& transceiver)
{
    uint32_t crystalFrequency = 0x01C9C380;
    uint8_t cmdBuff[COMMAND_POWER_UP_ARGUMENTS_COUNT];
    cmdBuff[0] = COMMAND_POWER_UP;
    cmdBuff[1] = 0x81;
    cmdBuff[2] = 0x00;
    cmdBuff[3] = (uint8_t)(crystalFrequency >> 24);
    cmdBuff[4] = (uint8_t)(crystalFrequency >> 16);
    cmdBuff[5] = (uint8_t)(crystalFrequency >> 8);
    cmdBuff[6] = (uint8_t)(crystalFrequency);
    transceiver.writeCommand( COMMAND_POWER_UP_ARGUMENTS_COUNT, cmdBuff);
}

void ESAT_COMTransceiverCommandsClass::readReceptionFIFOBuffer(ESAT_COMTransceiverHALClass& transceiver, uint8_t length, uint8_t* dataReadBuffer)
{
  transceiver.readData(COMMAND_READ_RECEPTION_FIFO, length, dataReadBuffer);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COMTransceiverCommandsClass::setProperty(ESAT_COMTransceiverHALClass& transceiver, uint8_t group, uint8_t numProperties, uint8_t startingProperty, uint8_t* properties)
{
  if (numProperties > 12)
  {
    return ESAT_COMTransceiverHALClass::TRANSCEIVER_COMMAND_ERROR;
  }
  uint8_t cmdIndex;
  uint8_t cmdBuff[16];
  cmdBuff[0] = COMMAND_SET_PROPERTY;
  cmdBuff[1] = group;
  cmdBuff[2] = numProperties;
  cmdBuff[3] = startingProperty;  
  for (cmdIndex = 0; cmdIndex < 12 && numProperties > 0; ++cmdIndex, --numProperties)
  {
    cmdBuff[cmdIndex + 4] = properties[cmdIndex];
  }
  if (transceiver.writeCommandAndRetrieveResponse(cmdIndex + 4, cmdBuff, 0, 0) != 0xFF)
  {
    // Timeout.
    return ESAT_COMTransceiverHALClass::TRANSCEIVER_CTS_TIMEOUT;
  }
  if (transceiver.checkInterruptPin() == 0)
  {
     return ESAT_COMTransceiverHALClass::TRANSCEIVER_CHIP_ERROR;
  }
  return ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS;
}

void ESAT_COMTransceiverCommandsClass::startReception(ESAT_COMTransceiverHALClass& transceiver, uint8_t channel, uint16_t receptionLength)
{
  uint8_t cmdBuff[8];  
  cmdBuff[0] = COMMAND_START_RECEPTION;
  cmdBuff[1] = channel;
  cmdBuff[2] = 0x00; // Condition
  cmdBuff[3] = (uint8_t)(receptionLength >> 8);
  cmdBuff[4] = (uint8_t)(receptionLength);
  cmdBuff[5] = START_RECEPTION_ARGUMENT_NEXT_STATE_1_RECEPTION_TIMEOUT_STATE_NO_CHANGE;
  cmdBuff[6] = START_RECEPTION_ARGUMENT_NEXT_STATE_2_RECEPTION_VALID_STATE_READY;
  cmdBuff[7] = START_RECEPTION_ARGUMENT_NEXT_STATE_3_RECEPTION_INVALID_STATE_RECEPTION;
  transceiver.writeCommand(COMMAND_START_RECEPTION_ARGUMENTS_COUNT, cmdBuff);
}

void ESAT_COMTransceiverCommandsClass::startTransmission(ESAT_COMTransceiverHALClass& transceiver, uint8_t channel, uint16_t transmissionLength)
{
  uint8_t cmdBuff[7];
  cmdBuff[0] = COMMAND_START_TRANSMISSION;
  cmdBuff[1] = channel;
  cmdBuff[2] = 0x30;
  cmdBuff[3] = (uint8_t)(transmissionLength >> 8);
  cmdBuff[4] = (uint8_t)(transmissionLength);
  cmdBuff[5] = 0x00;  
  // Don't repeat the packet, 
  // ie. transmit the packet only once.
  cmdBuff[6] = 0x00;
  transceiver.writeCommand(COMMAND_START_TRANSMISSION_ARGUMENTS_COUNT, cmdBuff);
}

void ESAT_COMTransceiverCommandsClass::writeTransmissionFIFOBuffer(ESAT_COMTransceiverHALClass& transceiver, uint8_t length, uint8_t* dataToBeWritten)
{
  transceiver.writeData(COMMAND_WRITE_TRANSMISSION_FIFO, length, dataToBeWritten);
} 

ESAT_COMTransceiverCommandsClass ESAT_COMTransceiverCommands;