/*
 * GPS.h
 *
 *  Created on: Jul 18, 2014
 *      Author: Grzegorz Wojcik
 */

#ifndef GPS_H_
#define GPS_H_

/*** Volatile variables ***/
volatile char GPS_DataFrame[100];		//Should start with '$', end with 0x0A
volatile uint8_t GPS_flag;				//GPS_flag is initialized with 0 during GPS_VariablesInit() execution
volatile float test;
volatile char test_string[30];

/*** Initialization functions ***/
void GPS_GPIOinit(void);
void GPS_USARTinit(void);
void GPS_VariablesInit(void);

/*** Functions ***/
void GPS_ClearDataFrame(void);
void GPS_ParseFloatGGA();
float GPS_ParseGGA(uint8_t CommaNumber);


typedef struct{
		uint16_t Speed; 		/* Speed over ground */
		int32_t Latitude;		/* Szerokosc geograficzna */
		int32_t Longitude;		/* Dlugosc geograficzna */
		uint16_t Altitude;		/* Above mean sea level [meters] */

		/* UTC Time */
		uint8_t Time_hours;
		uint8_t Time_minutes;
		uint8_t Time_seconds;

}GPS;

#endif /* GPS_H_ */
