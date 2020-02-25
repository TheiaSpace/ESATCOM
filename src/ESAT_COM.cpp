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

#include <Arduino.h>
#include <ESAT_CCSDSPacketFromKISSFrameReader.h>
#include <ESAT_CCSDSPacketToKISSFrameWriter.h>
#include <ESAT_I2CSlave.h>
#include "ESAT_COM.h"
#include "ESAT_COM-hardware/ESAT_COMHearthBeatLED.h"
#include "ESAT_COM-hardware/ESAT_COMTransceiverDriver.h"
// System telecommands
#include "ESAT_COM-telecommands/ESAT_COMDisableTelemetryTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMEnableTelemetryTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMSetTimeTelecommand.h"
// Receiver telecommands
#include "ESAT_COM-telecommands/ESAT_COMReceiver2FSKModulationSelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMReceiver2GFSKModulationSelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMReceiver4FSKModulationSelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMReceiver4GFSKModulationSelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMReceiverChannelSelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMReceiverEnableTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMReceiverDisableTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMReceiverFrequencySelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMReceiverOOKModulationSelectionTelecommand.h"
// Transmitter telecommands
#include "ESAT_COM-telecommands/ESAT_COMTransmitter2FSKModulationSelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitter2GFSKModulationSelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitter4FSKModulationSelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitter4GFSKModulationSelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterChannelSelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterContinuousWaveSelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterDisableRandomGeneratorTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterEnableRandomGeneratorTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterDisableTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterEnableTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterFrequencySelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterOOKModulationSelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterTransmissionPowerAdjustmentTelecommand.h"

#include "ESAT_COM-telemetry/ESAT_COMHousekeepingTelemetry.h"
#include "ESAT_COM-hardware/ESAT_COMRadioStream.h"

void ESAT_COMClass::addTelecommand(ESAT_CCSDSTelecommandPacketHandler& telecommand)
{
  telecommandPacketDispatcher.add(telecommand);
}

void ESAT_COMClass::addTelemetry(ESAT_CCSDSTelemetryPacketContents& telemetry)
{
  telemetryPacketBuilder.add(telemetry);
  enableTelemetry(telemetry.packetIdentifier());
}

void ESAT_COMClass::begin(byte radioInputBuffer[],
         const unsigned long radioInputBufferLength,
         byte radioOutputBuffer[],
         const unsigned long radioOutputBufferLength,
         byte serialInputBuffer[],
         const unsigned long serialInputBufferLength,
         byte i2cInputBuffer[],
         const unsigned long i2cInputBufferLength,
         byte i2cOutpuBuffer[],
         const unsigned long i2cOutpuBufferLength)
{
  beginTelemetry();
  beginTelecommands();  
  beginRadioSoftware(radioInputBuffer,
        radioInputBufferLength,
        radioOutputBuffer,
        radioOutputBufferLength,
        serialInputBuffer,
        serialInputBufferLength,
        i2cInputBuffer,
        i2cInputBufferLength,
        i2cOutpuBuffer,
        i2cOutpuBufferLength);
  beginHardware();
}

void ESAT_COMClass::beginHardware()
{  
  ESAT_COMHearthBeatLED.begin();
  WireCOM.begin(byte(APPLICATION_PROCESS_IDENTIFIER));
  // Despite this function may look like software initialization, 
  // it initializes and configures radio transceivers.   
  ESAT_COMRadioStream.begin();
  }

 void ESAT_COMClass::beginRadioSoftware(byte radioInputBufferArray[],
        const unsigned long radioInputBufferLength,
        byte radioOutputBufferArray[],
        const unsigned long radioOutputBufferLength,
        byte usbInputBuffer[],
        const unsigned long usbInputBufferLength,
        byte i2cInputBuffer[],
        const unsigned long i2cInputBufferLength,
        byte i2cOutpuBuffer[],
        const unsigned long i2cOutpuBufferLength)
{
  radioReader = ESAT_CCSDSPacketFromKISSFrameReader(ESAT_COMRadioStream,
                radioInputBufferArray,
                radioInputBufferLength);
  radioOutputBuffer = ESAT_Buffer(radioOutputBufferArray, radioOutputBufferLength);
  radioWriter = ESAT_KISSStream(radioOutputBuffer);
  usbReader =  ESAT_CCSDSPacketFromKISSFrameReader(Serial,
                                                   usbInputBuffer,
                                                   usbInputBufferLength);
  usbWriter = ESAT_CCSDSPacketToKISSFrameWriter(Serial);
  ESAT_I2CSlave.begin(WireCOM,
                    i2cOutpuBuffer,
                    i2cOutpuBufferLength,
                    i2cInputBuffer,
                    i2cInputBufferLength);
}

