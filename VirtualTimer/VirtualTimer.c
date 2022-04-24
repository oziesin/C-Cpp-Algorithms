#include "VirtualTimer.h"

void VirtualTimer_ISR( void )
{
	uint8_t Idx = 0;

	do
	{
		if ( stVirtualTimer.Activate.ucTimerStatus & (TRUE << Idx) )
		{
			++stVirtualTimer.tstVirtualTimer [ Idx ].CurrentTime;

			if ( stVirtualTimer.tstVirtualTimer [ Idx ].CurrentTime >= stVirtualTimer.tstVirtualTimer [ Idx ].SetTime )
			{
				stVirtualTimer.Timeout.ucTimerStatus |= (TRUE << Idx);
				stVirtualTimer.Activate.ucTimerStatus &= ~(TRUE << Idx);
			}
		}
	}while ( ++Idx < TIMER_SIZE_MAX );
}
