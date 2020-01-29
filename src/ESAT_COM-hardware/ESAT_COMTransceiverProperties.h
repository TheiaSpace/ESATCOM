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
#ifndef ESAT_COMTransceiverProperties_h
#define ESAT_COMTransceiverProperties_h

#include <Arduino.h>

// List of Si44463 transceiver properties.
static const uint8_t PROPERTY_GLOBAL = 0;
static const uint8_t PROPERTY_INTERRUPTS_CONTROL = 1;
static const uint8_t PROPERTY_FAST_RESPONSE_REGISTERS_CONTROL = 2;
static const uint8_t PROPERTY_PREAMBLE = 16;
static const uint8_t PROPERTY_PACKET = 18;
static const uint8_t PROPERTY_MODEM = 32;
static const uint8_t PROPERTY_MODEM_FILTER_COEFFICIENTES = 33;
static const uint8_t PROPERTY_POWER_AMPLIFIER = 34;
static const uint8_t PROPERTY_SYNTHESIZER = 35;
static const uint8_t PROPERTY_MATCH = 48;
static const uint8_t PROPERTY_FREQUENCY_CONTROL = 64;
static const uint8_t PROPERTY_RECEPTION_HOP = 80;

// Transceiver properties parameters.
// Format: PARAMETER_[PROPERTY]_[GROUP].
// Parameters for PROPERTY_MODEM (32).
static const uint8_t PARAMETER_MODEM_MODULATION_TYPE = 0;
static const uint8_t PARAMETER_MODEM_CLOCK_GENERATOR_BAND = 81;
// Parameters for PROPERTY_POWER_AMPLIFIER (34).
static const uint8_t PARAMETER_POWER_AMPLIFIER_POWER_LEVEL = 1;
// Parameters for PROPERTY_FREQUENCY_CONTROL (64).
static const uint8_t PARAMETER_FREQUENCY_CONTROL_INTEGER = 0;

// Transceiver properties parameters fields masks.
// Format: PARAMETER_[PROPERTY]_[GROUP]_[VALUE]_MASK.
// Masks for PARAMETER_MODEM_MODULATION_TYPE (0).
// Modulation type bitfields [2:0].
static const uint8_t PARAMETER_MODEM_MODULATION_TYPE_CONTINUOUS_WAVE_MASK = 0x0;
static const uint8_t PARAMETER_MODEM_MODULATION_TYPE_OOK_MASK = 0x1;
static const uint8_t PARAMETER_MODEM_MODULATION_TYPE_2FSK_MASK = 0x2;
static const uint8_t PARAMETER_MODEM_MODULATION_TYPE_2GFSK_MASK = 0x3;
static const uint8_t PARAMETER_MODEM_MODULATION_TYPE_4FSK_MASK = 0x4;
static const uint8_t PARAMETER_MODEM_MODULATION_TYPE_4GFSK_MASK = 0x5;
// Masks for PARAMETER_MODEM_MODULATION_TYPE (0).
// Modulation source bitfields [7:3].
static const uint8_t PARAMETER_MODEM_MODULATION_TYPE_PACKET_HANDLER_MASK = 0x0;
static const uint8_t PARAMETER_MODEM_MODULATION_TYPE_GPIO0_SYNCHRONOUS_MASK = 0x8;
static const uint8_t PARAMETER_MODEM_MODULATION_TYPE_GPIO0_ASYNCHRONOUS_MASK = 0x88;
static const uint8_t PARAMETER_MODEM_MODULATION_TYPE_GPIO1_SYNCHRONOUS_MASK = 0x28;
static const uint8_t PARAMETER_MODEM_MODULATION_TYPE_GPIO1_ASYNCHRONOUS_MASK = 0xA8;
static const uint8_t PARAMETER_MODEM_MODULATION_TYPE_GPIO2_SYNCHRONOUS_MASK = 0x48;
static const uint8_t PARAMETER_MODEM_MODULATION_TYPE_GPIO2_ASYNCHRONOUS_MASK = 0xC8;
static const uint8_t PARAMETER_MODEM_MODULATION_TYPE_GPIO3_SYNCHRONOUS_MASK = 0x68;
static const uint8_t PARAMETER_MODEM_MODULATION_TYPE_GPIO3_ASYNCHRONOUS_MASK = 0xE8;
static const uint8_t PARAMETER_MODEM_MODULATION_TYPE_RANDOM_GENERATOR_MASK = 0x10;
// Masks for PARAMETER_MODEM_CLOCK_GENERATOR_BAND (81).
static const uint8_t PARAMETER_MODEM_CLOCK_GENERATOR_BAND_HIGH_PERFORMANCE_MASK = 0x8;

#endif /*ESAT_COMTransceiverProperties_h*/