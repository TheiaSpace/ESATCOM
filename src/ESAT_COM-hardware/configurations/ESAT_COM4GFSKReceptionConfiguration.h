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
#ifndef ESAT_COM4GFSKReceptionConfiguration_h
#define ESAT_COM4GFSKReceptionConfiguration_h

#include <Arduino.h>
#include "ESAT_COMTransceiverConfiguration.h"
#include "../ESAT_COMTransceiverHAL.h"

// Implementation of the ESAT_COMTransceiverConfigurationClass class for
// the reception transceiver in 4GFSK mode.
class ESAT_COM4GFSKReceptionConfigurationClass: public ESAT_COMTransceiverConfigurationClass
{
  public:
    // Implementation of the applyConfiguration function for the current
    // transceiver and modulation.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError applyConfiguration(ESAT_COMTransceiverHALClass& transceiver);

  private:
    // Function for configuring the global properties parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureGlobalProperties(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the interrupts.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureInterrupts(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the fast response register A.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureFastResponseRegisterA(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the fast response register B.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureFastResponseRegisterB(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the fast response register C.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureFastResponseRegisterC(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the fast response register D.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureFastResponseRegisterD(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the preamble parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePreamble(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the preamble length parmenters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePreambleLength(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the preamble pattern parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePreamblePattern(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the synchronization word parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureSyncWord(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the packet parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacket(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the packet CRC parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketCRC(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the packet whitening parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketWhitening(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the packet length parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketLength(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the FIFO thresholds parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketFIFOThresholds(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the packet field 1.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketField1(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the packet field 2.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketField2(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the packet field 3.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketField3(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the packet field 4.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketField4(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the packet field 5.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketField5(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the packet reception field 1.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketReceptionField1(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the packet reception field 2.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketReceptionField2(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the packet reception field 3.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketReceptionField3(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the packet reception field 4.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketReceptionField4(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the packet reception field 5.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePacketReceptionField5(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem modulation type parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemModulationType(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem mapping control parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemMappingControl(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem DSM parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemDSMControl(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem data rate parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemDataRate(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem transmission NCO parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemTransmissionNCO(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem frequency deviation parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemFrequencyDeviation(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem transmission ramp down parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemTransmissionRampDown(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem MDM parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemMDMControl(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem intermediate frequency parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemIFControl(ESAT_COMTransceiverHALClass& transceiver);

    // Function for controlling the modem decimation parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemDecimationControl(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the IF PKD thresholds parametes.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemIFPKDThresholds(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem BCR parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemBCR(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem AFC parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemAFC(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem AGC parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemAGC(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem 4-level modulations parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemFSK4(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem OOK modulation parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemOOK(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem raw eye parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemRawEyeControl(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem antenna diversity parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemAntennaDiversity(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem RSSI parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemRSSI(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem raw search parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemRawSearch2(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the mode clock generator band parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemClockGeneratorBand(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem spike detector parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemSpikeDetector(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem one shot AFC parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemOneShotAFC(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the modem DSA parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureModemDSA(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the reception filter 1 coefficients.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureReceptionFilter1Coefficients(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the reception filter 2 coefficients.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureReceptionFilter2Coefficients(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the power amplifier.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configurePowerAmplifier(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the synthesizer.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureSynthesizer(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the match 1 parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureMatch1(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the match 2 parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureMatch2(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the match 3 parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureMatch3(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the match 4 parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureMatch4(ESAT_COMTransceiverHALClass& transceiver);

    // Function for configuring the frequency control parameters.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError configureFrequencyControl(ESAT_COMTransceiverHALClass& transceiver);
};

// Instance of the 4GFSK reception configuration class.
extern ESAT_COM4GFSKReceptionConfigurationClass ESAT_COM4GFSKReceptionConfiguration;

#endif /*ESAT_COM4GFSKReceptionConfiguration_h*/