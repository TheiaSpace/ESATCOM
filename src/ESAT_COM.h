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
#include <ESAT_CCSDSPacketQueue.h>
#include <ESAT_CCSDSTelemetryPacketContents.h>
#include <ESAT_CCSDSPacketFromKISSFrameReader.h>
#include <ESAT_CCSDSPacketToKISSFrameWriter.h>
#include <ESAT_CCSDSTelecommandPacketDispatcher.h>
#include <ESAT_CCSDSTelecommandPacketHandler.h>
#include <ESAT_CCSDSTelemetryPacketBuilder.h>
#include <ESAT_KISSStream.h>
#include <ESAT_FlagContainer.h>
#include <ESAT_SubsystemPacketHandler.h>
#include <ESAT_Task.h>
#include <ESAT_TaskScheduler.h>
#include "ESAT_COM-hardware/ESAT_COMBuiltinHardwareClock.h"

class ESAT_COMClass
{
  public: 
	// Task for reading and delivering the COM board telemetry periodically.
  	class OnBoardTelemetryDeliveryTaskClass: public ESAT_Task
	{
	  public:
		// Delivery period (in us).
		unsigned long period()
		{
		  return 1000000;
		}

		void run();		
	};
  
    // Maximum packet data length radio will handle.
    static const word PACKET_DATA_BUFFER_LENGTH = 256;

    // Maximum whole packet length radio will handle.
    static const word WHOLE_PACKET_BUFFER_LENGTH =
    ESAT_CCSDSPrimaryHeader::LENGTH + PACKET_DATA_BUFFER_LENGTH;

    // Maximum KISS frame length radio will handle.
    static const word WHOLE_KISS_FRAME_MAX_LENGTH = 
    ESAT_KISSStream::frameLength(WHOLE_PACKET_BUFFER_LENGTH);
		
	// Instance of OnBoardTelemetryDeliveryTaskClass.
	OnBoardTelemetryDeliveryTaskClass OnBoardTelemetryDeliveryTask;	
  
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
    
    // Queues a telecommand to the radio output buffer (for GS).
    boolean queueTelecommandToRadio(ESAT_CCSDSPacket& packet);
    
    // Queues a telemetry to the radio output buffer(for on-board module).
    boolean queueTelemetryToRadio(ESAT_CCSDSPacket& packet);

    // Fill the packet with data read from the radio interface.
    // Return true if there was a new packet; otherwise return false.
    boolean readPacketFromRadio(ESAT_CCSDSPacket& packet);
	
	// Performs the background tasks.
	void update();
		
    // Starts the radio transmission.
    boolean writePacketToRadio(ESAT_CCSDSPacket& packet);

    private:	
	
	// Multi-source transmission state machine states.
	enum RadioTransmissionState
	{
		IDLE,
		TRANSMITTING_EXTERNAL_DATA, // I2C received data
		EXTERNAL_DATA_TRANSMITTED,
		TRANSMITTING_OWN_DATA, // User controlled data
		OWN_DATA_TRANSMITTED
	};
	
	// Size of the board external (I2C) data radio transmission buffer.
	const unsigned long EXTERNAL_DATA_TRANSMISSION_QUEUE_CAPACITY = 17;
	
	// Size of the board own data radio transmission buffer.
	const unsigned long OWN_DATA_TRANSMISSION_QUEUE_CAPACITY = 2;
	
    // Unique identifier of the COM board for telemetry and
    // telecommand purposes.
    word applicationProcessIdentifier;
    
	// Allows the board to deliver its telemetry to the radio.
    boolean isTelemetryRadioDeliveryEnabled = true;
    
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
	
	// Use this to store the packet while it is sent.
	ESAT_CCSDSPacket ongoingTransmissionPacket;
	
	// Current state of the multi-source transmission state machine.
	RadioTransmissionState ongoingTransmissionState;
	
	// Use this queue to store the user controlled data.
	ESAT_CCSDSPacketQueue ownDataQueue;

    // Configures the board hardware.
    void beginHardware();
  
    // Configures the radio stream middleware.
    void beginRadioSoftware();

    // Configures the telecommand handlers.
    void beginTelecommands();

    // Configures the telemetry packets.
    void beginTelemetry();

};

// Instance of the tasks scheduler (should be global?).
extern ESAT_TaskScheduler ESAT_COMTaskScheduler;

extern ESAT_COMClass ESAT_COM;

#endif /* ESAT_COM_h */
