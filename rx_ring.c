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

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "rx_ring.h"

int start_rx_ring(int tap_fd)
{
    pthread_t thr;

    return pthread_create(&thr, NULL, thread_rx_ring, &tap_fd);
}

void* thread_rx_ring(void* args)
{
    //byte* packet_rx = (byte*)malloc(2048);
    //int packet_rx_len = read(tap_fd, packet_rx, 2048);
    //pp_ether(packet_rx, packet_rx_len);

    while(1) {
        sleep(1);
    }
}

