/************************************************************************/
/* sensorData.c                                                         */
/************************************************************************/
/* Author: Ryan M. Morrison                                             */
/* Date:   May 2014                                                     */
/*                                                                      */
/* Note: this source file contains functions for reading thermistor,    */
/*       reading ADC, averaging filter, convert to degrees              */
/************************************************************************/

#include "sensorData.h"

float ReadTherm(void){
  float temp;
  if(digitalRead(BUTTON) == HIGH){
	 int adcPortNum = 0;
   temp = handleTherm(adcAverage(SAMPLES, adcPortNum)); 
  }
  return temp;
}
 
int readadc(adcnum, clockpin, mosipin, misopin, cspin){
    
  int commandout, i, adcout;

  if ((adcnum > 7) || (adcnum < 0)){ return -1; }
                
  digitalWrite(cspin, 1); 
  digitalWrite(clockpin, 0);  /* start clock low*/
  digitalWrite(cspin, 0);     /* bring CS low*/
 
  commandout = adcnum;
  commandout |= 0x18;     /* start bit + single-ended bit*/
  commandout <<= 3 ;      /* we only need to send 5 bits here*/
    
  for (i =0; i< 5; i++){
    if (commandout & 0x80)
      digitalWrite(mosipin, 1);
    else
      digitalWrite(mosipin, 0);

    commandout <<= 1;
    digitalWrite(clockpin, 1);
    digitalWrite(clockpin, 0);
  }

  adcout = 0;
  /* read in one empty bit, one null bit and 10 ADC bits*/
  for (i=0; i< 12; i++){
    digitalWrite(clockpin, 1);
    digitalWrite(clockpin, 0);
    adcout <<= 1;
    if (digitalRead(misopin))
      adcout |= 0x1;
  }

  digitalWrite(cspin, 1);        
  adcout >>= 1;      /* first bit is 'null' so drop it*/

  return adcout;
 }
 
float adcAverage(int samples, int adcPortNum){

  int sampleSet[SAMPLES], i;
  float average;

  for (i = 0; i < samples; i++){

    if(digitalRead(BUTTON) == LOW){ 
      delay(1);
      break; 
    }

    sampleSet[i] = readadc(adcPortNum, SPICLK, SPIMOSI, SPIMISO, SPICS);
    delay(10);
  }

  average = 0;
  for (i = 0; i < samples; i++){

    if(digitalRead(BUTTON) == LOW){ 
      delay(1);
      break; 
    }

    average += sampleSet[i];
  }

  average /= samples;

  return average;
}

float handleTherm(float average){

  float steinhart;
  /* convert to resistance */
  average = average * 10000 / (1023 - average);
  /* convert to degrees C */
  steinhart = average / THERMNOMINAL;
  steinhart = log(steinhart);
  steinhart /= BCOEFFICIENT; /*B coefficient*/
  steinhart += 1.0 / (THERMTEMPNOM + 273.15);
  steinhart = 1.0 / steinhart;
  steinhart -= 273.15;
  steinhart = (steinhart*9/5) + 32;	/*convert to F*/

  return steinhart;
}
 