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

#ifndef ESAT_COM_h
#define ESAT_COM_h

#include <Arduino.h>
#include <ESAT_Buffer.h>
#include <ESAT_CCSDSPacket.h>
#include <ESAT_CCSDSTelemetryPacketContents.h>
#include <ESAT_CCSDSPacketFromKISSFrameReader.h>
#include <ESAT_CCSDSPacketToKISSFrameWriter.h>
#include <ESAT_CCSDSTelecommandPacketDispatcher.h>
#include <ESAT_CCSDSTelecommandPacketHandler.h>
#include <ESAT_CCSDSTelemetryPacketBuilder.h>
#include <ESAT_KISSStream.h>
#include <ESAT_FlagContainer.h>
#include "ESAT_COM-hardware/ESAT_COMBuiltinHardwareClock.h"

class ESAT_COMClass
{
  public:   
  
     // Set up the COM board.
     // Configures the APID and the version numbers.
    void begin(word subsystemApplicationProcessIdentifier, 
               byte subsystemMajorVersionNumber,
               byte subsystemMinorVersionNumber,
               byte subsystemPatchVersionNumber);
               
    // Disable COM telemetry delivery over radio without OBC interaction.
    void disableCOMTelemetryRadioDelivery();
               
    // Enable COM telemetry delivery over radio without OBC interaction.
    void enableCOMTelemetryRadioDelivery();
    
    // Check if COM telemetry delivery over radio is enabled.
    boolean isCOMTelemetryRadioDeliveryEnabled();
                
    // Check wether a packet is a telecommand for the current subsystem.
    boolean isSubsystemTelecommand(ESAT_CCSDSPacket& packet);

    // Fill the packet with data read from the radio interface.
    // Return true if there was a new packet; otherwise return false.
    boolean readPacketFromRadio(ESAT_CCSDSPacket& packet);

    // Send a packet by radio.
    boolean writePacketToRadio(ESAT_CCSDSPacket& packet);
    
    // Send a telecommand to the radio (for GS).
    boolean writeTelecommandToRadio(ESAT_CCSDSPacket& packet);
    
    // Send a telemetry to the radio (for on-board module).
    boolean writeTelemetryToRadio(ESAT_CCSDSPacket& packet);

    private:
    
    // Maximum packet data length radio will handle.
    static const word PACKET_DATA_BUFFER_LENGTH = 256;

    // Maximum whole packet length radio will handle.
    static const word WHOLE_PACKET_BUFFER_LENGTH =
    ESAT_CCSDSPrimaryHeader::LENGTH + PACKET_DATA_BUFFER_LENGTH;

    // Maximum KISS frame length radio will handle.
    static const word WHOLE_KISS_FRAME_MAX_LENGTH = 
    ESAT_KISSStream::frameLength(WHOLE_PACKET_BUFFER_LENGTH);
        
    // Unique identifier of the COM board for telemetry and
    // telecommand purposes.
    word applicationProcessIdentifier;
    
    boolean isTelemetryRadioDeliveryEnabled = false;
    
    // Version numbers.
    byte majorVersionNumber;
    byte minorVersionNumber;
    byte patchVersionNumber;
    
    // KISS frame transmission buffer.
    ESAT_Buffer radioOutputBuffer;
    
    // Backend array for the radioOutputBuffer.
    byte radioInputBufferBackendArray[WHOLE_PACKET_BUFFER_LENGTH];
    
    // Backend array for the radioInputBuffer.
    byte radioOutputBufferBackendArray[WHOLE_KISS_FRAME_MAX_LENGTH];
    
    // Use this to write packets to the radio interface.
    ESAT_KISSStream radioWriter;    

    // Use this to read CCSDS packets from the radio interface.
    ESAT_CCSDSPacketFromKISSFrameReader radioReader;

    // Configures the board hardware.
    void beginHardware();
  
    // Configures the radio stream middleware.
    void beginRadioSoftware();

    // Configures the telecommand handlers.
    void beginTelecommands();

    // Configures the telemetry packets.
    void beginTelemetry();

};

extern ESAT_COMClass ESAT_COM;

#endif /* ESAT_COM_h */
