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

#include "ESAT_COMTransceiverDriver.h"
#include <SPI.h>
#include "ESAT_COMReceptionLED.h"
#include "ESAT_COMTransmissionLED.h"
#include "ESAT_COMTransceiverCommands.h"
#include "ESAT_COMTransceiverProperties.h"
// Configurations for the different working schemas.
#include "configurations/ESAT_COMOOKReceptionConfiguration.h"
#include "configurations/ESAT_COM2FSKReceptionConfiguration.h"
#include "configurations/ESAT_COM2GFSKReceptionConfiguration.h"
#include "configurations/ESAT_COM4FSKReceptionConfiguration.h"
#include "configurations/ESAT_COM4GFSKReceptionConfiguration.h"
#include "configurations/ESAT_COMOOKTransmissionConfiguration.h"
#include "configurations/ESAT_COM2FSKTransmissionConfiguration.h"
#include "configurations/ESAT_COM2GFSKTransmissionConfiguration.h"
#include "configurations/ESAT_COM4FSKTransmissionConfiguration.h"
#include "configurations/ESAT_COM4GFSKTransmissionConfiguration.h"

ESAT_COMTransceiverDriverClass::ESAT_COMTransceiverDriverClass(ESAT_COMTransceiverHALClass& hardwareTransceiver)
{
  // Attach the proper HAL object pointer.
  transceiver = &hardwareTransceiver;
  outputDataStreamNextBit = 0;  
}

