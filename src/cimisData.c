/*******************************************************************/
/* cimisData.c                                                     */
/*******************************************************************/
/* Author: Ryan M. Morrison                                        */
/* Date:   May 2014                                                */
/*                                                                 */
/* Note: this source file contains function definitions related to */
/*       fetching and interpreting data from the CIMIS weather-    */
/*       -reporting website.                                       */
/*******************************************************************/


#include "cimisData.h"
#include <stdio.h>
#include <time.h>


void checkForUpdates(int *prevHour){
    int currHour = getSysHour();
    if(currHour > *prevHour){
        getHourlyData();
        prevHour += 1;
    }
    if(currHour == 1){
        getHourlyData();
        getDailyData();
        prevHour = &currHour;
    }
    if(currHour == 12){
        getDailyData();
    }
}

 void getDailyData(void){
    system("rm daily075.csv");
    system("wget ftp://ftpcimis.water.ca.gov/pub/daily/daily075.csv");
 }

 void getHourlyData(void){
    system("rm hourly075.csv");
    system("wget ftp://ftpcimis.water.ca.gov/pub/hourly/hourly075.csv");
 }

 float getTemp(void){
    float temp;
    Hour hourly;
    readHour("hourly075.csv", &hourly);
    temp = hourly.num15;
    return temp;   
 }

 float getHighTemp(void){
    float average;
    int i;
    R read;
    average = 0.0;
    for(i = 1; i < 8; i++){
        readLine("daily075.csv", i, &read);
        average += read.num8;
    }
    average /= 7.0;
    return average;
 }

 float getLowTemp(void){
    float average;
    int i;
    R read;
    average = 0.0;
    for(i = 1; i < 8; i++){
        readLine("daily075.csv", i, &read);
        average += read.num9;
    }
    average /= 7.0;
    return average;
 }

 float getWindDirection(void){
    float direction;
    Hour hourly;
    readHour("hourly075.csv", &hourly);
    direction = hourly.num15;
    return direction;
 }

float getRain(void){
    float rain;
    Hour hourly;
    readHour("hourly075.csv", &hourly);
    rain = hourly.num8;
    return rain;
}

float getWindSpeed(void){
    float windSpeed;
    Hour hourly;
    readHour("hourly075.csv", &hourly);
    windSpeed = hourly.num14;
    return windSpeed;    
}

float getDailyETO(void){
    float eto;
    R daily;
    readLine("daily075.csv", 7, &daily);
    eto = daily.num16;
    return eto;
}

int readLine(char *fileName, int line, R *r){
    int i;
    FILE * file;
    file = fopen( fileName , "r");
    if (file) {
        for(i = 0 ; i< line ; i++){
            if (fscanf(file, "%d,%d/%d/%d,%d,*,      %d,*,     %f,*,     %f,*,     %f,*,     %f,*,     %f,*,      %f,*,     %f,*,       %d,*,       %d,*,     %f,*,       %d,*,     %f,*,    %f", &r->num1, &r->num2, &r->num3, &r->num4, &r->num5, &r->num6, &r->num7, &r->num8, &r->num9, &r->num10, &r->num11, &r->num12, &r->num13, &r->num14, &r->num15, &r->num16, &r->num17, &r->num18, &r->num19))
                /*printf("%d,%d/%d/%d,%d,*,      %d,*,     %f,*,     %f,*,     %f,*,     %f,*,     %f,*,      %f,*,     %f,*,       %d,*,       %d,*,     %f,*,       %d,*,     %f,*,    %f\n", r->num1, r->num2, r->num3, r->num4, r->num5, r->num6, r->num7, r->num8, r->num9, r->num10, r->num11, r->num12, r->num13, r->num14, r->num15, r->num16, r->num17, r->num18, r->num19)*/
                ;
        }
        fclose(file);
    }
    else
        return 0;
    
    
    return 1;
}

int readHour(char *filename, Hour *hourly){
   int i;
   /* struct tm *t ;
    time_t tim ;
    tim = time (NULL) ;
    t = localtime (&tim) ;*/

    FILE * file;
    file = fopen(filename, "r");
    if(file){
        for(i = 0 ; i < 192 ; i++){
            
            if(fscanf(file, "%d,%d/%d/%d,%d,%d,%c,     %f,%c,     %f,%c,     %d,%c,     %f,%c,     %f,%c,      %d,%c,     %f,%c,       %f,%c,       %f,%c,     %f", &hourly->num1, &hourly->num2, &hourly->num3, &hourly->num4, &hourly->num5, &hourly->num6, &hourly->sentinel, &hourly->num7, &hourly->sentinel, &hourly->num8, &hourly->sentinel, &hourly->num9, &hourly->sentinel, &hourly->num10, &hourly->sentinel, &hourly->num11, &hourly->sentinel, &hourly->num12, &hourly->sentinel, &hourly->num13, &hourly->sentinel, &hourly->num14, &hourly->sentinel, &hourly->num15, &hourly->sentinel, &hourly->num16));   
            if(hourly->sentinel == 0x4d){
                break;
            }
        } 
        fclose(file);      
    }
    else
        return 0;

    return 1;
}

int printLine(R *r){
    printf("%d,%d/%d/%d,%d,*,      %d,*,     %f,*,     %f,*,     %f,*,     %f,*,     %f,*,      %f,*,     %f,*,       %d,*,       %d,*,     %f,*,       %d,*,     %f,*,    %f\n", r->num1, r->num2, r->num3, r->num4, r->num5, r->num6, r->num7, r->num8, r->num9, r->num10, r->num11, r->num12, r->num13, r->num14, r->num15, r->num16, r->num17, r->num18, r->num19);
    return 1;
}



