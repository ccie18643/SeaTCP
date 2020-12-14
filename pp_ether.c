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
   *  Github repository: https://github.com/ccie18643/SeaTCP                  *
   *                                                                          *
   ****************************************************************************
*/

#include <stdio.h>
#include <arpa/inet.h>

#include "types.h"
#include "ether.h"
#include "ether_type.h"
#include "pp_ether.h"
#include "lib/log.h"


void pp_ether(byte* ether_packet_rx, int ether_packet_rx_len)
{
    struct s_ether_header* ether_header_rx = (void*)ether_packet_rx;

    char src[18], dst[18], type[8];
    log_debug("ETHER %s > %s, 0x%04x (%s)", ether_ntoa(dst, ether_header_rx->dst),
              ether_ntoa(src, ether_header_rx->src), ntohs(ether_header_rx->type), ether_type(type, ntohs(ether_header_rx->type)));
}

