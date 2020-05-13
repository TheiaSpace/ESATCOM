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
// System telecommands.
#include "ESAT_COM-telecommands/ESAT_COMDisableTelemetryTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMEnableTelemetryTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMSetTimeTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMStoreSettingsTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMEraseStoredSettingsTelecommand.h"
// Receiver telecommands.
#include "ESAT_COM-telecommands/ESAT_COMReceiverChannelSelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMReceiverEnableTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMReceiverDisableTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMReceiverFrequencySelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMReceiverModulationSelectionTelecommand.h"
// Transmitter telecommands.
#include "ESAT_COM-telecommands/ESAT_COMTransmitterChannelSelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterDataSourceSelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterDisableTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterEnableTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterFrequencySelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterModulationSelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterTransmissionPowerAdjustmentTelecommand.h"
// Telemetries.
#include "ESAT_COM-telemetry/ESAT_COMHousekeepingTelemetry.h"
#include "ESAT_COM-hardware/ESAT_COMRadioStream.h"

void ESAT_COMClass::begin(word subsystemApplicationProcessIdentifier,
               byte subsystemMajorVersionNumber,
               byte subsystemMinorVersionNumber,
               byte subsystemPatchVersionNumber)
{
  applicationProcessIdentifier = subsystemApplicationProcessIdentifier;
  majorVersionNumber = subsystemMajorVersionNumber,
  minorVersionNumber = subsystemMinorVersionNumber;
  patchVersionNumber = subsystemPatchVersionNumber;
  ESAT_SubsystemPacketHandler.begin(applicationProcessIdentifier,
                                    majorVersionNumber,
                                    minorVersionNumber,
                                    patchVersionNumber,
                                    ESAT_COMBuiltinHardwareClock,
                                    WireCOM,
                                    WHOLE_PACKET_BUFFER_LENGTH,
                                    EXTERNAL_DATA_TRANSMISSION_QUEUE_CAPACITY);
  beginTelemetry();
  beginTelecommands();
  beginRadioSoftware(); 
  beginHardware();   
}

void ESAT_COMClass::beginHardware()
{  
  ESAT_COMHearthBeatLED.begin();
  WireCOM.begin(byte(COM_I2C_ADDRESS));
  TransmissionTransceiver.begin(ESAT_COMTransceiverDriverClass::TXMode);
  // A bug requires performing this twice.
  TransmissionTransceiver.begin(ESAT_COMTransceiverDriverClass::TXMode);
  ESAT_COMRadioStream.beginWriting();
  delay(1000);
  ReceptionTransceiver.begin(ESAT_COMTransceiverDriverClass::RXMode);
  // A bug requires performing this twice.
  ReceptionTransceiver.begin(ESAT_COMTransceiverDriverClass::RXMode);
  ESAT_COMRadioStream.beginReading();    
}

void ESAT_COMClass::beginRadioSoftware()
{  
  radioReader = ESAT_CCSDSPacketFromKISSFrameReader(ESAT_COMRadioStream,
                                                    radioInputBufferBackendArray,
                                                    WHOLE_PACKET_BUFFER_LENGTH);
  radioOutputBuffer = ESAT_Buffer(radioOutputBufferBackendArray, WHOLE_KISS_FRAME_MAX_LENGTH);
  radioWriter = ESAT_KISSStream(radioOutputBuffer);
  ownDataQueue = ESAT_CCSDSPacketQueue(OWN_DATA_TRANSMISSION_QUEUE_CAPACITY, WHOLE_PACKET_BUFFER_LENGTH);
  ongoingTransmissionPacket = ESAT_CCSDSPacket(WHOLE_PACKET_BUFFER_LENGTH);
  ongoingTransmissionState = IDLE;  
}

