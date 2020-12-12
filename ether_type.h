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

#ifndef _SEATCP_ETHER_TYPE_H_
#define _SEATCP_ETHER_TYPE_H_

/*
 * Protocol types used in 'type' field by Ethernet
 */

#define ETHER_TYPE_MIN          0x0600  /* minimal value of ether_type field */
#define ETHER_TYPE_IP           0x0800  /* IPv4 protocol */
#define ETHER_TYPE_ARP          0x0806  /* address resolution protocol */
#define ETHER_TYPE_IP6          0x86DD  /* IPv6 protocol */

#endif /* _SEATCP_ETHER_TYPE_H_ */
