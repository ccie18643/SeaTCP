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
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#include "types.h"
#include "rx_ring.h"
#include "lib/log.h"

struct s_rx_ring* rx_ring__init(char* tap_name, int tap_fd, int buffer_size)
{
    struct s_rx_ring* self = (struct s_rx_ring*)malloc(sizeof(struct s_rx_ring));
    strncpy(self->tap_name, tap_name, 16);
    self->tap_fd = tap_fd;
    self->buffer_size = buffer_size;
    self->run_thread = true;
    assert(!pthread_create(&self->thread, NULL, rx_ring__thread, self));
    return self;
}

void* rx_ring__thread(void* _)
{
    struct s_rx_ring* self = (struct s_rx_ring*)_;

    log_debug("Started rx_ring thread for %s interface, descriptor %d, buffer size %d", self->tap_name, self->tap_fd, self->buffer_size);

    self->buffer = (struct s_packet*)calloc(self->buffer_size, sizeof(struct s_packet));
    self->buffer_write = self->buffer;
    self->buffer_read = self->buffer;
    sem_init(&self->buffer_write_sem, false, 0);

    while(self->run_thread) {
        if(self->buffer_write->fresh) {
            log_warn("rx_ring - buffer full");
            sleep(1);
            continue;
        }
        self->buffer_write->len = read(self->tap_fd, self->buffer_write->data, 2048);
        self->buffer_write->fresh = true;
        sem_post(&self->buffer_write_sem);
        log_debug("rx_ring - enqueued packet, %d bytes, queue position %d", self->buffer_write->len, self->buffer_write - self->buffer);
        if(self->buffer_write == self->buffer + self->buffer_size) {
            self->buffer_write = self->buffer;
        } else {
            self->buffer_write++;
        }
    }

    log_debug("Stoping rx_ring thread");
    free(self->buffer);
    free(self);
    return NULL;
}

struct s_packet* rx_ring__dequeue(struct s_rx_ring* self)
{
    sem_wait(&self->buffer_write_sem);
    assert(self->buffer_read->fresh);
    struct s_packet* packet = self->buffer_read;
    if(self->buffer_read == self->buffer + self->buffer_size) {
        self->buffer_read = self->buffer;
    } else {
        self->buffer_read++;
    }
    return packet;
}


