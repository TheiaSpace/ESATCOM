/*
 * ESAT COM Main Program version 1.1.0
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

#ifndef ARDUINO_ESAT_COM
#error Wrong board: you need to use the ESAT-COM board with this program.
#endif

#include <ESAT_COM.h>
#include <ESAT_SubsystemPacketHandler.h>
#include <ESAT_Task.h>
#include <ESAT_TaskScheduler.h>
#include "ESAT_COM-hardware/ESAT_COMHeartBeatLED.h"
#include "ESAT_COM-hardware/ESAT_COMNonVolatileDataStorage.h"
#include "ESAT_COM-hardware/ESAT_COMTransceiverDriver.h"
#include "ESAT_COM-hardware/ESAT_COMTransceiverHAL.h"

const word COM_APPLICATION_PROCESS_IDENTIFIER = 5;
const byte COM_MAJOR_VERSION_NUMBER = 1;
const byte COM_MINOR_VERSION_NUMBER = 1;
const byte COM_PATCH_VERSION_NUMBER = 0;

ESAT_CCSDSPacket packet(ESAT_COMClass::PACKET_DATA_BUFFER_LENGTH);

// Configures the priodical delivery of the board telemetry.
// This funcion is called periodically by the scheduler according
// to the period set.
void ESAT_COMClass::PeriodicTelemetryDeliveryTaskClass::run()
{
  ESAT_CCSDSPacket telemetryPacket(ESAT_COMClass::PACKET_DATA_BUFFER_LENGTH);
  // Prepare telemetry.
  ESAT_SubsystemPacketHandler.prepareSubsystemsOwnTelemetry();
  // Send own telemetry.
  if  (ESAT_SubsystemPacketHandler.readSubsystemsOwnTelemetry(telemetryPacket))
  {
    // To USB
    telemetryPacket.rewind();
    ESAT_SubsystemPacketHandler.writePacketToUSB(telemetryPacket);
    // To radio if standalone mode is enabled
    if (ESAT_COM.isCOMTelemetryRadioDeliveryEnabled())
    {
      telemetryPacket.rewind();
      ESAT_COM.queueTelemetryToRadio(telemetryPacket);
    }
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
  ESAT_COMReceptionTransceiver.setLowestChannel(0);
  ESAT_COMReceptionTransceiver.setHighestChannel(31);
  ESAT_COMReceptionTransceiver.setDefaultChannel(31);
  ESAT_COMReceptionTransceiver.setDefaultModulationType(ESAT_COMTransceiverDriverClass::fourFSK);
  ESAT_COMTransmissionTransceiver.setLowestChannel(0);
  ESAT_COMTransmissionTransceiver.setHighestChannel(31);
  ESAT_COMTransmissionTransceiver.setDefaultChannel(0);
  ESAT_COMTransmissionTransceiver.setDefaultModulationType(ESAT_COMTransceiverDriverClass::fourFSK);
  ESAT_COMReceptionTransceiver.setModulationType(ESAT_COMNonVolatileDataStorage.readReceptionModulationType());
  ESAT_COMReceptionTransceiver.setFrequency(ESAT_COMNonVolatileDataStorage.readReceptionFrequency());
  ESAT_COMReceptionTransceiver.setChannel(ESAT_COMNonVolatileDataStorage.readReceptionChannel());
  ESAT_COMTransmissionTransceiver.setModulationType(ESAT_COMNonVolatileDataStorage.readTransmissionModulationType());
  ESAT_COMTransmissionTransceiver.setFrequency(ESAT_COMNonVolatileDataStorage.readTransmissionFrequency());
  ESAT_COMTransmissionTransceiver.setChannel(ESAT_COMNonVolatileDataStorage.readTransmissionChannel());
  ESAT_COM.begin(COM_APPLICATION_PROCESS_IDENTIFIER,
               COM_MAJOR_VERSION_NUMBER,
               COM_MINOR_VERSION_NUMBER,
               COM_PATCH_VERSION_NUMBER);
  ESAT_COMTransmissionTransceiver.setTransmissionPower(ESAT_COMNonVolatileDataStorage.readTransmissionPower());
  ESAT_COMTransmissionTransceiver.updateTransmissionPower();
  ESAT_COMTaskScheduler.begin();
  ESAT_COMReceptionTransceiver.startReception();
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
  packet.rewind();
  if (ESAT_SubsystemPacketHandler.readPacketFromUSB(packet))
  {
    packet.rewind();
    ESAT_SubsystemPacketHandler.dispatchTelecommand(packet);
  }

  // Handle radio received telecommands.
  packet.rewind();
  if (ESAT_COM.readPacketFromRadio(packet))
  {
    if (ESAT_COM.isSubsystemTelecommand(packet))
    {
      // Own telecommand: self processed.
      packet.rewind();
      ESAT_SubsystemPacketHandler.dispatchTelecommand(packet);
    }
    else
    {
      // Other telecommands: queued to I2C transmission to OCDH.
      packet.rewind();
      ESAT_SubsystemPacketHandler.queueTelecommandToI2C(packet);
    }
  }

  // Handle I2C requests.
  // They can be telemetry requests and/or telecommands queue status queries.
  // Note that this device is an I2C slave and the transactions will happen
  // when the master (OBC) will decide. This function only prepares the context
  // for them to happen under such requests.
  if (ESAT_SubsystemPacketHandler.pendingI2CPacketRequest())
  {
    ESAT_SubsystemPacketHandler.respondToI2CPacketRequest();
  }

  // Handles:
  //  -I2C written packets: radio telecommands or any subsystem telemetry.
  //                        Radio telecommands are handled and subsystem
  //                        is queued to be transmitted by the radio when it
  //                        were possible.
  //  -Radio transmissions: broadcasts either I2C received (and queued) telemetries
  //                        and queued own subsystem's telemetry using a sequential
  //                        dispatching algorithm.
  //  -Manual data stream:  updates the bit-banged transmission testing sequence.
  //  -Heartbeat LED update.
  ESAT_COM.update();

  // Updates the periodic tasks:
  // - PeriodicTelemetryDeliveryTask: Delivers system telemetry to USB and to
  //                                  the radio if the standalone mode is enabled.
  ESAT_COMTaskScheduler.run();
}
