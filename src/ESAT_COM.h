/*
 * Copyright (C) 2020 Theia Space, Universidad Politécnica de Madrid
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

// Communications subsystem main class. It contains the hardware, software,
// telemetry and telecommands initialization functions, the buffers and the
// queues for the telemetry and the telecommands and the callbacks for 
// handling the reading and the writing of the CCSDS packets and the KISS
// frames. This class software is used by both the ground station and the
// on-board software versions.
class ESAT_COMClass
{
  public: 
  
    // Periodic task for reading and delivering the board's telemetry.
    // This class is registered to an ESAT_TaskScheduler that will
    // call the run() function within the set period.
    class PeriodicalTelemetryDeliveryTaskClass: public ESAT_Task
    {
      public:
      
        // Delivery period (in us).
        // Set it here.
        unsigned long period()
        {
          return 1000000;
        }
        
        // Periodic task function. Called by an ESAT_TaskScheduler.
        // Its implementation is done inside the sketch and it varies
        // between the ground station and the on-board softwares.    
        void run();   
    };

    // Maximum packet data length that the board will handle.
    static const word PACKET_DATA_BUFFER_LENGTH = 256;

    // Maximum whole packet length that the board will handle.
    static const word WHOLE_PACKET_BUFFER_LENGTH =
    ESAT_CCSDSPrimaryHeader::LENGTH + PACKET_DATA_BUFFER_LENGTH;

    // Maximum KISS frame length taht the board will handle.
    static const word WHOLE_KISS_FRAME_MAX_LENGTH = 
    ESAT_KISSStream::frameLength(WHOLE_PACKET_BUFFER_LENGTH);
      
    // Instance of the TelemetryDeliveryTaskClass.
    PeriodicalTelemetryDeliveryTaskClass PeriodicalTelemetryDeliveryTask; 
    
    // Sets up the board.
    // Configures the APID and the version numbers (they change between
    // ground segment and on-board softwares).
    void begin(word subsystemApplicationProcessIdentifier, 
               byte subsystemMajorVersionNumber,
               byte subsystemMinorVersionNumber,
               byte subsystemPatchVersionNumber);
                 
    // Disables the on-board telemetry delivery over the radio without OBC
    // interaction.
    void disableCOMTelemetryRadioDelivery();
               
    // Enables the on-board telemetry delivery over radio without OBC
    // interaction.
    void enableCOMTelemetryRadioDelivery();
    
    // Empties the board's transmission pending telemetry queue.
    void clearRadioTelemetryQueue();
      
    // Checks if the on-board telemetry delivery over the radio is enabled.
    boolean isCOMTelemetryRadioDeliveryEnabled();
                  
    // Checks wether a packet is a telecommand for the current subsystem
    // (on-board or ground station).
    boolean isSubsystemTelecommand(ESAT_CCSDSPacket& packet);
      
    // Queues a telecommand to the radio output buffer (for the ground station).
    boolean queueTelecommandToRadio(ESAT_CCSDSPacket& packet);
      
    // Queues a telemetry to the radio output buffer(for the on-board module).
    boolean queueTelemetryToRadio(ESAT_CCSDSPacket& packet);

    // Fills the packet with the data read from the radio interface.
    // Returns true if a new packet was read, otherwise returns false.
    boolean readPacketFromRadio(ESAT_CCSDSPacket& packet);
    
    // Performs the background tasks:
    //  -I2C written packets: radio telecommands or any subsystem telemetry.
    //                        Radio telecommands are handled and the subsystem 
    //                        telemetry is queued to be transmitted by the radio
    //                        when it were possible.
    //  -Radio transmissions: broadcasts either any I2C received (and queued) telemetries
    //                        and the queued own subsystem's telemetry using a sequential 
    //                        dispatching algorithm.
    //  -Manual data stream:  updates the bit-banged transmission testing sequence.
    //  -Heath beat LED update.
    void update();
      
    // Starts the radio transmission of the given packet.
    // Returns true if a new packet was fully written and transmitted,
    // otherwise returns false.
    boolean writePacketToRadio(ESAT_CCSDSPacket& packet);

  private:  
  
    // Multi-source transmission state machine states.
    enum RadioTransmissionState
    {
      IDLE,
      TRANSMITTING_EXTERNAL_DATA, // I2C received telemetry.
      EXTERNAL_DATA_TRANSMITTED,
      TRANSMITTING_OWN_DATA, // Board's telemetry.
      OWN_DATA_TRANSMITTED
    };
  
    // I2C Address of the board.
    const byte COM_I2C_ADDRESS = 3;
  
    // Size of the board external (I2C) data radio transmission buffer.
    const unsigned long EXTERNAL_DATA_TRANSMISSION_QUEUE_CAPACITY = 10;

    // Size of the board own data radio transmission buffer.
    const unsigned long OWN_DATA_TRANSMISSION_QUEUE_CAPACITY = 2;

    // Unique identifier of the COM board for telemetry and
    // telecommand purposes.
    word applicationProcessIdentifier;

    // Allows the board to deliver its telemetry to the radio without
    // OBC interaction.
    boolean isTelemetryRadioDeliveryEnabled = true;

    // Version numbers.
    byte majorVersionNumber;
    byte minorVersionNumber;
    byte patchVersionNumber;

    // Use this to store the packet while it is sent.
    ESAT_CCSDSPacket ongoingTransmissionPacket;

    // Current state of the multi-source transmission state machine.
    RadioTransmissionState ongoingTransmissionState;

    // Use this queue to store the user controlled data.
    ESAT_CCSDSPacketQueue ownDataQueue;
    
    // Backend array for the radioOutputBuffer.
    byte radioInputBufferBackendArray[WHOLE_PACKET_BUFFER_LENGTH];
    
    // KISS frame transmission buffer.
    ESAT_Buffer radioOutputBuffer;

    // Backend array for the radioInputBuffer.
    byte radioOutputBufferBackendArray[WHOLE_KISS_FRAME_MAX_LENGTH];

    // Use this to read CCSDS packets from the radio interface.
    ESAT_CCSDSPacketFromKISSFrameReader radioReader;
    
    // Use this to write packets to the radio interface.
    ESAT_KISSStream radioWriter;

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

// Global instance of the ESAT_COMClass.
extern ESAT_COMClass ESAT_COM;

#endif /* ESAT_COM_h */
