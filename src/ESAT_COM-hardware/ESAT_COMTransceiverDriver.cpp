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
 
#include <SPI.h>
#include "ESAT_COMReceptionLED.h"
#include "ESAT_COMTransmissionLED.h"
#include "ESAT_COMTransceiverDriver.h"
#include "ESAT_COMTransceiverCommands.h"
#include "ESAT_COMTransceiverProperties.h"

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


ESAT_COMTransceiverDriverClass::ESAT_COMTransceiverDriverClass(ESAT_COMTransceiverInterfaceClass& hardwareTransceiver)
{   
  //Attaches the hardware transceiver pointer to be used by this ESAT_COMTransceiverDriverClass object
  transceiver = &hardwareTransceiver;  
  receptionFrequency = DEFAULT_RECEPTION_FREQUENCY;
  transmissionFrequency = DEFAULT_TRANSMISSION_FREQUENCY;
  transceiverOperationMode = notInitializedMode;
  transceiverModulationType = DEFAULT_MODULATION_TYPE;
  transmissionPowerRate = DEFAULT_TRANSMISSION_POWER_RATE;
  failedInitializationCounter = 0;
}
 
int8_t ESAT_COMTransceiverDriverClass::available(void)
{
  switch (transceiverOperationMode)
  {
    case TXInterruptsMode:
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
    case RXInterruptsMode:
    {  
      if (receptionAvailable == true) // If reception was available but still not read, return 1
      {
        DEBUG_PRINT("ReceptionAvailable");
        return 1;
      }
      else // If received data was read and reception reenabled.
      {
        noInterrupts();
        // Check if interrupt flag is set.
        if (receptionInterruptFlag) 
        { 
          DEBUG_PRINTLN("Pending available interrupt");
          receptionInterruptFlag = 0;
          interrupts(); 
          return checkReceptionAvailability(); // Retrieve received packet and set available flag.          
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
  // Configure hardware
  transceiver -> begin();
  return begin(mode, transceiverModulationType);  
} 

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::begin(ESAT_COMTransceiverDriverClass::TransceiverMode mode, ESAT_COMTransceiverDriverClass::ModulationType modulationType)
{
  transceiverOperationMode = mode;
  transceiverModulationType = modulationType;  
  TransceiverErrorCode error;
  switch (transceiverOperationMode)
  {
    case TXInterruptsMode:
    {
      ESAT_COMTransmissionLED.begin();
      //DEBUG_PRINTLN("Initializing TX interrupts");
      transmissionConfigurationData = switchTransmissionConfiguration(transceiverModulationType);
      error = translateLowLevelDriverError(initializeTransceiver(transmissionConfigurationData));
      if(noError != error)
      {        
        return error;
      }
      //Clear flag
      transmissionInterruptFlag = 0;
      //Enable interrupts. If ISR is fired during init and is not cleared interrupts may not be retriggered
      attachInterrupt(digitalPinToInterrupt(transceiver -> getInterruptPin()), setTransmissionTransceiverInterruptFlag,  FALLING);  
      // TODO
      // Check error handling
      setFrequency(transmissionFrequency);
      setTransmissionPower(transmissionPowerRate);
      break;
    }
    case RXInterruptsMode:
    {
      ESAT_COMReceptionLED.begin();      
      receptionConfigurationData = switchReceptionConfiguration(transceiverModulationType);
      error = translateLowLevelDriverError(initializeTransceiver(receptionConfigurationData));
      if(noError != error)
      {        
        return error;
      }     
      //Clear flag
      receptionInterruptFlag = 0;
      //Enable interrupts. If ISR is fired during init and is not cleared interrupts may not be retriggered
      attachInterrupt(digitalPinToInterrupt(transceiver -> getInterruptPin()), setReceptionTransceiverInterruptFlag,  FALLING);
      //Starts reception
      setFrequency(receptionFrequency);
      startReception(); 
      break;
    }
    default:
    {
      return wrongModeError;
    }  
  }  
  return noError;
}

int8_t ESAT_COMTransceiverDriverClass::checkReceptionAvailability()
{
  ESAT_COMTransceiverCommandsClass::InterruptStatusReply intStatusReply = ESAT_COMTransceiverCommands.getInterruptStatus(*transceiver, 0, 0, 0);
  if (intStatusReply.packetHandlerPending & ESAT_COMTransceiverCommandsClass::INTERRUPT_STATUS_REPLY_PACKET_HANDLER_PENDING_PACKET_RECEIVED_BITMASK) // If packet has ended.
  {
    DEBUG_PRINTLN("Packet RX pending");
    // Retrieve from fifo
    receptionAvailable = true;
    ESAT_COMReceptionLED.write(100.0);
    ESAT_COMTransceiverCommands.readReceptionFIFOBuffer(*transceiver, RADIO_MAX_PACKET_LENGTH, receptionBuffer);
    ESAT_COMReceptionLED.write(0.0);
    // Reception must be reenabled (ideally after reading).
    return 1;
  }
  return 0;
  
}

int8_t ESAT_COMTransceiverDriverClass::checkTransmissionAvailability()
{
  ESAT_COMTransceiverCommandsClass::InterruptStatusReply intStatusReply =  ESAT_COMTransceiverCommands.getInterruptStatus(*transceiver, 0, 0, 0);
  if (intStatusReply.packetHandlerPending & ESAT_COMTransceiverCommandsClass::INTERRUPT_STATUS_REPLY_PACKET_HANDLER_PENDING_PACKET_SENT_BITMASK)
  {
    transmissionInProgress = false;
    return 1;
  }
  return 0;
}

// TODO
// Move to interface
ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::configureModulationSource(ESAT_COMTransceiverDriverClass::ModulationSource modulationSource)
{  

  ESAT_COMTransceiverConfigurationClass* transceiverConfiguration;  
  switch (transceiverOperationMode)
  {
    case TXInterruptsMode:
    {
      transceiverConfiguration = transmissionConfigurationData;
      break;
    }
    case RXInterruptsMode:
    {
      transceiverConfiguration = receptionConfigurationData;
      break;
    }
    default:
    {
      return wrongModeError;
    }    
  }  
  uint8_t modulationSourceMask = 0;  
  uint8_t modulationTypeMask = 0;    
  //4 level modulations aren't supported if GPIO is used as modulation source
  if ((modulationSource != fifo && modulationSource != randomGenerator) && (transceiverModulationType == fourFSK || transceiverModulationType == fourGaussianFSK)) 
  {
    return wrongModeError;
  }  
  // Also 2-GFSK modulation isn't supported in asynchronous mode
  if ((modulationSource == gpio0_asynchronous || modulationSource == gpio1_asynchronous) && transceiverModulationType == twoGaussianFSK)
  {
    return wrongModeError;
  }  
  //Selects modulation source
  modulationSourceMask = switchModulationSource(modulationSource);
  if (modulationSourceMask == 0xFF) //If function returns 0xFF means that the selected source isn't available
  {
    return wrongModeError;
  }
  //Selects the modulation type bytes but DOESN'T CHANGE THE MODULATION HERE, NEEDS A RECONFIGURATION
  modulationTypeMask = switchModulationType(transceiverModulationType); //uses stored modulation
  if (modulationTypeMask == 0xFF) //If function returns 0xFF means that the selected modulation isn't available
  {
    return wrongModeError;
  }  
  return translateLowLevelDriverError(transceiverConfiguration -> configureModulationSource(*transceiver, (uint8_t)(modulationSourceMask | modulationTypeMask)));
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::configureModulationType(ESAT_COMTransceiverDriverClass::ModulationType modulationType)
{
  // Store new modulation type.
  transceiverModulationType = modulationType;
  return begin(transceiverOperationMode, transceiverModulationType);
}

void ESAT_COMTransceiverDriverClass::disable(void)
{
  disableInterrupts(); //Ensure ISRs are detached.
  transceiverOperationMode = notInitializedMode;
  transceiver -> disable();
} 


uint8_t ESAT_COMTransceiverDriverClass::getChannel()
{
  return transceiverRadioChannel;
}


float ESAT_COMTransceiverDriverClass::getFrequency()
{
  switch (transceiverOperationMode)
  {
    case TXInterruptsMode:
    {
      return transmissionFrequency;
    }
    case RXInterruptsMode:
    {
      return receptionFrequency;
    }
    default:
    {
      return -1.0;
    }    
  }
}


uint8_t ESAT_COMTransceiverDriverClass::getModulation()
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

uint8_t ESAT_COMTransceiverDriverClass::getReceivedSignalStrengthIndicator()
{
  if (transceiverOperationMode != RXInterruptsMode)
  {
    return 0;
  } 
  
  ESAT_COMTransceiverCommandsClass::ModemStatusReply reply = ESAT_COMTransceiverCommands.getModemStatus(*transceiver, 0xFF);
  return reply.currentReceivedSignalStregnthIndicator;
}

uint16_t ESAT_COMTransceiverDriverClass::getTransceiverTemperature()
{
  // If transceiver is disabled return 0 (better returning error but not yet)
  if ((transceiverOperationMode != RXInterruptsMode) && (transceiverOperationMode != TXInterruptsMode))
  {
    return 0;
  } 
  ESAT_COMTransceiverCommandsClass::ADCReadingsReply reply = ESAT_COMTransceiverCommands.getADCReading(*transceiver, ESAT_COMTransceiverCommandsClass::ADC_READ_ARGUMENT_READ_TEMPERATURE_BITMASK);
  return reply.temperatureRawValue; //MAY need to clear upper nibble bc is 11 bit adc.
}

uint16_t ESAT_COMTransceiverDriverClass::getTransceiverVoltage()
{
  // If transceiver is disabled return 0 (better returning error but not yet)
  if ((transceiverOperationMode!=RXInterruptsMode) && (transceiverOperationMode!=TXInterruptsMode))
  {
    return 0;
  } 
   ESAT_COMTransceiverCommandsClass::ADCReadingsReply reply =  ESAT_COMTransceiverCommands.getADCReading(*transceiver, ESAT_COMTransceiverCommandsClass::ADC_READ_ARGUMENT_READ_VOLTAGE_BITMASK);
  return reply.voltageRawValue; //MAY need to clear upper nibble bc is 11 bit adc.
}

float ESAT_COMTransceiverDriverClass::getTransmissionPowerRate()
{
  switch (transceiverOperationMode)
  {
    case ESAT_COMTransceiverDriverClass::TXInterruptsMode:
    {
      return transmissionPowerRate;
    }
    case ESAT_COMTransceiverDriverClass::RXInterruptsMode:
    default:
    {
      // If transceiver is disabled return 0 (better returning error but not yet)
      return 0.0;
    }    
  }
} 

ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError ESAT_COMTransceiverDriverClass::initializeTransceiver(ESAT_COMTransceiverConfigurationClass* transceiverConfiguration)
{ 
  transceiver -> reset();  
  // Load path (if defined).
  ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError error = ESAT_COMTransceiverCommands.applyPatch(*transceiver);
  if (ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS != error)
  {
    // If fail rate is overcome.
    if (MAXIMUM_FAILED_INITIALIZATIONS <= failedInitializationCounter)
    {
      return error;
    }       
    ++failedInitializationCounter;
    delay(10);    
    // Recursive retrial
    return initializeTransceiver(transceiverConfiguration);
  }
  // Load configuration.
  // TODO
  // Think about a CTS timeout for these
  // However, on WDS these commands don't request for CTS or check wrong interrupt level fault 
  // (they may not provide them; applyPatch and setProperty yes). This hardens the way for checking 
  // a communication fault.  
  ESAT_COMTransceiverCommands.powerUp(*transceiver);
  ESAT_COMTransceiverCommands.getInterruptStatus(*transceiver, 0, 0, 0);
  ESAT_COMTransceiverCommands.configureGPIODefault(*transceiver);
  error = transceiverConfiguration -> applyConfiguration(*transceiver);
  if (ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS != error)
  {
    // If fail rate is overcome.
    if (MAXIMUM_FAILED_INITIALIZATIONS <= failedInitializationCounter)
    {
      return error;
    }       
    ++failedInitializationCounter;
    delay(10);
    // Recursive retrial
    return initializeTransceiver(transceiverConfiguration);
  }
  // Read interrupts and clear pending ones.
  ESAT_COMTransceiverCommandsClass::InterruptStatusReply intStatusReply = ESAT_COMTransceiverCommands.getInterruptStatus(*transceiver, 0, 0, 0);
  // Check if chip is ready to accept commands.
  if ((intStatusReply.chipStatus & ESAT_COMTransceiverCommandsClass::INTERRUPT_STATUS_REPLY_CHIP_STATUS_CHIP_READY_BITMASK)&& !(intStatusReply.chipPending & ESAT_COMTransceiverCommandsClass::INTERRUPT_STATUS_REPLY_CHIP_PENDING_CHIP_READY_BITMASK)) 
  {
    return ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS;
  }
  return ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_CHIP_ERROR;
}

uint8_t* ESAT_COMTransceiverDriverClass::nonBlockingRead(void)
{
    receptionAvailable = false;
    startReception();
    return receptionBuffer;  
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::nonBlockingWrite(uint8_t* msgBuf)
{
  if (transceiverOperationMode != ESAT_COMTransceiverDriverClass::TXInterruptsMode)
  {
    return ESAT_COMTransceiverDriverClass::wrongModeError;
  }    
  // Reset FIFO
  ESAT_COMTransceiverCommands.getFIFOStatus(*transceiver, true, true);
  // Read interrupts and clear pending ones.
  ESAT_COMTransceiverCommands.getInterruptStatus(*transceiver, 0, 0, 0);
  // Load 129 bytes into fifo.
  ESAT_COMTransmissionLED.write(100.0);
  ESAT_COMTransceiverCommands.writeTransmissionFIFOBuffer(*transceiver, RADIO_MAX_PACKET_LENGTH, msgBuf);
  ESAT_COMTransmissionLED.write(0.0);
  // Start transmission
  ESAT_COMTransceiverCommands.startTransmission(*transceiver, transceiverRadioChannel, RADIO_MAX_PACKET_LENGTH); 
  transmissionInProgress = true;  
  return ESAT_COMTransceiverDriverClass::noError;
}

uint8_t* ESAT_COMTransceiverDriverClass::read(void)
{
  while(!available());
  receptionAvailable = false;
  startReception();
  return receptionBuffer;  
}

void ESAT_COMTransceiverDriverClass::setReceptionTransceiverInterruptFlag (void)
{
    receptionInterruptFlag = 0xFF;  
}

void ESAT_COMTransceiverDriverClass::setChannel(uint8_t channel)
{
  transceiverRadioChannel = channel;
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::setFrequency(float frequency)
{
  ESAT_COMTransceiverConfigurationClass* transceiverConfiguration;  
  // Store set frequency.
  switch (transceiverOperationMode)
  {
    case TXInterruptsMode:
    {
      transmissionFrequency = frequency;
      transceiverConfiguration = transmissionConfigurationData;
      break;
    }
    case RXInterruptsMode:
    {
      receptionFrequency = frequency;
      transceiverConfiguration = receptionConfigurationData;
      break;
    }
    default:
    {
      return wrongModeError;
    }    
  }   
  // See Si446x Data Sheet section 5.3.1
  // Also the Si446x PLL Synthesizer / VCO_CNT Calculator Rev 0.4
  uint8_t band;
  uint8_t outdiv;
  // Non-continuous frequency bands
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
  frequency *= 1000000.0; // Convert to Hz
  // Now generate the RF frequency properties
  // Need the Xtal/XO freq from the radio_config file:
  unsigned long f_pfd = 2 * CRYSTAL_FOR_FREQUENCY_COMPUTING / outdiv;
  unsigned int pll_integer = ((unsigned int)(frequency / f_pfd)) - 1; //Computes integer part less one.
  float ratio = frequency / (float)f_pfd; //The integer part is recalculated in floating point.
  float rest  = ratio - (float)pll_integer; //To get the decimal part plus one.
  unsigned long pll_fractional = (unsigned long)(rest * 524288UL); // Decimal part is casted to integer multiplying by 2^19.
  unsigned int pll_fractional_msb = pll_fractional / 0x10000; //And is assigned "properly" to registers.
  unsigned int pll_fractional_middle = (pll_fractional - pll_fractional_msb * 0x10000) / 0x100;
  unsigned int pll_fractional_lsb = (pll_fractional - pll_fractional_msb * 0x10000 - pll_fractional_middle * 0x100);  
  return translateLowLevelDriverError(transceiverConfiguration -> setFrequency(*transceiver, (uint8_t)pll_integer, (uint8_t)pll_fractional_msb, (uint8_t)pll_fractional_middle, (uint8_t)pll_fractional_lsb));
}
 
ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::disableInterrupts(void)
{
  switch (transceiverOperationMode)
  {   
    case TXInterruptsMode:
    {
      // Disable interrupts
      detachInterrupt(digitalPinToInterrupt(transceiver -> getInterruptPin()));
      // Clear flag
      transmissionInterruptFlag = 0;
      return noError;
    }
    case RXInterruptsMode:
    {
      // Disable interrupts
      detachInterrupt(digitalPinToInterrupt(transceiver -> getInterruptPin()));
      // Clear flags
      receptionInterruptFlag = 0;      
      return noError;
    }
    default:
    {
      return wrongModeError;
    }  
  }
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::setTransmissionPower(float transmissionPowerRateToBeSet)
{
  //Power can't be changed in non-TX mode (or disabled)
  if (transceiverOperationMode != ESAT_COMTransceiverDriverClass::TXInterruptsMode)
  {
    return ESAT_COMTransceiverDriverClass::wrongPowerError;
  }
  if (transmissionPowerRateToBeSet < MINIMUM_TRANSMISSION_POWER_RATE)
  {
    transmissionPowerRateToBeSet = MINIMUM_TRANSMISSION_POWER_RATE;
  }
  if (transmissionPowerRateToBeSet > MAXIMUM_TRANSMISSION_POWER_RATE)
  {
    transmissionPowerRateToBeSet = MAXIMUM_TRANSMISSION_POWER_RATE;
  }
  // Store set power.
  transmissionPowerRate = transmissionPowerRateToBeSet;
  const float mappedPowerValue = (transmissionPowerRateToBeSet / MAXIMUM_TRANSMISSION_POWER_RATE) * MAXIMUM_POWER_VALUE; 
  return translateLowLevelDriverError(transmissionConfigurationData -> setTransmissionPower(*transceiver, (uint8_t) mappedPowerValue));  
}
 
ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::startReception (void)
{
  if (transceiverOperationMode!=RXInterruptsMode)
  {
    return wrongModeError;
  }
  receptionAvailable = false;
  //Read and clear interrupts.  
  ESAT_COMTransceiverCommands.getInterruptStatus(*transceiver, 0, 0, 0);
  // Reset FIFO.
  ESAT_COMTransceiverCommands.getFIFOStatus(*transceiver, true, true);  
  // Start reception
  // Length field is zero beacause is controlled from the packet handler.
  ESAT_COMTransceiverCommands.startReception(*transceiver, transceiverRadioChannel, 0x00);
  return noError;
}

ESAT_COMTransceiverConfigurationClass* ESAT_COMTransceiverDriverClass::switchReceptionConfiguration(ESAT_COMTransceiverDriverClass::ModulationType modulationType)
{
  switch(modulationType)    
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
  switch(modulationType)    
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

uint8_t  ESAT_COMTransceiverDriverClass::switchModulationSource(ESAT_COMTransceiverDriverClass::ModulationSource source)
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
      return 0xFF; //WrongModeError
    }
  }
}

uint8_t  ESAT_COMTransceiverDriverClass::switchModulationType(ESAT_COMTransceiverDriverClass::ModulationType type)
{
  switch(type)    
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
      return 0xFF; //WrongModeError
    }
  }  
}

void ESAT_COMTransceiverDriverClass::setTransmissionTransceiverInterruptFlag (void)
{
    transmissionInterruptFlag = 0xFF; 
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::write(uint8_t* msgBuf)
{
  if (transceiverOperationMode != TXInterruptsMode)
  {
    return wrongModeError;
  }
  nonBlockingWrite(msgBuf);
  while(!available())
  {    
  }    
  return noError;
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::translateLowLevelDriverError(ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError error)
{
    switch(error)
    {
      case ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS:
        return ESAT_COMTransceiverDriverClass::noError;
      case ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_CTS_TIMEOUT: 
        return ESAT_COMTransceiverDriverClass::CTSError;
      case ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_COMMAND_ERROR:
      return ESAT_COMTransceiverDriverClass::commandError;
      case ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_CHIP_ERROR:
        return ESAT_COMTransceiverDriverClass::chipError;
      default:
        return ESAT_COMTransceiverDriverClass::error;
  }
}

volatile uint8_t ESAT_COMTransceiverDriverClass::receptionInterruptFlag;

ESAT_COMTransceiverDriverClass ReceptionTransceiver(ReceptionTransceiverLowLevelDriver);

volatile uint8_t ESAT_COMTransceiverDriverClass::transmissionInterruptFlag;

ESAT_COMTransceiverDriverClass TransmissionTransceiver(TransmissionTransceiverLowLevelDriver);
