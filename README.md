WeatherPi
=========
This is the final project for EECS 113 (processor hardware/software interfaces) at UC Irvine, Spring 2014. From the project prompt:
> The goal of this project is to make a Smart Weather Meter capable of scheduling irrigation systems, which uses weather data and sensor measurements. The overall system will be internet enabled and will access the California Irrigation Information System (CIMIS) database.

#### Requirements    
  * Raspberry Pi
  * Hitachi HD44780U LCD
  * MCP 3008 ADC
  * 10k Thermistor
  * Breadboard
  * Resistors, LEDs, trimmer, push button 
  * [wiringPi Library](wiringpi.com/download-and-install/ "Download wiringPi Library") 

####Installation
  * Download and install wiringPi library.
  * Setup components according to [this diagram.](https://www.dropbox.com/s/yphddx2n1vm46tv/weatherDevice.png "Fritzing Diagram")
  * Navigate into WeatherPi directory.
  * `make`
  * `sudo ./weather`
  

  

