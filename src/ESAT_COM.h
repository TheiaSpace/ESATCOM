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
  
    // Register a telecommand handler.
    void addTelecommand(ESAT_CCSDSTelecommandPacketHandler& telecommand);

    // Register a telemetry packet.
    // The telemetry packet will be enabled by default;
    // it can be disabled with disableTelemetry().
    void addTelemetry(ESAT_CCSDSTelemetryPacketContents& telemetry);

    // Set up the COM board.
    // Use the radio input buffer to store packets coming from the
    // radio interface.
    // Use the radio output buffer to store outcoming packets ready
    // to be transmitted.
    // Use the serial buffer to store packets coming from the
    // serial interface.
    // Use the I2C input buffer to store packets coming from any other
    // subsystem.
    // Use the I2C output buffer to store packets to be sent to any other
    // subsystem.
    void begin(byte radioInputBuffer[],
         const unsigned long radioInputBufferLength,
         byte radioOutputBuffer[],
         const unsigned long radioOutputBufferLength,
         byte serialInputBuffer[],
         const unsigned long serialInputBufferLength,
         byte i2cInputBuffer[],
         const unsigned long i2cInputBufferLength,
         byte i2cOutpuBuffer[],
         const unsigned long i2cOutpuBufferLength);

    // Disable the generation of the telemetry packet with the given
    // identifier.
    void disableTelemetry(byte identifier);

    // Enable the generation of the telemetry packet with the given
    // identifier.
    void enableTelemetry(byte identifier);

    // Handle a telecommand.
    void handleTelecommand(ESAT_CCSDSPacket& packet);

    // Fill the packet with data read from the radio interface.
    // Return true if there was a new packet; otherwise return false.
    boolean readPacketFromRadio(ESAT_CCSDSPacket& packet);
  
    // Fill the packet with data read from the USB interface.
    // Return true if there was a new packet; otherwise return false.
    boolean readPacketFromUSB(ESAT_CCSDSPacket& packet);

    // Fill a new ESAT COM board telemetry packet.
    // Return true if there was a new packet; otherwise return false.
    boolean readTelemetry(ESAT_CCSDSPacket& packet);

    // Set the time of the real-time clock.
    void setTime(ESAT_Timestamp timestamp);

    // Send a packet by radio.
    boolean writePacketToRadio(ESAT_CCSDSPacket& packet);
  
    // Write a packet to USB serial interface.
    void writePacketToUSB(ESAT_CCSDSPacket& packet);

    private:
    // Unique identifier of the COM board for telemetry and
    // telecommand purposes.
  
    // TODO
    // Check APID
    static const word APPLICATION_PROCESS_IDENTIFIER = 4;

    // Version numbers.
    static const byte MAJOR_VERSION_NUMBER = 1;
    static const byte MINOR_VERSION_NUMBER = 0;
    static const byte PATCH_VERSION_NUMBER = 0;
    
    // KISS frame transmission buffer.
    ESAT_Buffer radioOutputBuffer;

    // List of enabled telemetry packet identifiers.
    ESAT_FlagContainer enabledTelemetry;

    // List of pending telemetry packet identifiers.
    ESAT_FlagContainer pendingTelemetry;
    
    // Use this to write packets to the radio interface.
    ESAT_KISSStream radioWriter;    

    // Use this to read CCSDS packets from the radio interface.
    ESAT_CCSDSPacketFromKISSFrameReader radioReader;
  
    // Use this to read packets from the USB interface.
    ESAT_CCSDSPacketFromKISSFrameReader usbReader;
  
    // Use this to write packets to the USB interface.
    ESAT_CCSDSPacketToKISSFrameWriter usbWriter;

    // Use this for handling telecommand packets.
    ESAT_CCSDSTelecommandPacketDispatcher telecommandPacketDispatcher =
      ESAT_CCSDSTelecommandPacketDispatcher(APPLICATION_PROCESS_IDENTIFIER);     

    // Use this for building telemetry packets.
    ESAT_CCSDSTelemetryPacketBuilder telemetryPacketBuilder =
      ESAT_CCSDSTelemetryPacketBuilder(APPLICATION_PROCESS_IDENTIFIER,
                                       MAJOR_VERSION_NUMBER,
                                       MINOR_VERSION_NUMBER,
                                       PATCH_VERSION_NUMBER,
                                       ESAT_COMBuiltinHardwareClock);
    // Configure the hardware.
    void beginHardware();
  
    // Configure the radio stream middleware.
    // Use the radio input buffer to store packets coming from the
    // waves.
    // Use the radio output buffer to store packets ready to be radiated.
    // Use the USB input buffer to store packets coming from USB.
    // Use the I2C input buffer to store packets coming from any other
    // subsystem.
    // Use the I2C output buffer to store packets to be sent to any other
    // subsystem.
    void beginRadioSoftware(byte radioInputBufferArray[],
                const unsigned long radioInputBufferLength,
                byte radioOutputBufferArray[],
                const unsigned long radioOutputBufferLength,
                byte usbInputBuffer[],
                const unsigned long usbInputBufferLength,
                byte i2cInputBuffer[],
                const unsigned long i2cInputBufferLength,
                byte i2cOutpuBuffer[],
                const unsigned long i2cOutpuBufferLength);

    // Configure the telecommand handlers.
    void beginTelecommands();

    // Configure the telemetry packets.
    void beginTelemetry();

    // Reset the telemetry queue.
    void resetTelemetryQueue();
};

extern ESAT_COMClass ESAT_COM;

#endif /* ESAT_COM_h */
