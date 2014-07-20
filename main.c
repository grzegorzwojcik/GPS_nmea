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

	STM_EVAL_LEDInit(LED6);
	flag = 0;
	test = 0;

	while(1)
	{
		//GPS_ParseGGA(GPS_DataFrame);
		GPS_ParseFloatGGA();
	}
}



