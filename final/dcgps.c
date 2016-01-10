#include "dcgps.h"

int main()
{
	static struct fixsource_t source;
	struct gps_data_t* gpsdata;						
    	unsigned int flag = WATCH_ENABLE | WATCH_JSON;	// Set watch flags
	build_curses(); //build GUI
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
	gps_close(gpsdata);	// close gps stream
	kill_curses();
	return 0;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: deg_to_str
--
-- DATE: November 11, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jaegar Sarauer
--
-- PROGRAMMER: Jaegar Sarauer
--
-- INTERFACE: char *deg_to_str(double f)
--					-double f : The number to convert to
--
-- RETURNS: The string processed after the conversion
--
-- NOTES:
--	Converts latitude and lontitude values of gps_data to the corresponding string value
----------------------------------------------------------------------------------------------------------------------*/
char *deg_to_str(double f) {
	static char tmp[40];
	double fmin, fdeg;
	int ideg;

	if (f < 0 || f > 360) {
		(void)strcpy(tmp, "nan");
		return tmp;
	}

 	fmin = modf(f, &fdeg);
    	ideg = (int)fdeg;

	(void)sprintf(tmp, "%d", ideg);
	return tmp;
}




