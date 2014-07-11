/*******************************************************************/
/* screenRender.c                                                  */
/*******************************************************************/
/* Author: Ryan M. Morrison                                        */
/* Date:   May 2014                                                */
/*                                                                 */
/* Note: this source file contains functions for displaying data   */
/*       on the LCD                                                */
/*******************************************************************/

#include "screenRender.h"
#include "sensorData.h"
#include "cimisData.h"
#include "pumpOps.h"

static unsigned char therm1 [8] = { 0b00001, 0b00010, 0b00010, 0b00010, 0b00010, 0b00011, 0b00011, 0b00011 };
static unsigned char therm2 [8] = { 0b10000, 0b01000, 0b01001, 0b01010, 0b01010, 0b11001, 0b11000, 0b11000 };
static unsigned char therm3 [8] = { 0b00000, 0b00000, 0b10000, 0b01000, 0b01000, 0b10000, 0b01111, 0b01000 };
static unsigned char therm4 [8] = { 0b00011, 0b00011, 0b00111, 0b01111, 0b01111, 0b01111, 0b00111, 0b00011 };
static unsigned char therm5 [8] = { 0b11000, 0b11000, 0b11100, 0b11110, 0b11110, 0b11110, 0b11100, 0b11000 };
static unsigned char therm6 [8] = { 0b01110, 0b01000, 0b01000, 0b01000, 0b00000, 0b00000, 0b00000, 0b00000 };

static unsigned char sun1 [8] = { 0b00000, 0b00000, 0b00000, 0b00100, 0b00010, 0b00001, 0b00001, 0b11110 };
static unsigned char sun2 [8] = { 0b00100, 0b00100, 0b00100, 0b00100, 0b01110, 0b10001, 0b00000, 0b00000 };
static unsigned char sun3 [8] = { 0b00000, 0b00000, 0b00000, 0b00100, 0b01000, 0b10000, 0b10000, 0b01111 };
static unsigned char sun4 [8] = { 0b00010, 0b00001, 0b00001, 0b00010, 0b00100, 0b00000, 0b00000, 0b00000 };
static unsigned char sun5 [8] = { 0b00000, 0b00000, 0b10001, 0b01110, 0b00100, 0b00100, 0b00100, 0b00100 };
static unsigned char sun6 [8] = { 0b01000, 0b10000, 0b10000, 0b01000, 0b00100, 0b00000, 0b00000, 0b00000 };

static unsigned char cloud1 [8] = { 0b00000, 0b00000, 0b00001, 0b00010, 0b00100, 0b01000, 0b01000, 0b01100 };
static unsigned char cloud2 [8] = { 0b00000, 0b00000, 0b11000, 0b01100, 0b00011, 0b01100, 0b01000, 0b11000 };
static unsigned char cloud3 [8] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b11000, 0b00100, 0b00100, 0b00010 };
static unsigned char cloud4 [8] = { 0b00100, 0b01110, 0b10000, 0b10000, 0b01100, 0b00011, 0b00000, 0b00000 };
static unsigned char cloud5 [8] = { 0b00000, 0b00000, 0b00000, 0b00100, 0b00110, 0b11111, 0b00000, 0b00000 };
static unsigned char cloud6 [8] = { 0b00001, 0b00001, 0b00001, 0b00010, 0b00100, 0b11000, 0b00000, 0b00000 };

/*character set for sun with cloud icon*/
static unsigned char sunCloud1 [8] = { 0b01000, 0b00100, 0b00100, 0b00010, 0b10000, 0b01001, 0b00010, 0b00100 };
static unsigned char sunCloud2 [8] = { 0b10001, 0b10010, 0b10010, 0b00100, 0b00001, 0b11000, 0b01100, 0b00011 };
static unsigned char sunCloud3 [8] = { 0b00000, 0b00100, 0b01000, 0b10000, 0b00010, 0b00100, 0b00000, 0b00000 };
static unsigned char sunCloud4 [8] = { 0b01000, 0b01000, 0b01100, 0b00100, 0b01110, 0b10000, 0b10000, 0b01111 };
static unsigned char sunCloud5 [8] = { 0b00110, 0b01000, 0b01100, 0b00000, 0b00000, 0b00000, 0b01000, 0b11111 };
static unsigned char sunCloud6 [8] = { 0b10000, 0b01100, 0b00010, 0b00001, 0b00001, 0b00001, 0b00010, 0b11100 };

