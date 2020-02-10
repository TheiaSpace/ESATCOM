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
#ifndef ESAT_COM4FSKReceptionConfiguration_h
#define ESAT_COM4FSKReceptionConfiguration_h

#include <Arduino.h>
#include "ESAT_COMTransceiverConfiguration.h"
#include "../ESAT_COMTransceiverHAL.h"

class ESAT_COM4FSKReceptionConfigurationClass: public ESAT_COMTransceiverConfigurationClass
{
  public:
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError applyConfiguration(ESAT_COMTransceiverHALClass& transceiver);
    
  private:
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureGlobalProperties(ESAT_COMTransceiverHALClass& transceiver);
    
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureInterrupts(ESAT_COMTransceiverHALClass& transceiver);
    
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureFastResponseRegisterA(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureFastResponseRegisterB(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureFastResponseRegisterC(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureFastResponseRegisterD(ESAT_COMTransceiverHALClass& transceiver);
    
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePreamble(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePreambleLength(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePreamblePattern(ESAT_COMTransceiverHALClass& transceiver);
    
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureSyncWord(ESAT_COMTransceiverHALClass& transceiver);
    
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacket(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketCRC(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketWhitening(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketLength(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketFIFOThresholds(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketField1(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketField2(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketField3(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketField4(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketField5(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketReceptionField1(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketReceptionField2(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketReceptionField3(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketReceptionField4(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketReceptionField5(ESAT_COMTransceiverHALClass& transceiver);
    
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemModulationType(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemMappingControl(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemDSMControl(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemDataRate(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemTransmissionNCO(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemFrequencyDeviation(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemTransmissionRampDown(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemMDMControl(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemIFControl(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemDecimationControl(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemIFPKDThresholds(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemBCR(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemAFC(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemAGC(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemFSK4(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemOOK(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemRawEyeControl(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemAntennaDiversity(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemRSSI(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemRawSearch2(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemClockGeneratorBand(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemSpikeDetector(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemOneShotAFC(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemDSA(ESAT_COMTransceiverHALClass& transceiver);
    
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureReceptionFilter1Coefficients(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureReceptionFilter2Coefficients(ESAT_COMTransceiverHALClass& transceiver);
    
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePowerAmplifier(ESAT_COMTransceiverHALClass& transceiver);
    
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureSynthesizer(ESAT_COMTransceiverHALClass& transceiver);
    
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureMatch1(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureMatch2(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureMatch3(ESAT_COMTransceiverHALClass& transceiver);
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureMatch4(ESAT_COMTransceiverHALClass& transceiver);
    
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureFrequencyControl(ESAT_COMTransceiverHALClass& transceiver);    
};

extern ESAT_COM4FSKReceptionConfigurationClass ESAT_COM4FSKReceptionConfiguration;

#endif /*ESAT_COM4FSKReceptionConfiguration_h*/