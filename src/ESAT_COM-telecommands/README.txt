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


# ESAT_COMTransmitterEnableTelecommand

Telecommand handler for COM_TRANSMITTER_ENABLE (0x02): turn on the transmission
transceiver and start the transmission.


# ESAT_COMTransmitterDisableTelecommand

Telecommand handler for COM_TRANSMITTER_DISABLE (0x03): turn off the transmission
transceiver and disable the transmission.


# ESAT_COMReceiverEnableTelecommand

Telecommand handler for COM_RECEIVER_ENABLE (0x04): turn on the reception
transceiver and start the reception.


# ESAT_COMReceiverDisableTelecommand

Telecommand handler for COM_RECEIVER_DISABLE (0x05): turn off the reception
transceiver and disable the reception.


# ESAT_COMSetTimeTelecommand

Telecommand handler for COM_SET_TIME (0x06): set the time of the real-time clock 
of the ESAT COM board.


# ESAT_COMTransmitterOOKModulationSelectionTelecommand

Telecommand handler for COM_TRANSMITTER_OOK_MODULATION_SELECTION (0x10):
configure the on-board radiofrequency transmitter to use on-off keying 
modulation (OOK).


# ESAT_COMTransmitter2FSKModulationSelectionTelecommand

Telecommand handler for COM_TRANSMITTER_2FSK_MODULATION_SELECTION (0x11):
configure the on-board radiofrequency transmitter to use two frequency shift
keying modulation (2FSK).


# ESAT_COMTransmitter2GFSKModulationSelectionTelecommand

Telecommand handler for COM_TRANSMITTER_2GFSK_MODULATION_SELECTION (0x12):
configure the on-board radiofrequency transmitter to use two gaussian frequency 
shift keying modulation (2GFSK).


# ESAT_COMTransmitter4FSKModulationSelectionTelecommand

Telecommand handler for COM_TRANSMITTER_4FSK_MODULATION_SELECTION (0x13):
configure the on-board radiofrequency transmitter to use four frequency shift
keying modulation (4FSK).


# ESAT_COMTransmitter4GFSKModulationSelectionTelecommand

Telecommand handler for COM_TRANSMITTER_4GFSK_MODULATION_SELECTION (0x14):
configure the on-board radiofrequency transmitter to use four gaussian frequency 
shift keying modulation (4GFSK).


# ESAT_COMTransmitterChannelSelectionTelecommand

Telecommand handler for COM_TRANSMITTER_CHANNEL_SELECTION (0x15): configure the 
on-board radiofrequency transmitter transmission channel.


# ESAT_COMTransmitterFrequencySelectionTelecommand

Telecommand handler for COM_TRANSMITTER_FREQUENCY_SELECTION (0x16): configure the
on-board radiofrequency transmitter transmission central frequency.


# ESAT_COMTransmitterTransmissionPowerAdjustmentTelecommand

Telecommand handler for COM_TRANSMITTER_TRANSMISSION_POWER_ADJUSTMENT (0x17):
configure the transmitter output power.


# ESAT_COMTransmitterContinuousWaveSelectionTelecommand

Telecommand handler for COM_TRANSMITTER_CONTINUOUS_WAVE_SELECTION (0x18): configure
the transceiver to output a continuous carrier pilot waveform.


# ESAT_COMTransmitterEnableRandomGeneratorTelecommand

Telecommand handler for TRANSMITTER_ENABLE_RANDOM_GENERATOR (0x19): configure the
transceiver to output a stream of random data.


# ESAT_COMTransmitterDisableRandomGeneratorTelecommand

Telecommand handler for TRANSMITTER_DISABLE_RANDOM_GENERATOR (0x1A): configure the
transceiver to transmit the desired data.

# ESAT_COMTransmitterEnableModulationTestModeTelecommand

Telecommand handler for TRANSMITTER_ENABLE_MODULATION_TEST_MODE (0x1B): configure the
transceiver to output a "1-0-1-0" sequence.


# ESAT_COMTransmitterDisableModulationTestModeTelecommand

Telecommand handler for TRANSMITTER_DISABLE_MODULATION_TEST_MODE (0x1C): configure the
transceiver to transmit the desired data.


# ESAT_COMReceiverOOKModulationSelectionTelecommand

Telecommand handler for COM_RECEIVER_OOK_MODULATION_SELECTION (0x30):
configure the on-board radiofrequency receiver to use on-off keying 
modulation (OOK).


# ESAT_COMReceiver2FSKModulationSelectionTelecommand

Telecommand handler for COM_RECEIVER_2FSK_MODULATION_SELECTION (0x31):
configure the on-board radiofrequency receiver to use two frequency shift
keying modulation (2FSK).


# ESAT_COMReceiver2GFSKModulationSelectionTelecommand

Telecommand handler for COM_RECEIVER_2GFSK_MODULATION_SELECTION (0x32):
configure the on-board radiofrequency receiver to use two gaussian frequency 
shift keying modulation (2GFSK).


# ESAT_COMReceiver4FSKModulationSelectionTelecommand

Telecommand handler for COM_RECEIVER_4FSK_MODULATION_SELECTION (0x33):
configure the on-board radiofrequency receiver to use four frequency shift
keying modulation (4FSK).


# ESAT_COMReceiver4GFSKModulationSelectionTelecommand

Telecommand handler for COM_RECEIVER_4GFSK_MODULATION_SELECTION (0x34):
configure the on-board radiofrequency receiver to use four gaussian frequency 
shift keying modulation (4GFSK).


# ESAT_COMReceiverChannelSelectionTelecommand

Telecommand handler for COM_RECEIVER_CHANNEL_SELECTION (0x35): configure the 
on-board radiofrequency receiver reception channel.


# ESAT_COMReceiverFrequencySelectionTelecommand

Telecommand handler for COM_RECEIVER_FREQUENCY_SELECTION (0x36): configure the
on-board radiofrequency receiver reception central frequency.

