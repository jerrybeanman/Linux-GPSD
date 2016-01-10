#ifndef GPS_UTILS
#define GPS_UTILS
#include "globals.h"
/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: read
--
-- DATE: November 11, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Ruoqi Jia
--
-- PROGRAMMER: Ruoqi Jia
--
-- INTERFACE: void read(struct gps_data_t* gpsdata)
--					-struct gps_data_t* gpsdata : the structure to store gps info retrieved from the daemon
--
-- RETURNS: NONE
--
-- NOTES:
--	Continuous read loop that performs non-blocking read operations on the gps
--  daemon. (Also performs error checking)
----------------------------------------------------------------------------------------------------------------------*/
void read(struct gps_data_t* gpsdata);

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: dcgps_error
--
-- DATE: November 11, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Ruoqi Jia
--
-- PROGRAMMER: Ruoqi Jia
--
-- INTERFACE: void dcgps_error(int errorno)
--					-int errorno : error number defined by globals.h
--
-- RETURNS: NONE
--
-- NOTES:
--	Performs error checking for the gps program 
----------------------------------------------------------------------------------------------------------------------*/
void dcgps_error(int errorno);
#endif
