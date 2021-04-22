/*
 * Copyright (C) 2020, 2021 Theia Space, Universidad Politécnica de Madrid
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

// Abstract class for setting the transceiver properties according to
// the desired working mode and modulation. User must extend this class
// implementing the applyConfiguration function according to the desired
// settings. This class also provides already implemented functions for
// configuring the common properties that the user can change (modulation
// source, frequency and transmission power).
class ESAT_COMTransceiverConfigurationClass
{
  public:

    // Pure virtual function for implementing the different configuration
    // variations according to the desired settings. It receives the
    // HAL reference of the transceiver that has to be configured and
    // returns any possible error. Used by the COM driver during initialization.
    virtual ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError applyConfiguration(ESAT_COMTransceiverHALClass& transceiver) = 0;

    // Configures the transmission power property to the selected transceiver.
    // Requires the transceiver HAL and the power value. Returns any possible error.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError setTransmissionPower(ESAT_COMTransceiverHALClass& transceiver,
                                                                                    byte power)
    {
      const byte numProperties = 2;
      const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_POWER_AMPLIFIER;
      const byte offset = ESAT_COMTransceiverPropertiesClass::PARAMETER_POWER_AMPLIFIER_POWER_LEVEL;
      byte cmdBuff[numProperties];
      cmdBuff[0] = power;
      cmdBuff[1] = 0;
      return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
    }

    // Configures the clock generator property of the selected transceiver.
    // This function is used for setting the radio central frequency.
    // Requires the transceiver HAL and the clock generator band. Returns
    // any possible error.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureClockGenerator(ESAT_COMTransceiverHALClass& transceiver,
                                                                                        byte clkGenBand)
    {
      const byte numProperties = 1;
      const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
      const byte offset = ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_CLOCK_GENERATOR_BAND;
      byte cmdBuff[numProperties];
      cmdBuff[0] = clkGenBand | ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_CLOCK_GENERATOR_BAND_HIGH_PERFORMANCE_MASK;
      return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
    }

    // Configures the central frequency  property of the selected transceiver.
    // Requires the transceiver HAL and the central frequency. Returns
    // any possible error.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError setFrequency(ESAT_COMTransceiverHALClass& transceiver,
                                                                             byte PLLInteger,
                                                                             byte PLLFractionalMSB,
                                                                             byte PLLFractionalMiddle,
                                                                             byte PLLFractionalLSB)
    {
      const byte numProperties = 4;
      const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_FREQUENCY_CONTROL;
      const byte offset = ESAT_COMTransceiverPropertiesClass::PARAMETER_FREQUENCY_CONTROL_INTEGER;
      byte cmdBuff[numProperties];
      cmdBuff[0] = PLLInteger;
      cmdBuff[1] = PLLFractionalMSB;
      cmdBuff[2] = PLLFractionalMiddle;
      cmdBuff[3] = PLLFractionalLSB;
      return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
    }

    // Configures the modulation source property of the selected transceiver.
    // Requires the transceiver HAL and the modulation source value. Returns
    // any possible error.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModulationSource(ESAT_COMTransceiverHALClass& transceiver,
                                                                                          byte modulationSourceMask)
    {
      const byte numProperties = 1;
      const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
      const byte offset = ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_MODULATION_TYPE;
      byte cmdBuff[numProperties];
      cmdBuff[0] = modulationSourceMask;
      return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
    }
};

#endif /*ESAT_COMTransceiverConfiguration_h*/