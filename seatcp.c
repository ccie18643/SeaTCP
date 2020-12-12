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

int open_tap(char* tap)
{
  struct ifreq ifr;
  int fd, err;

  if((fd = open("/dev/net/tun", O_RDWR)) < 0) {
    printf("Error opening /dev/net/tun\n");
    return fd;
  }
  printf("Opened /dv/net/tun\n");

  memset(&ifr, 0, sizeof(ifr));
  ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
  strncpy(ifr.ifr_name, tap, IFNAMSIZ);

  if((err = ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0) {
    printf("Error setting /dev/net/tun parameters with ioctl\n");
    close(fd);
    return err;
  }
  printf("Set /dev/net/tun parameters with ioctl\n");

  return fd;
}

int main(int argc, char** argv)
{
    char* tap = "tap7";
    int tap_fd = 0;

    if((tap_fd = open_tap(tap)) < 0)  {
        printf("Error connecting to %s interface\n", tap);
        exit(1);
    }
    printf("Connected to %s interface\n", tap);

    char* packet_rx = (char*)malloc(2048);
    read(tap_fd, packet_rx, 2048);
}
