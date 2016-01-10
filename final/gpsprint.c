#include "gpsprint.h"


WINDOW *visualWindow;
WINDOW *rawDataWindow;
WINDOW *errorWindow;
WINDOW *mainwin;
struct satData satelites[16];
struct outputData output;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: updateInformation
--
-- DATE: November 8th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jaegar Sarauer
--
-- PROGRAMMER: Jaegar Sarauer
--
-- INTERFACE:   updateInformation(struct gps_data_t *d)
--		- struct gps_data_t *d : A gps_data_t struct read from the GPS reader. Contains GPS data.
--
-- RETURNS: VOID
--
-- NOTES: This function takes in a struct which contains GPS data. The function parses the data on the struct for each
--	satellite into local structs of char arrays, for easy output their respective windows.
----------------------------------------------------------------------------------------------------------------------*/
void updateInformation(struct gps_data_t *d) {
	char tmp[256];
	int i;
	output.sats = d->satellites_visible;
	for (i = 0; i < output.sats; i++) {
		sprintf(tmp, "%3d", d->skyview[i].PRN);
		strcpy(satelites[i].prn, tmp);
		sprintf(tmp, "%2d", d->skyview[i].elevation);
		strcpy(satelites[i].elev, tmp);
		sprintf(tmp, "%3d", d->skyview[i].azimuth);
		strcpy(satelites[i].azim, tmp);
		sprintf(tmp, "%2d", (int)d->skyview[i].ss);
		strcpy(satelites[i].ss, tmp);
		strcpy(satelites[i].used, d->skyview[i].used ? "Y" : "N");
	}
	if (d->fix.mode >= MODE_2D) {
	double time = d->fix.time;
	time_t sec = (time_t)time;
	sprintf(tmp, "%s", ctime(&sec));
	strcpy(output.time, tmp);
		sprintf(tmp, "%s %c", deg_to_str(fabs (d->fix.latitude)), (d->fix.latitude < 0) ? 'S' : 'N');
		strcpy(output.lat, tmp);
		sprintf(tmp, "%s %c", deg_to_str(fabs (d->fix.longitude)), (d->fix.longitude < 0) ? 'S' : 'N');
		strcpy(output.lon, tmp);
	} else {
		strcpy(output.time, "N/A");
		strcpy(output.lat, "N/A");
		strcpy(output.lon, "N/A");
	}
	wclear(errorWindow);
	box(errorWindow, 0, 0);
	wrefresh(errorWindow);

	resizeWindows();
	drawRawData();
	drawVisualData();
	updateWindows();
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: drawRawData
--
-- DATE: November 8th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jaegar Sarauer
--
-- PROGRAMMER: Jaegar Sarauer
--
-- INTERFACE: drawRawData()
--
-- RETURNS: VOID
--
-- NOTES: This function draws the computed data from the updateInformation function. This is updated to specifically
--	raw data window, which contains latitude, longitude, satellites found, and timestamp.
----------------------------------------------------------------------------------------------------------------------*/
void drawRawData() {
	int row = 0;
	mvwprintw(rawDataWindow, row++ + 1, 1, "Visible Satelites:\t\t%d", output.sats);
	mvwprintw(rawDataWindow, row++ + 1, 1, "Time Stamp:\t\t\t%s", output.time);
	mvwprintw(rawDataWindow, row++ + 1, 1, "Latitude:\t\t\t%s", output.lat);
	mvwprintw(rawDataWindow, row + 1, 1, "Longitude:\t\t\t%s", output.lon);
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: drawVisualData
--
-- DATE: November 8th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jaegar Sarauer
--
-- PROGRAMMER: Jaegar Sarauer
--
-- INTERFACE: drawVisualData()
--
-- RETURNS: VOID
--
-- NOTES: This function draws the computed data from the updateInformation function. This is updated to specifically
--	draw onto the visual data window, which includes the specific information from each currently found satellite.
----------------------------------------------------------------------------------------------------------------------*/
void drawVisualData() {
	int tmpH, tmpW;
	getmaxyx(visualWindow, tmpH, tmpW);
	int i;
	
	for (i = 0; i < output.sats; i++) {
		mvwprintw(visualWindow, 1 + (i * 3), 1, "PRN:\t%s\t\tElevation:\t%s\t\tAzimuth:\t%s", satelites[i].prn, satelites[i].elev, satelites[i].azim);
		mvwprintw(visualWindow, 2 + (i * 3), 1, "SNR:\t%s\t\tUsed:\t\t%s", satelites[i].ss, satelites[i].used);
	}
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: showError
--
-- DATE: November 8th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jaegar Sarauer
--
-- PROGRAMMER: Jaegar Sarauer
--
-- INTERFACE:   showError(char err[])
--		char err[] : The message to show in the errorWindow.
--
-- RETURNS: VOID
--
-- NOTES: This function draws a single error string to the errorWindow, at the bottom of the screen.
----------------------------------------------------------------------------------------------------------------------*/
void showError(char err[]) {
	updateWindows();
	wclear(errorWindow);
	int i, width, height;
	getmaxyx(stdscr, height, width);
	mvwprintw(errorWindow, 1, 1, "%s", err);
	box(errorWindow, 0, 0);
	wrefresh(errorWindow);
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: updateWindows
--
-- DATE: November 8th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jaegar Sarauer
--
-- PROGRAMMER: Jaegar Sarauer
--
-- INTERFACE: updateWindows()
--
-- RETURNS: VOID
--
-- NOTES: This function updates the borders of the windows on the screen. The update is used after a draw so that the 
--	borders will still be shown.
----------------------------------------------------------------------------------------------------------------------*/
void updateWindows() {
	box(visualWindow, 0, 0);
	box(rawDataWindow, 0, 0);
	wrefresh(visualWindow);
	wrefresh(rawDataWindow);
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: resizeWindows
--
-- DATE: November 8th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jaegar Sarauer
--
-- PROGRAMMER: Jaegar Sarauer
--
-- INTERFACE: resizeWindows()
--
--
-- RETURNS: VOID
--
-- NOTES: This function updates all windows to their new width, height, and allignment on the screen when the window is
-- 	updated/resized. Redraws all windows after resize.
----------------------------------------------------------------------------------------------------------------------*/
void resizeWindows() {	
	int screenHeight, screenWidth;
	getmaxyx(stdscr, screenHeight, screenWidth);
	wresize(visualWindow, screenHeight - 9, screenWidth);
	wresize(rawDataWindow, 6, screenWidth);
	wresize(errorWindow, 3, screenWidth);
	mvwin(rawDataWindow, screenHeight - 9, 0);
	mvwin(errorWindow, screenHeight - 3, 0);
	wclear(stdscr);
	wclear(visualWindow);
	wclear(rawDataWindow);
	box(visualWindow, 0, 0);
	box(rawDataWindow, 0, 0);
	wrefresh(visualWindow);
	wrefresh(rawDataWindow);
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: createWindow
--
-- DATE: November 8th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jaegar Sarauer
--
-- PROGRAMMER: Jaegar Sarauer
--
-- INTERFACE: createWindow(int height, int width, int xx, int yy)
--	- int height : Height of the new window.
--	- int width  : Width of the new window.
--	- int xx     : Starting X position of the new window.
--	- int yy     : Starting Y position of the new window.
--
-- RETURNS: WINDOW* : A pointer to a new window.
--
-- NOTES: This function creates a new window with specific width/height and the starting position of the screen, 
--	relative to the main window, stdscr. This function will create a new window, and return the pointer, to be
--	held for reference.
--
--
----------------------------------------------------------------------------------------------------------------------*/
WINDOW* createWindow(int height, int width, int xx, int yy) {
	WINDOW *local;
	local = newwin(height, width, xx, yy);
	box(local, 0, 0);
	wrefresh(local);
	return local;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: build_curses
--
-- DATE: November 8th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jaegar Sarauer
--
-- PROGRAMMER: Jaegar Sarauer
--
-- INTERFACE: build_curses()
--
-- RETURNS: VOID
--
-- NOTES: This function constructs all windows for the GUI. The windows are stored as global as they ust be accessed by
--	several functions in order to update, draw, destroy and resize. This function must be called in order for the
--	GUI to be initialized, work properly, and allow use of the other functions in this file.
----------------------------------------------------------------------------------------------------------------------*/
void build_curses() {

	WINDOW *mainwin;
	int screenHeight, screenWidth;
	//initializeSats();


	if ( (mainwin = initscr()) == NULL) {
	fprintf(stderr, "Error initialising ncurses.\n");
	exit(EXIT_FAILURE);
	}

	getmaxyx(stdscr, screenHeight, screenWidth);

	visualWindow = createWindow(screenHeight - 9, screenWidth, 0, 0);
	rawDataWindow = createWindow(9, screenWidth, screenHeight - 9, 0);
	errorWindow = createWindow(3, screenWidth, screenHeight - 3, 0);

}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: kill_curses
--
-- DATE: November 8th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jaegar Sarauer
--
-- PROGRAMMER: Jaegar Sarauer
--
-- INTERFACE: kill_curses()
--
--
-- RETURNS: VOID
--
-- NOTES: This function is called when the program is terminated, either by the user, or by timeouts or the inability to
--	connect to a device. It destroys the windows from referece and ends the ncurses program.
----------------------------------------------------------------------------------------------------------------------*/
void kill_curses() {
	delwin(mainwin);
	delwin(visualWindow);
	delwin(rawDataWindow);
	delwin(errorWindow);
	endwin();
	refresh();
}
