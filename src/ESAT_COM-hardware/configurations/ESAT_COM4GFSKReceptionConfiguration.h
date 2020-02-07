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
#ifndef ESAT_COM4GFSKReceptionConfiguration_h
#define ESAT_COM4GFSKReceptionConfiguration_h

#include <Arduino.h>
#include "ESAT_COMTransceiverConfiguration.h"
#include "../ESAT_COMTransceiverInterface.h"

class ESAT_COM4GFSKReceptionConfigurationClass: public ESAT_COMTransceiverConfigurationClass
{
  public:
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError applyConfiguration(ESAT_COMTransceiverInterfaceClass& transceiver);
    
  private:
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureGlobalProperties(ESAT_COMTransceiverInterfaceClass& transceiver);
    
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureInterrupts(ESAT_COMTransceiverInterfaceClass& transceiver);
    
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureFastResponseRegisterA(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureFastResponseRegisterB(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureFastResponseRegisterC(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureFastResponseRegisterD(ESAT_COMTransceiverInterfaceClass& transceiver);
    
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePreamble(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePreambleLength(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePreamblePattern(ESAT_COMTransceiverInterfaceClass& transceiver);
    
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureSyncWord(ESAT_COMTransceiverInterfaceClass& transceiver);
    
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePacket(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePacketCRC(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePacketWhitening(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePacketLength(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePacketFIFOThresholds(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePacketField1(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePacketField2(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePacketField3(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePacketField4(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePacketField5(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePacketReceptionField1(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePacketReceptionField2(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePacketReceptionField3(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePacketReceptionField4(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePacketReceptionField5(ESAT_COMTransceiverInterfaceClass& transceiver);
    
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemModulationType(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemMappingControl(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemDSMControl(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemDataRate(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemTransmissionNCO(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemFrequencyDeviation(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemTransmissionRampDown(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemMDMControl(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemIFControl(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemDecimationControl(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemIFPKDThresholds(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemBCR(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemAFC(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemAGC(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemFSK4(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemOOK(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemRawEyeControl(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemAntennaDiversity(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemRSSI(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemRawSearch2(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemClockGeneratorBand(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemSpikeDetector(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemOneShotAFC(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureModemDSA(ESAT_COMTransceiverInterfaceClass& transceiver);
    
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureReceptionFilter1Coefficients(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureReceptionFilter2Coefficients(ESAT_COMTransceiverInterfaceClass& transceiver);
    
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configurePowerAmplifier(ESAT_COMTransceiverInterfaceClass& transceiver);
    
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureSynthesizer(ESAT_COMTransceiverInterfaceClass& transceiver);
    
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureMatch1(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureMatch2(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureMatch3(ESAT_COMTransceiverInterfaceClass& transceiver);
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureMatch4(ESAT_COMTransceiverInterfaceClass& transceiver);
    
    ESAT_COMTransceiverInterfaceClass::TransceiverLowLevelDriverError configureFrequencyControl(ESAT_COMTransceiverInterfaceClass& transceiver);    
};

extern ESAT_COM4GFSKReceptionConfigurationClass ESAT_COM4GFSKReceptionConfiguration;

#endif /*ESAT_COM4GFSKReceptionConfiguration_h*/