void ESAT_COMClass::beginTelecommands()
{
  // System telecommands.
  addTelecommand(ESAT_COMDisableTelemetryTelecommand);
  addTelecommand(ESAT_COMEnableTelemetryTelecommand);
  addTelecommand(ESAT_COMSetTimeTelecommand);
  // Reception telecommands.
  addTelecommand(ESAT_COMReceiverOOKModulationSelectionTelecommand);
  addTelecommand(ESAT_COMReceiver2FSKModulationSelectionTelecommand);
  addTelecommand(ESAT_COMReceiver2GFSKModulationSelectionTelecommand);
  addTelecommand(ESAT_COMReceiver4FSKModulationSelectionTelecommand);
  addTelecommand(ESAT_COMReceiver4GFSKModulationSelectionTelecommand);
  addTelecommand(ESAT_COMReceiverChannelSelectionTelecommand);
  addTelecommand(ESAT_COMReceiverDisableTelecommand);
  addTelecommand(ESAT_COMReceiverEnableTelecommand);
  addTelecommand(ESAT_COMReceiverFrequencySelectionTelecommand); 
  // Transmission telecommands.
  addTelecommand(ESAT_COMTransmitterOOKModulationSelectionTelecommand);
  addTelecommand(ESAT_COMTransmitter2FSKModulationSelectionTelecommand);
  addTelecommand(ESAT_COMTransmitter2GFSKModulationSelectionTelecommand);
  addTelecommand(ESAT_COMTransmitter4FSKModulationSelectionTelecommand);
  addTelecommand(ESAT_COMTransmitter4GFSKModulationSelectionTelecommand);
  addTelecommand(ESAT_COMTransmitterChannelSelectionTelecommand);
  addTelecommand(ESAT_COMTransmitterDisableRandomGeneratorTelecommand);
  addTelecommand(ESAT_COMTransmitterEnableRandomGeneratorTelecommand);  
  addTelecommand(ESAT_COMTransmitterDisableTelecommand);
  addTelecommand(ESAT_COMTransmitterEnableTelecommand); 
  addTelecommand(ESAT_COMTransmitterFrequencySelectionTelecommand);
  addTelecommand(ESAT_COMTransmitterTransmissionPowerAdjustmentTelecommand);
  addTelecommand(ESAT_COMTransmitterContinuousWaveSelectionTelecommand); 
}

void ESAT_COMClass::beginTelemetry()
{
  addTelemetry(ESAT_COMHousekeepingTelemetry);
  enableTelemetry(ESAT_COMHousekeepingTelemetry.packetIdentifier());
}

void ESAT_COMClass::disableTelemetry(const byte identifier)
{
  enabledTelemetry.clear(identifier);
}

void ESAT_COMClass::enableTelemetry(const byte identifier)
{
  enabledTelemetry.set(identifier);
}

void ESAT_COMClass::handleTelecommand(ESAT_CCSDSPacket& packet)
{
  // We hide the complexity of handling telecommands with a
  // telecommand packet dispatcher.
  (void) telecommandPacketDispatcher.dispatch(packet);
}

boolean ESAT_COMClass::readPacketFromRadio(ESAT_CCSDSPacket& packet)
{
  return radioReader.read(packet);
}

boolean ESAT_COMClass::readPacketFromUSB(ESAT_CCSDSPacket& packet)
{
  return usbReader.read(packet);
}

boolean ESAT_COMClass::readTelemetry(ESAT_CCSDSPacket& packet)
{
  // We hide the complexity of building telemetry packets with a
  // telemetry packet builder.
  // We build telemetry packets as long as they are pending.
  if (pendingTelemetry.available())
  {
    const byte identifier = byte(pendingTelemetry.readNext());
    pendingTelemetry.clear(identifier);
    return telemetryPacketBuilder.build(packet, identifier);
  }
  else
  {
    return false;
  }
}

void ESAT_COMClass::setTime(const ESAT_Timestamp timestamp)
{
  ESAT_COMBuiltinHardwareClock.write(timestamp);
}

void ESAT_COMClass::updatePendingTelemetryLists()
{
  const ESAT_FlagContainer availableTelemetry =
    telemetryPacketBuilder.available();
  const ESAT_FlagContainer availableAndEnabledTelemetry =
    availableTelemetry & enabledTelemetry;
  pendingTelemetry =
    availableAndEnabledTelemetry;
}

boolean ESAT_COMClass::writePacketToRadio(ESAT_CCSDSPacket& packet)
{ 
  // Input CCSDS packet is already read and processed (empty).
  if (packet.available() == 0)
  {    
    return true;
  }
  if (ESAT_COMRadioStream.availableWrite() <= 0)
  {
    return false;   
  }   
  radioOutputBuffer.flush();
  // Handle the preparation of a KISS frame.
  if (packet.position() == 0)
  { 
    // 2 Bytes (KISS header) + 2 (max) * 6 bytes (Primary header) = 14 bytes: 
    // must fit in the radioOutputBuffer.
    radioWriter.beginFrame();
    packet.readPrimaryHeader().writeTo(radioWriter);    
  }  
  // Fifo maximum size is 129 bytes, first is length => remains 128 
  // [127 is the largest index from zero], and we need at least 2 free
  // bytes for scaping last character (if it were necessary) 
  // => 129 - 1 (length) - 2 (scape margin) - 1 (zero offset) = 125.  
  // If there is data to be written and still fits in the output buffer 
  // we write to it.
  while (packet.available() && (radioOutputBuffer.position() < 126)) 
  {
    const byte readByte = packet.read();
    radioWriter.write(readByte);    
  } 
  // If the CCSDS input packet is over, KISS frame is closed and start the
  // transmission.
  if ((packet.available() == 0) && (radioOutputBuffer.position() < 127))
  {
    radioWriter.endFrame();    
    radioOutputBuffer.writeTo(ESAT_COMRadioStream);
    return true;
  }
  // If  the CCSDS packet isn't empty but output buffer is full, transmission is
  // started but without closing the KISS frame and false is returned.
  else if (radioOutputBuffer.position() >= 126)
  {    
    radioOutputBuffer.writeTo(ESAT_COMRadioStream);
  }
  // Returned if output buffer is full.
  return false;
}

void ESAT_COMClass::writePacketToUSB(ESAT_CCSDSPacket& packet)
{
  (void) usbWriter.unbufferedWrite(packet);
}

ESAT_COMClass ESAT_COM;
