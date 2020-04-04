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
#include <ESAT_SubsystemPacketHandler.h>
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
#include "ESAT_COM-telecommands/ESAT_COMTransmitterDisableModulationTestModeTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterEnableModulationTestModeTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterDisableTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterEnableTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterFrequencySelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterOOKModulationSelectionTelecommand.h"
#include "ESAT_COM-telecommands/ESAT_COMTransmitterTransmissionPowerAdjustmentTelecommand.h"
// Telemetries
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
  DEBUG_PRINTLN("HARDWARE BEGIN");
  ESAT_COMHearthBeatLED.begin();
  WireCOM.begin(byte(3));
  // Despite this function may look like software initialization, 
  // it initializes and configures radio transceivers. 
  DEBUG_PRINTLN("TX BEGIN");
  TransmissionTransceiver.begin(ESAT_COMTransceiverDriverClass::TXMode);
  DEBUG_PRINTLN("RX BEGIN");
  ReceptionTransceiver.begin(ESAT_COMTransceiverDriverClass::RXMode);
  // todo
  // may be moved to init sw
  DEBUG_PRINTLN("STREAM BEGIN");
  ESAT_COMRadioStream.begin();
}

void ESAT_COMClass::beginRadioSoftware()
{
  DEBUG_PRINTLN("RADIO SOFTWARE BEGIN");
  radioReader = ESAT_CCSDSPacketFromKISSFrameReader(ESAT_COMRadioStream,
                radioInputBufferBackendArray,
                WHOLE_PACKET_BUFFER_LENGTH);
  radioOutputBuffer = ESAT_Buffer(radioOutputBufferBackendArray, WHOLE_KISS_FRAME_MAX_LENGTH);
  radioWriter = ESAT_KISSStream(radioOutputBuffer); 
  ownDataQueue = ESAT_CCSDSPacketQueue(OWN_DATA_TRANSMISSION_QUEUE_CAPACITY,
									   WHOLE_PACKET_BUFFER_LENGTH);
  ongoingTransmissionPacket = ESAT_CCSDSPacket(WHOLE_PACKET_BUFFER_LENGTH);
  ongoingTransmissionState = IDLE;  
}

void ESAT_COMClass::beginTelecommands()
{
  // System telecommands.
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMDisableTelemetryTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMEnableTelemetryTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMSetTimeTelecommand);
  // Reception telecommands.
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMReceiverOOKModulationSelectionTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMReceiver2FSKModulationSelectionTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMReceiver2GFSKModulationSelectionTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMReceiver4FSKModulationSelectionTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMReceiver4GFSKModulationSelectionTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMReceiverChannelSelectionTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMReceiverDisableTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMReceiverEnableTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMReceiverFrequencySelectionTelecommand); 
  // Transmission telecommands.
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitterOOKModulationSelectionTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitter2FSKModulationSelectionTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitter2GFSKModulationSelectionTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitter4FSKModulationSelectionTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitter4GFSKModulationSelectionTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitterChannelSelectionTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitterDisableRandomGeneratorTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitterEnableRandomGeneratorTelecommand);  
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitterDisableModulationTestModeTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitterEnableModulationTestModeTelecommand);  
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitterDisableTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitterEnableTelecommand); 
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitterFrequencySelectionTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitterTransmissionPowerAdjustmentTelecommand);
  ESAT_SubsystemPacketHandler.addTelecommand(ESAT_COMTransmitterContinuousWaveSelectionTelecommand); 
}

void ESAT_COMClass::beginTelemetry()
{
  ESAT_SubsystemPacketHandler.addTelemetry(ESAT_COMHousekeepingTelemetry);
  ESAT_SubsystemPacketHandler.enableTelemetry(ESAT_COMHousekeepingTelemetry.packetIdentifier());
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
				// If the packet is a telecommand for the subsystem, dispatches it instead of broadcasting it.
				// On the next cycle a new packet will be retrieved from the I2C queue (if available).
				if (isSubsystemTelecommand(ongoingTransmissionPacket))
				{
					ongoingTransmissionPacket.rewind();
					ESAT_SubsystemPacketHandler.dispatchTelecommand(ongoingTransmissionPacket);
					break;
				}
				ongoingTransmissionState = TRANSMITTING_EXTERNAL_DATA; // Packet transmission will begin on the next cycle.			
				break;
			}
			if (ownDataQueue.length() > 0 && ownDataQueue.read(ongoingTransmissionPacket))
			{
				ongoingTransmissionPacket.rewind();			
				ongoingTransmissionState = TRANSMITTING_OWN_DATA;
				break;
			}
			break;
		case  TRANSMITTING_EXTERNAL_DATA:
			if (ESAT_COM.writePacketToRadio(ongoingTransmissionPacket)) //Packet was fully transmitted.
			{					
				ongoingTransmissionState = EXTERNAL_DATA_TRANSMITTED;
			}
			else
			{
				ongoingTransmissionState = TRANSMITTING_EXTERNAL_DATA; // Part of the packet could not be transmitted.
			}
			break;			
		case TRANSMITTING_OWN_DATA:
			if (ESAT_COM.writePacketToRadio(ongoingTransmissionPacket))
			{					
				ongoingTransmissionState = OWN_DATA_TRANSMITTED;
			}
			else
			{
				ongoingTransmissionState = TRANSMITTING_OWN_DATA;
			}
			break;
		case OWN_DATA_TRANSMITTED:
			if (ownDataQueue.length() > 0 && ownDataQueue.read(ongoingTransmissionPacket))
			{
				ongoingTransmissionPacket.rewind();			
				ongoingTransmissionState = TRANSMITTING_OWN_DATA;
				break;
			}
			ongoingTransmissionState = IDLE;
			break;
		default:
			ongoingTransmissionState = IDLE;
			break;
	}
	// Updates the transmission bit banging sequence.
	TransmissionTransceiver.updateManualDataStream();
	ESAT_COMHearthBeatLED.update();	
}

boolean ESAT_COMClass::writePacketToRadio(ESAT_CCSDSPacket& packet)
{ 
  // Input CCSDS packet is already read and processed (empty).
  if (packet.available() == 0)
  {    
    DEBUG_PRINTLN("packet empty");
	return true;
  }
  if (ESAT_COMRadioStream.availableWrite() <= 0)
  {
	DEBUG_PRINTLN("Buffer full empty");
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
	DEBUG_PRINTLN("Frame closed");
    return true;
  }
  // If  the CCSDS packet isn't empty but output buffer is full, transmission is
  // started but without closing the KISS frame and false is returned.
  else if (radioOutputBuffer.position() >= 126)
  {    
    radioOutputBuffer.writeTo(ESAT_COMRadioStream);
	DEBUG_PRINTLN("Frame unclosed");
  }
  // Returned if output buffer is full.
  return false;
}

ESAT_COMClass ESAT_COM;
