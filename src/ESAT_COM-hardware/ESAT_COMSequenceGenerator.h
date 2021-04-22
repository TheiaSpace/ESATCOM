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

#ifndef ESAT_COMSequenceGenerator_h
#define ESAT_COMSequenceGenerator_h

#include <Arduino.h>
#include <ESAT_Task.h>

// Periodic task for varying the sequence
class SequenceIncrementingTaskClass: public ESAT_Task
{
  public:

    // Updating period (in us).
    // Set it here.
    unsigned long period()
    {
      return 300000;
    }

    // Periodic task function. Called by an ESAT_TaskScheduler.
    // Transmits the proper frame.
    void run();

};

// This class generates a binary or quaternary CCSDS packet to test the
// transmission modulations
class ESAT_COMSequenceGeneratorClass
{
  public:

    // Perodic task instance.
    SequenceIncrementingTaskClass SequenceIncrementingTask;

    // Disables the sequential mode.
    void disable();

    // Configures the 4-level radio sweep.
    void enableFourLevels();

    // Configures the 2-level radio sweep.
    void enableTwoLevels();

    // Returns if the sweep is enabled and the selected mode.
    byte getMode();

    // Process the sequence transmission
    void handleSequenceTransmission();

  private:

    // Controls the working mode of the sequence generator.
    enum SequenceMode
    {
      DISABLED = 0,
      TWO_LEVELS = 1,
      FOUR_LEVELS = 2
    };

    // Number of times a packet is repeated before skipping to the next oen.
    const byte NUMBER_OF_RETRIALS = 1;

    // Index of the sequence.
    byte levelCounter = 0;

    // Mode of operation.
    SequenceMode mode = DISABLED;

    // Number of times each step of the sequence have been repeated.
    byte retrialsCounter = 0;

    // Sends the packet.
    // Requires the symbol to be transmitted
    boolean transmitPacket(byte symbol);
};

// Global instance of the ESAT_COMSequenceGeneratorClass.
extern ESAT_COMSequenceGeneratorClass ESAT_COMSequenceGenerator;

#endif /* ESAT_COMSequenceGenerator_h */
