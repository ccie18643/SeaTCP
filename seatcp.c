/*
   ****************************************************************************
   *                                                                          *
   *  SeaTCP- Low latency TCP/IP stack                                       *
   *  Copyright (C) 2020  Sebastian Majewski                                  *
   *                                                                          *
   *  This program is free software: you can redistribute it and/or modify    *
   *  it under the terms of the GNU General Public License as published by    *
   *  the Free Software Foundation, either version 3 of the License, or       *
   *  (at your option) any later version.                                     *
   *                                                                          *
   *  This program is distributed in the hope that it will be useful,         *
   *  but WITHOUT ANY WARRANTY; without even the implied warranty of          *
   *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
   *  GNU General Public License for more details.                            *
   *                                                                          *
   *  You should have received a copy of the GNU General Public License       *
   *  along with this program.  If not, see <https://www.gnu.org/licenses/>.  *
   *                                                                          *
   *  Author's email: ccie18643@gmail.com                                     *
   *  Github repository: https://github.com/ccie18643/SeaTCP                  *
   *                                                                          *
   ****************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lib/log.h"
#include "types.h"
#include "ph.h"


int main(int argc, char** argv)
{
    packet_handler__init();

    while(true)
        sleep(1);

    return 0;
}
