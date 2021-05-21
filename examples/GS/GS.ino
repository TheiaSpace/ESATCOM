/*
 * ESAT COM Ground Station Main Program version 1.0.0
 * Copyright (C) 2020, 2021 Theia Space, Universidad Politécnica
 * de Madrid.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Theia Space's ESAT OBC library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <ESAT_COM.h>
#include <ESAT_SubsystemPacketHandler.h>
#include <ESAT_Task.h>
#include <ESAT_TaskScheduler.h>
#include "ESAT_COM-hardware/ESAT_COMHeartBeatLED.h"
#include "ESAT_COM-hardware/ESAT_COMNonVolatileDataStorage.h"
#include "ESAT_COM-hardware/ESAT_COMTransceiverDriver.h"
#include "ESAT_COM-hardware/ESAT_COMTransceiverHAL.h"

const word GS_APPLICATION_PROCESS_IDENTIFIER = 6;
const byte GS_MAJOR_VERSION_NUMBER = 1;
const byte GS_MINOR_VERSION_NUMBER = 0;
const byte GS_PATCH_VERSION_NUMBER = 0;

ESAT_CCSDSPacket packet(ESAT_COMClass::PACKET_DATA_BUFFER_LENGTH);

// Configures the priodical delivery of the board telemetry.
// This funcion is called periodically by the scheduler according
// to the period set.
void ESAT_COMClass::PeriodicTelemetryDeliveryTaskClass::run()
{
  ESAT_CCSDSPacket telemetryPacket(ESAT_COMClass::PACKET_DATA_BUFFER_LENGTH);
  // Prepare telemetry.
  ESAT_SubsystemPacketHandler.prepareSubsystemsOwnTelemetry();
  // Read GS telemetry.
  if (ESAT_SubsystemPacketHandler.readSubsystemsOwnTelemetry(telemetryPacket))
  {
    // Write to USB.
   ESAT_SubsystemPacketHandler.writePacketToUSB(telemetryPacket);
  }
}

// Start peripherals and do the initial bookkeeping here:
// - Activate the reception of telecommands from the USB interface.
// - Activate the emission of telemetry through the USB interface.
// - Register the available subsystems for use by the on-board data
//   handling module.
// - Begin the subsystems.
// - Begin the timer that keeps a precise timing of the main loop.
// This is the first function of the program to be run at it runs only
// once.
void setup()
{
  Serial.begin(9600);
  Serial.blockOnOverrun(false);
  delay(1000);
  ReceptionTransceiver.setLowestChannel(0);
  ReceptionTransceiver.setHighestChannel(31);
  ReceptionTransceiver.setDefaultChannel(0);
  TransmissionTransceiver.setLowestChannel(0);
  TransmissionTransceiver.setHighestChannel(31);
  TransmissionTransceiver.setDefaultChannel(31);
  ReceptionTransceiver.setModulationType(ESAT_COMNonVolatileDataStorage.readReceptionModulationType());
  ReceptionTransceiver.setFrequency(ESAT_COMNonVolatileDataStorage.readReceptionFrequency());
  ReceptionTransceiver.setChannel(ESAT_COMNonVolatileDataStorage.readReceptionChannel());
  TransmissionTransceiver.setModulationType(ESAT_COMNonVolatileDataStorage.readTransmissionModulationType());
  TransmissionTransceiver.setFrequency(ESAT_COMNonVolatileDataStorage.readTransmissionFrequency());
  TransmissionTransceiver.setChannel(ESAT_COMNonVolatileDataStorage.readTransmissionChannel());
  ESAT_COM.begin(GS_APPLICATION_PROCESS_IDENTIFIER,
               GS_MAJOR_VERSION_NUMBER,
               GS_MINOR_VERSION_NUMBER,
               GS_PATCH_VERSION_NUMBER);
  TransmissionTransceiver.setTransmissionPower(ESAT_COMNonVolatileDataStorage.readTransmissionPower());
  TransmissionTransceiver.updateTransmissionPower();
  ESAT_COMTaskScheduler.begin();
  ReceptionTransceiver.startReception();
  delay(1000);
}

// Body of the main loop of the program:
// - Retrieve the incoming telecommands.
// - Dispatch the incoming telecommands on their target subsystems.
// - Update the subsystems.
// - Retrieve the telemetry packets from the subsystems.
// - Forward the retrieved telemetry packets to the subsystems so that
//   they can use them (for example, a subsystem may send telemetry
//   packets to the ground station or it can store them for later use).
// This function is run in an infinite loop that starts after setup().
void loop()
{
  // Handle USB telecommands.
  if (ESAT_SubsystemPacketHandler.readPacketFromUSB(packet))
  {
    packet.rewind();
    if (ESAT_COM.isSubsystemTelecommand(packet))
    {
      // Own telecommand: self processed.
      packet.rewind();
      ESAT_SubsystemPacketHandler.dispatchTelecommand(packet);
    }
    else
    {
      packet.rewind();
      // Only if the sequencial sweep is disabled.
      if (!((boolean) ESAT_COMSequenceGenerator.getMode()))
      {
        // Other telecommands: send it to the radio.
        ESAT_COM.writePacketToRadio(packet);
      }
    }
  }

  // Handle radio received telemetry.
  packet.rewind();
  if (ESAT_COM.readPacketFromRadio(packet))
  {
    packet.rewind();
    ESAT_SubsystemPacketHandler.writePacketToUSB(packet);
  }

  // Handles:
  //  -Radio transmissions: broadcasts nong-GS received telecommands.
  //  -Manual data stream:  updates the bit-banged transmission testing sequence.
  //  -Heath beat LED update.
  ESAT_COM.update();

  // Updates the periodic tasks:
  // - PeriodicTelemetryDeliveryTask: Delivers system telemetry to the USB port.
  ESAT_COMTaskScheduler.run();
}