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
#ifndef ESAT_COMTransceiverDriver_h
#define ESAT_COMTransceiverDriver_h

#include <Arduino.h>
#include <SPI.h>
#include "ESAT_COMTransceiverHAL.h"
#include "configurations/ESAT_COMTransceiverConfiguration.h"

// Radio communications devices driver class.
// Interactions with Si4463 rev C2A transceivers
// (either transmission or reception) are done through
// this class.
class ESAT_COMTransceiverDriverClass
{
  public:

    // Data type for the different radio data sinks and sources.
    // FIFO and random generator supports all modulation types.
    // GPIO synchronous sources only support, OOK 2FSK and 2GFSK.
    // GPIO asynchronous sources only support OOK and 2FSK.

    enum ModulationSource
    {
      fifo = 0, // Data is obtained from the FIFO written packets.
      randomGenerator     = 1, // Data is obtained from a pseudo-random generator.
      gpio0_synchronous   = 2, // Data is sampled from GPIO0 using an external clock.
      gpio0_asynchronous  = 3, // Data is obtained from GPIO0 level (no clock).
      gpio1_synchronous   = 4, // Data is sampled from GPIO1 using an external clock.
      gpio1_asynchronous  = 5, // Data is obtained from GPIO1 level (no clock).
      gpio2_synchronous   = 6, // Data is sampled from GPIO2 using an external clock.
      gpio2_asynchronous  = 7, // Data is obtained from GPIO2 level (no clock).
      gpio3_synchronous   = 8, // Data is sampled from GPIO3 using an external clock.
      gpio3_asynchronous  = 9, // Data is obtained from GPIO3 level (no clock).
    };

    // Data type for the different modulation schemas.
    // Continuous wave broadcast a continuos carrier.
    enum ModulationType
    {
      OOK = 0, // On-Off keying modulation.
      twoFSK = 1, // Two level frequency shift keying modulation.
      twoGaussianFSK = 2, // Two level gaussian frequency shift keying modulation.
      fourFSK = 3, // Four level frequency shift keying modulation.
      fourGaussianFSK = 4, // Four level gaussian frequency shift keying modulation.
      continuousWave = 5, // Continuous carrier.
    };

    // Data type for all possible errors returned by the driver.
    enum TransceiverErrorCode
    {
      noError = 0,
      // High level errors.
      notInitializedError = 1, // Unused.
      wrongModeError = 2, // Configuration not compatible with the set mode.
      wrongFrequencyError = 3, // Frequency out of hardware bounds.
      wrongChannelError = 4, // Channel out of set band bounds.
      wrongPowerError = 5, // Transmission set power out of hardware bounds.
      // Low level errors.
      CTSError = 6, // Transceiver doesn't accept commands.
      commandError = 7, // Unused.
      chipError = 8, // Fired if the interrupt line changes unexpectedly.
      // GenericError.
      error = 9,
    };

    // Data type for the different radio working modes.
    enum TransceiverMode
    {
      notInitializedMode = 0, // Transceiver not configured yet.
      TXMode = 1, // Transceiver configured as a transmitter.
      RXMode = 2, // Transceiver configured as a receiver.
    };

    // Highest allowed frequency (in MHz) for reception.
    const float HIGHEST_RECEPTION_FREQUENCY = 1050.0;

    // Highest allowed frequency (in MHz) for transmission.
    const float HIGHEST_TRANSMISSION_FREQUENCY = 1050.0;

    // Lowest allowed frequency (in MHz) for reception.
    const float LOWEST_RECEPTION_FREQUENCY = 142.0;

    // Lowest allowed frequency (in MHz) for transmission.
    const float LOWEST_TRANSMISSION_FREQUENCY = 142.0;

    // Maximum value for transmission power rate.
    const float MAXIMUM_TRANSMISSION_POWER_RATE = 100.0;

    // Minimum value for transmission power rate.
    const float MINIMUM_TRANSMISSION_POWER_RATE = 0.0;

    // Maximum packet length supported by radio transceiver.
    static const byte RADIO_MAX_PACKET_LENGTH = 129;

    // Highest channel allowed for the transceiver band.
    byte highestChannel = 31;

    // Lowest channel allowed for the transceiver band.
    byte lowestChannel = 0;

    // Constructor. Initialize the transceiver API software
    // and attaches it to a physical interface.
    ESAT_COMTransceiverDriverClass(ESAT_COMTransceiverHALClass& hardwareTransceiver);

    // Process the transmission (keep filling the FIFO
    // until packet is over); and the reception (if a
    // packet has been received, retrieve it from the FIFO).
    signed char available();