/*character set for cloud with rain icon*/
static unsigned char rainCloud1 [8] = { 0b00001, 0b00010, 0b00100, 0b01000, 0b01000, 0b01100, 0b00100, 0b01100 };
static unsigned char rainCloud2 [8] = { 0b11000, 0b01100, 0b00011, 0b00110, 0b00100, 0b01100, 0b00000, 0b00000 };
static unsigned char rainCloud3 [8] = { 0b00000, 0b00000, 0b11000, 0b00100, 0b00100, 0b00010, 0b00001, 0b00001 };
static unsigned char rainCloud4 [8] = { 0b10000, 0b10000, 0b01100, 0b00011, 0b00100, 0b10010, 0b01001, 0b00100 };
static unsigned char rainCloud5 [8] = { 0b00000, 0b00100, 0b01111, 0b11100, 0b00010, 0b10001, 0b01000, 0b00100 };
static unsigned char rainCloud6 [8] = { 0b00010, 0b01100, 0b11000, 0b00010, 0b01001, 0b00100, 0b10010, 0b01001 };

static unsigned char north [8] = { 0b00100, 0b01110, 0b10101, 0b00100, 0b00100, 0b00100, 0b00100, 0b00000 };
static unsigned char south [8] = { 0b00000, 0b00100, 0b00100, 0b00100, 0b00100, 0b10101, 0b01110, 0b00100 };
static unsigned char east [8] = { 0b00000, 0b00100, 0b00010, 0b11111, 0b00010, 0b00100, 0b00000, 0b00000 };
static unsigned char west [8] = { 0b00000, 0b00100, 0b01000, 0b11111, 0b01000, 0b00100, 0b00000, 0b00000 };
static unsigned char northEast [8] = { 0b00000, 0b01111, 0b00011, 0b00101, 0b01001, 0b10000, 0b00000, 0b00000 };
static unsigned char northWest [8] = { 0b00000, 0b11110, 0b11000, 0b10100, 0b10010, 0b00001, 0b00000, 0b00000 };
static unsigned char southEast [8] = { 0b00000, 0b10000, 0b01001, 0b00101, 0b00011, 0b01111, 0b00000, 0b00000 };
static unsigned char southWest [8] = { 0b00000, 0b00001, 0b10010, 0b10100, 0b11000, 0b11110, 0b00000, 0b00000 };

static unsigned char deg [8] = { 0b01100, 0b10010, 0b010010, 0b01100, 0b00000, 0b00000, 0b00000, 0b00000 };

static unsigned char drop [8] = { 0b00000, 0b00100, 0b00100, 0b01110, 0b11111, 0b11111, 0b11111, 0b01110 };

static const char *month [12] = { "Jan.", "Feb.", "Mar.", "Apr.", "May", "Jun.", "Jul.", "Aug.", "Sep.", "Oct.", "Nov.", "Dec." };

