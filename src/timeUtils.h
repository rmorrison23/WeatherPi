/*******************************************************************/
/* timeUtils.h                                                     */
/*******************************************************************/
/* Author: Ryan M. Morrison                                        */
/* Date:   May 2014												   */
/*                                                                 */
/* Note: this header file contains function prototypes for         */
/*       timeUtils.c                                               */
/*******************************************************************/

#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <unistd.h>
#include <string.h>
#include <time.h>

/* returns system hour */
int getSysHour(void);

/* returns system minutes */
int getSysMin(void);

/* returns month/day/year */
const char *getDate();

/* returns hour:minutes */
const char *getTime();

#endif