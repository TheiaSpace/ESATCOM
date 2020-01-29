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
 
#include "ESAT_COMTransceiverDriver.h"
#include "ESAT_COMReceptionLED.h"
#include "ESAT_COMTransmissionLED.h"
#include <SPI.h>
#include "ESAT_COMTransceiverCommands.h"
#include "ESAT_COMTransceiverProperties.h"
#include "configurations/ConfigurationFileReception2FSK.h"
#include "configurations/ConfigurationFileReception2GFSK.h"
#include "configurations/ConfigurationFileReception4FSK.h"
#include "configurations/ConfigurationFileReception4GFSK.h"
#include "configurations/ConfigurationFileReceptionOOK.h"
#include "configurations/ConfigurationFileTransmission2FSK.h"
#include "configurations/ConfigurationFileTransmission2GFSK.h"
#include "configurations/ConfigurationFileTransmission4FSK.h"
#include "configurations/ConfigurationFileTransmission4GFSK.h"
#include "configurations/ConfigurationFileTransmissionOOK.h"

ESAT_COMTransceiverDriverClass::ESAT_COMTransceiverDriverClass(ESAT_COMTransceiverInterfaceClass& hardwareTransceiver)
{   
  //Attaches the hardware transceiver to be used by this ESAT_COMTransceiverDriverClass object
  transceiver = &hardwareTransceiver;  
  receptionFrequency = DEFAULT_RECEPTION_FREQUENCY;
  transmissionFrequency = DEFAULT_TRANSMISSION_FREQUENCY;
  transceiverOperationMode = notInitializedMode;
  transceiverModulationType = DEFAULT_MODULATION_TYPE;
  transmissionPowerRate = DEFAULT_TRANSMISSION_POWER_RATE;
}
 
uint8_t ESAT_COMTransceiverDriverClass::applyPatch()
{  
  volatile uint16_t line = 0;
  volatile uint8_t row = 0;
  const uint8_t TRANSCEIVER_PATCH[] = {
    8, 4, 33, 113, 75, 0, 0, 220, 149, 8, 5, 166, 34, 33, 240, 65, 91, 38, \
    8, 226, 47, 28, 187, 10, 168, 148, 40, 8, 5, 135, 103, 226, 88, 26, \
    7, 91, 8, 225, 208, 114, 216, 138, 184, 91, 125, 8, 5, 17, 236, 158, \
    40, 35, 27, 109, 8, 226, 79, 138, 178, 169, 41, 20, 19, 8, 5, 209, \
    46, 113, 106, 81, 76, 44, 8, 229, 128, 39, 66, 164, 105, 176, 127, 8, \
    5, 170, 129, 42, 189, 69, 232, 168, 8, 234, 228, 240, 36, 201, 159, \
    204, 60, 8, 5, 8, 245, 5, 4, 39, 98, 152, 8, 234, 107, 98, 132, 161, \
    249, 74, 226, 8, 5, 233, 119, 5, 79, 132, 238, 53, 8, 226, 67, 195, \
    141, 251, 173, 84, 37, 8, 5, 20, 6, 94, 57, 54, 47, 69, 8, 234, 12, \
    28, 116, 208, 17, 252, 50, 8, 5, 218, 56, 186, 14, 60, 231, 139, 8, \
    234, 176, 9, 230, 255, 148, 187, 169, 8, 5, 215, 17, 41, 254, 220, \
    113, 213, 8, 234, 127, 131, 167, 96, 144, 98, 24, 8, 5, 132, 127, \
    106, 209, 145, 198, 82, 8, 234, 42, 216, 123, 142, 74, 159, 145, 8, \
    5, 189, 170, 157, 22, 24, 6, 21, 8, 226, 85, 173, 45, 10, 20, 31, 93, \
    8, 5, 211, 224, 124, 57, 207, 1, 240, 8, 239, 58, 145, 114, 106, 3, \
    187, 150, 8, 231, 131, 109, 164, 146, 252, 19, 167, 8, 239, 248, 253, \
    207, 98, 7, 111, 30, 8, 231, 76, 234, 74, 117, 79, 214, 207, 8, 226, \
    246, 17, 228, 38, 13, 77, 198, 8, 5, 251, 191, 232, 7, 137, 195, 81, \
    8, 239, 130, 39, 4, 63, 150, 168, 88, 8, 231, 65, 41, 60, 117, 42, \
    3, 28, 8, 239, 175, 89, 152, 54, 170, 15, 6, 8, 230, 246, 147, 65, \
    45, 236, 14, 153, 8, 5, 41, 25, 144, 229, 170, 54, 64, 8, 231, 251, \
    104, 16, 125, 119, 93, 192, 8, 231, 203, 180, 221, 206, 144, 84, 190, \
    8, 231, 114, 138, 214, 2, 244, 221, 204, 8, 231, 106, 33, 11, 2, 134, \
    236, 21, 8, 231, 123, 124, 61, 107, 129, 3, 208, 8, 239, 125, 97, 54, \
    148, 124, 160, 223, 8, 239, 204, 133, 59, 218, 224, 92, 28, 8, 231, \
    227, 117, 187, 57, 34, 75, 168, 8, 239, 249, 206, 224, 94, 235, 29, \
    203, 8, 231, 189, 226, 112, 213, 171, 78, 63, 8, 231, 183, 141, 32, \
    104, 107, 9, 82, 8, 239, 161, 27, 144, 205, 152, 0, 99, 8, 239, 84, \
    103, 93, 156, 17, 252, 69, 8, 231, 212, 155, 200, 151, 190, 138, 7, \
    8, 239, 82, 141, 144, 99, 115, 213, 42, 8, 239, 3, 188, 110, 28, 118, \
    190, 74, 8, 231, 194, 237, 103, 186, 94, 102, 33, 8, 239, 231, 63, \
    135, 190, 224, 122, 109, 8, 231, 201, 112, 147, 29, 100, 245, 108, \
    8, 239, 245, 40, 8, 52, 179, 182, 44, 8, 239, 58, 10, 236, 15, 219, \
    86, 202, 8, 239, 57, 160, 110, 237, 121, 208, 36, 8, 231, 108, 11, \
    175, 169, 78, 64, 181, 8, 233, 185, 175, 191, 37, 80, 209, 55, 8, 5, \
    158, 219, 222, 63, 148, 233, 107, 8, 236, 197, 5, 170, 87, 220, 138, \
    94, 8, 5, 112, 218, 132, 132, 221, 202, 144
  };
  uint8_t cmdBuff[8];
  // Check if patch is needed.
  const ESAT_COMTransceiverDriverClass::PartInfoReply partInfoReply = partInfo();       
  if ((partInfoReply.ROMID == TRANSCEIVER_PATCH_ROMID) && ((partInfoReply.ID >> 8) <= TRANSCEIVER_PATCH_ID))
  {       
    for (line = 0; line < (sizeof(TRANSCEIVER_PATCH) / 9); line++)
    {             
      for (row = 0; row < 8; row++)
      {    
        cmdBuff[row] = TRANSCEIVER_PATCH[(line * 9) + row + 1];
      }
      if (transceiver -> writeCommandAndRetrieveResponse(8, cmdBuff, 0, 0) != 0xFF)
      {
        return ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_CTS_TIMEOUT;
      }
      // Check if error has occured.
      if (transceiver -> checkInterruptPin() == 0)
      {        
        getInterruptStatus(0, 0, 0);
        //No return values are necessary.
        return ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_PATCH_FAIL;
      }
    }
  }
  return ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS;
}

