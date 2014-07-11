/*******************************************************************/
/* pumpOps.c                                                       */
/*******************************************************************/
/* Author: Ryan M. Morrison                                        */
/* Date:   May 2014                                                */
/*                                                                 */
/* Note: this source file contains functions related to irrigation */
/*******************************************************************/

#include "pumpOps.h"

float computeGPD(void){
	float eto = getDailyETO();
	float gpd = (eto * 1 * SF * 0.62) / IE;
	return gpd;
}

float computeIrrTime(void){
	float ratio = (computeGPD() / PA) / 24;
	float irrTime = 100 * ratio;
	return irrTime;
}

int scheduleIrrigate(void){
	float irrInterval = (computeIrrTime() * 10 * 60);
	int irrPeriod = FREQ * 60; 
	int irrCounter = irrPeriod - irrInterval;
	return irrCounter;
}

void checkPumpStatus(void){
	int irrInterval = (int)ceil(computeIrrTime() / 10 * 60);	
	struct tm *t ;
    time_t tim ;
    tim = time (NULL) ;
    t = localtime (&tim) ;

    if(t->tm_min % 10 == 0 && t->tm_sec <= irrInterval){
    	digitalWrite(GREEN_LED, HIGH);
    	digitalWrite(RED_LED, LOW);
    }
    else{
    	digitalWrite(GREEN_LED, LOW);
    	digitalWrite(RED_LED, HIGH);
    }
}