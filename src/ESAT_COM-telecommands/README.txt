Copyright (C) 2019 Theia Space, Universidad Politécnica de Madrid

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


COM telecommand handlers provide telecommand responses.  Each
telecommand handler implements the ESAT_CCSDSPacketConsumer interface
from ESATUtil and responds to one or several telecommands.  They are
used by ESAT_COM.


# ESAT_COMEnableTelemetryTelecommand

Telecommand handler for COM_ENABLE_TELEMETRY (0x00): enable the
generation of a COM telemetry packet.


#ESAT_COMDisableTelemetryTelecommand

Telecommand handler for COM_DISABLE_TELEMETRY (0x01): disable the
generation of a COM telemetry packet.


# ESAT_COMEnableTransmitterTelecommand

Telecommand handler for COM_ENABLE_TRANSMITTER (0x02): turn on the transmission
transceiver and start the transmission.


# ESAT_COMDisableTransmitterTelecommand

Telecommand handler for COM_DISABLE_TRANSMITTER (0x03): turn off the transmission
transceiver and disable the transmission.


# ESAT_COMEnableReceiverTelecommand

Telecommand handler for COM_ENABLE_RECEIVER (0x04): turn on the reception
transceiver and start the reception.


# ESAT_COMDisableReceiverTelecommand

Telecommand handler for COM_DISABLE_RECEIVER (0x05): turn off the reception
transceiver and disable the reception.


# ESAT_COMSetTimeTelecommand

Telecommand handler for COM_SET_TIME (0x06): set the time of the real-time clock
of the ESAT COM board.


# ESAT_COMEnableStandaloneModeTelecommand

Telecommand handler for COM_ENABLE_STANDALONE_MODE (0x07): enable the
COM telecommands self handling without OBC.


# ESAT_COMDisableStandaloneModeTelecommand

Telecommand handler for COM_DISABLE_STANDALONE_MODE (0x08): disable the
COM telecommands self handling without OBC.


# ESAT_COMStoreSettingsTelecommand

Telecommand handler for COM_STORE_SETTINGS (0x09): store the current
radio settings into non-volatile memory.


# ESAT_COMEraseStoredSettingsTelecommand

Telecommand handler for COM_ERASE_STORED_SETTINGS (0x0A): erase all
the settings stored in non-volatile memory.


# ESAT_COMTransmitterModulationSelectionTelecommand

Telecommand handler for COM_TRANSMITTER_MODULATION_SELECTION (0x10): configure
the on-board radiofrequency transmitter to use any of the 5 available
modulations plus continuous wave.


# ESAT_COMTransmitterChannelSelectionTelecommand

Telecommand handler for COM_TRANSMITTER_CHANNEL_SELECTION (0x11): configure the
on-board radiofrequency transmitter transmission channel.


# ESAT_COMTransmitterFrequencySelectionTelecommand

Telecommand handler for COM_TRANSMITTER_FREQUENCY_SELECTION (0x12): configure the
on-board radiofrequency transmitter transmission central frequency.


# ESAT_COMTransmitterTransmissionPowerAdjustmentTelecommand

Telecommand handler for COM_TRANSMITTER_TRANSMISSION_POWER_ADJUSTMENT (0x13):
configure the transmitter output power.


# ESAT_COMTransmitterDataSourceSelectionTelecommand

Telecommand handler for TRANSMITTER_DATA_SOURCE_SELECTION (0x14): configures
the transmitter data sequence to be broadcasted.


# ESAT_COMReceiverModulationSelectionTelecommand

Telecommand handler for COM_RECEIVER_MODULATION_SELECTION (0x30): configure
the on-board radiofrequency receiver to use any of the 5 available modulations.


# ESAT_COMReceiverChannelSelectionTelecommand

Telecommand handler for COM_RECEIVER_CHANNEL_SELECTION (0x31): configure the
on-board radiofrequency receiver reception channel.


# ESAT_COMReceiverFrequencySelectionTelecommand

Telecommand handler for COM_RECEIVER_FREQUENCY_SELECTION (0x32): configure the
on-board radiofrequency receiver reception central frequency.

