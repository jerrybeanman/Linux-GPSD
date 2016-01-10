#include "gpsprint.h"

void  print_gps(struct gps_data_t *gpsdata)
{
	fprintf(stderr,"%d\n", gpsdata->satellites_visible);
	if (gpsdata->satellites_visible != 0) // Some satellites are visible
	{
		int i;
	    for (i = 0; i < MAX_POSSIBLE_SATS; i++) {
		    if (i < gpsdata->satellites_visible && gpsdata->skyview[i].used) {
				fprintf(stdout, "PRN: %3d		Elevation: %2d 			Azimuth: %3d		SNR: %2d		Used: %c\n",
				       gpsdata->skyview[i].PRN,
				       gpsdata->skyview[i].elevation,
				       gpsdata->skyview[i].azimuth,
				       (int)gpsdata->skyview[i].ss,
				       gpsdata->skyview[i].used ? 'Y' : 'N');
		    }
	    }
	    if (gpsdata->fix.mode >= MODE_2D && isnan (gpsdata->fix.latitude) == 0)
	    {
		fprintf (stdout, "Latitude: %s %c;", 
		    deg_to_str(fabs (gpsdata->fix.latitude)),
		    (gpsdata->fix.latitude < 0) ? 'S' : 'N');
		fflush (stdout);
	    }else
		printf("n/a\n");
	}
}
