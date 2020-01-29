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

// List of Si44463 transceiver SPI commands.

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

#endif /*ESAT_COMTransceiverCommands_h*/