signed char ESAT_COMTransceiverDriverClass::available(void)
{
  switch (transceiverOperationMode)
  {
    case TXMode:
    {
      if (transmissionInProgress == true)
      {
        noInterrupts();
        if (transmissionInterruptFlag == 0xFF)
        {
          transmissionInterruptFlag = 0;
          interrupts();
          return checkTransmissionAvailability();
        }
        interrupts();
        return 0;
      }
      else
      {
        return 1;
      }
    }
    case RXMode:
    {
      // If there is any received and unread data return 1.
      if (receptionAvailable == true)
      {
        return 1;
      }
      // If the received data was read and the reception was reenabled.
      else
      {
        noInterrupts();
        // Check if the interrupt flag is set.
        if (receptionInterruptFlag)
        {
          receptionInterruptFlag = 0;
          interrupts();
          // Retrieve the received packet and set the available flag.
          return checkReceptionAvailability();
        }
        interrupts();
        return 0;
      }
    }
    default:
    {
      return 0;
    }
  }
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::begin(ESAT_COMTransceiverDriverClass::TransceiverMode mode)
{
  // Configure hardware.
  transceiver -> begin();
  return begin(mode, transceiverModulationType);
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::begin(ESAT_COMTransceiverDriverClass::TransceiverMode mode,
                                                                                           ESAT_COMTransceiverDriverClass::ModulationType modulationType)
{
  transceiverOperationMode = mode;
  transceiverModulationType = modulationType;
  TransceiverErrorCode error;
  switch (transceiverOperationMode)
  {
    case TXMode:
    {
      ESAT_COMTransmissionLED.begin();
      transmissionConfigurationData = switchTransmissionConfiguration(transceiverModulationType);
      error = translateLowLevelDriverError(initializeTransceiver(transmissionConfigurationData));
      if(noError != error)
      {
        return error;
      }
      // Clear ISR flag.
      transmissionInterruptFlag = 0;
      // Enable interrupts. If the ISR is fired during initialization
      // and it is not cleared, interrupts may not retrigger.
      attachInterrupt(digitalPinToInterrupt(transceiver -> getInterruptPin()), setTransmissionTransceiverInterruptFlag,  FALLING);
      setModulationSource(transmitterModulationSource);
      updateFrequency();
      updateTransmissionPower();
      break;
    }
    case RXMode:
    {
      ESAT_COMReceptionLED.begin();
      receptionConfigurationData = switchReceptionConfiguration(transceiverModulationType);
      error = translateLowLevelDriverError(initializeTransceiver(receptionConfigurationData));
      if(noError != error)
      {
    return error;
      }
      // Clear ISR flag.
      receptionInterruptFlag = 0;
      // Enable interrupts. If the ISR is fired during initialization
      // and it is not cleared, interrupts may not retrigger.
      attachInterrupt(digitalPinToInterrupt(transceiver -> getInterruptPin()), setReceptionTransceiverInterruptFlag,  FALLING);
      updateFrequency();
      break;
    }
    default:
    {
      return wrongModeError;
    }
  }
  return noError;
}

signed char ESAT_COMTransceiverDriverClass::checkReceptionAvailability()
{
  ESAT_COMTransceiverCommandsClass::InterruptStatusReply intStatusReply = ESAT_COMTransceiverCommands.getInterruptStatus(*transceiver, 0, 0, 0);
  // Check if the packet is fully received.
  if (intStatusReply.packetHandlerPending & ESAT_COMTransceiverCommandsClass::INTERRUPT_STATUS_REPLY_PACKET_HANDLER_PENDING_PACKET_RECEIVED_BITMASK)
  {
    // Retrieve the packet from the FIFO.
    receptionAvailable = true;
    switchLED(RXMode, true);
    ESAT_COMTransceiverCommands.readReceptionFIFOBuffer(*transceiver, RADIO_MAX_PACKET_LENGTH, receptionBuffer);
    switchLED(RXMode, false);
    // Reception must be reenabled (ideally after reading).
    return 1;
  }
  return 0;
}

signed char ESAT_COMTransceiverDriverClass::checkTransmissionAvailability()
{
  ESAT_COMTransceiverCommandsClass::InterruptStatusReply intStatusReply =  ESAT_COMTransceiverCommands.getInterruptStatus(*transceiver, 0, 0, 0);
  // Check if the packet is fully sent.
  if (intStatusReply.packetHandlerPending & ESAT_COMTransceiverCommandsClass::INTERRUPT_STATUS_REPLY_PACKET_HANDLER_PENDING_PACKET_SENT_BITMASK)
  {
    transmissionInProgress = false;
    return 1;
  }
  return 0;
}

void ESAT_COMTransceiverDriverClass::disable(void)
{
  disableInterrupts(); // Ensure ISRs are detached.
  transceiverOperationMode = notInitializedMode;
  transceiver -> disable();
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::disableInterrupts(void)
{
  switch (transceiverOperationMode)
  {
    case TXMode:
    {
      // Disable interrupts.
      detachInterrupt(digitalPinToInterrupt(transceiver -> getInterruptPin()));
      // Clear flag.
      transmissionInterruptFlag = 0;
      return noError;
    }
    case RXMode:
    {
      // Disable interrupts.
      detachInterrupt(digitalPinToInterrupt(transceiver -> getInterruptPin()));
      // Clear flags.
      receptionInterruptFlag = 0;
      return noError;
    }
    default:
    {
      return wrongModeError;
    }
  }
}

byte ESAT_COMTransceiverDriverClass::getChannel()
{
  return transceiverRadioChannel;
}

byte ESAT_COMTransceiverDriverClass::getDefaultChannel()
{
  return defaultChannel;
}

float ESAT_COMTransceiverDriverClass::getDefaultFrequency()
{
  return defaultFrequency;
}

ESAT_COMTransceiverDriverClass::ModulationSource ESAT_COMTransceiverDriverClass::getDefaultModulationSource()
{
  return defaultModulationSource;
}

ESAT_COMTransceiverDriverClass::ModulationType ESAT_COMTransceiverDriverClass::getDefaultModulationType()
{
  return defaultModulationType;
}

float ESAT_COMTransceiverDriverClass::getDefaultTransmissionPower()
{
  return defaultTransmissionPowerRate;
}

float ESAT_COMTransceiverDriverClass::getFrequency()
{
  return transceiverFrequency;
}

byte ESAT_COMTransceiverDriverClass::getModulation()
{
  switch(transceiverModulationType)
  {
    case (OOK):
    {
      return 0;
    }
    case (twoFSK):
    {
      return 1;
    }
    case (twoGaussianFSK):
    {
      return 2;
    }
    case (fourFSK):
    {
      return 3;
    }
    case (fourGaussianFSK):
    {
      return 4;
    }
    case (continuousWave):
    {
      return 5;
    }
    default:
    {
      return 255;
    }
  }
}

signed char ESAT_COMTransceiverDriverClass::getModulationSource()
{
  if (transceiverOperationMode != ESAT_COMTransceiverDriverClass::TXMode)
  {
    return -1;
  }
  switch (transmitterModulationSource)
  {
    case ESAT_COMTransceiverDriverClass::fifo:
      return 0;
    case ESAT_COMTransceiverDriverClass::randomGenerator:
      return 1;
    case ESAT_COMTransceiverDriverClass::gpio0_synchronous:
      return 2;
    case ESAT_COMTransceiverDriverClass::gpio0_asynchronous:
      return 3;
    case ESAT_COMTransceiverDriverClass::gpio1_synchronous:
      return 4;
    case ESAT_COMTransceiverDriverClass::gpio1_asynchronous:
      return 5;
    case ESAT_COMTransceiverDriverClass::gpio2_synchronous:
      return 6;
    case ESAT_COMTransceiverDriverClass::gpio2_asynchronous:
      return 7;
    case ESAT_COMTransceiverDriverClass::gpio3_synchronous:
      return 8;
    case ESAT_COMTransceiverDriverClass::gpio3_asynchronous:
      return 9;
    default:
      return -1;
  }
}

float ESAT_COMTransceiverDriverClass::getReceivedSignalStrengthIndicator()
{
  if (transceiverOperationMode != RXMode)
  {
    return 0.0;
  }
  ESAT_COMTransceiverCommandsClass::ModemStatusReply reply = ESAT_COMTransceiverCommands.getModemStatus(*transceiver, 0xFF);
  return (reply.currentReceivedSignalStregnthIndicator / 2.0) - RECEPTION_LOSSES_dB;
}

float ESAT_COMTransceiverDriverClass::getTransceiverTemperature()
{
  // If the transceiver is disabled return 0.
  if ((transceiverOperationMode != RXMode) && (transceiverOperationMode != TXMode))
  {
    return 0;
  }
  ESAT_COMTransceiverCommandsClass::ADCReadingsReply reply = ESAT_COMTransceiverCommands.getADCReading(*transceiver, ESAT_COMTransceiverCommandsClass::ADC_READ_ARGUMENT_READ_TEMPERATURE_BITMASK);
  return (899.0 * reply.temperatureRawValue) / 4096.0 - 293.0;
}

float ESAT_COMTransceiverDriverClass::getTransceiverVoltage()
{
  // If the transceiver is disabled return 0.
  if ((transceiverOperationMode!=RXMode) && (transceiverOperationMode!=TXMode))
  {
    return 0;
  }
   ESAT_COMTransceiverCommandsClass::ADCReadingsReply reply =  ESAT_COMTransceiverCommands.getADCReading(*transceiver, ESAT_COMTransceiverCommandsClass::ADC_READ_ARGUMENT_READ_VOLTAGE_BITMASK);
  return (3.0 * reply.voltageRawValue) / 1280.0;
}

float ESAT_COMTransceiverDriverClass::getTransmissionPowerRate()
{
  switch (transceiverOperationMode)
  {
    case ESAT_COMTransceiverDriverClass::TXMode:
    {
      return transmissionPowerRate;
    }
    case ESAT_COMTransceiverDriverClass::RXMode:
    default:
    {
      // If the transceiver is disabled return 0.
      return 0.0;
    }
  }
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COMTransceiverDriverClass::initializeTransceiver(ESAT_COMTransceiverConfigurationClass* transceiverConfiguration)
{
  switchLED(transceiverOperationMode, true);
  ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError error;
  byte failedInitializationCounter = 0;
  do
  {
    transceiver -> reset();
    // Load patch (if there is available).
    error = ESAT_COMTransceiverCommands.applyPatch(*transceiver);
    if (ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS == error)
    {
      (void) ESAT_COMTransceiverCommands.partInfo(*transceiver);
      (void) ESAT_COMTransceiverCommands.powerUp(*transceiver);
      (void) ESAT_COMTransceiverCommands.getInterruptStatus(*transceiver, 0, 0, 0);
      (void) ESAT_COMTransceiverCommands.configureGPIO(*transceiver,
                                                       ESAT_COMTransceiverCommandsClass::DONOTHING, false,
                                                       ESAT_COMTransceiverCommandsClass::CTS, false,
                                                       ESAT_COMTransceiverCommandsClass::INPUT_READ, false,
                                                       ESAT_COMTransceiverCommandsClass::DONOTHING, false,
                                                       ESAT_COMTransceiverCommandsClass::RADIO_HIGH);
      error = transceiverConfiguration -> applyConfiguration(*transceiver);
      if (error == ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
      {
        ESAT_COMTransceiverCommandsClass::InterruptStatusReply intStatusReply = ESAT_COMTransceiverCommands.getInterruptStatus(*transceiver, 0, 0, 0);
        // Check if the chip is ready to accept commands.
        if ((intStatusReply.chipStatus & ESAT_COMTransceiverCommandsClass::INTERRUPT_STATUS_REPLY_CHIP_STATUS_CHIP_READY_BITMASK)
            && !(intStatusReply.chipPending & ESAT_COMTransceiverCommandsClass::INTERRUPT_STATUS_REPLY_CHIP_PENDING_CHIP_READY_BITMASK))
        {
          switchLED(transceiverOperationMode, false);
          return ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS;
        }
        return ESAT_COMTransceiverHALClass::TRANSCEIVER_CHIP_ERROR;
      }
    }
    if (MAXIMUM_FAILED_INITIALIZATIONS <= failedInitializationCounter)
    {
      switchLED(transceiverOperationMode, false);
      return error;
    }
    ++failedInitializationCounter;
    delay(10);
  }
  while (MAXIMUM_FAILED_INITIALIZATIONS <= failedInitializationCounter);
  switchLED(transceiverOperationMode, false);
  return error;
}

byte* ESAT_COMTransceiverDriverClass::nonBlockingRead(void)
{
  receptionAvailable = false;
  startReception();
  return receptionBuffer;
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::nonBlockingWrite(byte* msgBuf)
{
  if (transceiverOperationMode != ESAT_COMTransceiverDriverClass::TXMode)
  {
    return ESAT_COMTransceiverDriverClass::wrongModeError;
  }
  // Reset FIFO.
  ESAT_COMTransceiverCommands.getFIFOStatus(*transceiver, true, true);
  // Read interrupts and clear pending ones.
  ESAT_COMTransceiverCommands.getInterruptStatus(*transceiver, 0, 0, 0);
  // Load 129 bytes into fifo.
  switchLED(TXMode, true);
  ESAT_COMTransceiverCommands.writeTransmissionFIFOBuffer(*transceiver, RADIO_MAX_PACKET_LENGTH, msgBuf);
  switchLED(TXMode, false);
  // Start transmission.
  ESAT_COMTransceiverCommands.startTransmission(*transceiver, transceiverRadioChannel, RADIO_MAX_PACKET_LENGTH);
  transmissionInProgress = true;
  return ESAT_COMTransceiverDriverClass::noError;
}

byte* ESAT_COMTransceiverDriverClass::read(void)
{
  while (!available());
  receptionAvailable = false;
  startReception();
  return receptionBuffer;
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::setChannel(byte channel)
{
  if (channel < lowestChannel || channel > highestChannel)
  {
    return wrongChannelError;
  }
  transceiverRadioChannel = channel;
  return noError;
}

void ESAT_COMTransceiverDriverClass::setDefaultChannel(byte channel)
{
  defaultChannel = channel;
}

void ESAT_COMTransceiverDriverClass::setDefaultFrequency(float frequency)
{
  defaultFrequency = frequency;
}

void ESAT_COMTransceiverDriverClass::setDefaultModulationSource(ESAT_COMTransceiverDriverClass::ModulationSource modulationSource)
{
  defaultModulationSource = modulationSource;
}

void ESAT_COMTransceiverDriverClass::setDefaultModulationType(ESAT_COMTransceiverDriverClass::ModulationType modulationType)
{
  defaultModulationType = modulationType;
}

void ESAT_COMTransceiverDriverClass::setDefaultTransmissionPower(float transmissionPowerRate)
{
  defaultTransmissionPowerRate = transmissionPowerRate;
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::setFrequency(float frequency)
{
  if ((frequency <= 1050.0 && frequency >= 850.0)
      || (frequency <= 525.0 && frequency >= 425.0)
      || (frequency <= 350.0 && frequency >= 284.0)
      || (frequency <= 175.0 && frequency >= 142.0))
  {
    // Store the set frequency.
    transceiverFrequency = frequency;
    return noError;
  }
  return wrongFrequencyError;
}

void ESAT_COMTransceiverDriverClass::setHighestChannel(byte channel)
{
  highestChannel = channel;
}

void ESAT_COMTransceiverDriverClass::setLowestChannel(byte channel)
{
  lowestChannel = channel;
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::setModulationSource(ESAT_COMTransceiverDriverClass::ModulationSource modulationSource)
{
  transmitterModulationSource = modulationSource;
  ESAT_COMTransceiverConfigurationClass* transceiverConfiguration;
  switch (transceiverOperationMode)
  {
    case TXMode:
    {
      transceiverConfiguration = transmissionConfigurationData;
      break;
    }
    case RXMode:
    {
      transceiverConfiguration = receptionConfigurationData;
      break;
    }
    default:
    {
      return wrongModeError;
    }
  }
  byte modulationSourceMask = 0;
  byte modulationTypeMask = 0;
  // Four level modulations aren't supported if GPIOs are used as modulation source.
  if ((modulationSource != fifo && modulationSource != randomGenerator) && (transceiverModulationType == fourFSK || transceiverModulationType == fourGaussianFSK))
  {
    return wrongModeError;
  }
  // Also 2-GFSK modulation isn't supported in asynchronous modes.
  if ((modulationSource == gpio0_asynchronous || modulationSource == gpio1_asynchronous) && transceiverModulationType == twoGaussianFSK)
  {
    return wrongModeError;
  }
  // Select the modulation source.
  modulationSourceMask = switchModulationSource(modulationSource);
  // If the function returns 0xFF means that the selected source isn't available.
  if (modulationSourceMask == 0xFF)
  {
    return wrongModeError;
  }
  // Select the modulation type bytes but THE MODULATION DOESN'T CHANGE HERE, IT NEEDS A RECONFIGURATION.
  modulationTypeMask = switchModulationType(transceiverModulationType); // Use the stored modulation.
  if (modulationTypeMask == 0xFF) // If the function returns 0xFF, it means that the selected modulation isn't available.
  {
    return wrongModeError;
  }
  return translateLowLevelDriverError(transceiverConfiguration -> configureModulationSource(*transceiver, (byte)(modulationSourceMask | modulationTypeMask)));
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::setModulationType(ESAT_COMTransceiverDriverClass::ModulationType modulationType)
{
  transceiverModulationType = modulationType;
  return noError;
}

void ESAT_COMTransceiverDriverClass::setReceptionTransceiverInterruptFlag (void)
{
  receptionInterruptFlag = 0xFF;
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::setTransmissionPower(float transmissionPowerRateToBeSet)
{
  // Power can't be changed unless transmission mode is selected.
  if (transceiverOperationMode != ESAT_COMTransceiverDriverClass::TXMode)
  {
    return ESAT_COMTransceiverDriverClass::wrongPowerError;
  }
  if (transmissionPowerRateToBeSet < MINIMUM_TRANSMISSION_POWER_RATE)
  {
    transmissionPowerRateToBeSet = MINIMUM_TRANSMISSION_POWER_RATE;
  }
  else if (transmissionPowerRateToBeSet > MAXIMUM_TRANSMISSION_POWER_RATE)
  {
    transmissionPowerRateToBeSet = MAXIMUM_TRANSMISSION_POWER_RATE;
  }
  // Store the set power.
  transmissionPowerRate = transmissionPowerRateToBeSet;
  return noError;
}

void ESAT_COMTransceiverDriverClass::setTransmissionTransceiverInterruptFlag (void)
{
    transmissionInterruptFlag = 0xFF;
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::startReception (void)
{
  if (transceiverOperationMode!=RXMode)
  {
    return wrongModeError;
  }
  receptionAvailable = false;
  // Read and clear interrupts.
  ESAT_COMTransceiverCommands.getInterruptStatus(*transceiver, 0, 0, 0);
  // Reset the FIFO.
  ESAT_COMTransceiverCommands.getFIFOStatus(*transceiver, true, true);
  // Start reception.
  // Length field is zero beacause it is controlled from the packet handler.
  ESAT_COMTransceiverCommands.startReception(*transceiver, transceiverRadioChannel, 0x00);
  return noError;
}

void ESAT_COMTransceiverDriverClass::switchLED(ESAT_COMTransceiverDriverClass::TransceiverMode modeLED, boolean level)
{
  switch(modeLED)
  {
    case TXMode:
      if (level)
      {
        ESAT_COMTransmissionLED.write(100.0);
        return;
      }
      else
      {
        ESAT_COMTransmissionLED.write(0.0);
        return;
      }
    case RXMode:
      if (level)
      {
        ESAT_COMReceptionLED.write(100.0);
        return;
      }
      else
      {
        ESAT_COMReceptionLED.write(0.0);
        return;
      }
    default:
      return;
  }
}

byte  ESAT_COMTransceiverDriverClass::switchModulationSource(ESAT_COMTransceiverDriverClass::ModulationSource source)
{
  switch(source)
  {
    case (fifo):
    {
      return ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_MODULATION_TYPE_PACKET_HANDLER_MASK;
    }
    case (gpio0_synchronous):
    {
      return ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_MODULATION_TYPE_GPIO0_SYNCHRONOUS_MASK;
    }
    case (gpio0_asynchronous):
    {
      return ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_MODULATION_TYPE_GPIO0_ASYNCHRONOUS_MASK;
    }
    case (gpio1_synchronous):
    {
      return ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_MODULATION_TYPE_GPIO1_SYNCHRONOUS_MASK;
    }
    case (gpio1_asynchronous):
    {
      return ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_MODULATION_TYPE_GPIO1_ASYNCHRONOUS_MASK;
    }
    case (gpio2_synchronous):
    {
      return ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_MODULATION_TYPE_GPIO2_SYNCHRONOUS_MASK;
    }
    case (gpio2_asynchronous):
    {
      return ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_MODULATION_TYPE_GPIO2_ASYNCHRONOUS_MASK;
    }
    case (gpio3_synchronous):
    {
      return ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_MODULATION_TYPE_GPIO3_SYNCHRONOUS_MASK;
    }
    case (gpio3_asynchronous):
    {
      return ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_MODULATION_TYPE_GPIO3_ASYNCHRONOUS_MASK;
    }
    case (randomGenerator):
    {
      return ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_MODULATION_TYPE_RANDOM_GENERATOR_MASK;
    }
    default:
    {
      return 0xFF; // WrongModeError.
    }
  }
}

byte  ESAT_COMTransceiverDriverClass::switchModulationType(ESAT_COMTransceiverDriverClass::ModulationType type)
{
  switch (type)
  {
    case (continuousWave):
    {
      return ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_MODULATION_TYPE_CONTINUOUS_WAVE_MASK;
    }
    case (OOK):
    {
      return ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_MODULATION_TYPE_OOK_MASK;
    }
    case (twoFSK):
    {
      return ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_MODULATION_TYPE_2FSK_MASK;
    }
    case (twoGaussianFSK):
    {
      return ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_MODULATION_TYPE_2GFSK_MASK;
    }
    case (fourFSK):
    {
      return ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_MODULATION_TYPE_4FSK_MASK;
    }
    case (fourGaussianFSK):
    {
      return ESAT_COMTransceiverPropertiesClass::PARAMETER_MODEM_MODULATION_TYPE_4GFSK_MASK;
    }
    default:
    {
      return 0xFF; // WrongModeError.
    }
  }
}

ESAT_COMTransceiverConfigurationClass* ESAT_COMTransceiverDriverClass::switchReceptionConfiguration(ESAT_COMTransceiverDriverClass::ModulationType modulationType)
{
  switch (modulationType)
  {
    case (twoFSK):
    {
    return &ESAT_COM2FSKReceptionConfiguration;
    }
    case (twoGaussianFSK):
    {
      return &ESAT_COM2GFSKReceptionConfiguration;
    }
    case (fourFSK):
    {
      return &ESAT_COM4FSKReceptionConfiguration;
    }
    case (fourGaussianFSK):
    {
      return &ESAT_COM4GFSKReceptionConfiguration;
    }
    case (continuousWave):
    case (OOK):
    default:
    {
      return &ESAT_COMOOKReceptionConfiguration;
    }
  }
}

ESAT_COMTransceiverConfigurationClass* ESAT_COMTransceiverDriverClass::switchTransmissionConfiguration(ESAT_COMTransceiverDriverClass::ModulationType modulationType)
{
  switch (modulationType)
  {

    case (twoFSK):
    {
      return &ESAT_COM2FSKTransmissionConfiguration;
    }
    case (twoGaussianFSK):
    {
      return &ESAT_COM2GFSKTransmissionConfiguration;
    }
    case (fourFSK):
    {
      return &ESAT_COM4FSKTransmissionConfiguration;
    }
    case (fourGaussianFSK):
    {
      return &ESAT_COM4GFSKTransmissionConfiguration;
    }
    case (continuousWave):
    case (OOK):
    default:
    {
      return &ESAT_COMOOKTransmissionConfiguration;
    }
  }
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::translateLowLevelDriverError(ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError error)
{
  switch (error)
  {
    case ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS:
      return ESAT_COMTransceiverDriverClass::noError;
    case ESAT_COMTransceiverHALClass::TRANSCEIVER_CTS_TIMEOUT:
      return ESAT_COMTransceiverDriverClass::CTSError;
    case ESAT_COMTransceiverHALClass::TRANSCEIVER_COMMAND_ERROR:
      return ESAT_COMTransceiverDriverClass::commandError;
    case ESAT_COMTransceiverHALClass::TRANSCEIVER_CHIP_ERROR:
      return ESAT_COMTransceiverDriverClass::chipError;
    default:
      return ESAT_COMTransceiverDriverClass::error;
  }
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::updateFrequency()
{
  float frequency = transceiverFrequency;
  // Get the configuration.
  ESAT_COMTransceiverConfigurationClass* transceiverConfiguration;
  switch (transceiverOperationMode)
  {
    case TXMode:
    {
      transceiverConfiguration = transmissionConfigurationData;
      break;
    }
    case RXMode:
    {
      transceiverConfiguration = receptionConfigurationData;
      break;
    }
    default:
    {
      return wrongModeError;
    }
  }
  // See Si446x Data Sheet section 5.3.1.
  // Also the Si446x PLL Synthesizer / VCO_CNT Calculator Rev 0.4.
  byte band;
  byte outdiv;
  // Non-continuous frequency bands.
  if (frequency <= 1050.0 && frequency >= 850.0)
  {
    outdiv = 4;
    band = 0;
  }
  else if (frequency <= 525.0 && frequency >= 425.0)
  {
    outdiv = 8;
    band = 2;
  }
  else if (frequency <= 350.0 && frequency >= 284.0)
  {
    outdiv = 12;
    band = 3;
  }
  else if (frequency <= 175.0 && frequency >= 142.0)
  {
    outdiv = 24;
    band = 5;
  }
  else
  {
    return wrongFrequencyError;
  }
  TransceiverErrorCode error = translateLowLevelDriverError(transceiverConfiguration -> configureClockGenerator(*transceiver, band));
  if (noError != error)
  {
    return error;
  }
  frequency *= 1000000.0; // Convert to Hz.
  // Now generate the RF frequency properties.
  // Need the Xtal/XO freq from the radio_config file.
  unsigned long f_pfd = 2 * CRYSTAL_FOR_FREQUENCY_COMPUTING / outdiv;
  unsigned int pll_integer = ((unsigned int)(frequency / f_pfd)) - 1; // Compute integer part less one.
  float ratio = frequency / (float)f_pfd; // The integer part is recalculated in floating point.
  float rest  = ratio - (float)pll_integer; // To get the decimal part plus one.
  unsigned long pll_fractional = (unsigned long)(rest * 524288UL); // Decimal part is casted to integer multiplying by 2^19.
  unsigned int pll_fractional_msb = pll_fractional / 0x10000; // And is assigned "properly" to the registers.
  unsigned int pll_fractional_middle = (pll_fractional - pll_fractional_msb * 0x10000) / 0x100;
  unsigned int pll_fractional_lsb = (pll_fractional - pll_fractional_msb * 0x10000 - pll_fractional_middle * 0x100);
  return translateLowLevelDriverError(transceiverConfiguration -> setFrequency(*transceiver, (byte)pll_integer, (byte)pll_fractional_msb, (byte)pll_fractional_middle, (byte)pll_fractional_lsb));
}

void ESAT_COMTransceiverDriverClass::updateManualDataStream()
{
  const word milliseconds = millis() % OUTPUT_DATA_STREAM_TOGGLING_PERIOD_MS;
  if (milliseconds > (OUTPUT_DATA_STREAM_TOGGLING_PERIOD_MS / 2))
  {
    if (transmitterModulationSource == gpio2_asynchronous)
    {
      transceiver -> writeDataStreamGPIO(outputDataStreamNextBit);
    }
    else
    {
      transceiver -> writeDataStreamGPIO(LOW);
    }
    if (outputDataStreamNextBit == 1)
    {
      outputDataStreamNextBit = 0;
    }
    else
    {
      outputDataStreamNextBit = 1;
    }
  }
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::updateTransmissionPower()
{
  const float mappedPowerValue = (transmissionPowerRate / MAXIMUM_TRANSMISSION_POWER_RATE) * MAXIMUM_POWER_VALUE;
  return translateLowLevelDriverError(transmissionConfigurationData -> setTransmissionPower(*transceiver, (byte) mappedPowerValue));
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::write(byte* msgBuf)
{
  if (transceiverOperationMode != TXMode)
  {
    return wrongModeError;
  }
  nonBlockingWrite(msgBuf);
  while (!available())
  {
  }
  return noError;
}

volatile byte ESAT_COMTransceiverDriverClass::receptionInterruptFlag;

ESAT_COMTransceiverDriverClass ESAT_COMReceptionTransceiver(ESAT_COMReceptionTransceiverLowLevelDriver);

volatile byte ESAT_COMTransceiverDriverClass::transmissionInterruptFlag;

ESAT_COMTransceiverDriverClass ESAT_COMTransmissionTransceiver(ESAT_COMTransmissionTransceiverLowLevelDriver);
