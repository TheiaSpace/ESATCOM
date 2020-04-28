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
#ifndef ESAT_COMTransceiverConfiguration_h
#define ESAT_COMTransceiverConfiguration_h

#include <Arduino.h>
#include "../ESAT_COMTransceiverHAL.h"
#include "../ESAT_COMTransceiverCommands.h"
#include "../ESAT_COMTransceiverProperties.h"

class ESAT_COMTransceiverConfigurationClass
{
  public:
    
    virtual ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError applyConfiguration(ESAT_COMTransceiverHALClass& transceiver) = 0;
    
   ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError setTransmissionPower(ESAT_COMTransceiverHALClass& transceiver,
                                                                                    uint8_t power)
   {
     const uint8_t numProperties = 2;
     const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_POWER_AMPLIFIER;
     const uint8_t offset = ESAT_COMTransceiverPropertiesClass::PARAMETER_POWER_AMPLIFIER_POWER_LEVEL;
     uint8_t cmdBuff[numProperties];
     cmdBuff[0] = power;
     cmdBuff[1] = 0;
     return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
   }
   
   ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureClockGenerator(ESAT_COMTransceiverHALClass& transceiver,
                                                                                       uint8_t clkGenBand)
    {
     const uint8_t numProperties = 1;
     const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
     const uint8_t offset = ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_CLOCK_GENERATOR_BAND;
     uint8_t cmdBuff[numProperties];     
     cmdBuff[0] = clkGenBand | ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_CLOCK_GENERATOR_BAND_HIGH_PERFORMANCE_MASK;
     return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
    }
    
   ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError setFrequency(ESAT_COMTransceiverHALClass& transceiver,
                                                                            uint8_t PLLInteger,
                                                                            uint8_t PLLFractionalMSB,
                                                                            uint8_t PLLFractionalMiddle,
                                                                            uint8_t PLLFractionalLSB)
   {
     const uint8_t numProperties = 4;
     const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_FREQUENCY_CONTROL;
     const uint8_t offset = ESAT_COMTransceiverPropertiesClass::PARAMETER_FREQUENCY_CONTROL_INTEGER;
     uint8_t cmdBuff[numProperties];
     cmdBuff[0] = PLLInteger;
     cmdBuff[1] = PLLFractionalMSB;
     cmdBuff[2] = PLLFractionalMiddle;
     cmdBuff[3] = PLLFractionalLSB;
     return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
   }
   
   ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModulationSource(ESAT_COMTransceiverHALClass& transceiver,
                                                                                         uint8_t modulationSourceMask)
   {
     const uint8_t numProperties = 1;
     const uint8_t group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
     const uint8_t offset = ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_MODULATION_TYPE;
     uint8_t cmdBuff[numProperties];
     cmdBuff[0] = modulationSourceMask;
     return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
   }
};

#endif /*ESAT_COMTransceiverConfiguration_h*/