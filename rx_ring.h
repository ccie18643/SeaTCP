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


#ifndef _SEATCP_RX_RING_H_
#define _SEATCP_RX_RING_H_

#include <pthread.h>
#include <semaphore.h>

#include "packet.h"

struct s_rx_ring {
    char tap_name[16];
    int tap_fd;
    int buffer_size;
    int run_thread;
    struct s_packet* buffer;
    struct s_packet* buffer_write;
    struct s_packet* buffer_read;
    pthread_t thread;
    sem_t buffer_write_sem;
};


struct s_rx_ring* rx_ring__init(char*, int, int);
void* rx_ring__thread(void*);
struct s_packet* rx_ring__dequeue(struct s_rx_ring*);

#endif /* _SEATCP_RX_RING_H_ */
