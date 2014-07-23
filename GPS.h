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
volatile char GPS_DataFrame[100];		//Should start with '$', end with 0x0A
volatile uint8_t GPS_flag;				//GPS_flag is initialized with 0 during GPS_VariablesInit() execution

/*** Initialization functions and structures***/
void GPS_GPIOinit(void);
void GPS_USARTinit(void);
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

		float Angle_pitch;
		float Angle_yaw;
		float DeltaAltitude;	/* UAV_alt - AAT_alt	Relative height	[meters] */
		float DeltaLatitude;	/* AAT_lat - UAV_lat */
		float DeltaLongitude;	/* AAT_lon - UAV_lon */
		float Distance;			/* Distance between AAT and tracking object [meters] */


}ATracker;
ATracker ATracker_StructInit(void);

// 50 17.30118, 18 40.66723


/*** Functions ***/
void GPS_ClearDataFrame(void);
void GPS_ParseGGA(GPS* GPS_Structure);
void GPS_ConvertToDecimalDegrees(GPS* GPS_Structure);
void AT_Calculations(GPS* GPS_AAT, GPS* GPS_UAV, ATracker* ATracker_Structure);




#endif /* GPS_H_ */
