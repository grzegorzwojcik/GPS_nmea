/*
 * GPS.c
 *
 *  Created on: Jul 18, 2014
 *      Author: Grzegorz Wojcik
 */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "GPS.h"

								/*** Initialization functions ***/
void GPS_GPIOinit(void){
	/* STM32F407VGT6
	 * USART1:
	 * TX: PB6
	 * RX: PB7 */

	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE );	//Enabling peripherial clock for PORTB


	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* STM32F407VGT6
	 * USART6:
	 * TX: PC6
	 * RX: PC7 */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );	//Enabling peripherial clock for PORTC
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	/* Connecting the RX and TX pins to their AlternateFunctions */
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);
}

/* GPS_USARTinit function should be executed after GPS_GPIOinit function */
void GPS_USART1init(void){
	/* STM32F407VGT6
	 * USART1:
	 * TX: PB6
	 * RX: PB7 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 	// Enabling peripherial clock for USART1
															// Note that only USART1 and USART6 are connected
															// to APB2
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 	// we want to enable the transmitter and the receiver
	USART_Init(USART1, &USART_InitStruct);

	/* Here the USART1 receive interrupt is enabled
	 * and the interrupt controller is configured
	 * to jump to the USART1_IRQHandler() function
	 * if the USART1 receive interrupt occurs */

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 			// enable the USART1 receive interrupt

	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;		 // we want to configure the USART1 interrupts
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group of the USART1 interrupts
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;		 // this sets the subpriority inside the group
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			 // the USART1 interrupts are globally enabled
	NVIC_Init(&NVIC_InitStruct);							 // the properties are passed to the NVIC_Init function which takes care of the low level stuff

	USART_Cmd(USART1, ENABLE);	// Enabling the complete USART1 peripherial
}

void GPS_USART6init(void){
	/* STM32F407VGT6
	 * USART1:
	 * TX: PC6
	 * RX: PC7 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE); 	// Enabling peripherial clock for USART1
															// Note that only USART1 and USART6 are connected
															// to APB2
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 	// we want to enable the transmitter and the receiver
	USART_Init(USART6, &USART_InitStruct);

	/* Here the USART1 receive interrupt is enabled
	 * and the interrupt controller is configured
	 * to jump to the USART1_IRQHandler() function
	 * if the USART1 receive interrupt occurs */

	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE); 			// enable the USART1 receive interrupt

	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART6_IRQn;		 // we want to configure the USART1 interrupts
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group of the USART1 interrupts
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;		 // this sets the subpriority inside the group
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			 // the USART1 interrupts are globally enabled
	NVIC_Init(&NVIC_InitStruct);							 // the properties are passed to the NVIC_Init function which takes care of the low level stuff

	USART_Cmd(USART6, ENABLE);	// Enabling the complete USART1 peripherial
}

GPS GPS_StructInit(){
	/* Structure initialization */
	/* THis function returns GPS structure with basic values, initializes GPS_flag with 0,
	 * and initializes(clears) volatile GPS_DataFrame*/
	GPS_AATflag = 0;
	GPS_UAVflag = 0;
	GPS_ClearDataFrameAAT();
	GPS_ClearDataFrameUAV();

	GPS GPS_Struct;
	GPS_Struct.Altitude				= 0;

	GPS_Struct.Latitude				= 0;
	GPS_Struct.Latitude_degrees 	= 0;
	GPS_Struct.Latitude_minutes 	= 0;
	GPS_Struct.Latitude_decimal		= 0;

	GPS_Struct.Longitude 			= 0;
	GPS_Struct.Longitude_degrees	= 0;
	GPS_Struct.Longitude_minutes	= 0;
	GPS_Struct.Longitude_decimal	= 0;

	GPS_Struct.Time_hours 			= 0;
	GPS_Struct.Time_minutes 		= 0;
	GPS_Struct.Time_seconds 		= 0;

	return GPS_Struct;
}

