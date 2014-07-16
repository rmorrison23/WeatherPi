/*******************************************************************/
/* main.c                                                          */
/*******************************************************************/
/* Author: Ryan M. Morrison                                        */
/* Date:   May 2014                                                */
/*																   */
/* Note: see constants.h for GPIO connections      				   */
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <unistd.h>
#include <string.h>
#include <time.h>

#include <wiringPi.h>
#include <lcd.h>
#include "screenRender.h"
#include "sensorData.h"
#include "cimisData.h"
#include "timeUtils.h"
#include "pumpOps.h"

#ifndef	TRUE
#  define	TRUE	(1==1)
#  define	FALSE	(1==2)
#endif

static int lcdHandle ;

int main (void){

	/* fetch daily/hourly data from CIMIS */
	/*getDailyData();
	getHourlyData();*/

	printf ("  Internet-Enabled Weather Reporting Device\n") ;
	printf ("=============================================\n\n") ;

	/* setup RPI and LCD */
	wiringPiSetup ();
	pinMode(GREEN_LED, OUTPUT);
	pinMode(RED_LED, OUTPUT);
	pinMode(BUTTON, INPUT);
	pinMode(SPIMOSI, OUTPUT);
	pinMode(SPIMISO, INPUT);
	pinMode(SPICLK, OUTPUT);
	pinMode(SPICS, OUTPUT);
	lcdHandle = lcdInit (2, 16, 4, 11,10, 4,5,15,16,0,0,0,0);
	lcdClear(lcdHandle);
	
	/*int *initHour; 
	int hour = getSysHour();
	initHour = &hour;*/

	while(1){
			/*hour = getSysHour();
			//checkPumpStatus();
			//checkForUpdates(initHour = &hour);
			//drawHomeScreen(lcdHandle, 5);
			//delay(250);
 			//drawTempScreen(lcdHandle, 5);
 			//delay(250);
 			//drawSkyScreen(lcdHandle, 5);
 			//delay(250);
 			//drawIrrigateScreen(lcdHandle, 5);	
 			//delay(250);		
 			checkPumpStatus();*/	
			drawSun(lcdHandle);
			/*drawCloud(lcdHandle);*/
			/*drawCloudySun(lcdHandle);*/
			/*drawRain(lcdHandle);*/
			
	}
	lcdClear(lcdHandle);
	return 0 ;
}
