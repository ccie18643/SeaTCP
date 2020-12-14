/*
   ****************************************************************************
   *                                                                          *
   *  SeaTCP - Low latency TCP/IP stack                                       *
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
   *  Github repository: https://github.com/ccie18643/SeaTCP                   *
   *                                                                          *
   ****************************************************************************
*/


#include <stdio.h>

#include "types.h"
#include "ether.h"
#include "ether_type.h"


char* ether_ntoa(char* str, byte* addr)
{
    sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x",
            *(addr + 0),
            *(addr + 1),
            *(addr + 2),
            *(addr + 3),
            *(addr + 4),
            *(addr + 5));

    return str;
}

char* ether_type(char* str, word type)
{
    switch(type) {
    case ETHER_TYPE_ARP:
        sprintf(str, "%s", "ARP");
        break;
    case ETHER_TYPE_IP4:
        sprintf(str, "%s", "IPv4");
        break;
    case ETHER_TYPE_IP6:
        sprintf(str, "%s", "IPv6");
        break;
    default:
        sprintf(str, "%s", "UNK");
    }

    return str;
}