ATracker ATracker_StructInit(){

	ATracker ATracker_Struct;
	ATracker_Struct.Angle_alfa		 = 0;
	ATracker_Struct.Angle_beta		 = 0;
	ATracker_Struct.DeltaAltitude	 = 0;
	ATracker_Struct.Distance		 = 0;

	return ATracker_Struct;
}


								/*** Functions ***/
void GPS_ClearDataFrameAAT(){
	static uint8_t i = 0;
	for( i = 0; i < 100; i++){
		GPS_DataFrame[i] = 0;
	}
}

void GPS_ClearDataFrameUAV(){
	static uint8_t i = 0;
	for( i = 0; i < 100; i++){
		UAV_DataFrame[i] = 0;
	}
}

void GPS_AATParseGGA(GPS* GPS_Structure){

	if( (GPS_DataFrame[3] == 'G') && (GPS_DataFrame[4] == 'G') && (GPS_DataFrame[5] == 'A') ){

		static uint8_t i 	= 0;	//GPS_DataFrame[i]
		static uint8_t j	= 0;	//LatitudeStr[j]
		static uint8_t k	= 0;	//LongitudeStr[k]
		static uint8_t l 	= 0;	//AltitudeStr[l]
		static uint8_t m 	= 0;	//TimeStr[m]
		uint8_t CommaCounter= 0;

		char TimeStr[20]		= {0};	// Temporary char array
		char LatitudeStr[20]	= {0};	// Temporary char array
		char LongitudeStr[20]	= {0};	// Temporary char array
		char AltitudeStr[20]	= {0};	// Temporary char array


		for( i =0, j =0, k=0, l =0, m =0 ; i < 100; i++ ){
			if( GPS_DataFrame[i] == ',' )
				CommaCounter++;

			if( (GPS_DataFrame[i] != ',') && (CommaCounter == 1)){
				TimeStr[m] = GPS_DataFrame[i];
				m++;
			}

			if( (GPS_DataFrame[i] != ',') && (CommaCounter == 2)){
				LatitudeStr[j] = GPS_DataFrame[i];
				j++;
			}

			if( (GPS_DataFrame[i] != ',') && (CommaCounter == 4) ){
				LongitudeStr[k] = GPS_DataFrame[i];
				k++;
			}

			if( (GPS_DataFrame[i] != ',') && (CommaCounter == 9) ){
				AltitudeStr[l] = GPS_DataFrame[i];
				l++;
			}

			if( CommaCounter == 2 ){
				char TmpStr[2] = {TimeStr[0], TimeStr[1]};
				GPS_Structure->Time_hours = atoi(TmpStr);
				TmpStr[0] = TimeStr[2];
				TmpStr[1] = TimeStr[3];
				GPS_Structure->Time_minutes = atoi(TmpStr);
				TmpStr[0] = TimeStr[4];
				TmpStr[1] = TimeStr[5];
				GPS_Structure->Time_seconds = atoi(TmpStr);
			}

			/* Parsowanie Latitude */
			if( CommaCounter == 3 ){
				char TmpLatD[2] = {LatitudeStr[0], LatitudeStr[1]};
				GPS_Structure->Latitude_degrees = atoi(TmpLatD);

				uint8_t tmp = strlen(LatitudeStr);
				char TmpLatM[tmp-2];

				for(j = 2; j < tmp; j++){
					TmpLatM[j-2] = LatitudeStr[j];
				}
				GPS_Structure->Latitude_minutes = atoff(TmpLatM);
				GPS_Structure->Latitude = atoff(LatitudeStr);
				GPS_Structure->Latitude_decimal = GPS_Structure->Latitude_degrees + (0.016666667 * GPS_Structure->Latitude_minutes);
			}

			/* Parsowanie Longitude */
			if( CommaCounter == 5 ){
				char TmpLonD[2] = {LongitudeStr[1], LongitudeStr[2]};
				GPS_Structure->Longitude_degrees = atoi(TmpLonD);

				uint8_t tmp = strlen(LongitudeStr);
				char TmpLonM[tmp-3];

				for(k = 3; k < tmp; k++){
					TmpLonM[k-3] = LongitudeStr[k];
				}
				GPS_Structure->Longitude_minutes = atoff(TmpLonM);
				GPS_Structure->Longitude = atoff(LongitudeStr);
				GPS_Structure->Longitude_decimal = GPS_Structure->Longitude_degrees + (0.016666667 * GPS_Structure->Longitude_minutes);
			}

			if( CommaCounter >= 10){
				GPS_Structure->Altitude = atoff(AltitudeStr);
				break;
			}
		}
	}
}

