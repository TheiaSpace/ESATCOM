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
#include <ProcessorVoltage.h>
#include "ESAT_COM-hardware/ESAT_COMTransceiverDriver.h"
#include "ESAT_COM-hardware/ESAT_COMHearthBeatLED.h"
#include "ESAT_COM-hardware/ESAT_COMTransceiverHAL.h"

// Cycle period in iterations.
const word PERIOD = 1000;

word counter;

// Maximum packet data length we will handle.
const word PACKET_DATA_BUFFER_LENGTH = 256;

// Maximum whole packet length we will handle.
const word WHOLE_PACKET_BUFFER_LENGTH =
  ESAT_CCSDSPrimaryHeader::LENGTH + PACKET_DATA_BUFFER_LENGTH;

const word WHOLE_KISS_FRAME_MAX_LENGTH = 
  ESAT_KISSStream::frameLength(WHOLE_PACKET_BUFFER_LENGTH);

word iterationCounter;

byte usbInputBuffer[WHOLE_PACKET_BUFFER_LENGTH];

byte radioInputBuffer[WHOLE_PACKET_BUFFER_LENGTH];

byte radioOutputBuffer[WHOLE_KISS_FRAME_MAX_LENGTH];

byte I2COutputBuffer[WHOLE_KISS_FRAME_MAX_LENGTH];

byte I2CInputBuffer[WHOLE_KISS_FRAME_MAX_LENGTH];

byte RXBuffer[PACKET_DATA_BUFFER_LENGTH];
byte buffer[PACKET_DATA_BUFFER_LENGTH];

ESAT_CCSDSPacket RXPacket(RXBuffer, sizeof(RXBuffer));
ESAT_CCSDSPacket packet(buffer, sizeof(buffer));

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
     
  ESAT_COM.begin(radioInputBuffer,
                (unsigned long) WHOLE_PACKET_BUFFER_LENGTH,
                radioOutputBuffer,
                (unsigned long) WHOLE_KISS_FRAME_MAX_LENGTH,
                usbInputBuffer,
                (unsigned long) WHOLE_PACKET_BUFFER_LENGTH,
                I2CInputBuffer,
                (unsigned long) WHOLE_PACKET_BUFFER_LENGTH,
                I2COutputBuffer,
                (unsigned long) WHOLE_PACKET_BUFFER_LENGTH);
  interrupts();             
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
    packet.flush();
     // We create and fill the primary header.
    ESAT_CCSDSPrimaryHeader primaryHeader;
    primaryHeader.packetVersionNumber = 0;
    primaryHeader.packetType =
      primaryHeader.TELEMETRY;
    primaryHeader.secondaryHeaderFlag =
      primaryHeader.SECONDARY_HEADER_IS_PRESENT;
    primaryHeader.applicationProcessIdentifier = 4;
    primaryHeader.sequenceFlags =
      primaryHeader.UNSEGMENTED_USER_DATA;
    primaryHeader.packetSequenceCount =
      counter;
    packet.writePrimaryHeader(primaryHeader);
    // We create and fill the secondary header.
    ESAT_CCSDSSecondaryHeader secondaryHeader;
    secondaryHeader.preamble =
      secondaryHeader.CALENDAR_SEGMENTED_TIME_CODE_MONTH_DAY_VARIANT_1_SECOND_RESOLUTION;
    secondaryHeader.timestamp = ESAT_COMBuiltinHardwareClock.read();
    secondaryHeader.majorVersionNumber = 1;
    secondaryHeader.minorVersionNumber = 0;
    secondaryHeader.patchVersionNumber = 0;
    secondaryHeader.packetIdentifier = 0;
    packet.writeSecondaryHeader(secondaryHeader);
    // Finally, we define the user data.
    packet.writeByte('T');
    packet.writeByte('E');
    packet.writeByte('M');
    packet.writeByte('P');
    packet.print(TransmissionTransceiver.getTransceiverVoltage(), 3);
    packet.print("V ");
    packet.print(TransmissionTransceiver.getTransceiverTemperature(), 2);
    packet.print("ºC ");
    packet.print(ReceptionTransceiver.getTransceiverVoltage(), 3);
    packet.print("V ");
    packet.print(ReceptionTransceiver.getTransceiverTemperature(), 2);
    packet.println("ºC");
   //DEBUG_PRINTLN(packet);
   DEBUG_PRINT("Recently written packet availability: ");
   DEBUG_PRINTLNFORMAT(packet.available(), DEC);     
    packet.rewind();  
    DEBUG_PRINT("Rewinded packet availability: ");
   DEBUG_PRINTLNFORMAT(packet.available(), DEC);
    iterationCounter = 0;
    ++counter;  

    while(ESAT_COM.readTelemetry(RXPacket))
    {
      ESAT_COM.writePacketToUSB(RXPacket);
    }      
  }

    ESAT_COM.writePacketToRadio(packet);

  if (ESAT_COM.readPacketFromRadio(RXPacket))
  {
    ESAT_COM.writePacketToUSB(RXPacket);
  }

  while(ESAT_COM.readPacketFromUSB(packet))
  {
    ESAT_COM.handleTelecommand(packet);
  }
  ++iterationCounter;  
  
  ESAT_COMHearthBeatLED.update();
  ESAT_COM.updatePendingTelemetryLists();
  TransmissionTransceiver.updateManualDataStream();
  
  delay(1);
}
