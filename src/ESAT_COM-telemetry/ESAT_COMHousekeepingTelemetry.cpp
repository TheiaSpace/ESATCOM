/*
 * Copyright (C) 2019 Theia Space, Universidad Politécnica de Madrid
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
 

#include "ESAT_COM-telemetry/ESAT_COMHousekeepingTelemetry.h"
#include "../ESAT_COM-hardware/ESAT_COMTransceiverDriver.h"
#include <ProcessorTemperature.h>
#include <ProcessorVoltage.h>

boolean ESAT_COMHousekeepingTelemetryClass::available()
{
  // The COM housekeeping telemetry packet is always available.
  return true;
}

boolean ESAT_COMHousekeepingTelemetryClass::fillUserData(ESAT_CCSDSPacket& packet)
{
  // Transmission transceiver telemetry.
  packet.writeByte((byte) TransmissionTransceiver.getModulation());
  packet.writeFloat(TransmissionTransceiver.getFrequency());
  packet.writeByte((byte) TransmissionTransceiver.getChannel());
  packet.writeFloat(TransmissionTransceiver.getTransmissionPowerRate());
  packet.writeFloat(TransmissionTransceiver.getTransceiverVoltage());
  packet.writeFloat(TransmissionTransceiver.getTransceiverTemperature());
  // Reception transceiver telemetry.
  packet.writeByte((byte) ReceptionTransceiver.getModulation());
  packet.writeFloat(ReceptionTransceiver.getFrequency());
  packet.writeByte((byte) ReceptionTransceiver.getChannel());
  packet.writeFloat(ReceptionTransceiver.getReceivedSignalStrengthIndicator());
  packet.writeFloat(ReceptionTransceiver.getTransceiverVoltage());
  packet.writeFloat(ReceptionTransceiver.getTransceiverTemperature());  
  // MCU telemetry (calibrated)
  packet.writeFloat(ProcessorVoltage.read());
  packet.writeFloat(ProcessorTemperature.read());
  return true;
}

ESAT_COMHousekeepingTelemetryClass ESAT_COMHousekeepingTelemetry;
