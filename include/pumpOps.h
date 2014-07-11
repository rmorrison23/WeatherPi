/*******************************************************************/
/* pumpOps.h                                                       */
/*******************************************************************/
/* Author: Ryan M. Morrison                                        */
/* Date:   May 2014												   */
/*                                                                 */
/* Note: this header file contains function prototypes for         */
/*       pumpOps.c                                                 */
/*******************************************************************/

#ifndef PUMPOPS_H
#define PUMPOPS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "cimisData.h"
#include "lcd.h"
#include "wiringPi.h"
#include "constants.h"

/* compute gallons-per-day needed for irrigation */
float computeGPD(void);

/* compute daily time needed to irrigate */
float computeIrrTime(void);

/* compute intervals for pump turn-on */
int scheduleIrrigate(void);

/* control pump on/of states */
void checkPumpStatus(void);

#endif