void drawHomeScreen(int lcdHandle, int refreshRate){

  lcdClear (lcdHandle) ;

  struct tm *t ;
  time_t tim ;
  char timeBuf [32];
  int i, del;
  del = 1000;

  for(i = 0; i < refreshRate; i++){

    checkPumpStatus();

    if(digitalRead(BUTTON) == LOW){ 
      lcdClear(lcdHandle);
      del = 0;
      delay(1);
      break; 
    }
  
    tim = time (NULL) ;
    t = localtime (&tim) ;

    lcdPosition (lcdHandle, 2, 0) ;
    lcdPuts (lcdHandle, month[t->tm_mon]);
    sprintf (timeBuf, "%2d, %4d", t->tm_mday, t->tm_year+1900);
    lcdPuts (lcdHandle, timeBuf);


    if (t->tm_hour >= 12){ 
      t->tm_hour -= 12;
      if (t->tm_hour == 0){ t->tm_hour += 12;} 
      sprintf (timeBuf, "%2d:%02d:%02d PM", t->tm_hour, t->tm_min, t->tm_sec);
    }
    else{
      sprintf (timeBuf, "%2d:%02d:%02d AM", t->tm_hour, t->tm_min, t->tm_sec) ;  
    }       
  
    lcdPosition (lcdHandle, 2, 1) ;
    lcdPuts     (lcdHandle, timeBuf) ;

    delay(del);

    if(digitalRead(BUTTON) == LOW){ 
      lcdClear(lcdHandle);
      del = 0;
      delay(1);
      break; 
    }
  }
}

void drawTempScreen(int lcdHandle, int refreshRate){

  lcdClear (lcdHandle) ;
  char stringBuffer[32];
  float adcRead;
  int i, del;
  del = 1000;

  lcdCharDef  (lcdHandle, 1, therm1);
  lcdCharDef  (lcdHandle, 2, therm2);
  lcdCharDef  (lcdHandle, 3, therm3);
  lcdCharDef  (lcdHandle, 4, therm4);
  lcdCharDef  (lcdHandle, 5, therm5);
  lcdCharDef  (lcdHandle, 6, therm6); 
  lcdCharDef  (lcdHandle, 7, deg);

  lcdPosition (lcdHandle, 0, 0) ;
  lcdPutchar  (lcdHandle, 1) ;
  lcdPutchar  (lcdHandle, 2) ;
  lcdPutchar  (lcdHandle, 3) ; 

  lcdPuts (lcdHandle, "Curr High Low");

  lcdPosition (lcdHandle, 0, 1) ;
  lcdPutchar  (lcdHandle, 4) ;
  lcdPutchar  (lcdHandle, 5) ;
  lcdPutchar  (lcdHandle, 6) ;

  lcdPosition (lcdHandle, 6, 1) ;
  lcdPutchar  (lcdHandle, 7);     

  lcdPosition (lcdHandle, 8, 1) ;
  sprintf(stringBuffer, "%3.0f", getHighTemp());
  lcdPuts (lcdHandle, stringBuffer); 
  lcdPosition (lcdHandle, 11, 1) ;
  lcdPutchar  (lcdHandle, 7);

  lcdPosition (lcdHandle, 12, 1) ;
  sprintf(stringBuffer, "%3.0f", getLowTemp());
  lcdPuts (lcdHandle, stringBuffer); 
  lcdPosition (lcdHandle, 15, 1) ;
  lcdPutchar  (lcdHandle, 7);

  for(i = 0; i < refreshRate; i++){

    checkPumpStatus();

    adcRead = ReadTherm();

    if(digitalRead(BUTTON) == LOW){ 
      lcdClear(lcdHandle);
      del = 0;
      delay(1);
      break; 
    }

    lcdPosition(lcdHandle, 3, 1);
    sprintf(stringBuffer, "%3.0f", adcRead);
    lcdPuts (lcdHandle, stringBuffer);

    delay(del);

    if(digitalRead(BUTTON) == LOW){ 
      lcdClear(lcdHandle);
      del = 0;
      delay(1);
      break;
    }
  }
}

