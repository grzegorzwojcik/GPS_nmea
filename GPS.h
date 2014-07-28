/*
 * GPS.h
 *
 *  Created on: Jul 18, 2014
 *      Author: Grzegorz Wojcik
 */

#ifndef GPS_H_
#define GPS_H_

#define PI 3.14159265				/* PI */
#define PI_180 0.01745329252		/* PI divided by 180 (for conversion degrees <->radians */
#define Earth_Radius 6371			/* Mean Earth radius [kilometers] */

/*** Volatile variables ***/
volatile char GPS_DataFrame[100];		//AAT GPS: Should start with '$', end with 0x0A
volatile char UAV_DataFrame[100];		//UAV GPS: Should start with '$', end with 0x0A
volatile uint8_t GPS_AATflag;			//GPS_AATflag is set to 0 during GPS_VariablesInit() execution
volatile uint8_t GPS_UAVflag;			//GPS_UAVflag is set to 0 during GPS_VariablesInit() execution

/*** Initialization functions and structures***/
void GPS_GPIOinit(void);
void GPS_USART1init(void);
void GPS_USART6init(void);
typedef struct{

		float Altitude;		/* Above mean sea level [meters] */

		float Latitude;
		uint8_t Latitude_degrees;
		float Latitude_minutes;
		float Latitude_decimal;

		float Longitude;
		uint8_t Longitude_degrees;
		float Longitude_minutes;
		float Longitude_decimal;

		/* UTC Time */
		uint8_t Time_hours;
		uint8_t Time_minutes;
		uint8_t Time_seconds;

}GPS;
GPS GPS_StructInit(void);

typedef struct{

		float Angle_alfa;
		float Angle_beta;
		float DeltaAltitude;	/* UAV_alt - AAT_alt	Relative height	[meters] */
		float Distance;			/* Distance between AAT and tracking object [meters] */


}ATracker;
ATracker ATracker_StructInit(void);

// 50 17.30118, 18 40.66723


/*** Functions ***/
void GPS_ClearDataFrameAAT(void);
void GPS_ClearDataFrameUAV(void);
void GPS_AATParseGGA(GPS* GPS_Structure);
void GPS_UAVParseGGA(GPS* GPS_Structure);
void AT_Calculations(GPS* GPS_AAT, GPS* GPS_UAV, ATracker* ATracker_Structure);


/* HOW TO USE GPS.h example:
int main(void)
{
	// Initialization -functions //
	GPS_GPIOinit();
	GPS_USART1init();
	GPS_USART6init();
	// Initialization -structures //
	GPS GPS_AAT = GPS_StructInit();
	GPS GPS_UAV = GPS_StructInit();
	ATracker AAT = ATracker_StructInit();

	while(1)
	{
		// Getting Antenna tracker coordinates -this might be executed just once after getting FIX
		// or every 10seconds (for example)
		if( GPS_AATflag == 1 ){
			GPS_AATParseGGA(&GPS_AAT);
			GPS_ClearDataFrameAAT();
			GPS_AATflag = 0;
		}
		// Getting tracking UAV coordinates -this should be executed very often //
		if( GPS_UAVflag == 1 ){
			GPS_UAVParseGGA(&GPS_UAV);
			GPS_ClearDataFrameUAV();
			GPS_UAVflag = 0;
		}

		if( a >= 500 ){		// FOR EXAMPLE CALCULATE EVERY 0.5s //
			if( (GPS_AAT.Latitude_decimal !=0) && (GPS_AAT.Longitude_decimal !=0) &&
				(GPS_UAV.Latitude_decimal !=0) && (GPS_UAV.Longitude_decimal !=0)){
					AT_Calculations(&GPS_AAT, &GPS_UAV, &AAT);
					a = 0;
			}
		}
	}
}
*/

#endif /* GPS_H_ */
