CFLAGS=-Wall -DLOG_USE_COLOR -pthread

all: clean format seatcp

seatcp: ph.o rx_ring.o tx_ring.o ether.o pp_ether.o lib/log.o

format:
	astyle --style=linux --indent=spaces --align-pointer=type --convert-tabs --max-code-length=160 --suffix=none *.h *.c

clean:
	rm -f seatcp *.o
