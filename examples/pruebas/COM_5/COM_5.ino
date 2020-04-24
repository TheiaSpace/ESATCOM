/*
 * ESAT COM Main Program version 1.0.0
 * Copyright (C) 2019 Theia Space, Universidad Politécnica
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
#include "ESAT_COM-hardware/ESAT_COMTransceiverDriver.h"
#include "ESAT_COM-hardware/ESAT_COMHearthBeatLED.h"
#include "ESAT_COM-hardware/ESAT_COMTransceiverHAL.h"

const word COM_APPLICATION_PROCESS_IDENTIFIER = 5;
const byte COM_MAJOR_VERSION_NUMBER = 1;
const byte COM_MINOR_VERSION_NUMBER = 0;
const byte COM_PATCH_VERSION_NUMBER = 0;

// Cycle period in iterations.
const word PERIOD = 1000;

word counter;

word iterationCounter;

ESAT_CCSDSPacket packet(ESAT_COMClass::PACKET_DATA_BUFFER_LENGTH);

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
  iterationCounter = 0;
  counter = 0;
  Serial.begin(9600);
  Serial.blockOnOverrun(false); 
//  Serial.println("Press any key to start");
//  while (Serial.available() <= 0)
//  {
//    if (iterationCounter >= 3*PERIOD)
//    {
//      Serial.println("Press any key to start");
//      iterationCounter = 0;
//    }
//    ++iterationCounter;
//    delay(1);
//  }
//  while (Serial.available() > 0)
//  {
//    Serial.read();
//  }
//  Serial.println("Go on!");
  iterationCounter = 0;
  delay(1000);
     
  ESAT_COM.begin(COM_APPLICATION_PROCESS_IDENTIFIER,
                 COM_MAJOR_VERSION_NUMBER,
                 COM_MINOR_VERSION_NUMBER,
                 COM_PATCH_VERSION_NUMBER);
  ReceptionTransceiver.setLowestChannel(0);
  ReceptionTransceiver.setHighestChannel(15);  
  TransmissionTransceiver.setLowestChannel(16);
  TransmissionTransceiver.setHighestChannel(31);  
  ReceptionTransceiver.setFrequency(433.0);
  TransmissionTransceiver.setFrequency(433.0);
  TransmissionTransceiver.setTransmissionPower(100.0);
  interrupts();  
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
  if (iterationCounter >= PERIOD)
  { 
    // Prepare telemetry.   
    ESAT_SubsystemPacketHandler.prepareSubsystemsOwnTelemetry();
    // Send own telemetry.
    if  (ESAT_SubsystemPacketHandler.readSubsystemsOwnTelemetry(packet))
    {
      // To USB
      ESAT_SubsystemPacketHandler.writePacketToUSB(packet);
      // To radio if standalone mode is enabled
      if (ESAT_COM.isCOMTelemetryRadioDeliveryEnabled())
      {
        ESAT_COM.writePacketToRadio(packet);
      }
    }
    // Handle USB telecommands.
    if (ESAT_SubsystemPacketHandler.readPacketFromUSB(packet))
    {
      ESAT_SubsystemPacketHandler.dispatchTelecommand(packet);
    }
    // Handle radio received telecommands.
    if (ESAT_COM.readPacketFromRadio(packet))
    {
      if (ESAT_COM.isSubsystemTelecommand(packet))
      {
        // Own telecommand: self processed.
        ESAT_SubsystemPacketHandler.dispatchTelecommand(packet);
      }
      else
      {
        // Other telecommands: queued to I2C transmission to OCDH.
        ESAT_SubsystemPacketHandler.queueTelecommandToI2C(packet);
      }
    }    
    // Handle I2C written packets.
    // They can be either radio telecommands or any subsystem telemetry.
    if (ESAT_SubsystemPacketHandler.readPacketFromI2C(packet))
    {
      if (ESAT_COM.isSubsystemTelecommand(packet))
      {
        // Radio telecommands are processed.
        ESAT_SubsystemPacketHandler.dispatchTelecommand(packet);
      }
      else
      {
       // Any telemetry is transmitted.
       ESAT_COM.writePacketToRadio(packet);
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
    
    iterationCounter = 0;
    ++counter;       
  }

  ++iterationCounter;  
  
  ESAT_COMHearthBeatLED.update();
  TransmissionTransceiver.updateManualDataStream();
  
  delay(1);
}
