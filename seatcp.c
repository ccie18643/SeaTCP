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
#include <string.h>
#include <unistd.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>

#include "log.h"
#include "types.h"
#include "rx_ring.h"
#include "tx_ring.h"
#include "pp_ether.h"


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

int main(int argc, char** argv)
{
    char* tap_name = "tap7";

    int tap_fd = open_tap(tap_name);
    if(tap_fd < 0) {
        log_error("Error connecting to %s interface", tap_name);
        exit(1);
    }
    log_debug("Connected to %s interface", tap_name);
    assert(!start_rx_ring(tap_fd));
    assert(!start_tx_ring(tap_fd));

    while(1) {
        sleep(1);
    }

    return 0;
}
