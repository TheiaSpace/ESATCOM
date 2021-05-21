/*
 * Copyright (C) 2019, 2021 Theia Space, Universidad Politécnica de Madrid
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
#include "ESAT_COMSequenceGenerator.h"
#include <string.h>
#include "ESAT_COM-hardware/ESAT_COMTransceiverDriver.h"

void SequenceIncrementingTaskClass::run()
{
  ESAT_COMSequenceGenerator.handleSequenceTransmission();
}

void ESAT_COMSequenceGeneratorClass::disable()
{
  mode = ESAT_COMSequenceGeneratorClass::DISABLED;
}

void ESAT_COMSequenceGeneratorClass::enableFourLevels()
{
  mode = ESAT_COMSequenceGeneratorClass::FOUR_LEVELS;
  levelCounter = 0;
  retrialsCounter = 0;
}

void ESAT_COMSequenceGeneratorClass::enableTwoLevels()
{
  mode = ESAT_COMSequenceGeneratorClass::TWO_LEVELS;
  levelCounter = 0;
  retrialsCounter = 0;
}

byte ESAT_COMSequenceGeneratorClass::getMode()
{
  switch (mode)
  {
    default:
      case ESAT_COMSequenceGeneratorClass::DISABLED:
        return 0;
      case ESAT_COMSequenceGeneratorClass::TWO_LEVELS:
        return 1;
      case ESAT_COMSequenceGeneratorClass::FOUR_LEVELS:
        return 2;
  }
}

void ESAT_COMSequenceGeneratorClass::handleSequenceTransmission()
{
  switch (mode)
  {
    default:
    case DISABLED:
      levelCounter = 0;
      retrialsCounter = 0;
      break;
    case TWO_LEVELS:
      Serial.println((byte)transmitPacket(levelCounter));
      Serial.println(levelCounter, DEC);
      Serial.println(retrialsCounter, DEC);
      if (retrialsCounter > NUMBER_OF_RETRIALS)
      {
        retrialsCounter = 0;
        ++(levelCounter);
        if (levelCounter > 1)
        {
          levelCounter = 0;
        }
      }
      break;
    case FOUR_LEVELS:
      transmitPacket(levelCounter);
      if (retrialsCounter > NUMBER_OF_RETRIALS)
      {
        retrialsCounter = 0;
        ++(levelCounter);
        if (levelCounter > 3)
        {
          levelCounter = 0;
        }
      }
      break;
  }
}

boolean ESAT_COMSequenceGeneratorClass::transmitPacket(byte symbol)
{
  // Transmission buffer.
  byte txBuffer[ESAT_COMTransceiverDriverClass::RADIO_MAX_PACKET_LENGTH];
  // Pattern to be sent.
  byte fillValue;
  if (ESAT_COMTransmissionTransceiver.available())
  {
    switch (symbol)
    {
      default:
      case 0:
        fillValue = 0b00000000;
        break;
      case 1:
        fillValue = 0b11111111;
        break;
      case 2:
        fillValue = 0b01010101;
        break;
      case 3:
        fillValue = 0b10101010;
        break;
    }
    memset(txBuffer, (int) fillValue, ESAT_COMTransceiverDriverClass::RADIO_MAX_PACKET_LENGTH);
    if (ESAT_COMTransmissionTransceiver.nonBlockingWrite(txBuffer) != ESAT_COMTransceiverDriverClass::noError)
    {
      return false;
    }
    ++retrialsCounter;
    return true;
  }
  return false;
}

ESAT_COMSequenceGeneratorClass ESAT_COMSequenceGenerator;
