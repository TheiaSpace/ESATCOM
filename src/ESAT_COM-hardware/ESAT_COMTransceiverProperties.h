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
#ifndef ESAT_COMTransceiverProperties_h
#define ESAT_COMTransceiverProperties_h

#include <Arduino.h>

// This class contains the transceiver properties that can be read
// or written using ESAT_COMTransceiverCommandsClass.
class ESAT_COMTransceiverPropertiesClass
{
  public:

    // Global properties group number.
    static const byte PROPERTY_GLOBAL = 0;

    // Interrupts control properties group number.
    static const byte PROPERTY_INTERRUPTS_CONTROL = 1;

    // Fast response registers control properties number.
    static const byte PROPERTY_FAST_RESPONSE_REGISTERS_CONTROL = 2;

    // Preamble properties group number.
    static const byte PROPERTY_PREAMBLE = 16;

    // Sync properties group number.
    static const byte PROPERTY_SYNC = 17;

    // Packet properties group number.
    static const byte PROPERTY_PACKET = 18;

    // Modem properties group number.
    static const byte PROPERTY_MODEM = 32;

    // Filter coefficients properties group number.
    static const byte PROPERTY_MODEM_FILTER_COEFFICIENTES = 33;

    // Power amplifier properties group number.
    static const byte PROPERTY_POWER_AMPLIFIER = 34;

    // Synthesizer properties group number.
    static const byte PROPERTY_SYNTHESIZER = 35;

    // Match properties group number.
    static const byte PROPERTY_MATCH = 48;

    // Frequency control properties group number.
    static const byte PROPERTY_FREQUENCY_CONTROL = 64;

    // Reception hop properties group number.
    static const byte PROPERTY_RECEPTION_HOP = 80;

    // Transceiver properties parameters.
    // Format: PARAMETER_[PROPERTY]_[GROUP].
    // Parameters for PROPERTY_MODEM (32).
    static const byte PARAMETER_MODEM_MODULATION_TYPE = 0;
    static const byte PARAMETER_MODEM_CLOCK_GENERATOR_BAND = 81;
    // Parameters for PROPERTY_POWER_AMPLIFIER (34).
    static const byte PARAMETER_POWER_AMPLIFIER_POWER_LEVEL = 1;
    // Parameters for PROPERTY_FREQUENCY_CONTROL (64).
    static const byte PARAMETER_FREQUENCY_CONTROL_INTEGER = 0;

    // Transceiver properties parameters fields masks.
    // Format: PARAMETER_[PROPERTY]_[GROUP]_[VALUE]_MASK.
    // Masks for PARAMETER_MODEM_MODULATION_TYPE (0).
    // Modulation type bitfields [2:0].
    static const byte PARAMETER_MODEM_MODULATION_TYPE_CONTINUOUS_WAVE_MASK = 0x0;
    static const byte PARAMETER_MODEM_MODULATION_TYPE_OOK_MASK = 0x1;
    static const byte PARAMETER_MODEM_MODULATION_TYPE_2FSK_MASK = 0x2;
    static const byte PARAMETER_MODEM_MODULATION_TYPE_2GFSK_MASK = 0x3;
    static const byte PARAMETER_MODEM_MODULATION_TYPE_4FSK_MASK = 0x4;
    static const byte PARAMETER_MODEM_MODULATION_TYPE_4GFSK_MASK = 0x5;
    // Masks for PARAMETER_MODEM_MODULATION_TYPE (0).
    // Modulation source bitfields [7:3].
    static const byte PARAMETER_MODEM_MODULATION_TYPE_PACKET_HANDLER_MASK = 0x0;
    static const byte PARAMETER_MODEM_MODULATION_TYPE_GPIO0_SYNCHRONOUS_MASK = 0x8;
    static const byte PARAMETER_MODEM_MODULATION_TYPE_GPIO0_ASYNCHRONOUS_MASK = 0x88;
    static const byte PARAMETER_MODEM_MODULATION_TYPE_GPIO1_SYNCHRONOUS_MASK = 0x28;
    static const byte PARAMETER_MODEM_MODULATION_TYPE_GPIO1_ASYNCHRONOUS_MASK = 0xA8;
    static const byte PARAMETER_MODEM_MODULATION_TYPE_GPIO2_SYNCHRONOUS_MASK = 0x48;
    static const byte PARAMETER_MODEM_MODULATION_TYPE_GPIO2_ASYNCHRONOUS_MASK = 0xC8;
    static const byte PARAMETER_MODEM_MODULATION_TYPE_GPIO3_SYNCHRONOUS_MASK = 0x68;
    static const byte PARAMETER_MODEM_MODULATION_TYPE_GPIO3_ASYNCHRONOUS_MASK = 0xE8;
    static const byte PARAMETER_MODEM_MODULATION_TYPE_RANDOM_GENERATOR_MASK = 0x10;
    // Masks for PARAMETER_MODEM_CLOCK_GENERATOR_BAND (81).
    static const byte PARAMETER_MODEM_CLOCK_GENERATOR_BAND_HIGH_PERFORMANCE_MASK = 0x8;
};

#endif /*ESAT_COMTransceiverProperties_h*/