int8_t ESAT_COMTransceiverDriverClass::available(void)
{
  switch (transceiverOperationMode)
  {
    case ESAT_COMTransceiverDriverClass::TXMode:
    {
      if (transmissionInProgress == true)
      {
        if (transceiver -> checkInterruptPin() == 0)
        {
          return checkTransmissionAvailability();
        }
        return 0;
      }
      else
      {
        return 1;
      }      
    }
    case ESAT_COMTransceiverDriverClass::TXInterruptsMode:
    {
      if (transmissionInProgress == true)
      {
        noInterrupts();
        if (ESAT_COMTransceiverDriverClass::transmissionInterruptFlag == 0xFF)
        {  
          ESAT_COMTransceiverDriverClass::transmissionInterruptFlag = 0;          
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
    case ESAT_COMTransceiverDriverClass::RXMode:
    {
      if (receptionAvailable == true) // If reception was available but still not read, return 1
      {
        return 1; 
      }
      else // If received data was read and reception reenabled.
      {
        if (transceiver -> checkInterruptPin() == 0)
        {
          return checkReceptionAvailability(); // Retrieve received packet and set available flag.     
        }
        return 0; 
      }
    }
    case ESAT_COMTransceiverDriverClass::RXInterruptsMode:
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
        if (ESAT_COMTransceiverDriverClass::receptionInterruptFlag) 
        { 
          DEBUG_PRINTLN("Pending available interrupt");
          ESAT_COMTransceiverDriverClass::receptionInterruptFlag = 0;
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
  switch (transceiverOperationMode)
  {
    case ESAT_COMTransceiverDriverClass::TXMode:
    {
      ESAT_COMTransmissionLED.begin();
      transmissionConfigurationData = switchTransmissionConfigurationFile(transceiverModulationType);
      if(initializeTransceiver(transmissionConfigurationData) == false)
      {
        return ESAT_COMTransceiverDriverClass::notInitializedError;
      }
      setFrequency(transmissionFrequency);
      setTransmissionPower(transmissionPowerRate);
      break;
    }
    case ESAT_COMTransceiverDriverClass::TXInterruptsMode:
    {
      ESAT_COMTransmissionLED.begin();
      //DEBUG_PRINTLN("Initializing TX interrupts");
      transmissionConfigurationData = switchTransmissionConfigurationFile(transceiverModulationType);
      if(initializeTransceiver(transmissionConfigurationData) == false)
      {        
        return ESAT_COMTransceiverDriverClass::notInitializedError;
      }
      //Clear flag
      ESAT_COMTransceiverDriverClass::transmissionInterruptFlag = 0;
      //Enable interrupts. If ISR is fired during init and is not cleared interrupts may not be retriggered
      attachInterrupt(digitalPinToInterrupt(transceiver -> getInterruptPin()), setTransmissionTransceiverInterruptFlag,  FALLING);  
      setFrequency(transmissionFrequency);
      setTransmissionPower(transmissionPowerRate);
      break;
    }
    case ESAT_COMTransceiverDriverClass::RXMode:
    {
      ESAT_COMReceptionLED.begin();
      receptionConfigurationData = switchReceptionConfigurationFile(transceiverModulationType);
      if(initializeTransceiver(receptionConfigurationData) == false)
      {
        return ESAT_COMTransceiverDriverClass::notInitializedError;
      }
      setFrequency(receptionFrequency);
      startReception();
      break;
    }
    case ESAT_COMTransceiverDriverClass::RXInterruptsMode:
    {
      ESAT_COMReceptionLED.begin();      
      receptionConfigurationData = switchReceptionConfigurationFile(transceiverModulationType);
      if(initializeTransceiver(receptionConfigurationData) == false)
      {
        return ESAT_COMTransceiverDriverClass::notInitializedError;
      }        
      //Clear flag
      ESAT_COMTransceiverDriverClass::receptionInterruptFlag = 0;
      //Enable interrupts. If ISR is fired during init and is not cleared interrupts may not be retriggered
      attachInterrupt(digitalPinToInterrupt(transceiver -> getInterruptPin()), setReceptionTransceiverInterruptFlag,  FALLING);
      //Starts reception
      setFrequency(receptionFrequency);
      startReception(); 
      break;
    }
    default:
    {
      return ESAT_COMTransceiverDriverClass::wrongModeError;
    }  
  }  
  return ESAT_COMTransceiverDriverClass::noError;
}

void ESAT_COMTransceiverDriverClass::changeState(uint8_t nextState)
{
  uint8_t cmdBuff[2];
  cmdBuff[0] = COMMAND_CHANGE_STATE;
  cmdBuff[1] = nextState;
  transceiver -> writeCommand(COMMAND_CHANGE_STATE_ARGUMENTS_COUNT, cmdBuff);
}

int8_t ESAT_COMTransceiverDriverClass::checkReceptionAvailability()
{
  ESAT_COMTransceiverDriverClass::InterruptStatusReply intStatusReply = getInterruptStatus(0, 0, 0);
  if (intStatusReply.packetHandlerPending & INTERRUPT_STATUS_REPLY_PACKET_HANDLER_PENDING_PACKET_RECEIVED_BITMASK) // If packet has ended.
  {
    DEBUG_PRINTLN("Packet RX pending");
    // Retrieve from fifo
    receptionAvailable = true;
    ESAT_COMReceptionLED.write(100.0);
    transceiver -> readData(COMMAND_READ_RECEPTION_FIFO, 0, RADIO_MAX_PACKET_LENGTH, receptionBuffer);
    ESAT_COMReceptionLED.write(0.0);
    // Reception must be reenabled (ideally after reading).
    return 1;
  }
  return 0;
  
}

int8_t ESAT_COMTransceiverDriverClass::checkTransmissionAvailability()
{
  ESAT_COMTransceiverDriverClass::InterruptStatusReply intStatusReply =  getInterruptStatus(0, 0, 0);
  if (intStatusReply.packetHandlerPending & INTERRUPT_STATUS_REPLY_PACKET_HANDLER_PENDING_PACKET_SENT_BITMASK)
  {
    transmissionInProgress = false;
    return 1;
  }
  return 0;
}

uint8_t ESAT_COMTransceiverDriverClass::configureClockGenerator(const float frequency)
{
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
    return ESAT_COMTransceiverDriverClass::wrongFrequencyError;
  }  

   // Set the MODEM_CLKGEN_BAND (not documented)
   uint8_t modem_clkgen[] = {COMMAND_SET_PROPERTY, PROPERTY_MODEM, 1, PARAMETER_MODEM_CLOCK_GENERATOR_BAND, (uint8_t)(band | PARAMETER_MODEM_CLOCK_GENERATOR_BAND_HIGH_PERFORMANCE_MASK)};
   transceiver -> writeCommand(sizeof(modem_clkgen), modem_clkgen);
   return outdiv;
}

ESAT_COMTransceiverDriverClass::GPIOConfigurationReply ESAT_COMTransceiverDriverClass::configureGPIO(uint8_t GPIO0, uint8_t GPIO1, uint8_t GPIO2, uint8_t GPIO3, uint8_t NIRQ, uint8_t SDO, uint8_t driveStrength)
{
  uint8_t cmdBuff[8];
  ESAT_COMTransceiverDriverClass::GPIOConfigurationReply GPIOConfigurationReply;  
  cmdBuff[0] = COMMAND_CONFIGURE_GPIO;
  cmdBuff[1] = GPIO0;
  cmdBuff[2] = GPIO1;
  cmdBuff[3] = GPIO2;
  cmdBuff[4] = GPIO3;
  cmdBuff[5] = NIRQ;
  cmdBuff[6] = SDO;
  cmdBuff[7] = driveStrength;
  transceiver -> writeCommandAndRetrieveResponse(COMMAND_CONFIGURE_GPIO_ARGUMENTS_COUNT,
                                  cmdBuff,
                                  COMMAND_CONFIGURE_GPIO_REPLY_COUNT,
                                  cmdBuff);
  GPIOConfigurationReply.GPIO[0]        = cmdBuff[0];
  GPIOConfigurationReply.GPIO[1]        = cmdBuff[1];
  GPIOConfigurationReply.GPIO[2]        = cmdBuff[2];
  GPIOConfigurationReply.GPIO[3]        = cmdBuff[3];
  GPIOConfigurationReply.NIRQ           = cmdBuff[4];
  GPIOConfigurationReply.SDO            = cmdBuff[5];
  GPIOConfigurationReply.generalConfiguration   = cmdBuff[6];  
  return GPIOConfigurationReply;
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::configureModulationSource(ESAT_COMTransceiverDriverClass::ModulationSource modulationSource)
{  
  uint8_t modulationSourceMask = 0;  
  uint8_t modulationTypeMask = 0;    
  //4 level modulations aren't supported if GPIO is used as modulation source
  if ((modulationSource!=ESAT_COMTransceiverDriverClass::fifo && modulationSource!=ESAT_COMTransceiverDriverClass::randomGenerator) && (transceiverModulationType==ESAT_COMTransceiverDriverClass::fourFSK || transceiverModulationType==ESAT_COMTransceiverDriverClass::fourGaussianFSK)) 
  {
    return ESAT_COMTransceiverDriverClass::wrongModeError;
  }  
  // Also 2-GFSK modulation isn't supported in asynchronous mode
  if ((modulationSource == ESAT_COMTransceiverDriverClass::gpio0_asynchronous || modulationSource == ESAT_COMTransceiverDriverClass::gpio1_asynchronous) && transceiverModulationType==ESAT_COMTransceiverDriverClass::twoGaussianFSK)
  {
    return ESAT_COMTransceiverDriverClass::wrongModeError;
  }  
  //Selects modulation source
  modulationSourceMask = switchModulationSource(modulationSource);
  if (modulationSourceMask == 0xFF) //If function returns 0xFF means that the selected source isn't available
  {
    return ESAT_COMTransceiverDriverClass::wrongModeError;
  }
  //Selects the modulation type bytes but DOESN'T CHANGE THE MODULATION HERE, NEEDS A RECONFIGURATION
  modulationTypeMask = switchModulationType(transceiverModulationType); //uses stored modulation
  if (modulationTypeMask == 0xFF) //If function returns 0xFF means that the selected modulation isn't available
  {
    return ESAT_COMTransceiverDriverClass::wrongModeError;
  }  
  uint8_t txBuffer[] = {COMMAND_SET_PROPERTY, PROPERTY_MODEM, 1, PARAMETER_MODEM_MODULATION_TYPE, (uint8_t)(modulationSourceMask | modulationTypeMask)};  
  transceiver -> writeCommand(sizeof(txBuffer), txBuffer);
  return ESAT_COMTransceiverDriverClass::noError; //We assume that the writing is done rigth because the function doesn't provide CTS feedback
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::configureModulationType(ESAT_COMTransceiverDriverClass::ModulationType modulationType)
{
  // Store new modulation type.
  transceiverModulationType = modulationType;
  return begin(transceiverOperationMode, transceiverModulationType);
}

void ESAT_COMTransceiverDriverClass::disable(void)
{
  setPollingMode(); //Ensure ISRs are detached.
  transceiverOperationMode = notInitializedMode;
  transceiver -> disable();
} 

ESAT_COMTransceiverDriverClass::ADCReadingsReply ESAT_COMTransceiverDriverClass::getADCReading(uint8_t analogChannels)
{
  uint8_t cmdBuff[8];
  ESAT_COMTransceiverDriverClass::ADCReadingsReply ADCReadingsReply;  
  cmdBuff[0] = COMMAND_ADC_READ;
  cmdBuff[1] = analogChannels;
  transceiver -> writeCommandAndRetrieveResponse(COMMAND_ADC_READ_ARGUMENTS_COUNT,
                                  cmdBuff,
                                  COMMAND_ADC_READ_REPLY_COUNT,
                                  cmdBuff);
  ADCReadingsReply.GPIOAnalogRawValue   = ((uint16_t)cmdBuff[0] << 8) & 0xFF00;
  ADCReadingsReply.GPIOAnalogRawValue  |= (uint16_t)cmdBuff[1] & 0x00FF;
  ADCReadingsReply.voltageRawValue      = ((uint16_t)cmdBuff[2] << 8) & 0xFF00;
  ADCReadingsReply.voltageRawValue     |= (uint16_t)cmdBuff[3] & 0x00FF;
  ADCReadingsReply.temperatureRawValue  = ((uint16_t)cmdBuff[4] << 8) & 0xFF00;
  ADCReadingsReply.temperatureRawValue |= (uint16_t)cmdBuff[5] & 0x00FF;
  return ADCReadingsReply;
}

uint8_t ESAT_COMTransceiverDriverClass::getChannel()
{
  return transceiverRadioChannel;
}

ESAT_COMTransceiverDriverClass::ChipStatusReply ESAT_COMTransceiverDriverClass::getChipStatus(uint8_t clearPendingFlagsMask)
{
  uint8_t cmdBuff[4];
  ESAT_COMTransceiverDriverClass::ChipStatusReply chipStatusReply;  
  cmdBuff[0] = COMMAND_GET_CHIP_STATUS;
  cmdBuff[1] = clearPendingFlagsMask;
  transceiver -> writeCommandAndRetrieveResponse(COMMAND_GET_CHIP_STATUS_ARGUMENTS_COUNT,
                                  cmdBuff,
                                  COMMAND_GET_CHIP_STATUS_REPLY_COUNT,
                                  cmdBuff);
  chipStatusReply.chipPending             = cmdBuff[0];
  chipStatusReply.chipStatus              = cmdBuff[1];
  chipStatusReply.lastCommandErrorStatus  = cmdBuff[2];  
  chipStatusReply.lastCommandErrorCommand = cmdBuff[3];
  return chipStatusReply;
}

ESAT_COMTransceiverDriverClass::FastResponseRegisterAReply ESAT_COMTransceiverDriverClass::getFastResponseRegisterA(uint8_t responseByteCount)
{
  uint8_t cmdBuff[4];
  ESAT_COMTransceiverDriverClass::FastResponseRegisterAReply fastResponseRegisterAReply;  
  transceiver -> readData(COMMAND_GET_FAST_RESPONSE_REGISTER_A,
            0,
            responseByteCount,
            cmdBuff);
  fastResponseRegisterAReply.fastResponseRegisterA = cmdBuff[0];
  fastResponseRegisterAReply.fastResponseRegisterB = cmdBuff[1];
  fastResponseRegisterAReply.fastResponseRegisterC = cmdBuff[2];
  fastResponseRegisterAReply.fastResponseRegisterD = cmdBuff[3];  
  return fastResponseRegisterAReply;
}

ESAT_COMTransceiverDriverClass::FastResponseRegisterBReply ESAT_COMTransceiverDriverClass::getFastResponseRegisterB(uint8_t responseByteCount)
{
  uint8_t cmdBuff[4];
  ESAT_COMTransceiverDriverClass::FastResponseRegisterBReply fastResponseRegisterBReply;  
  transceiver -> readData(COMMAND_GET_FAST_RESPONSE_REGISTER_B,
            0,
            responseByteCount,
            cmdBuff);
  fastResponseRegisterBReply.fastResponseRegisterB = cmdBuff[0];
  fastResponseRegisterBReply.fastResponseRegisterC = cmdBuff[1];
  fastResponseRegisterBReply.fastResponseRegisterD = cmdBuff[2];
  fastResponseRegisterBReply.fastResponseRegisterA = cmdBuff[3];  
  return fastResponseRegisterBReply;
}

ESAT_COMTransceiverDriverClass::FastResponseRegisterCReply ESAT_COMTransceiverDriverClass::getFastResponseRegisterC(uint8_t responseByteCount)
{
  uint8_t cmdBuff[4];
  ESAT_COMTransceiverDriverClass::FastResponseRegisterCReply fastResponseRegisterCReply;  
  transceiver -> readData(COMMAND_GET_FAST_RESPONSE_REGISTER_C,
            0,
            responseByteCount,
            cmdBuff);
  fastResponseRegisterCReply.fastResponseRegisterC = cmdBuff[0];
  fastResponseRegisterCReply.fastResponseRegisterD = cmdBuff[1];
  fastResponseRegisterCReply.fastResponseRegisterA = cmdBuff[2];
  fastResponseRegisterCReply.fastResponseRegisterB = cmdBuff[3];  
  return fastResponseRegisterCReply;
}

ESAT_COMTransceiverDriverClass::FastResponseRegisterDReply ESAT_COMTransceiverDriverClass::getFastResponseRegisterD(uint8_t responseByteCount)
{
  uint8_t cmdBuff[4];
  ESAT_COMTransceiverDriverClass::FastResponseRegisterDReply fastResponseRegisterDReply;  
  transceiver -> readData(COMMAND_GET_FAST_RESPONSE_REGISTER_D,
            0,
            responseByteCount,
            cmdBuff);
  fastResponseRegisterDReply.fastResponseRegisterD = cmdBuff[0];
  fastResponseRegisterDReply.fastResponseRegisterA = cmdBuff[1];
  fastResponseRegisterDReply.fastResponseRegisterB = cmdBuff[2];
  fastResponseRegisterDReply.fastResponseRegisterC = cmdBuff[3];  
  return fastResponseRegisterDReply;
}

ESAT_COMTransceiverDriverClass::FIFOStatusReply ESAT_COMTransceiverDriverClass::getFIFOStatus(uint8_t FIFOsResetFlags)
{
  uint8_t cmdBuff[2];
  ESAT_COMTransceiverDriverClass::FIFOStatusReply fifoStatusReply;  
  cmdBuff[0] = COMMAND_GET_FIFO_STATUS;
  cmdBuff[1] = FIFOsResetFlags;
  transceiver -> writeCommandAndRetrieveResponse(COMMAND_GET_FIFO_STATUS_ARGUMENTS_COUNT,
                                  cmdBuff,
                                  COMMAND_GET_FIFO_STATUS_REPLY_COUNT,
                                  cmdBuff);
  fifoStatusReply.receptionFIFOCount     = cmdBuff[0];
  fifoStatusReply.transmissionFIFOSpace  = cmdBuff[1];  
  return fifoStatusReply;
}

float ESAT_COMTransceiverDriverClass::getFrequency()
{
  switch (transceiverOperationMode)
  {
    case ESAT_COMTransceiverDriverClass::TXMode:
    case ESAT_COMTransceiverDriverClass::TXInterruptsMode:
    {
      return transmissionFrequency;
    }
    case ESAT_COMTransceiverDriverClass::RXMode:
    case ESAT_COMTransceiverDriverClass::RXInterruptsMode:
    {
      return receptionFrequency;
    }
    default:
    {
      return -1.0;
    }    
  }
}

ESAT_COMTransceiverDriverClass::InterruptStatusReply ESAT_COMTransceiverDriverClass::getInterruptStatus(uint8_t packetHandlerClearingPendingInterruptsMask, uint8_t modemClearingPendingInterruptsMask, uint8_t chipClearingPendingInterruptsMask)
{
  uint8_t cmdBuff[8];
  ESAT_COMTransceiverDriverClass::InterruptStatusReply interruptStatusReply;
  cmdBuff[0] = COMMAND_GET_INTERRUPTS_STATUS;
  cmdBuff[1] = packetHandlerClearingPendingInterruptsMask;
  cmdBuff[2] = modemClearingPendingInterruptsMask;
  cmdBuff[3] = chipClearingPendingInterruptsMask;    
  transceiver -> writeCommandAndRetrieveResponse(COMMAND_GET_INTERRUPTS_STATUS_ARGUMENTS_COUNT,
                                  cmdBuff,
                                  COMMAND_GET_INTERRUPTS_STATUS_REPLY_COUNT,
                                  cmdBuff);
  interruptStatusReply.interruptPending     = cmdBuff[0];
  interruptStatusReply.interruptStatus      = cmdBuff[1];
  interruptStatusReply.packetHandlerPending = cmdBuff[2];
  interruptStatusReply.packetHandlerStatus  = cmdBuff[3];
  interruptStatusReply.modemPending         = cmdBuff[4];
  interruptStatusReply.modemStatus          = cmdBuff[5];
  interruptStatusReply.chipPending          = cmdBuff[6];
  interruptStatusReply.chipStatus           = cmdBuff[7];  
  return interruptStatusReply;
}

ESAT_COMTransceiverDriverClass::ModemStatusReply ESAT_COMTransceiverDriverClass::getModemStatus(uint8_t clearPendingFlagsMask)
{
  uint8_t cmdBuff[8];
  ESAT_COMTransceiverDriverClass::ModemStatusReply modemStatusReply;  
  cmdBuff[0] = COMMAND_GET_MODEM_STATUS;
  cmdBuff[1] = clearPendingFlagsMask;
  transceiver -> writeCommandAndRetrieveResponse(COMMAND_GET_MODEM_STATUS_ARGUMENTS_COUNT,
                                  cmdBuff,
                                  COMMAND_GET_MODEM_STATUS_REPLY_COUNT,
                                  cmdBuff);
  modemStatusReply.modemPending                               = cmdBuff[0];
  modemStatusReply.modemStatus                                = cmdBuff[1];
  modemStatusReply.currentReceivedSignalStregnthIndicator     = cmdBuff[2];
  modemStatusReply.latchedReceivedSignalStrengthIndicator     = cmdBuff[3];
  modemStatusReply.antenna1ReceivedSignalStrengthIndicator    = cmdBuff[4];
  modemStatusReply.antenna2ReceivedSignalStrengthIndicator    = cmdBuff[5];  
  modemStatusReply.automaticFrequencyControlFrequencyOffset   = ((uint16_t)cmdBuff[6] << 8) & 0xFF00;
  modemStatusReply.automaticFrequencyControlFrequencyOffset  |= (uint16_t)cmdBuff[7] & 0x00FF;    
  return modemStatusReply;
}

uint8_t ESAT_COMTransceiverDriverClass::getModulation()
{
  switch(transceiverModulationType)    
  {
    case (ESAT_COMTransceiverDriverClass::OOK):
    {
      return 0;
    }
    case (ESAT_COMTransceiverDriverClass::twoFSK):
    {
      return 1;
    }
    case (ESAT_COMTransceiverDriverClass::twoGaussianFSK):
    {
      return 2;
    }
    case (ESAT_COMTransceiverDriverClass::fourFSK):
    {
      return 3;
    }
    case (ESAT_COMTransceiverDriverClass::fourGaussianFSK):
    {
      return 4;
    }
    case (ESAT_COMTransceiverDriverClass::continuousWave):
    {
      return 5;
    }    
    default:
    {
      return 255;
    }
  }
}

// Unused but desired
ESAT_COMTransceiverDriverClass::PacketHandlerStatusReply ESAT_COMTransceiverDriverClass::getPacketHandlerStatus(uint8_t clearPendingFlagsMask)
{
  uint8_t cmdBuff[2];
  ESAT_COMTransceiverDriverClass::PacketHandlerStatusReply packetHandlerStatusReply;  
  cmdBuff[0] = COMMAND_GET_PACKET_HANDLER_STATUS;
  cmdBuff[1] = clearPendingFlagsMask;
  transceiver -> writeCommandAndRetrieveResponse(COMMAND_GET_PACKET_HANDLER_STATUS_ARGUMENTS_COUNT,
                                  cmdBuff,
                                  COMMAND_GET_PACKET_HANDLER_STATUS_REPLY_COUNT,
                                  cmdBuff);
  packetHandlerStatusReply.packetHandlerPending      = cmdBuff[1];
  packetHandlerStatusReply.packetHandlerStatus       = cmdBuff[0];  
  return packetHandlerStatusReply;
}

// Unused but desired
ESAT_COMTransceiverDriverClass::PacketInfoReply ESAT_COMTransceiverDriverClass::getPacketInfo(uint8_t fieldNumberMask, uint16_t newLength, int16_t differenceLength)
{
  uint8_t cmdBuff[6];
  ESAT_COMTransceiverDriverClass::PacketInfoReply packetInfoReply;  
  cmdBuff[0] = COMMAND_GET_PACKET_INFO;
  cmdBuff[1] = fieldNumberMask;
  cmdBuff[2] = (uint8_t)(newLength >> 8);
  cmdBuff[3] = (uint8_t)(newLength);
  cmdBuff[4] = (uint8_t)((uint16_t)differenceLength >> 8);
  cmdBuff[5] = (uint8_t)(differenceLength);
  transceiver -> writeCommandAndRetrieveResponse(COMMAND_GET_PACKET_INFO_ARGUMENTS_COUNT,
                                  cmdBuff,
                                  COMMAND_GET_PACKET_INFO_REPLY_COUNT,
                                  cmdBuff);
  packetInfoReply.length   = ((uint16_t)cmdBuff[0] << 8) & 0xFF00;
  packetInfoReply.length  |= (uint16_t)cmdBuff[1] & 0x00FF;  
  return packetInfoReply;
}

// Unused but desired
ESAT_COMTransceiverDriverClass::PropertiesReply ESAT_COMTransceiverDriverClass::getProperty(uint8_t group, uint8_t numProperties, uint8_t startingProperty)
{
  uint8_t cmdBuff[16];
  ESAT_COMTransceiverDriverClass::PropertiesReply propertyReply;  
  cmdBuff[0] = COMMAND_GET_PROPERTY;
  cmdBuff[1] = group;
  cmdBuff[2] = numProperties;
  cmdBuff[3] = startingProperty;
  transceiver -> writeCommandAndRetrieveResponse(COMMAND_GET_PROPERTY_ARGUMENTS_COUNT,
                                  cmdBuff,
                                  numProperties,
                                  cmdBuff);
  propertyReply.buffer[0]    = cmdBuff[0];
  propertyReply.buffer[1]    = cmdBuff[1];
  propertyReply.buffer[2]    = cmdBuff[2];
  propertyReply.buffer[3]    = cmdBuff[3];
  propertyReply.buffer[4]    = cmdBuff[4];
  propertyReply.buffer[5]    = cmdBuff[5];
  propertyReply.buffer[6]    = cmdBuff[6];
  propertyReply.buffer[7]    = cmdBuff[7];
  propertyReply.buffer[8]    = cmdBuff[8];
  propertyReply.buffer[9]    = cmdBuff[9];
  propertyReply.buffer[10]   = cmdBuff[10];
  propertyReply.buffer[11]   = cmdBuff[11];
  propertyReply.buffer[12]   = cmdBuff[12];
  propertyReply.buffer[13]   = cmdBuff[13];
  propertyReply.buffer[14]   = cmdBuff[14];
  propertyReply.buffer[15]   = cmdBuff[15];  
  return propertyReply;
}

uint8_t ESAT_COMTransceiverDriverClass::getReceivedSignalStrengthIndicator()
{
  if ((transceiverOperationMode!=ESAT_COMTransceiverDriverClass::RXMode) && (transceiverOperationMode!=ESAT_COMTransceiverDriverClass::RXInterruptsMode))
  {
    return 0;
  } 
  
  ESAT_COMTransceiverDriverClass::ModemStatusReply reply = getModemStatus(0xFF);
  return reply.currentReceivedSignalStregnthIndicator;
}

uint16_t ESAT_COMTransceiverDriverClass::getTransceiverTemperature()
{
  // If transceiver is disabled return 0 (better returning error but not yet)
  if ((transceiverOperationMode!=ESAT_COMTransceiverDriverClass::RXMode) && (transceiverOperationMode!=ESAT_COMTransceiverDriverClass::RXInterruptsMode) && (transceiverOperationMode!=ESAT_COMTransceiverDriverClass::TXMode) && (transceiverOperationMode!=ESAT_COMTransceiverDriverClass::TXInterruptsMode))
  {
    return 0;
  } 
  ESAT_COMTransceiverDriverClass::ADCReadingsReply reply = getADCReading(ADC_READ_ARGUMENT_READ_TEMPERATURE_BITMASK);
  return reply.temperatureRawValue; //MAY need to clear upper nibble bc is 11 bit adc.
}

uint16_t ESAT_COMTransceiverDriverClass::getTransceiverVoltage()
{
  // If transceiver is disabled return 0 (better returning error but not yet)
  if ((transceiverOperationMode!=ESAT_COMTransceiverDriverClass::RXMode) && (transceiverOperationMode!=ESAT_COMTransceiverDriverClass::RXInterruptsMode) && (transceiverOperationMode!=ESAT_COMTransceiverDriverClass::TXMode) && (transceiverOperationMode!=ESAT_COMTransceiverDriverClass::TXInterruptsMode))
  {
    return 0;
  } 
   ESAT_COMTransceiverDriverClass::ADCReadingsReply reply =  getADCReading(ADC_READ_ARGUMENT_READ_VOLTAGE_BITMASK);
  return reply.voltageRawValue; //MAY need to clear upper nibble bc is 11 bit adc.
}

float ESAT_COMTransceiverDriverClass::getTransmissionPowerRate()
{
  switch (transceiverOperationMode)
  {
    case ESAT_COMTransceiverDriverClass::TXMode:
    case ESAT_COMTransceiverDriverClass::TXInterruptsMode:
    {
      return transmissionPowerRate;
    }
    case ESAT_COMTransceiverDriverClass::RXMode:
    case ESAT_COMTransceiverDriverClass::RXInterruptsMode:
    default:
    {
      // If transceiver is disabled return 0 (better returning error but not yet)
      return 0.0;
    }    
  }
} 

 boolean ESAT_COMTransceiverDriverClass::initializeTransceiver(const uint8_t* configurationData)
 {
  transceiver -> reset();  
  // Load path (if defined).
  while(ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS != applyPatch())
  {
    // If fails (radio driver does this but has litte sense).
    delay(10);
    transceiver -> reset();
  }
  // Load configuration generated by WDS.
  while (ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS != initializeConfigurations(configurationData))
  {
    delay(10);
    transceiver -> reset();
  }
  // Read interrupts and clear pending ones.
  ESAT_COMTransceiverDriverClass::InterruptStatusReply intStatusReply = getInterruptStatus(0, 0, 0);
  //Check if chip is ready to accept commands.
  if ((intStatusReply.chipStatus & INTERRUPT_STATUS_REPLY_CHIP_STATUS_CHIP_READY_BITMASK)&& !(intStatusReply.chipPending & INTERRUPT_STATUS_REPLY_CHIP_PENDING_CHIP_READY_BITMASK)) 
  {
    return true;
  }
  return false;
}

uint8_t ESAT_COMTransceiverDriverClass::initializeConfigurations(const uint8_t* initialConfigurationsList)
{
  uint8_t column = 0;
  uint8_t numOfBytes = 0;
  uint8_t cmdBuff[16];
  // While the pointer points to a command (last values are 0x00).
  while (*initialConfigurationsList != 0x00)
  {
    numOfBytes = *initialConfigurationsList++;

    if (numOfBytes > 16)
    {
      // Command bytes count is greater than maximun (16).
      return ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_COMMAND_ERROR;
    }

    for (column = 0; column < numOfBytes; column++)
    {
      cmdBuff[column] = *initialConfigurationsList;
      initialConfigurationsList++;
    }

    if (transceiver -> writeCommandAndRetrieveResponse(numOfBytes, cmdBuff, 0, 0) != 0xFF)
    {
      // Timeout.
      return ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_CTS_TIMEOUT;
    }

    if (transceiver -> checkInterruptPin() == 0)
    {
      // An error has occured. Clear interrupts.
      ESAT_COMTransceiverDriverClass::InterruptStatusReply interruptStatusReply = getInterruptStatus(0, 0, 0);
      if (interruptStatusReply.chipPending & INTERRUPT_STATUS_REPLY_CHIP_PENDING_COMMAND_ERROR_BITMASK)
      {
        return ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_COMMAND_ERROR;
      }
    }
  }
  return ESAT_COMTransceiverInterfaceClass::TRANSCEIVER_SUCCESS;
}

uint8_t* ESAT_COMTransceiverDriverClass::nonBlockingRead(void)
{
    receptionAvailable = false;
    startReception();
    return receptionBuffer;  
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::nonBlockingWrite(uint8_t* msgBuf)
{
  if ((transceiverOperationMode!=ESAT_COMTransceiverDriverClass::TXMode) && (transceiverOperationMode!=ESAT_COMTransceiverDriverClass::TXInterruptsMode))
  {
    return ESAT_COMTransceiverDriverClass::wrongModeError;
  }    
  // Reset FIFO
  getFIFOStatus(FIFO_STATUS_ARGUMENT_TRANSMISSION_FIFO_BITMASK | FIFO_STATUS_ARGUMENT_RECEPTION_FIFO_BITMASK);
  // Read interrupts and clear pending ones.
  getInterruptStatus(0, 0, 0);
  // Load 129 bytes into fifo.
  ESAT_COMTransmissionLED.write(100.0);
  transceiver -> writeData(COMMAND_WRITE_TRANSMISSION_FIFO, 0, RADIO_MAX_PACKET_LENGTH, msgBuf);
  ESAT_COMTransmissionLED.write(0.0);
  // Start transmission
  startTransmission(transceiverRadioChannel, 0x30, RADIO_MAX_PACKET_LENGTH); 
  transmissionInProgress = true;  
  return ESAT_COMTransceiverDriverClass::noError;
}

void ESAT_COMTransceiverDriverClass::nop()
{
  uint8_t cmdBuff[2];   
  cmdBuff[1] = COMMAND_NOP;  
  transceiver -> writeCommand(COMMAND_NOP_ARGUMENTS_COUNT, cmdBuff);
}

ESAT_COMTransceiverDriverClass::PartInfoReply ESAT_COMTransceiverDriverClass::partInfo()
{
    uint8_t cmdBuff[8];
    ESAT_COMTransceiverDriverClass::PartInfoReply partInfoReply;  
    cmdBuff[0] = COMMAND_PART_INFO;
    transceiver -> writeCommandAndRetrieveResponse(COMMAND_PART_INFO_ARGUMENTS_COUNT,
                                    cmdBuff,
                                    COMMAND_PART_INFO_REPLY_COUNT,
                                    cmdBuff);
    partInfoReply.chipRevision  = cmdBuff[0];
    partInfoReply.partNumber    = ((uint16_t)cmdBuff[1] << 8) & 0xFF00;
    partInfoReply.partNumber   |= (uint16_t)cmdBuff[2] & 0x00FF;
    partInfoReply.partBuild     = cmdBuff[3];
    partInfoReply.ID            = ((uint16_t)cmdBuff[4] << 8) & 0xFF00;
    partInfoReply.ID           |= (uint16_t)cmdBuff[5] & 0x00FF;
    partInfoReply.customerID    = cmdBuff[6];
    partInfoReply.ROMID         = cmdBuff[7];  
  return partInfoReply;
}

void ESAT_COMTransceiverDriverClass::powerUp(uint8_t bootOptions, uint8_t crystalOptions, uint32_t crystalFrequency)
{
    uint8_t cmdBuff[COMMAND_POWER_UP_ARGUMENTS_COUNT];
    cmdBuff[0] = COMMAND_POWER_UP;
    cmdBuff[1] = bootOptions;
    cmdBuff[2] = crystalOptions;
    cmdBuff[3] = (uint8_t)(crystalFrequency >> 24);
    cmdBuff[4] = (uint8_t)(crystalFrequency >> 16);
    cmdBuff[5] = (uint8_t)(crystalFrequency >> 8);
    cmdBuff[6] = (uint8_t)(crystalFrequency);
    transceiver -> writeCommand( COMMAND_POWER_UP_ARGUMENTS_COUNT, cmdBuff);
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
    /* Read ITs, clear pending ones */
    ESAT_COMTransceiverDriverClass::receptionInterruptFlag = 0xFF;  
}

void ESAT_COMTransceiverDriverClass::setChannel(uint8_t channel)
{
  transceiverRadioChannel=channel;
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::setInterruptsMode(void)
{
  switch (transceiverOperationMode)
  {
    case ESAT_COMTransceiverDriverClass::RXInterruptsMode:
    case ESAT_COMTransceiverDriverClass::TXInterruptsMode:
    {
      //Already in interrupts mode
      return ESAT_COMTransceiverDriverClass::noError;
    }    
    case ESAT_COMTransceiverDriverClass::TXMode:
    {
      //Change behavioural to interrupts mode
      transceiverOperationMode=ESAT_COMTransceiverDriverClass::TXInterruptsMode;
      //Clear flag
      ESAT_COMTransceiverDriverClass::transmissionInterruptFlag = 0;
      //digitalWrite(79, LOW);
      //Enable interrupts
      attachInterrupt(digitalPinToInterrupt(transceiver -> getInterruptPin()), setTransmissionTransceiverInterruptFlag,  FALLING);
      return ESAT_COMTransceiverDriverClass::noError;
    }
    case ESAT_COMTransceiverDriverClass::RXMode:
    {
      //Change behavioural to interrupts mode
      transceiverOperationMode=ESAT_COMTransceiverDriverClass::RXInterruptsMode;
      //Clear flag
      ESAT_COMTransceiverDriverClass::receptionInterruptFlag = 0;
      //Enable interrupts
      attachInterrupt(digitalPinToInterrupt(transceiver -> getInterruptPin()), setReceptionTransceiverInterruptFlag,  FALLING);
      return ESAT_COMTransceiverDriverClass::noError;
    }
    default:
    {
      return ESAT_COMTransceiverDriverClass::wrongModeError;
    }  
  }
}
 
ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::setFrequency(float frequency)
{
  // Store set frequency.
  switch (transceiverOperationMode)
  {
    case ESAT_COMTransceiverDriverClass::TXMode:
    case ESAT_COMTransceiverDriverClass::TXInterruptsMode:
    {
      transmissionFrequency = frequency;
      break;
    }
    case ESAT_COMTransceiverDriverClass::RXMode:
    case ESAT_COMTransceiverDriverClass::RXInterruptsMode:
    {
      receptionFrequency = frequency;
      break;
    }
    default:
    {
      return ESAT_COMTransceiverDriverClass::wrongModeError;
    }    
  }  
  const uint8_t outdiv = configureClockGenerator(frequency);  
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
  // Fill command.
  uint8_t freq_control[] = {COMMAND_SET_PROPERTY, PROPERTY_FREQUENCY_CONTROL, 4, PARAMETER_FREQUENCY_CONTROL_INTEGER, (uint8_t)pll_integer, (uint8_t)pll_fractional_msb, (uint8_t)pll_fractional_middle, (uint8_t)pll_fractional_lsb };
  transceiver -> writeCommand(sizeof(freq_control), freq_control);  
  return ESAT_COMTransceiverDriverClass::noError; 
}
 
ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::setPollingMode(void)
{
  switch (transceiverOperationMode)
  {
    case ESAT_COMTransceiverDriverClass::RXMode:
    case ESAT_COMTransceiverDriverClass::TXMode:
    {
      //Already in polling
      return ESAT_COMTransceiverDriverClass::noError;
    }    
    case ESAT_COMTransceiverDriverClass::TXInterruptsMode:
    {
      //Enable interrupts
      detachInterrupt(digitalPinToInterrupt(transceiver -> getInterruptPin()));
      //Clear flag
      ESAT_COMTransceiverDriverClass::transmissionInterruptFlag = 0;
      //digitalWrite(79, LOW);
      //Change behavioural to polling mode
      transceiverOperationMode=ESAT_COMTransceiverDriverClass::TXMode;
      return ESAT_COMTransceiverDriverClass::noError;
    }
    case ESAT_COMTransceiverDriverClass::RXInterruptsMode:
    {
      //Enable interrupts
      detachInterrupt(digitalPinToInterrupt(transceiver -> getInterruptPin()));
      //Clear flags
      ESAT_COMTransceiverDriverClass::receptionInterruptFlag = 0;
      //Change behavioural to interrupts mode
      transceiverOperationMode=ESAT_COMTransceiverDriverClass::RXMode;
      return ESAT_COMTransceiverDriverClass::noError;
    }
    default:
    {
      return ESAT_COMTransceiverDriverClass::wrongModeError;
    }  
  }
}

void ESAT_COMTransceiverDriverClass::setProperty(uint8_t group, uint8_t numProperties, uint8_t startingProperty, uint8_t* properties)
{
  uint8_t cmdIndex;
  uint8_t cmdBuff[16];
  cmdBuff[0] = COMMAND_SET_PROPERTY;
  cmdBuff[1] = group;
  cmdBuff[2] = numProperties;
  cmdBuff[3] = startingProperty;  
  for (cmdIndex = 0; cmdIndex < 12 && numProperties > 0; ++cmdIndex, --numProperties)
  {
    cmdBuff[cmdIndex + 4] = properties[cmdIndex];
  }
  transceiver -> writeCommand(cmdIndex + 4, cmdBuff);
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::setTransmissionPower(float transmissionPowerRateToBeSet)
{
  //Power can't be changed in non-TX mode (or disabled)
  if ((transceiverOperationMode!=ESAT_COMTransceiverDriverClass::TXMode) && (transceiverOperationMode!=ESAT_COMTransceiverDriverClass::TXInterruptsMode))
  {
    return ESAT_COMTransceiverDriverClass::wrongPowerError;
  }
  if (transmissionPowerRateToBeSet<MINIMUM_TRANSMISSION_POWER_RATE)
  {
    transmissionPowerRateToBeSet=MINIMUM_TRANSMISSION_POWER_RATE;
  }
  if (transmissionPowerRateToBeSet>MAXIMUM_TRANSMISSION_POWER_RATE)
  {
    transmissionPowerRateToBeSet=MAXIMUM_TRANSMISSION_POWER_RATE;
  }
  // Store set power.
  transmissionPowerRate = transmissionPowerRateToBeSet;
  const float mappedPowerValue = (transmissionPowerRateToBeSet / MAXIMUM_TRANSMISSION_POWER_RATE) * MAXIMUM_POWER_VALUE; 
  uint8_t txBuffer[]={COMMAND_SET_PROPERTY, PROPERTY_POWER_AMPLIFIER, 2, PARAMETER_POWER_AMPLIFIER_POWER_LEVEL, (uint8_t) mappedPowerValue, 0x00}; 
  transceiver -> writeCommand(sizeof(txBuffer), txBuffer);
  return ESAT_COMTransceiverDriverClass::noError;
}
 
ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::startReception (void)
{
  if ((transceiverOperationMode!=ESAT_COMTransceiverDriverClass::RXMode) && (transceiverOperationMode!=ESAT_COMTransceiverDriverClass::RXInterruptsMode))
  {
    return ESAT_COMTransceiverDriverClass::wrongModeError;
  }
  receptionAvailable = false;
  //Read and clear interrupts.  
  getInterruptStatus(0, 0, 0);
  // Reset FIFO.
  getFIFOStatus(FIFO_STATUS_ARGUMENT_TRANSMISSION_FIFO_BITMASK | FIFO_STATUS_ARGUMENT_RECEPTION_FIFO_BITMASK);  
  // Start reception
  startReception(transceiverRadioChannel, 0, 0x00,
      START_RECEPTION_ARGUMENT_NEXT_STATE_1_RECEPTION_TIMEOUT_STATE_NO_CHANGE,
      START_RECEPTION_ARGUMENT_NEXT_STATE_2_RECEPTION_VALID_STATE_READY,
      START_RECEPTION_ARGUMENT_NEXT_STATE_3_RECEPTION_INVALID_STATE_RECEPTION);
  return ESAT_COMTransceiverDriverClass::noError;
}

void ESAT_COMTransceiverDriverClass::startReception(uint8_t channel, uint8_t condition, uint16_t receptionLength, uint8_t nextState1, uint8_t nextState2, uint8_t nextState3)
{
  uint8_t cmdBuff[8];  
  cmdBuff[0] = COMMAND_START_RECEPTION;
  cmdBuff[1] = channel;
  cmdBuff[2] = condition;
  cmdBuff[3] = (uint8_t)(receptionLength >> 8);
  cmdBuff[4] = (uint8_t)(receptionLength);
  cmdBuff[5] = nextState1;
  cmdBuff[6] = nextState2;
  cmdBuff[7] = nextState3;
  transceiver -> writeCommand(COMMAND_START_RECEPTION_ARGUMENTS_COUNT, cmdBuff);
}

void ESAT_COMTransceiverDriverClass::startTransmission(uint8_t channel, uint8_t condition, uint16_t transmissionLength)
{
  uint8_t cmdBuff[7];
  cmdBuff[0] = COMMAND_START_TRANSMISSION;
  cmdBuff[1] = channel;
  cmdBuff[2] = condition;
  cmdBuff[3] = (uint8_t)(transmissionLength >> 8);
  cmdBuff[4] = (uint8_t)(transmissionLength);
  cmdBuff[5] = 0x00;  
  // Don't repeat the packet, 
  // ie. transmit the packet only once.
  cmdBuff[6] = 0x00;
  transceiver -> writeCommand(COMMAND_START_TRANSMISSION_ARGUMENTS_COUNT, cmdBuff);
}

uint8_t* ESAT_COMTransceiverDriverClass::switchReceptionConfigurationFile(ESAT_COMTransceiverDriverClass::ModulationType modulationType)
{
  switch(modulationType)    
  {

    case (ESAT_COMTransceiverDriverClass::twoFSK):
    {
      return (uint8_t*) RECEPTION_2FSK_CONFIGURATION_ARRAY;
    }
    case (ESAT_COMTransceiverDriverClass::twoGaussianFSK):
    {
      return (uint8_t*) RECEPTION_2GFSK_CONFIGURATION_ARRAY;
    }
    case (ESAT_COMTransceiverDriverClass::fourFSK):
    {
      return (uint8_t*) RECEPTION_4FSK_CONFIGURATION_ARRAY;
    }
    case (ESAT_COMTransceiverDriverClass::fourGaussianFSK):
    {
      return (uint8_t*) RECEPTION_4GFSK_CONFIGURATION_ARRAY;
    }
    case (ESAT_COMTransceiverDriverClass::continuousWave):
    case (ESAT_COMTransceiverDriverClass::OOK):
    default:
    {
      return (uint8_t*) RECEPTION_OOK_CONFIGURATION_ARRAY;
    }
  }  
}

uint8_t* ESAT_COMTransceiverDriverClass::switchTransmissionConfigurationFile(ESAT_COMTransceiverDriverClass::ModulationType modulationType)
{
  switch(modulationType)    
  {

    case (ESAT_COMTransceiverDriverClass::twoFSK):
    {
      return (uint8_t*) TRANSMISSION_2FSK_CONFIGURATION_ARRAY;
    }
    case (ESAT_COMTransceiverDriverClass::twoGaussianFSK):
    {
      return (uint8_t*) TRANSMISSION_2GFSK_CONFIGURATION_ARRAY;
    }
    case (ESAT_COMTransceiverDriverClass::fourFSK):
    {
      return (uint8_t*) TRANSMISSION_4FSK_CONFIGURATION_ARRAY;
    }
    case (ESAT_COMTransceiverDriverClass::fourGaussianFSK):
    {
      return (uint8_t*) TRANSMISSION_4GFSK_CONFIGURATION_ARRAY;
    }
    case (ESAT_COMTransceiverDriverClass::continuousWave):
    case (ESAT_COMTransceiverDriverClass::OOK):
    default:
    {
      return (uint8_t*) TRANSMISSION_OOK_CONFIGURATION_ARRAY;
    }
  }  
}

uint8_t  ESAT_COMTransceiverDriverClass::switchModulationSource(ESAT_COMTransceiverDriverClass::ModulationSource source)
{    
  switch(source)
  {
    case (ESAT_COMTransceiverDriverClass::fifo):
    {
      return PARAMETER_MODEM_MODULATION_TYPE_PACKET_HANDLER_MASK;
    }
    case (gpio0_synchronous):
    {
      return PARAMETER_MODEM_MODULATION_TYPE_GPIO0_SYNCHRONOUS_MASK;
    }
    case (gpio0_asynchronous):
    {
      return PARAMETER_MODEM_MODULATION_TYPE_GPIO0_ASYNCHRONOUS_MASK;
    }
    case (gpio1_synchronous):
    {
      return PARAMETER_MODEM_MODULATION_TYPE_GPIO1_SYNCHRONOUS_MASK;
    }
    case (gpio1_asynchronous):
    {
      return PARAMETER_MODEM_MODULATION_TYPE_GPIO1_ASYNCHRONOUS_MASK;
    }
    case (gpio2_synchronous):
    {
      return PARAMETER_MODEM_MODULATION_TYPE_GPIO2_SYNCHRONOUS_MASK;
    }
    case (gpio2_asynchronous):
    {
      return PARAMETER_MODEM_MODULATION_TYPE_GPIO2_ASYNCHRONOUS_MASK;
    }
    case (gpio3_synchronous):
    {
      return PARAMETER_MODEM_MODULATION_TYPE_GPIO3_SYNCHRONOUS_MASK;
    }
    case (gpio3_asynchronous):
    {
      return PARAMETER_MODEM_MODULATION_TYPE_GPIO3_ASYNCHRONOUS_MASK;
    }     
    case (ESAT_COMTransceiverDriverClass::randomGenerator):
    {
      return PARAMETER_MODEM_MODULATION_TYPE_RANDOM_GENERATOR_MASK;
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
    case (ESAT_COMTransceiverDriverClass::continuousWave):
    {
      return PARAMETER_MODEM_MODULATION_TYPE_CONTINUOUS_WAVE_MASK;
    }
    case (ESAT_COMTransceiverDriverClass::OOK):
    {
      return PARAMETER_MODEM_MODULATION_TYPE_OOK_MASK;
    }
    case (ESAT_COMTransceiverDriverClass::twoFSK):
    {
      return PARAMETER_MODEM_MODULATION_TYPE_2FSK_MASK;
    }
    case (ESAT_COMTransceiverDriverClass::twoGaussianFSK):
    {
      return PARAMETER_MODEM_MODULATION_TYPE_2GFSK_MASK;
    }
    case (ESAT_COMTransceiverDriverClass::fourFSK):
    {
      return PARAMETER_MODEM_MODULATION_TYPE_4FSK_MASK;
    }
    case (ESAT_COMTransceiverDriverClass::fourGaussianFSK):
    {
      return PARAMETER_MODEM_MODULATION_TYPE_4GFSK_MASK;
    }
    default:
    {
      return 0xFF; //WrongModeError
    }
  }  
}

void ESAT_COMTransceiverDriverClass::setTransmissionTransceiverInterruptFlag (void)
{
    /* Read ITs, clear pending ones */  
    ESAT_COMTransceiverDriverClass::transmissionInterruptFlag = 0xFF; 
}

ESAT_COMTransceiverDriverClass::TransceiverErrorCode ESAT_COMTransceiverDriverClass::write(uint8_t* msgBuf)
{
  if ((transceiverOperationMode != ESAT_COMTransceiverDriverClass::TXMode) && (transceiverOperationMode != ESAT_COMTransceiverDriverClass::TXInterruptsMode))
  {
    return ESAT_COMTransceiverDriverClass::wrongModeError;
  }
  nonBlockingWrite(msgBuf);
  while(!available())
  {    
  }    
  return ESAT_COMTransceiverDriverClass::noError;
}

volatile uint8_t ESAT_COMTransceiverDriverClass::receptionInterruptFlag;

ESAT_COMTransceiverDriverClass ReceptionTransceiver(ReceptionTransceiverLowLevelDriver);

volatile uint8_t ESAT_COMTransceiverDriverClass::transmissionInterruptFlag;

ESAT_COMTransceiverDriverClass TransmissionTransceiver(TransmissionTransceiverLowLevelDriver);
