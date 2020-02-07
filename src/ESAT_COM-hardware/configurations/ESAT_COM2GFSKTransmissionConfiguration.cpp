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
#include "ESAT_COM2GFSKTransmissionConfiguration.h"

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::applyConfiguration(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  
  ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError returnBuff;
  returnBuff = configureGlobalProperties(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureInterrupts(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }    
  returnBuff = configureFastResponseRegisterA(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureFastResponseRegisterB(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureFastResponseRegisterC(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureFastResponseRegisterD(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }

  returnBuff = configurePreamble(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePreambleLength(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePreamblePattern(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }

  returnBuff = configureSyncWord(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }

  returnBuff = configurePacket(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketCRC(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketWhitening(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketLength(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketFIFOThresholds(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketField1(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketField2(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketField3(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketField4(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketField5(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketReceptionField1(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketReceptionField2(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketReceptionField3(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketReceptionField4(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketReceptionField5(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }

  returnBuff = configureModemModulationType(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemMappingControl(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemDSMControl(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemDataRate(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemTransmissionNCO(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemFrequencyDeviation(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemTransmissionRampDown(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemMDMControl(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemIFControl(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemDecimationControl(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemIFPKDThresholds(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemBCR(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemAFC(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemAGC(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemFSK4(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemOOK(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemRawEyeControl(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemAntennaDiversity(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemRawSearch2(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemClockGeneratorBand(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemSpikeDetector(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemOneShotAFC(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemDSA(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }

  returnBuff = configureReceptionFilter1Coefficients(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureReceptionFilter2Coefficients(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }

  returnBuff = configurePowerAmplifier(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }

  returnBuff = configureSynthesizer(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }

  returnBuff = configureMatch1(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureMatch2(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureMatch3(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureMatch4(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  
  returnBuff = configureFrequencyControl(transceiver);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  return ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS;
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureGlobalProperties(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 2;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_GLOBAL;
  uint8_t offset = 0x00;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x52;
  cmdBuff[1] = 0x00;  
  ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError returnBuff = ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  const uint8_t numProperties2 = 1;
  offset = 0x03;
  cmdBuff[0] = 0x31;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties2, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureInterrupts(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 2;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_INTERRUPTS_CONTROL;
  uint8_t offset = 0x00;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x01;
  cmdBuff[1] = 0x20;  
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureFastResponseRegisterA(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 1;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_FAST_RESPONSE_REGISTERS_CONTROL;
  uint8_t offset = 0x00;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureFastResponseRegisterB(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 1;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_FAST_RESPONSE_REGISTERS_CONTROL;
  uint8_t offset = 0x01;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureFastResponseRegisterC(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 1;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_FAST_RESPONSE_REGISTERS_CONTROL;
  uint8_t offset = 0x02;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureFastResponseRegisterD(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 1;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_FAST_RESPONSE_REGISTERS_CONTROL;
  uint8_t offset = 0x03;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePreambleLength(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 1;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PREAMBLE;
  uint8_t offset = 0x00;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x08;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePreamble(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 4;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PREAMBLE;
  uint8_t offset = 0x01;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x14;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x0F;
  cmdBuff[3] = 0x31;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePreamblePattern(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 4;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PREAMBLE;
  uint8_t offset = 0x05;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);  
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureSyncWord(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 6;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_SYNC;
  uint8_t offset = 0x00;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x13;
  cmdBuff[1] = 0xD6;
  cmdBuff[2] = 0xD6;
  cmdBuff[3] = 0xD6;
  cmdBuff[4] = 0xD6;
  cmdBuff[5] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);  
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketCRC(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 1;
  const uint8_t numProperties2 = 4;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  uint8_t offset = 0x00;
  uint8_t cmdBuff[numProperties2];  
  cmdBuff[0] = 0x00; 
  ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError returnBuff = ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }  
  offset = 0x36;
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties2, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketWhitening(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 5;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  uint8_t offset = 0x01;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x01;
  cmdBuff[1] = 0x08;
  cmdBuff[2] = 0xFF;
  cmdBuff[3] = 0xFF;
  cmdBuff[4] = 0x20;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);  
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacket(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 2;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  uint8_t offset = 0x06;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x02;
  cmdBuff[1] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);  
}


ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketLength(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 3;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  uint8_t offset = 0x08;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);    
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketFIFOThresholds(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 2;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  uint8_t offset = 0x0B;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x81;
  cmdBuff[1] = 0x30;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);    
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketField1(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 4;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  uint8_t offset = 0x0D;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x81;
  cmdBuff[2] = 0x04;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);    
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketField2(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 4;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  uint8_t offset = 0x11;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);    
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketField3(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 4;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  uint8_t offset = 0x15;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff); 
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketField4(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 4;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  uint8_t offset = 0x19;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff); 
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketField5(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 4;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  uint8_t offset = 0x1D;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff); 
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketReceptionField1(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 4;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  uint8_t offset = 0x21;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff); 
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketReceptionField2(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 4;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  uint8_t offset = 0x25;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff); 
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketReceptionField3(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 4;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  uint8_t offset = 0x29;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff); 
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketReceptionField4(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 4;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  uint8_t offset = 0x2D;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff); 
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketReceptionField5(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 4;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  uint8_t offset = 0x31;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff); 
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemModulationType(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 1;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x00;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x03;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);  
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemMappingControl(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 1;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x01;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);  
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemDSMControl(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 1;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x02;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x07;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);  
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemDataRate(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 3;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x03;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x05;
  cmdBuff[1] = 0xDC;
  cmdBuff[2] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff); 
}
ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemTransmissionNCO(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 4;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x06;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x05;
  cmdBuff[1] = 0xC9;
  cmdBuff[2] = 0xC3;
  cmdBuff[3] = 0x80;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff); 
}
ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemFrequencyDeviation(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 3;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x0A;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0xD2;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemTransmissionRampDown(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 1;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x18;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x01;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemMDMControl(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 1;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x19;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemIFControl(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 4;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x1A;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x08;
  cmdBuff[1] = 0x03;
  cmdBuff[2] = 0x80;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}
ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemDecimationControl(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 3;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x1E;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x30;
  cmdBuff[1] = 0x10;
  cmdBuff[2] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}
ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemIFPKDThresholds(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 1;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x21;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0xE8;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}
ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemBCR(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 10;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x22;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x82;
  cmdBuff[2] = 0x03;
  cmdBuff[3] = 0xEE;
  cmdBuff[4] = 0xA2;
  cmdBuff[5] = 0x06;
  cmdBuff[6] = 0x4D;
  cmdBuff[7] = 0x02;
  cmdBuff[8] = 0x00;
  cmdBuff[9] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemAFC(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 7;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x2C;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x12;
  cmdBuff[2] = 0x80;
  cmdBuff[3] = 0x54;
  cmdBuff[4] = 0x03;
  cmdBuff[5] = 0x22;
  cmdBuff[6] = 0xA0;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemAGC(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 1;
  const uint8_t numProperties2 = 3;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x35;
  uint8_t cmdBuff[numProperties2];  
  cmdBuff[0] = 0xE0; 
  ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError returnBuff = ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  offset = 0x38;
  cmdBuff[0] = 0x11;
  cmdBuff[1] = 0x1C;
  cmdBuff[2] = 0x1C;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties2, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemFSK4(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 5;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x3B;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x80;
  cmdBuff[1] = 0x1A;
  cmdBuff[2] = 0x28;
  cmdBuff[3] = 0x00;
  cmdBuff[4] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemOOK(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 4;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x40;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x29;
  cmdBuff[1] = 0x0C;
  cmdBuff[2] = 0xA4;
  cmdBuff[3] = 0x23;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemRawEyeControl(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 3;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x45;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x03;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x64;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}
ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemAntennaDiversity(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 2;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x48;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x01;
  cmdBuff[1] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemRSSI(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 1;
  const uint8_t numProperties2 = 2;
  const uint8_t numProperties3 = 1;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x4B;
  uint8_t cmdBuff[numProperties2];  
  cmdBuff[0] = 0x06; 
  ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError returnBuff = ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  offset = 0x4D;
  cmdBuff[0] = 0x18;
  cmdBuff[1] = 0x40;
  returnBuff = ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties2, offset, cmdBuff);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  offset = 0x57;
  cmdBuff[0] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties3, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemRawSearch2(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 1;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x50;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x84;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff); 
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemClockGeneratorBand(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 1;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x51;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x0A;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff); 
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemSpikeDetector(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 1;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x54;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x03;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff); 
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemOneShotAFC(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 1;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x55;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x07;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff); 
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemDSA(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 5;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  uint8_t offset = 0x5B;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x40;
  cmdBuff[1] = 0x04;
  cmdBuff[2] = 0x05;
  cmdBuff[3] = 0x78;
  cmdBuff[4] = 0x20;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff); 
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureReceptionFilter1Coefficients(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 12;
  const uint8_t numProperties2 = 6;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM_FILTER_COEFFICIENTES;
  uint8_t offset = 0x00;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0xFF;
  cmdBuff[1] = 0xC4;
  cmdBuff[2] = 0x30;
  cmdBuff[3] = 0x7F;
  cmdBuff[4] = 0xF5;
  cmdBuff[5] = 0xB5;
  cmdBuff[6] = 0xB8;
  cmdBuff[7] = 0xDE;
  cmdBuff[8] = 0x05;
  cmdBuff[9] = 0x17;
  cmdBuff[10] = 0x16;
  cmdBuff[11] = 0x0C;
  ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError returnBuff = ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  offset = 0x0C;
  cmdBuff[0] = 0x03;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x15;
  cmdBuff[3] = 0xFF;
  cmdBuff[4] = 0x00;
  cmdBuff[5] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties2, offset, cmdBuff); 
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureReceptionFilter2Coefficients(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 12;
  const uint8_t numProperties2 = 6;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM_FILTER_COEFFICIENTES;
  uint8_t offset = 0x12;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0xFF;
  cmdBuff[1] = 0xC4;
  cmdBuff[2] = 0x30;
  cmdBuff[3] = 0x7F;
  cmdBuff[4] = 0xF5;
  cmdBuff[5] = 0xB5;
  cmdBuff[6] = 0xB8;
  cmdBuff[7] = 0xDE;
  cmdBuff[8] = 0x05;
  cmdBuff[9] = 0x17;
  cmdBuff[10] = 0x16;
  cmdBuff[11] = 0x0C;
  ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError returnBuff = ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
  if (returnBuff != ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  offset = 0x1E;
  cmdBuff[0] = 0x03;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x15;
  cmdBuff[3] = 0xFF;
  cmdBuff[4] = 0x00;
  cmdBuff[5] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties2, offset, cmdBuff); 
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePowerAmplifier(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 4;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_POWER_AMPLIFIER;
  uint8_t offset = 0x00;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x08;
  cmdBuff[1] = 0x7F;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x1D;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureSynthesizer(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 7;;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_SYNTHESIZER;
  uint8_t offset = 0x00;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x2C;
  cmdBuff[1] = 0x0E;
  cmdBuff[2] = 0x0B;
  cmdBuff[3] = 0x04;
  cmdBuff[4] = 0x0C;
  cmdBuff[5] = 0x73;
  cmdBuff[6] = 0x03;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureMatch1(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 3;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MATCH;
  uint8_t offset = 0x00;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureMatch2(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 3;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MATCH;
  uint8_t offset = 0x03;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureMatch3(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 3;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MATCH;
  uint8_t offset = 0x06;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureMatch4(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 3;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MATCH;
  uint8_t offset = 0x09;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureFrequencyControl(ESAT_COMTransceiverInterfaceClass& transceiver)
{
  const uint8_t numProperties = 8;
  const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_FREQUENCY_CONTROL;
  uint8_t offset = 0x00;
  uint8_t cmdBuff[numProperties];  
  cmdBuff[0] = 0x39;
  cmdBuff[1] = 0x09;
  cmdBuff[2] = 0xEE;
  cmdBuff[3] = 0x40;
  cmdBuff[4] = 0x44;
  cmdBuff[5] = 0x44;
  cmdBuff[6] = 0x20;
  cmdBuff[7] = 0xFE;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COM2GFSKTransmissionConfigurationClass ESAT_COM2GFSKTransmissionConfiguration;