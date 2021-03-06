/*
 * Copyright (C) 2019, 2021 Theia Space, Universidad Politécnica de Madrid
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
#include <ProcessorTemperature.h>
#include <ProcessorVoltage.h>
#include <BatteryVoltage.h>
#include "ESAT_COM-hardware/ESAT_COMSequenceGenerator.h"
#include "ESAT_COM-hardware/ESAT_COMTransceiverDriver.h"

boolean ESAT_COMHousekeepingTelemetryClass::available()
{
  // The COM housekeeping telemetry packet is always available.
  return true;
}

boolean ESAT_COMHousekeepingTelemetryClass::fillUserData(ESAT_CCSDSPacket& packet)
{
  // Transmission transceiver telemetry.
  packet.writeByte((byte) ESAT_COMTransmissionTransceiver.getModulation());
  packet.writeFloat(ESAT_COMTransmissionTransceiver.getFrequency());
  packet.writeByte((byte) ESAT_COMTransmissionTransceiver.getChannel());
  packet.writeChar(writeModulationSource());
  packet.writeFloat(ESAT_COMTransmissionTransceiver.getTransmissionPowerRate());
  packet.writeFloat(ESAT_COMTransmissionTransceiver.getTransceiverVoltage());
  packet.writeFloat(ESAT_COMTransmissionTransceiver.getTransceiverTemperature());
  // Reception transceiver telemetry.
  packet.writeByte((byte) ESAT_COMReceptionTransceiver.getModulation());
  packet.writeFloat(ESAT_COMReceptionTransceiver.getFrequency());
  packet.writeByte((byte) ESAT_COMReceptionTransceiver.getChannel());
  packet.writeFloat(ESAT_COMReceptionTransceiver.getReceivedSignalStrengthIndicator());
  packet.writeFloat(ESAT_COMReceptionTransceiver.getTransceiverVoltage());
  packet.writeFloat(ESAT_COMReceptionTransceiver.getTransceiverTemperature());
  // MCU telemetry (calibrated)
  packet.writeFloat(ProcessorVoltage.read());
  packet.writeFloat(ProcessorTemperature.read());
  packet.writeFloat(BatteryVoltage.read());
  return true;
}

char ESAT_COMHousekeepingTelemetryClass::writeModulationSource()
{
  switch (ESAT_COMSequenceGenerator.getMode())
  {
    default:
    case 0: // Normal working
      return (char) ESAT_COMTransmissionTransceiver.getModulationSource();
    case 1: // Two levels sweep
      return 10;
    case 2: // Four levels sweep
      return 11;
  }
}

ESAT_COMHousekeepingTelemetryClass ESAT_COMHousekeepingTelemetry;
