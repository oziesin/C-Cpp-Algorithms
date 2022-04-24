/*
 * PushButton.h
 *
 *  Created on: 24 Nis 2022
 *      Author: Oziesin
 */

#ifndef INC_PUSHBUTTON_H_
#define INC_PUSHBUTTON_H_

#include "stdint.h"
#include "string.h"

#define SET 1
#define RESET 0

typedef enum
{
	Err_Ok, Err_Initialise
} e_ErrStatus_t;

typedef union
{
	uint8_t ucStatus;
	struct
	{
		uint8_t b0isInitialised :1;
		uint8_t b1State :1;
		uint8_t b2BeforeState :1;
		uint8_t b3 :1;
		uint8_t b4 :1;
		uint8_t b5 :1;
		uint8_t b6 :1;
		uint8_t b7 :1;
	};
} stButtonStaBits_t;

typedef uint8_t (*PushButton_Read_Func_t) ( uint32_t*, uint32_t );

typedef struct
{
	uint32_t* 		GPIO_PORT;
	uint32_t 			GPIO_PIN;
	PushButton_Read_Func_t ReadPin;
} stPushButton_IO_t;

typedef struct
{
	uint16_t usTime;
	uint8_t ucRepeatCounter;
	stButtonStaBits_t stButtonStaBits;
	stPushButton_IO_t IO;
} stPushButton_t;

void PushButton_Init( stPushButton_t* stPushButton,stPushButton_IO_t* pIO  );
e_ErrStatus_t PushButton_Control( stPushButton_t* stPushButton );

#endif /* INC_PUSHBUTTON_H_ */
