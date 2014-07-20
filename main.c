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
	GPS_GPIOinit();
	GPS_USARTinit();
	GPS_VariablesInit();

	STM_EVAL_LEDInit(LED6);
	static float Latitude = 0;
	static float Longitude = 0;
	static float Altitude = 0;
	static float Time = 0;

	while(1)
	{
		//GPS_ParseGGA(GPS_DataFrame);
		if( GPS_flag == 1 ){
			Time = GPS_ParseGGA(1);
			Latitude = GPS_ParseGGA(2);
			Longitude = GPS_ParseGGA(4);
			Altitude =  GPS_ParseGGA(7);
			GPS_ClearDataFrame();
			GPS_flag = 0;
		}

	}
}