void GPS_UAVParseGGA(GPS* GPS_Structure){

	if( (UAV_DataFrame[3] == 'G') && (UAV_DataFrame[4] == 'G') && (UAV_DataFrame[5] == 'A') ){

		static uint8_t i 	= 0;	//UAV_DataFrame[i]
		static uint8_t j	= 0;	//LatitudeStr[j]
		static uint8_t k	= 0;	//LongitudeStr[k]
		static uint8_t l 	= 0;	//AltitudeStr[l]
		static uint8_t m 	= 0;	//TimeStr[m]
		uint8_t CommaCounter= 0;

		char TimeStr[20]		= {0};	// Temporary char array
		char LatitudeStr[20]	= {0};	// Temporary char array
		char LongitudeStr[20]	= {0};	// Temporary char array
		char AltitudeStr[20]	= {0};	// Temporary char array


		for( i =0, j =0, k=0, l =0, m =0 ; i < 100; i++ ){
			if( UAV_DataFrame[i] == ',' )
				CommaCounter++;

			if( (UAV_DataFrame[i] != ',') && (CommaCounter == 1)){
				TimeStr[m] = UAV_DataFrame[i];
				m++;
			}

			if( (UAV_DataFrame[i] != ',') && (CommaCounter == 2)){
				LatitudeStr[j] = UAV_DataFrame[i];
				j++;
			}

			if( (UAV_DataFrame[i] != ',') && (CommaCounter == 4) ){
				LongitudeStr[k] = UAV_DataFrame[i];
				k++;
			}

			if( (UAV_DataFrame[i] != ',') && (CommaCounter == 9) ){
				AltitudeStr[l] = UAV_DataFrame[i];
				l++;
			}

			if( CommaCounter == 2 ){
				char TmpStr[2] = {TimeStr[0], TimeStr[1]};
				GPS_Structure->Time_hours = atoi(TmpStr);
				TmpStr[0] = TimeStr[2];
				TmpStr[1] = TimeStr[3];
				GPS_Structure->Time_minutes = atoi(TmpStr);
				TmpStr[0] = TimeStr[4];
				TmpStr[1] = TimeStr[5];
				GPS_Structure->Time_seconds = atoi(TmpStr);
			}

			/* Parsowanie Latitude */
			if( CommaCounter == 3 ){
				char TmpLatD[2] = {LatitudeStr[0], LatitudeStr[1]};
				GPS_Structure->Latitude_degrees = atoi(TmpLatD);

				uint8_t tmp = strlen(LatitudeStr);
				char TmpLatM[tmp-2];

				for(j = 2; j < tmp; j++){
					TmpLatM[j-2] = LatitudeStr[j];
				}
				GPS_Structure->Latitude_minutes = atoff(TmpLatM);
				GPS_Structure->Latitude = atoff(LatitudeStr);
				GPS_Structure->Latitude_decimal = GPS_Structure->Latitude_degrees + (0.016666667 * GPS_Structure->Latitude_minutes);
			}

			/* Parsowanie Longitude */
			if( CommaCounter == 5 ){
				char TmpLonD[2] = {LongitudeStr[1], LongitudeStr[2]};
				GPS_Structure->Longitude_degrees = atoi(TmpLonD);

				uint8_t tmp = strlen(LongitudeStr);
				char TmpLonM[tmp-3];

				for(k = 3; k < tmp; k++){
					TmpLonM[k-3] = LongitudeStr[k];
				}
				GPS_Structure->Longitude_minutes = atoff(TmpLonM);
				GPS_Structure->Longitude = atoff(LongitudeStr);
				GPS_Structure->Longitude_decimal = GPS_Structure->Longitude_degrees + (0.016666667 * GPS_Structure->Longitude_minutes);
			}

			if( CommaCounter >= 10){
				GPS_Structure->Altitude = atoff(AltitudeStr);
				break;
			}
		}
	}
}

