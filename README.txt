Copyright (C) 2021 Theia Space, Universidad Politécnica de Madrid

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


ESAT COM library version 1.0.1.

Radio Communications Subsystem (COM) for ESAT.

This software runs in the ESAT COM and ESAT GS boards. Use it
with Arduino 1.8.0 or newer together with the Arduino core for
STM32L4-based ESAT boards (Theia Space's ESAT Boards (STM32L4))
1.1.0 or a newer 1.x.y version and the ESAT utility library
ESATUtil) version 2.2.0 or a newer 2.x.y version. Select ESAT-COM
as target board for the COM board and ESAT-GS for the GS board.

See the example COM program (examples/COM/COM.ino) and GS program
(examples/GS/GS.ino). These programs uses the modules of the COM
library.

The src/ directory contains the COM library (ESAT_COM) as well as
several subdirectories:


# ESAT_COM

This is the main library that provides the general COM functionality.


# ESAT_COM-hardware directory

This directory contains drivers for the peripherals of the ESAT COM
and ESAT GS boards used by ESAT_COM.


# ESAT_COM-telecommands directory

Telecommand handlers.


# ESAT_COM-telemetry directory

Telemetry packets.