    // Initialize the transceiver according to the selected
    // mode (transmission or reception).
    // Return if the initialization goes wrong or not.
    TransceiverErrorCode begin(TransceiverMode mode);

    // Initialize the transceiver according to the working
    // mode and modulation set.
    // Return if the initialization goes wrong or not.
    TransceiverErrorCode begin(TransceiverMode mode, ModulationType modulationType);

    // Disable and holds the transceiver in reset state.
    void disable();

    // Disable interrupts.
    // Return if the change goes wrong or not.
    TransceiverErrorCode disableInterrupts();

    // Return the configured channel.
    byte getChannel();

    // Return the default channel.
    byte getDefaultChannel();

    // Return the configured center frequency.
    float getDefaultFrequency();

    // Return the default modulation source.
    ModulationSource getDefaultModulationSource();

    // Return the default modulation.
    ModulationType getDefaultModulationType();

    // Return the default transmission power rate.
    float getDefaultTransmissionPower();

    // Return the configured center frequency.
    float getFrequency();

    // Return the current set modulation.
    byte getModulation();

    // Return the transmission data source.
    signed char getModulationSource();

    // Read the last received signal strength indicator value.
    float getReceivedSignalStrengthIndicator();

    // Read the transceiver temperature.
    float getTransceiverTemperature();

    // Read the transceiver supply voltage.
    float getTransceiverVoltage();

    // Return the transmisssion power (0.0 if it is in receiving mode).
    float getTransmissionPowerRate();

    // Retrieve the reception buffer pointer without
    // polling before wheter a packet has been received
    // or not, thus not holding the process.
    byte* nonBlockingRead();

    // Send a packets without waiting for it to be sent,
    // thus not holding the execution.
    // Return if the process goes wrong.
    TransceiverErrorCode nonBlockingWrite(byte* msgBuf);

    // Poll for a packet to be received holding the
    // execution.
    // Return the reception buffer.
    byte* read();

    // Change the radio channel.
    TransceiverErrorCode setChannel(byte channel);

    // Change the center frequency.
    // This function doesn't write the value to the transceiver.
    // To write the new frequency to the chip, call updateFrequency
    // after.
    // Return if the process goes wrong.
    TransceiverErrorCode setFrequency(float frequency);

    // Configure the transceiver default channel.
    // No parameter check is performed, so a valid value must be provided.
    void setDefaultChannel(byte channel);

    // Configure the transceiver default frequency.
    // No parameter check is performed, so a valid value must be provided.
    void setDefaultFrequency(float frequency);

    // Configure the transmitter default moodulation source.
    // No parameter check is performed, so a valid value must be provided.
    void setDefaultModulationSource(ModulationSource modulationSource);

    // Configure the transceiver default moodulation type.
    // No parameter check is performed, so a valid value must be provided.
    void setDefaultModulationType(ModulationType modulationType);

    // Configure the transmitter default transmission power rate.
    // No parameter check is performed, so a valid value must be provided.
    void setDefaultTransmissionPower(float transmissionPowerRate);

    // Configures the transceiver lowest channel.
    void setHighestChannel(byte channel);

    // Configure the transceiver highest channel.
    void setLowestChannel(byte channel);

    // Change the modulation source.
    // Return if the process goes wrong.
    TransceiverErrorCode setModulationSource(ModulationSource modulationSource);

    // Change the modulation type. Only valid for enabling continuous wave.
    // This does not reset the chip. For other modulation settings, a
    // transceiver reset and full reconfiguration is required.
    // Return if the process goes wrong.
    TransceiverErrorCode setModulationType(ModulationType modulationType);

    // Change transmision power.
    // This function doesn't write the value to the transceiver.
    // To write the new power to the chip, call updateFrequency
    // after.
    // Return if the process goes wrong.
    TransceiverErrorCode setTransmissionPower(float transmissionPowerRateToBeSet);

    // Enable the reception (only in reception mode).
    // Return if the process goes wrong.
    TransceiverErrorCode startReception();

    // Applythe last set frequency change to the transceiver.
    TransceiverErrorCode updateFrequency();

    // Handle the manual data transmission.
    void updateManualDataStream();

    // Apply the last set transmitter power change to the transceiver.
    TransceiverErrorCode updateTransmissionPower();

    // Write a packet and wait for it to be sent,
    // either by ISR or by polling checking methods.
    // Return if the process goes wrong.
    TransceiverErrorCode write(byte* msgBuf);

  private:

