/*******************************************************************/
/* sensorData.h                                                    */
/*******************************************************************/
/* Author: Ryan M. Morrison                                        */
/* Date:   May 2014												   */
/*                                                                 */
/* Note: this header file contains function prototypes for         */
/*       sensorData.c                                              */
/*******************************************************************/

#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <errno.h>
#include <math.h>
#include <wiringPi.h>
#include <lcd.h>
#include "constants.h"

/* returns temperature in degrees F */
float ReadTherm(void);

/* return ADC reading */
int readadc(int adcnum, int clockpin, int mosipin, int misopin, int cspin);

/* averaging filter */
float adcAverage(int samples, int adcPortNum);

/* convert thermistor reading into temperature */
float handleTherm(float average);

#endif