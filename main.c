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
	GPS_USART1init();
	GPS_USART6init();

	/* Initialization -structures */
	GPS GPS_AAT = GPS_StructInit();
	GPS GPS_UAV = GPS_StructInit();
	ATracker AAT = ATracker_StructInit();


	while(1)
	{

		if( GPS_AATflag == 1 ){
			GPS_AATParseGGA(&GPS_AAT);
			GPS_ClearDataFrameAAT();
			AT_Calculations(&GPS_AAT, &GPS_UAV, &AAT);
			GPS_AATflag = 0;
		}

		if( GPS_UAVflag == 1 ){
			GPS_UAVParseGGA(&GPS_UAV);
			GPS_ClearDataFrameUAV();
			GPS_UAVflag = 0;
		}

		/* calculate each 0.5s */
		if( a >= 500 ){

			a = 0;
		}

	}
}



