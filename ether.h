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
   *  Github repository: https://github.com/ccie18643/PyTCP                   *
   *                                                                          *
   ****************************************************************************
*/


#ifndef _SEATCP_ETHER_H_
#define _SEATCP_ETHER_H_

#include "types.h"


#define ETHER_ADDR_LEN 6

/*
 *   Ethernet frame header
 *
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *   |                                                               >
 *   +    Destination MAC Address    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *   >                               |                               >
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+      Source MAC Address       +
 *   >                                                               |
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *   |           EtherType           |
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

struct s_ether_header {
    byte dst[ETHER_ADDR_LEN];       /* destination mac address */
    byte src[ETHER_ADDR_LEN];       /* source mac destination */
    word type;                      /* type of carried protocol */
};


#define ETHER_HEADER_LEN sizeof(s_ether_header)


/*
 * Definitions of protocols (type)
 */

#include "ether_type.h"             /* definitions and print function */

#endif /* _SEATCP_ETHER_H_ */
