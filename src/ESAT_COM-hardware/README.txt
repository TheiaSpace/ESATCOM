Copyright (C) 2021 Theia Space, Universidad Politécnica de Madrid

This file is part of Theia Space's ESAT COM library.

Theia Space's ESAT COM library is free software: you can
redistribute it and/or modify it under the terms of the GNU General
Public License as published by the Free Software Foundation, either
version 3 of the License, or (at your option) any later version.

Theia Space's ESAT COM library is distributed in the hope that it
will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Theia Space's ESAT COM library.  If not, see
<http://www.gnu.org/licenses/>.


Drivers for COM peripherals.  They are used by ESAT_COM.


# ESAT_COMBuiltinHardwareClock

Hardware real-time clock.


# ESAT_COMHeartBeatLED

Heartbeat LED of the COM board.


# ESAT_COMNonVolatileDataStorage

COM no volatile data storage controller.  Handles and stores all
configuration parameters into non volatile memory to have persistence
between reboots.


# ESAT_COMRadioStream

Stream interface for radio communication.


# ESAT_COMReceptionLED

Reception heartbeat LED on the COM board.


# ESAT_COMSequenceGenerator

Periodic task for varying the sequence.


# ESAT_COMTransceiverCommands

Transceiver's SPI commands.


# ESAT_COMTransceiverDriver

Driver of the transceiver.


# ESAT_COMTransceiverhal

Hardware abstraction layer of the transceiver.


# ESAT_COMTransceiverProperties

Transceiver properties that can be read or written using
ESAT_COMTransceiverCommands.


# ESAT_COMTransmissionLED

Transmission heartbeat LED on the COM board.


# ESAT_COMHousekeepingTelemetry

Fill the COM_HOUSEKEEPING (0x00) telemetry packet.


# configurations/ESAT_COMTransceiverConfiguration

Abstract class for setting the transceiver properties according to the
desired working mode and modulation.


# configurations/ESAT_COM2FSKReceptionConfiguration

Configuration for reception with 2FSK modulation.


# configurations/ESAT_COM2FSKTransmissionConfiguration

Configuration for transmission with 2FSK modulation.


# configurations/ESAT_COM2GFSKReceptionConfiguration

Configuration for reception with 2GFSK modulation.


# configurations/ESAT_COM2GFSKTransmissionConfiguration

Configuration for transmission with 2GFSK modulation.


# configurations/ESAT_COM4FSKReceptionConfiguration

Configuration for reception with 4FSK modulation.


# configurations/ESAT_COM4FSKTransmissionConfiguration

Configuration for transmission with 4FSK modulation.


# configurations/ESAT_COM4GFSKReceptionConfiguration

Configuration for reception with 4GFSK modulation.


# configurations/ESAT_COM4GFSKTransmissionConfiguration

Configuration for transmission with 4GFSK modulation.


# configurations/ESAT_COMOOKReceptionConfiguration

Configuration for reception with OOK modulation.


# configurations/ESAT_COMOOKTransmissionConfiguration

Configuration for transmission with OOK modulation.