void drawSkyScreen(int lcdHandle, int refreshRate){

  lcdClear (lcdHandle) ;
  char stringBuffer[32];
  int temp, rain, i, del;
  temp = getTemp();
  rain = getRain();
  del = 1000;
  
  lcdPosition (lcdHandle, 0, 0);
  lcdPuts(lcdHandle, "Wind");
  lcdPosition (lcdHandle, 11, 0);
  lcdPuts (lcdHandle, "Rain");
  lcdPosition(lcdHandle, 3, 1);
  lcdPuts(lcdHandle, "mph");
  lcdPosition (lcdHandle, 14, 1);
  lcdPuts (lcdHandle, "in"); 
  
  lcdPosition(lcdHandle, 0, 1);
  sprintf(stringBuffer, "%2.1f", getWindSpeed());
  lcdPuts (lcdHandle, stringBuffer);

  lcdPosition(lcdHandle, 11, 1);  
  sprintf(stringBuffer, "%2.1f", getRain());
  lcdPuts (lcdHandle, stringBuffer);  
  
  if(temp > 80.0){ drawSun(lcdHandle); }
  if(temp < 80.0 && temp > 68.0){ drawCloudySun(lcdHandle); }
  if(temp < 68.0){ drawCloud(lcdHandle); }
  if(rain > 0.5){ drawRain(lcdHandle); }

  drawDirection(lcdHandle);
  for(i = 0; i < refreshRate; i++){ 
    checkPumpStatus();
    if(digitalRead(BUTTON) == LOW){ 
      lcdClear(lcdHandle);
      del = 0;
      delay(1);
      break;
    }
    delay(del);
  }
}

void drawIrrigateScreen(int lcdHandle, int refreshRate){

  lcdClear (lcdHandle) ;

  int i, del;
  char stringBuffer[32];

  del = 1000;

  lcdCharDef(lcdHandle, 1, drop);
  lcdPosition(lcdHandle, 0, 0);
  lcdPutchar(lcdHandle, 1);
  lcdPosition(lcdHandle, 0, 1);
  lcdPutchar(lcdHandle, 1);

  lcdPosition (lcdHandle, 2, 0);
  lcdPuts(lcdHandle, "Gpd: ");
  sprintf(stringBuffer, "%4.0f", computeGPD());
  lcdPuts(lcdHandle, stringBuffer);  

  lcdPosition(lcdHandle, 2, 1);
  lcdPuts(lcdHandle, "Tpd: ");
  sprintf(stringBuffer, "%3.1f", computeIrrTime());
  lcdPuts(lcdHandle, stringBuffer);  
  lcdPuts(lcdHandle, "\%");

  lcdPosition(lcdHandle, 12, 0);
  lcdPuts(lcdHandle, "Pump");

  for(i = 0; i < refreshRate; i++){

    if(digitalRead(BUTTON) == LOW){ 
      lcdClear(lcdHandle);
      del = 0;
      delay(1);
      break;
    }

    if(digitalRead(GREEN_LED) == HIGH){
      lcdPosition(lcdHandle, 14, 1);
      lcdPuts(lcdHandle, "ON");
    }
    else{
      lcdPosition(lcdHandle, 13, 1);
      lcdPuts(lcdHandle, "OFF"); 
    }
    checkPumpStatus(); 
    delay(del);   
  }
}

void drawSun(int lcdHandle){
         
    lcdCharDef  (lcdHandle, 1, sun1);
    lcdCharDef  (lcdHandle, 2, sun2);
    lcdCharDef  (lcdHandle, 3, sun3);
    lcdCharDef  (lcdHandle, 4, sun4);
    lcdCharDef  (lcdHandle, 5, sun5);
    lcdCharDef  (lcdHandle, 6, sun6); 
    
    lcdPosition (lcdHandle, 7, 0) ;
    lcdPutchar  (lcdHandle, 1) ;
    lcdPutchar  (lcdHandle, 2) ;
    lcdPutchar  (lcdHandle, 3) ; 
    
    lcdPosition (lcdHandle, 7, 1) ;
    lcdPutchar  (lcdHandle, 4) ;
    lcdPutchar  (lcdHandle, 5) ;
    lcdPutchar  (lcdHandle, 6) ;
}

