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
