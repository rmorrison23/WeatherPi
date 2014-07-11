/*******************************************************************/
/* timeUtils.c                                                     */
/*******************************************************************/
/* Author: Ryan M. Morrison                                        */
/* Date:   May 2014                                                */
/*                                                                 */
/* Note: this source file contains functions to get and display    */
/*       time-related data										   */
/*******************************************************************/

#include "timeUtils.h"


 int getSysHour(void){
    struct tm *t ;
    time_t tim ;
    tim = time (NULL) ;
    t = localtime (&tim) ;  
    return t->tm_hour; 
 }

 int getSysMin(void){
    struct tm *t ;
    time_t tim ;
    tim = time (NULL) ;
    t = localtime (&tim) ;  
    return t->tm_min;     
 }

const char *getDate(){

	static const char *month [12] = { "Jan.", "Feb.", "Mar.", "Apr.", "May", "Jun.", "Jul.", "Aug.", "Sep.", "Oct.", "Nov.", "Dec." };
	struct tm *t ;
	time_t tim ;

	static char timeBuf [32];
	tim = time (NULL) ;
	t = localtime (&tim) ;
	sprintf (timeBuf, "%s%2d, %4d", month[t->tm_mon], t->tm_mday, t->tm_year+1900);
	return timeBuf;
}

const char *getTime(){
	
	struct tm *t ;
	time_t tim ;

	static char timeBuf [32];
	tim = time (NULL) ;
	t = localtime (&tim) ;
	if (t->tm_hour >= 12)
	{ 
		t->tm_hour -= 12;
		if (t->tm_hour == 0)
			t->tm_hour += 12;
		sprintf (timeBuf, "%2d:%02d PM", t->tm_hour, t->tm_min);
	}
	else
    sprintf (timeBuf, "%2d:%02d AM", t->tm_hour, t->tm_min) ;  
	    
	return timeBuf;
}