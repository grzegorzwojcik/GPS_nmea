/* Includes ------------------------------------------------------------------*/
#include <stddef.h>
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "functions.h"
#include <stdlib.h>
#include "gps.h"


int main(void)
{
	SysTick_Config( SystemCoreClock / 1000 );

	/* Initialization functions */
	GPS_GPIOinit();
	GPS_USARTinit();
	STM_EVAL_LEDInit(LED6);
	/* Initialization -structures */
	GPS GPS_AAT = GPS_StructInit();
	GPS GPS_UAV = GPS_StructInit();

	static float Time = 0;
	while(1)
	{
		//GPS_ParseGGA(GPS_DataFrame);
		if( GPS_flag == 1 ){
			Time = GPS_ParseTime();
			//GPS_AAT.Latitude = GPS_ParseLatitude();
			//GPS_AAT.Longitude = GPS_ParseLongitude();
			//GPS_AAT.Altitude =  GPS_ParseAltitude();
			GPS_ParseGGA(&GPS_AAT);
			GPS_ClearDataFrame();
			GPS_flag = 0;
		}
	}
}



