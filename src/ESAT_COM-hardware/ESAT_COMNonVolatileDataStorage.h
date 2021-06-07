/*
 * Copyright (C) 2020, 2021 Theia Space, Universidad Politécnica de Madrid
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

#ifndef ESAT_COMNonVolatileDataStorage_h
#define ESAT_COMNonVolatileDataStorage_h

#include <Arduino.h>
#include "ESAT_COMTransceiverDriver.h"

// COM non volatile data storage controller.
// Handles and stores all configuration parameters into
// non volatile memory to have persistence between reboots.
// The configuration parameters are simple attributes that are
// loaded during power up and stored under request.
// To load the stored values, call
// ESAT_COMNonVolatileDataStorage.readConfiguration().
// To store the values, call
// ESAT_COMNonVolatileDataStorage.writeConfiguration().
// To erase all the values, call
// ESAT_COMNonVolatileDataStorage.eraseAll().
class ESAT_COMNonVolatileDataStorageClass
{
  public:
    // Check if the stored data is valid or not.
    boolean checkMemoryStatus();

    // Erase all the non volatile memory contents
    void eraseAll();

    // Read the stored transmission channel.
    byte readTransmissionChannel();

    // Read the stored transmission frequency.
    float readTransmissionFrequency();

    // Read the stored transmission power.
    float readTransmissionPower();

    // Read the stored modulation type.
    ESAT_COMTransceiverDriverClass::ModulationType readTransmissionModulationType();

    // Read the stored reception channel.
    byte readReceptionChannel();

    // Read the stored reception frequency.
    float readReceptionFrequency();

    // Read the stored reception modulation type.
    ESAT_COMTransceiverDriverClass::ModulationType readReceptionModulationType();

    // Write all radio driver configurations into
    // non volatile memory.
    void writeConfigurations();

  private:
    // Length of the memory valid flag.
    static const word MEMORY_CONTENTS_STATUS_LENGHT = 1;

    // Offset of the memory valid flag.
    static const word MEMORY_CONTENTS_STATUS_OFFSET = 0;

    // Length of the transmission channel parameter.
    static const word TRANSMISSION_CHANNEL_PARAMETER_LENGTH = 1;

    // Offset of the transmission channel parameter.
    static const word TRANSMISSION_CHANNEL_PARAMETER_OFFSET =
      MEMORY_CONTENTS_STATUS_OFFSET
      + MEMORY_CONTENTS_STATUS_LENGHT;

    // Length of the transmission frequency parameter.
    static const word TRANSMISSION_FREQUENCY_PARAMETER_LENGTH = 4;

    // Offset of the transmission frequency parameter.
    static const word TRANSMISSION_FREQUENCY_PARAMETER_OFFSET =
      TRANSMISSION_CHANNEL_PARAMETER_OFFSET
      + TRANSMISSION_CHANNEL_PARAMETER_LENGTH;

    // Length of the transmission modulation type parameter;
    static const word TRANSMISSION_MODULTATION_TYPE_PARAMETER_LENGTH = 1;

    // Offset of the transmission modulation type parameter;
    static const word TRANSMISSION_MODULTATION_TYPE_PARAMETER_OFFSET =
      TRANSMISSION_FREQUENCY_PARAMETER_OFFSET
      + TRANSMISSION_FREQUENCY_PARAMETER_LENGTH;

    // Length of the transmission power parameter.
    static const word TRANSMISSION_POWER_PARAMETER_LENGTH = 4;

    // Offset of the transmission power parameter.
    static const word TRANSMISSION_POWER_PARAMETER_OFFSET =
      TRANSMISSION_MODULTATION_TYPE_PARAMETER_OFFSET
      + TRANSMISSION_MODULTATION_TYPE_PARAMETER_LENGTH;

    // Length of the reception channel parameter.
    static const word RECEPTION_CHANNEL_PARAMETER_LENGTH = 1;

    // Offset of the reception channel parameter.
    static const word RECEPTION_CHANNEL_PARAMETER_OFFSET =
      TRANSMISSION_POWER_PARAMETER_OFFSET
      + TRANSMISSION_POWER_PARAMETER_LENGTH;

    // Length of the reception frequency parameter.
    static const word RECEPTION_FREQUENCY_PARAMETER_LENGTH = 4;

    // Offset of the reception frequency parameter.
    static const word RECEPTION_FREQUENCY_PARAMETER_OFFSET =
      RECEPTION_CHANNEL_PARAMETER_OFFSET
      + RECEPTION_CHANNEL_PARAMETER_LENGTH;

    // Length of the reception modulation type parameter;
    static const word RECEPTION_MODULTATION_TYPE_PARAMETER_LENGTH = 1;

    // Offset of the reception modulation type parameter;
    static const word RECEPTION_MODULTATION_TYPE_PARAMETER_OFFSET =
      RECEPTION_FREQUENCY_PARAMETER_OFFSET
      + RECEPTION_FREQUENCY_PARAMETER_LENGTH;

    // Total length of the configuration.
    static const word CONFIGURATION_LENGTH =
      MEMORY_CONTENTS_STATUS_LENGHT
      + TRANSMISSION_CHANNEL_PARAMETER_LENGTH
      + TRANSMISSION_FREQUENCY_PARAMETER_LENGTH
      + TRANSMISSION_MODULTATION_TYPE_PARAMETER_LENGTH
      + TRANSMISSION_POWER_PARAMETER_LENGTH
      + RECEPTION_CHANNEL_PARAMETER_LENGTH
      + RECEPTION_FREQUENCY_PARAMETER_LENGTH
      + RECEPTION_MODULTATION_TYPE_PARAMETER_LENGTH;

    // Value to store in memory if the data was erased.
    const byte MEMORY_CONTENTS_ERASED = 0;

    // Value to store in memory if the data was updated.
    const byte MEMORY_CONTENTS_VALID = 0b01010101;

    // Store the transmission channel into non volatile memory.
    void writeTransmissionChannel();

    // Store the transmission frequency into non volatile memory.
    void writeTransmissionFrequency();

    // Store the transmission modulation type into non volatile
    // memory.
    void writeTransmissionModulationType();

    // Store the transmission power into non volatile memory.
    void writeTransmissionPower();

    // Store the reception channel into non volatile memory.
    void writeReceptionChannel();

    // Store the reception frequency into non volatile memory.
    void writeReceptionFrequency();

    // Store the reception modulation type into non volatile memory.
    void writeReceptionModulationType();
};

// Global instance of the COM non-volatile data storage library.
extern ESAT_COMNonVolatileDataStorageClass ESAT_COMNonVolatileDataStorage;

#endif /* ESAT_COMNonVolatileDataStorage_h */