    // Clock frequency for computing the radio frequency.
    const unsigned long CRYSTAL_FOR_FREQUENCY_COMPUTING = 30000000;

    // Maximum failed initialization sequences allowed.
    const byte MAXIMUM_FAILED_INITIALIZATIONS = 25;

    // Maximum value for mapping the power rate to the transceiver values.
    const float MAXIMUM_POWER_VALUE = 127.0;

    // Minimum value for mapping the power rate to the transceiver values.
    const float MINIMUM_POWER_VALUE = 0.0;

    // Period for toggling a manual 1-0 bit stream.
    const word OUTPUT_DATA_STREAM_TOGGLING_PERIOD_MS = 2000;

    // Reception chain losses for RSSI calculation.
    const float RECEPTION_LOSSES_dB = 130.0;

    // Default radio channel.
    byte defaultChannel = 0;

     // Default radio frequency.
    float defaultFrequency = 433.0; // In MHz.

    // Default data source.
    enum ModulationSource defaultModulationSource = fifo;

    // Default modulation schema.
    enum ModulationType defaultModulationType = OOK;

    // Default transmission power rate.
    float defaultTransmissionPowerRate = 100.0;

    // Next bit of the manual bit stream.
    byte outputDataStreamNextBit;

    // Indicates if there is received and unread data.
    boolean receptionAvailable;

    // FIFO reception buffer.
    byte receptionBuffer[RADIO_MAX_PACKET_LENGTH];

    // Reception configuration object pointer.
    ESAT_COMTransceiverConfigurationClass* receptionConfigurationData;

    // Interrupt flag for the reception transceiver.
    static volatile byte receptionInterruptFlag;

    // Radio hardware abstranction layer entity.
    ESAT_COMTransceiverHALClass* transceiver;

    // Transmission data source.
    ModulationSource transmitterModulationSource;

    // Modulation used by the transceiver.
    ModulationType transceiverModulationType;

    // Current transceiver configuration mode.
    TransceiverMode transceiverOperationMode = notInitializedMode;

    // Transceiver radio channel.
    byte transceiverRadioChannel;

    // Transceiver radio central frequency.
    float transceiverFrequency;

    // Transmission configuration object pointer.
    ESAT_COMTransceiverConfigurationClass* transmissionConfigurationData;

    // Interrupt flag for the transmission transceiver.
    static volatile byte transmissionInterruptFlag;

    // Indicate if a transmission is going on.
    boolean transmissionInProgress;

    // Transmitter power rate.
    float transmissionPowerRate;

    // Check if there is a packet ready to be read.
    signed char checkReceptionAvailability();

    // Check if the last packet is already transmitted.
    signed char checkTransmissionAvailability();

    // Configure the transceiver using the pointed configuration.
    ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError initializeTransceiver(ESAT_COMTransceiverConfigurationClass* transceiverConfiguration);

    // Interrupt service routine for the reception transceiver.
    // Set the reception interrupt flag when it is called.
    static void setReceptionTransceiverInterruptFlag (void);

    // Interrupt service routine for the transmission transceiver.
    // Set the transmission interrupt flag when it is called.
    static void setTransmissionTransceiverInterruptFlag (void);

    // Turn the selected LED on or off. Requires the switched mode led
    // (transmission or reception) and the level (true for high and
    // false for low).
    void switchLED(TransceiverMode modeLED, boolean level);

    // Select the configuration file acording to the
    // chose modulation for the reception mode.
    // Returns the pointer to the configuration file.
    ESAT_COMTransceiverConfigurationClass* switchReceptionConfiguration(ModulationType modulationType);

    // Select the modulation source configuration
    // command according to the chosen modulation source.
    // Return the modulation source command.
    byte switchModulationSource(ModulationSource source);

    // Select the modulation source configuration type
    // according to the modulation type chosen. However
    // this function doesn't change the modulation at all.
    // Only set the command bits according to the modulation.
    // Return the modulation source command.
    byte switchModulationType(ModulationType type);

    // Select the configuration class acording to the
    // modulation chosen for the transmission channel.
    // Return the pointer to the configuration class.
    ESAT_COMTransceiverConfigurationClass* switchTransmissionConfiguration(ModulationType modulationType);

    // Cast from HAL error to device driver error.
    TransceiverErrorCode translateLowLevelDriverError(ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError);
};

// Global instace of the reception transceiver.
extern ESAT_COMTransceiverDriverClass ReceptionTransceiver;

// Global instace of the transmission transceiver.
extern ESAT_COMTransceiverDriverClass TransmissionTransceiver;

#endif /* ESAT_COMTransceiverDriver_h */
