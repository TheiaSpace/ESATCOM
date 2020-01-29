/*
 * Copyright (C) 2098 Theia Space, Universidad Politécnica de Madrid
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

#ifndef ESAT_COMHousekeepingTelemetry_h
#define ESAT_COMHousekeepingTelemetry_h

#include <Arduino.h>
#include <ESAT_CCSDSTelemetryPacketContents.h>

// COM (Communications Subsystem) housekeeping telemetry packet contents.
// ESAT_COMSubsystem uses this.
class ESAT_COMHousekeepingTelemetryClass: public ESAT_CCSDSTelemetryPacketContents
{
  public:
    // Return true when a new telemetry packet is available;
    // otherwise return false.
    boolean available();

    // Return the packet identifier.
    byte packetIdentifier()
    {
      return 0x00;
    }

    // Fill the user data field of the given packet.
    // The write pointer of the packet is already at the start
    // of the user data field.
    // Return true on success; otherwise return false.
    boolean fillUserData(ESAT_CCSDSPacket& packet);
};

// Global instance of ESAT_COMHousekeepingTelemetry.  ESAT_COMSubsystem uses this
// to fill the COM housekeeping telemetry packet.
extern ESAT_COMHousekeepingTelemetryClass ESAT_COMHousekeepingTelemetry;

#endif /* ESAT_COMHousekeepingTelemetry_h */
