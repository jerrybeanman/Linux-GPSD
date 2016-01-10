#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#include "gps.h"
#include "dcgps.h"
#include "gpsprint.h"
#include "gps-utils.h"

//Error values
#define NO_GPS			0
#define GPS_TIMEOUT		-1
#define SOCKET_ERROR	-2

#define MAXCHANNELS     72      
#define MAX_POSSIBLE_SATS (MAXCHANNELS - 2)
struct fixsource_t		/* structure to the device informaton */
{
    char *spec;         /* pointer to actual storage */
    char *server;
    char *port;
    char *device;
};
struct satData {
	char prn[DATA_SIZE];
	char elev[DATA_SIZE];
	char azim[DATA_SIZE];
	char ss[DATA_SIZE];
	char used[DATA_SIZE];
};

struct outputData {
	int sats;
	char time[DATA_SIZE];
	char lat[DATA_SIZE];
	char lon[DATA_SIZE];
};
#endif
