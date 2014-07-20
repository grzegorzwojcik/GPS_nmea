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

/*** Initialization functions ***/
void GPS_GPIOinit(void);
void GPS_USARTinit(void);
void GPS_VariablesInit(void);

/*** Functions ***/
void GPS_ClearDataFrame(void);
float GPS_ParseGGA(uint8_t CommaNumber);


typedef struct{
		float Speed; 		/* Speed over ground */
		float Latitude;		/* Szerokosc geograficzna */
		float Longitude;		/* Dlugosc geograficzna */
		float Altitude;		/* Above mean sea level [meters] */

		/* UTC Time */
		uint8_t Time_hours;
		uint8_t Time_minutes;
		uint8_t Time_seconds;

}GPS;

#endif /* GPS_H_ */
