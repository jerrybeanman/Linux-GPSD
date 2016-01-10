#include "dcgps.h"


int main()
{
	static struct fixsource_t source;
	struct gps_data_t* gpsdata;						
    unsigned int flag = WATCH_ENABLE | WATCH_JSON;	// Set watch flags
	gpsdata = (struct gps_data_t*)malloc (sizeof (struct gps_data_t));	// Retrieve a pointer to the structure
	if (gps_open(source.server , source.port, gpsdata) == -1)
	{
		dcgps_error(NO_GPS);
		return 1;
	}
	if(source.device != NULL)
		flag |= WATCH_DEVICE;
	gps_stream(gpsdata, flag, source.device);	// start data report stream from the sensor
	read(gpsdata);
	gps_stream(gps_data, WATCH_DISABLE, NULL);	// disable watch flag
	gps_close(gpsdata);	// close gps stream
	return 0;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: deg_to_str
--
-- DATE: November 11, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Ruoqi Jia
--
-- PROGRAMMER: Ruoqi Jia
--
-- INTERFACE: char *deg_to_str(double f)
--					-double f : The number to convert to
--
-- RETURNS: The string processed after the conversion
--
-- NOTES:
--	Converts latitude and lontitude values of gps_data to the corresponding string value
----------------------------------------------------------------------------------------------------------------------*/
char *deg_to_str(double f)
{
	static char str[40];
	int dsec, sec, deg, min;
	double fdsec, fsec, fdeg, fmin;

	if (f < 0 || f > 360)
		(void)strcpy(str, "nan");
    	else
    	{
    	fmin = modf(f, &fdeg);
    	deg = (int)fdeg;

    	fdsec = modf(fsec * 60, &fsec);
    	sec = (int)fsec;
    	dsec = (int)(fdsec * 1000.0);
    	(void)snprintf(str, sizeof(str), "%3d %02d' %02d.%03d\"", deg, min, sec, dsec);
    	}
    	return str;
}










