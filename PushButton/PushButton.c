/*
 * PushButton.c
 *
 *  Created on: 24 Nis 2022
 *      Author: Oziesin
 */
#include "PushButton.h"

void PushButton_Init( stPushButton_t* stPushButton,stPushButton_IO_t* pIO  )
{
	memset ( stPushButton, 0, sizeof(*stPushButton) );
	stPushButton->stButtonStaBits.b1State = 1;
	stPushButton->stButtonStaBits.b2BeforeState = 1;

	stPushButton->IO.GPIO_PORT = pIO->GPIO_PORT;
	stPushButton->IO.GPIO_PIN= pIO->GPIO_PIN;
	stPushButton->IO.ReadPin = pIO->ReadPin;

	stPushButton->stButtonStaBits.b0isInitialised = SET;
}

e_ErrStatus_t PushButton_Control( stPushButton_t* stPushButton )
{
	if( ! stPushButton->stButtonStaBits.b0isInitialised )
	{
		return Err_Initialise;
	}
	stPushButton->stButtonStaBits.b1State = stPushButton->IO.ReadPin ( stPushButton->IO.GPIO_PORT, stPushButton->IO.GPIO_PIN);

	if( stPushButton->stButtonStaBits.b2BeforeState > stPushButton->stButtonStaBits.b1State )
	{
		//UP
		++stPushButton->usTime;
	}
	else if( stPushButton->stButtonStaBits.b2BeforeState < stPushButton->stButtonStaBits.b1State )
	{
		//DOWN
		stPushButton->usTime = 0;
		++stPushButton->ucRepeatCounter;
	}

	if ( stPushButton->stButtonStaBits.b2BeforeState != stPushButton->stButtonStaBits.b1State )
	{
		stPushButton->stButtonStaBits.b2BeforeState = stPushButton->stButtonStaBits.b1State;
	}
	else
	{
		if ( !stPushButton->stButtonStaBits.b2BeforeState )
		{
			++stPushButton->usTime;
		}
	}
	return Err_Ok;
}
