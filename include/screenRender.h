/*******************************************************************/
/* screenRender.h                                                  */
/*******************************************************************/
/* Author: Ryan M. Morrison                                        */
/* Date:   May 2014												   */
/*                                                                 */
/* Note: this header file contains function prototypes for         */
/*       screenRender.c                                            */
/*******************************************************************/

#ifndef SCREENRENDER_H
#define SCREENRENDER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <unistd.h>
#include <string.h>
#include <time.h>

#include <wiringPi.h>
#include <lcd.h>
#include "sensorData.h"
#include "constants.h"

#ifndef	TRUE
#  define	TRUE	(1==1)
#  define	FALSE	(1==2)
#endif


/* display home screen on LCD (time and date) */
void drawHomeScreen(int lcdHandle, int refreshRate);

/* display temperature screen on LCD (high, low, current) */
void drawTempScreen(int lcdHandle, int refreshRate);

/* display wind conditions, precipitation on LCD */
void drawSkyScreen(int lcdHandle, int refreshRate);

/* display irrigation data on LCD (gpd, tpd, on/off) */
void drawIrrigateScreen(int lcdHandle, int refreshRate);

/* display full sun on LCD */
void drawSun(int lcdHandle);

/* display 1/2 sun on LCD */
void drawCloudySun(int lcdHandle);

/* display rainy cloud on LCD */
void drawRain(int lcdHandle);

/* display cloud on LCD */
void drawCloud(int lcdHandle);

/* display 8-direction arrow for wind */
void drawDirection(int lcdHandle);

#endif