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

	/* Initialization -structures */
	GPS GPS_AAT = GPS_StructInit();
	GPS GPS_UAV = GPS_StructInit();

	while(1)
	{
		//GPS_ParseGGA(GPS_DataFrame);
		if( GPS_flag == 1 ){
			GPS_ParseGGA(&GPS_AAT);
			GPS_ClearDataFrame();
			GPS_flag = 0;
		}
	}
}