void AT_Calculations(GPS* GPS_AAT, GPS* GPS_UAV, ATracker* ATracker_Structure){
	/* Degrees to radians */
	float DeltaLatitude = 0;	/* AAT_lat - UAV_lat */
	float DeltaLongitude = 0;	/* AAT_lon - UAV_lon */
	float AAT_LatRad = GPS_AAT->Latitude_decimal	* PI_180;
	float AAT_LonRad = GPS_AAT->Longitude_decimal	* PI_180;
	float UAV_LatRad = GPS_UAV->Latitude_decimal	* PI_180;
	float UAV_LonRad = GPS_UAV->Longitude_decimal 	* PI_180;

	DeltaLatitude = AAT_LatRad - UAV_LatRad;
	DeltaLongitude = AAT_LonRad - UAV_LonRad;

	/* Haversine formula -distance between 2 points on a sphere */
	float a = 0;
	a = sinf(DeltaLatitude/2) * sinf(DeltaLatitude/2) +
		cosf(AAT_LatRad) * cosf(UAV_LatRad) *
		sinf(DeltaLongitude/2) * sinf(DeltaLongitude/2);
	float c = 0;
	c = 2 * atan2f(sqrtf(a), sqrtf((1-a)));

	ATracker_Structure->Distance = Earth_Radius * c * 1000;

	/* Tracked UAV current relative height */
	ATracker_Structure->DeltaAltitude = GPS_UAV->Altitude - GPS_AAT->Altitude;

	/* Alfa angle, atan2f result is in [rad], so by multiplying it by 57.2957795 we get degrees */
	ATracker_Structure->Angle_alfa = (atan2f(DeltaLatitude,DeltaLongitude)) * 57.2957795;

	/* Beta angle, atan2f result is in [rad], so by multiplying it by 57.2957795 we get degrees */
	ATracker_Structure->Angle_beta = (atan2f(ATracker_Structure->DeltaAltitude,ATracker_Structure->Distance)) * 57.2957795;
}

				/*** Interrupt Request Handler (IRQ) for ALL USART1 interrupts ***/
void USART1_IRQHandler(void){

	if( USART_GetITStatus(USART1, USART_IT_RXNE) ){

		static uint8_t cnt = 0; 	// String length
		char t = USART1->DR; 		// Received character from USART1 data register is saved in t

		if( (GPS_AATflag == 0) ){
			if( t == '$' ){
				cnt = 0;
				GPS_DataFrame[cnt] = t;
				cnt++;
			}
			if( (t != '$') && (GPS_DataFrame[0] == '$') ){
				GPS_DataFrame[cnt] = t;
				cnt++;
				if( t == 0x0D ){
					cnt = 0;
					GPS_AATflag = 1;
				}
			}
		}
	}
}

/*** Interrupt Request Handler (IRQ) for ALL USART1 interrupts ***/
void USART6_IRQHandler(void){

	if( USART_GetITStatus(USART6, USART_IT_RXNE) ){

		static uint8_t cnt = 0; 	// String length
		char t = USART6->DR; 		// Received character from USART1 data register is saved in t

		if( (GPS_UAVflag == 0) ){
			if( t == '$' ){
			cnt = 0;
			UAV_DataFrame[cnt] = t;
			cnt++;
			}
			if( (t != '$') && (UAV_DataFrame[0] == '$') ){
				UAV_DataFrame[cnt] = t;
				cnt++;
				if( t == 0x0D ){
					cnt = 0;
					GPS_UAVflag = 1;
				}
			}
		}
	}
}

