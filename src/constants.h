/************************************************************************/
/* constants.h                                                     		*/
/************************************************************************/
/* Author: Ryan M. Morrison                                        		*/
/* Date:   May 2014												   		*/
/*                                                                 		*/
/* Note: this header file contains constants for RPI pins, irrigation   */
/*       values, average filter, temp. conversion                       */
/************************************************************************/

#ifndef CONSTANTS_H
#define CONSTANTS_H

/* RPI pins */
#define SPICLK   0
#define SPIMISO  1
#define SPIMOSI  2
#define SPICS    3

#define RED_LED   6
#define GREEN_LED 7
#define BUTTON    8

/* irrigation values */
#define PF 		1 		/* plant factor */
#define IE 	   .75  	/* irrigation efficiency */
#define SF 		8150 	/* square foot area of irrigated grass */
#define PA 		2900 	/* gallons per hour capacity of pump */
#define FREQ 	10 		/* interval in minutes for irrigation */

/* avg. filter */
#define SAMPLES  50

#define THERMNOMINAL 	10000		/* nominal thermistor value */
#define THERMTEMPNOM 	25			/* nominal constant */
#define BCOEFFICIENT 	3950		/* coeffecient */
#define PULLUPDOWN 	 	10000		/* pulldown resistor value */
#define TIMEOUT 	 	999

#endif