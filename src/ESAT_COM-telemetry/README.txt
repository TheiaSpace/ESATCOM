Copyright (C) 2020 Theia Space, Universidad Politécnica de Madrid

This file is part of Theia Space's ESAT COM library.

Theia Space's ESAT COM library is free software: you can
redistribute it and/or modify it under the terms of the GNU General
Public License as published by the Free Software Foundation, either
version 3 of the License, or (at your option) any later version.

Theia Space's ESAT COM library is distributed in the hope that it
will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Theia Space's ESAT COM library.  If not, see
<http://www.gnu.org/licenses/>.


COM telemetry packet contents objects fill telemetry packets.  Each
telemetry packet contents object implements the
ESAT_CCSDSPacketContents interface from ESATUtil and fills one
telemetry packet.  They are used by ESAT_COM.


# ESAT_COMHousekeepingTelemetry

Fill the COM_HOUSEKEEPING (0x00) telemetry packet.
