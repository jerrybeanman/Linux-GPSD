#ifndef GPSPRINT_H
#define GPSPRINT_H
#define DATA_SIZE	512
#include "globals.h"  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>    
#include <curses.h>         
#include <ncurses.h>
#include <gps.h>




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
void updateWindows();


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
void resizeWindows();


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
void showError(char err[]);


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
void drawRawData();


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
void drawVisualData();


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
void updateInformation(struct gps_data_t *d);



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
WINDOW* createWindow(int height, int width, int xx, int yy);


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
void build_curses();



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
void kill_curses();
#endif