void ESAT_COMClass::beginTelecommands()
{
  // System telecommands.
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMDisableTelemetryTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMEnableTelemetryTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMSetTimeTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMStoreSettingsTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMEraseStoredSettingsTelecommand);
  // Reception telecommands.
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMReceiverChannelSelectionTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMReceiverDisableTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMReceiverEnableTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMReceiverFrequencySelectionTelecommand); 
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMReceiverModulationSelectionTelecommand);
  // Transmission telecommands.
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitterChannelSelectionTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitterDataSourceSelectionTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitterDisableTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitterEnableTelecommand); 
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitterFrequencySelectionTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitterModulationSelectionTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitterTransmissionPowerAdjustmentTelecommand);
}

void ESAT_COMClass::beginTelemetry()
{
  ESAT_SubsystemPacketHandler.addTelemetry(ESAT_COMHousekeepingTelemetry);
  ESAT_SubsystemPacketHandler.enableTelemetry(ESAT_COMHousekeepingTelemetry.packetIdentifier());
  ESAT_COMTaskScheduler.add(ESAT_COM.PeriodicalTelemetryDeliveryTask);
}

void ESAT_COMClass::disableCOMTelemetryRadioDelivery()
{
  isTelemetryRadioDeliveryEnabled = false;
}
           
void ESAT_COMClass::enableCOMTelemetryRadioDelivery()
{
  isTelemetryRadioDeliveryEnabled = true;
}

boolean ESAT_COMClass::isCOMTelemetryRadioDeliveryEnabled()
{
  return isTelemetryRadioDeliveryEnabled;
}

boolean ESAT_COMClass::isSubsystemTelecommand(ESAT_CCSDSPacket& packet)
{
  packet.rewind();
  const ESAT_CCSDSPrimaryHeader primaryHeader = packet.readPrimaryHeader();
  if (primaryHeader.packetType != primaryHeader.TELECOMMAND)
  {
    return false;
  }
  if (applicationProcessIdentifier == primaryHeader.applicationProcessIdentifier)
  {
    return true;
  }
  return false;
}

boolean ESAT_COMClass::queueTelecommandToRadio(ESAT_CCSDSPacket& packet)
{
  packet.rewind();
  const ESAT_CCSDSPrimaryHeader primaryHeader = packet.readPrimaryHeader();
  if (primaryHeader.packetType != primaryHeader.TELECOMMAND)
  {
    return false;
  }
  packet.rewind();
  return ownDataQueue.write(packet);
}

boolean ESAT_COMClass::queueTelemetryToRadio(ESAT_CCSDSPacket& packet)
{  
  packet.rewind();
  const ESAT_CCSDSPrimaryHeader primaryHeader = packet.readPrimaryHeader();
  if (primaryHeader.packetType != primaryHeader.TELEMETRY)
  {
  return false;
  }
  packet.rewind();
  return ownDataQueue.write(packet);
}

boolean ESAT_COMClass::readPacketFromRadio(ESAT_CCSDSPacket& packet)
{
  return radioReader.read(packet);
}

