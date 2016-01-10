CC=gcc
CLIB=-lgps -lncurses -lm -lcurses

dcgps: dcgps.o gps-utils.o gpsprint.o
	$(CC) -o dcgps dcgps.o gps-utils.o gpsprint.o $(CLIB)

clean:
	rm -f *.o core.* dcgps
dcgps.o: dcgps.c dcgps.h
	$(CC) -c dcgps.c 
gps-utils.o: gps-utils.c gps-utils.h
	$(CC) -c gps-utils.c
gpsprint.o: gpsprint.c gpsprint.h
	$(CC) -c gpsprint.c

