
 #include "gps-utils.h"
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
void read(struct gps_data_t* gpsdata)
{
	while(1)
	{ 
		if (!gps_waiting(gpsdata, 2000000))	// Wait for 1 second before timeout
			dcgps_error(GPS_TIMEOUT);
		else
		{
		    if (gps_read(gpsdata) == -1)  	// Performs non-blocking read
				dcgps_error(SOCKET_ERROR);
	        else			
			updateInformation(gpsdata);			// Process data on screen
		}
	} 
}

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
void dcgps_error(int errorno)
{
	switch(errorno)
	{
		case NO_GPS :
			showError("dcgps: no gpsd running or network");
			break;
		case GPS_TIMEOUT:
			showError("No signal or satellites detected");
			break;
		case SOCKET_ERROR:
			showError("gps-utils: socket error");
			break;
		case 4:
			showError("Device Successfully Opened");
			break;
		default:
			return;
	}
}