void drawCloud(int lcdHandle){

    lcdCharDef  (lcdHandle, 1, cloud1);
    lcdCharDef  (lcdHandle, 2, cloud2);
    lcdCharDef  (lcdHandle, 3, cloud3);
    lcdCharDef  (lcdHandle, 4, cloud4);
    lcdCharDef  (lcdHandle, 5, cloud5);
    lcdCharDef  (lcdHandle, 6, cloud6); 
    
    lcdPosition (lcdHandle, 7, 0) ;
    lcdPutchar  (lcdHandle, 1) ;
    lcdPutchar  (lcdHandle, 2) ;
    lcdPutchar  (lcdHandle, 3) ; 
        
    lcdPosition (lcdHandle, 7, 1) ;
    lcdPutchar  (lcdHandle, 4) ;
    lcdPutchar  (lcdHandle, 5) ;
    lcdPutchar  (lcdHandle, 6) ;
}

void drawCloudySun(int lcdHandle){
         
  lcdCharDef  (lcdHandle, 1, sunCloud1);
  lcdCharDef  (lcdHandle, 2, sunCloud2);
  lcdCharDef  (lcdHandle, 3, sunCloud3);
  lcdCharDef  (lcdHandle, 4, sunCloud4);
  lcdCharDef  (lcdHandle, 5, sunCloud5);
  lcdCharDef  (lcdHandle, 6, sunCloud6); 

  lcdPosition (lcdHandle, 7, 0) ;
  lcdPutchar  (lcdHandle, 1) ;
  lcdPutchar  (lcdHandle, 2) ;
  lcdPutchar  (lcdHandle, 3) ; 

  lcdPosition (lcdHandle, 7, 1) ;
  lcdPutchar  (lcdHandle, 4) ;
  lcdPutchar  (lcdHandle, 5) ;
  lcdPutchar  (lcdHandle, 6) ;
}

void drawRain(int lcdHandle){
         
  lcdCharDef  (lcdHandle, 1, rainCloud1);
  lcdCharDef  (lcdHandle, 2, rainCloud2);
  lcdCharDef  (lcdHandle, 3, rainCloud3);
  lcdCharDef  (lcdHandle, 4, rainCloud4);
  lcdCharDef  (lcdHandle, 5, rainCloud5);
  lcdCharDef  (lcdHandle, 6, rainCloud6); 

  lcdPosition (lcdHandle, 7, 0) ;
  lcdPutchar  (lcdHandle, 1) ;
  lcdPutchar  (lcdHandle, 2) ;
  lcdPutchar  (lcdHandle, 3) ; 

  lcdPosition (lcdHandle, 7, 1) ;
  lcdPutchar  (lcdHandle, 4) ;
  lcdPutchar  (lcdHandle, 5) ;
  lcdPutchar  (lcdHandle, 6) ;
}

void drawDirection(int lcdHandle){

  float dirRead = getWindDirection();

  if(dirRead > 22.5 && dirRead < 67.5){ lcdCharDef(lcdHandle, 7, northEast); }
  if(dirRead > 67.5 && dirRead < 112.5){ lcdCharDef(lcdHandle, 7, east); }
  if(dirRead > 112.5 && dirRead < 157.5){ lcdCharDef(lcdHandle, 7, southEast); }
  if(dirRead > 157.5 && dirRead < 202.5){ lcdCharDef(lcdHandle, 7, south); }
  if(dirRead > 202.5 && dirRead < 247.5){ lcdCharDef(lcdHandle, 7, southWest); }
  if(dirRead > 247.5 && dirRead < 292.5){ lcdCharDef(lcdHandle, 7, west); }
  if(dirRead > 292.5 && dirRead < 337.5){ lcdCharDef(lcdHandle, 7, northWest); }
  if(dirRead > 337.5 || dirRead < 22.5){ lcdCharDef(lcdHandle, 7, north); }

  lcdPosition(lcdHandle, 5, 0);
  lcdPutchar(lcdHandle, 7);
}



