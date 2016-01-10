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
void updateWindows();
void resizeWindows();
void showError(char err[]);
void print_gps(struct gps_data_t *gpsdata);
void drawRawData();
void drawVisualData();
void initializeSats();
void updateInformation(struct gps_data_t *d);
WINDOW* createWindow(int height, int width, int xx, int yy);
void build_curses();
void kill_curses();
#endif
