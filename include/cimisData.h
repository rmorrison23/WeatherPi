/*******************************************************************/
/* cimisData.h                                                     */
/*******************************************************************/
/* Author: Ryan M. Morrison                                        */
/* Date:   May 2014												   */
/*                                                                 */
/* Note: this header file contains function prototypes for         */
/*       cimisData.c                                               */
/*******************************************************************/


#ifndef CIMISDATA_H
#define CIMISDATA_H

#include <stdio.h>
#include <stdlib.h>
#include "timeUtils.h"


/* structure for line-read of CIMIS daily data */
struct R{
    int num1, num2, num3, num4, num5, num6 , num14 , num15, num17;
    float num7, num8, num9, num10, num11, num12, num13, num16, num18, num19;
};
typedef struct R R;

/* structure for line-read of CIMIS hourly data */
struct Hour{
	int num1, num2, num3, num4, num5, num6, num9, num12;
	float num7, num8, num10, num11, num13, num14, num15, num16;
	char sentinel;
};
typedef struct Hour Hour;

/* fetch and download CIMIS hourly report */
void getHourlyData(void);

/* fetch and download CIMIS daily report */
void getDailyData(void);

/* check if hourly and/or daily CIMIS data needs to be updated */
void checkForUpdates(int *prevHour);

/* get hourly temperature from CIMIS */
float getTemp(void);

/* calculate predicted high temp. from avg. of CIMIS 7-day highs */
float getHighTemp(void);

/* calculate predicted low temp. from avg. of CIMIS 7-day lows */
float getLowTemp(void);

/* get hourly wind direction from CIMIS */
float getWindDirection(void);

/* get hourly precipitation from CIMIS */
float getRain(void);

/* get hourly wind speed from CIMIS */
float getWindSpeed(void);

/* get daily ETO value from CIMIS */
float getDailyETO(void);

/* read desired line of CIMIS daily data */
int readLine(char *fileName, int line, R *r);

/* read desired line of CIMIS hourly data */
int readHour(char *filename, Hour *hourly);

/* debug printing */
int printLine(R *r);

#endif
