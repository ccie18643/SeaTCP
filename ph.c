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
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "types.h"
#include "ph.h"
#include "rx_ring.h"
#include "packet.h"
#include "pp_ether.h"
#include "lib/log.h"

struct s_packet_handler* packet_handler__init()
{
    struct s_packet_handler* self = (struct s_packet_handler*)malloc(sizeof(struct s_packet_handler));
    self->run_thread = true;
    assert(!pthread_create(&self->thread, NULL, packet_handler__thread, self));
    return self;
}

void* packet_handler__thread(void* _)
{
    struct s_packet_handler* self = (struct s_packet_handler*)_;

    log_debug("Started packet_handler thread");

    char* tap_name = "tap7";

    int tap_fd = open_tap(tap_name);
    if(tap_fd < 0) {
        log_error("Error connecting to %s interface", tap_name);
        exit(1);
    }
    log_debug("Connected to %s interface", tap_name);

    struct s_rx_ring* rx_ring = rx_ring__init(tap_name, tap_fd, 10);

    while(self->run_thread) {
        struct s_packet* packet_rx = rx_ring__dequeue(rx_ring);
        pp_ether(packet_rx->data, packet_rx->len);
        packet_rx->fresh = false;
    }

    log_debug("Stoping packet_handler thread");
    free(self);
    return NULL;
}

int open_tap(char* tap_name)
{
    int tap_fd = open("/dev/net/tun", O_RDWR);
    if(tap_fd < 0) {
        log_error("Error opening /dev/net/tun");
        return tap_fd;
    }
    log_debug("Opened /dev/net/tun");

    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
    strncpy(ifr.ifr_name, tap_name, IFNAMSIZ);

    int error = ioctl(tap_fd, TUNSETIFF, (void*)&ifr);
    if(error < 0) {
        log_error("Error setting /dev/net/tun parameters with ioctl");
        close(tap_fd);
        return error;
    }
    log_debug("Set /dev/net/tun parameters with ioctl");

    return tap_fd;
}