void ESAT_COMClass::update()
{
  switch(ongoingTransmissionState)
  {
    case IDLE:
    case EXTERNAL_DATA_TRANSMITTED:
      if (ESAT_SubsystemPacketHandler.readPacketFromI2C(ongoingTransmissionPacket))
      { 
        ongoingTransmissionPacket.rewind(); 
        // If the packet is a telecommand for the board, it is dispatched 
        // instead of being broadcasted and on the next cycle a new packet will be
        // retrieved from the I2C queue (if there are any available).
        if (isSubsystemTelecommand(ongoingTransmissionPacket))
        {         
          ongoingTransmissionPacket.rewind();
          ESAT_SubsystemPacketHandler.dispatchTelecommand(ongoingTransmissionPacket);
          break;
        }
        ongoingTransmissionPacket.rewind();
        ongoingTransmissionState = TRANSMITTING_EXTERNAL_DATA;
        // Packet transmission will begin on the next cycle.
        break;
      }       
      if (ownDataQueue.read(ongoingTransmissionPacket))
      {       
        ongoingTransmissionPacket.rewind();       
        ongoingTransmissionState = TRANSMITTING_OWN_DATA;
        // Packet transmission will begin on the next cycle.
        break;
      }
      break;
    case  TRANSMITTING_EXTERNAL_DATA:
      if (ESAT_COM.writePacketToRadio(ongoingTransmissionPacket))
      { 
        // Packet was successfully transmitted.
        ongoingTransmissionState = EXTERNAL_DATA_TRANSMITTED;
      }
      else
      {
        // Part of the packet could not be transmitted. It will be
        // resumed on the next cycle.
        ongoingTransmissionState = TRANSMITTING_EXTERNAL_DATA; 
      }
      break;      
    case TRANSMITTING_OWN_DATA:
      if (ESAT_COM.writePacketToRadio(ongoingTransmissionPacket))
      {   
        // Packet was successfully transmitted.;
        ongoingTransmissionState = OWN_DATA_TRANSMITTED;
      }
      else
      {
        // Part of the packet could not be transmitted. It will be
        // resumed on the next cycle.
        ongoingTransmissionState = TRANSMITTING_OWN_DATA;
      }
      break;
    case OWN_DATA_TRANSMITTED:
      if (ownDataQueue.read(ongoingTransmissionPacket))
      {
        ongoingTransmissionPacket.rewind();
        ongoingTransmissionState = TRANSMITTING_OWN_DATA;
        // Packet transmission will begin on the next cycle.
        break;
      }
      // No packets to be transmitted.
      ongoingTransmissionState = IDLE;
      break;
    default:
      ongoingTransmissionState = IDLE;
      break;
  }
  // Updates the transmission manual bit banging sequence.
  TransmissionTransceiver.updateManualDataStream();
  ESAT_COMHearthBeatLED.update(); 
}

boolean ESAT_COMClass::writePacketToRadio(ESAT_CCSDSPacket& packet)
{ 
  // Input CCSDS packet is already read and processed (empty).
  if (packet.available() == 0)
  {  
  return true;
  }
  // The transmission buffer is full and the radio is busy.
  if (ESAT_COMRadioStream.availableWrite() <= 0)
  {
    return false;   
  }   
  radioOutputBuffer.flush();
  // Handle the preparation of a KISS frame.
  if (packet.position() == 0)
  { 
    // 2 bytes (KISS header) + 2 (max) * 6 bytes (Primary header) =
    // 14 bytes. They must fit in the radioOutputBuffer.
    radioWriter.beginFrame();
    packet.readPrimaryHeader().writeTo(radioWriter);
  }  
  // FIFO size is 129 bytes and the first is the length, so there
  // are 128 free bytes. 2 free bytes should be reserved for scaping 
  // the last character if it were necessary. This leaves 126 free
  // bytes, being 125 the largest allowed index for indexing the buffer.
  // If there is some data to be written and still fits in the buffer,
  // it will be written.
  while (packet.available() && (radioOutputBuffer.position() < 126))
  {
    const byte readByte = packet.read();
    radioWriter.write(readByte);
  } 
  // If the CCSDS input packet is over, the KISS frame is closed and the
  // transmission starts.
  if ((packet.available() == 0) && (radioOutputBuffer.position() < 127))
  {
    radioWriter.endFrame();    
    radioOutputBuffer.writeTo(ESAT_COMRadioStream);
    return true;
  }
  // If the CCSDS packet isn't empty but the output buffer is already full,
  // the transmission starts without closing the KISS frame and false is
  // returned as the whole CCSDS packet wasn't fully sent yet.
  else if (radioOutputBuffer.position() >= 126)
  {    
    radioOutputBuffer.writeTo(ESAT_COMRadioStream);
  }
  // Returned if the output buffer is full.
  return false;
}

ESAT_TaskScheduler ESAT_COMTaskScheduler;

ESAT_COMClass ESAT_COM;