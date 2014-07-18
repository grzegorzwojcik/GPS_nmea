/* Includes ------------------------------------------------------------------*/
#include <stddef.h>
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "functions.h"
#include "gps.h"


int main(void)
{
	SysTick_Config( SystemCoreClock / 1000 );
	GPS_GPIOinit();
	GPS_USARTinit();

	STM_EVAL_LEDInit(LED6);
	flag = 1;

	//char *check_string = "$GPGSV";

	while(1)
	{
		//receive_frame("$GPGGA");
		//receive_frame("$GPGSA");
		//receive_frame("$GPGSV");
		//receive_frame("$GPRMC");
		//receive_frame("$GPVTG");

	}
}



