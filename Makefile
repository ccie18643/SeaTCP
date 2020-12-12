CFLAGS=-DLOG_USE_COLOR -pthread

all: clean seatcp

seatcp: rx_ring.o tx_ring.o pp_ether.o log.o

clean:
	rm -f seatcp *.o
