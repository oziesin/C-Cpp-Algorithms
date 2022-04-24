#ifndef INC_VIRTUALTIMER_H_
#define INC_VIRTUALTIMER_H_

#include <stdint.h>

#define TIMER_SIZE_MAX	8					// How many virtual timers create
#define mVIRTUAL_TIMER_SET(stVirtualTimer,TimerID,Time)	{ 	stVirtualTimer.tstVirtualTimer[ TimerID ].CurrentTime = 0;					\
																																stVirtualTimer.tstVirtualTimer[ TimerID ].SetTime = Time;				\
																																stVirtualTimer.Activate.ucTimerStatus |= ( TRUE << TimerID ) ;	\
																																stVirtualTimer.Timeout.ucTimerStatus &=  ~( TRUE << TimerID );	}

#define mVIRTUAL_TIMER_RESET(stVirtualTimer,TimerID)		{ stVirtualTimer.tstVirtualTimer[ TimerID ].CurrentTime = 0;						\
																													stVirtualTimer.Timeout.ucTimerStatus &=  ~( TRUE << TimerID );				\
																													stVirtualTimer.Activate.ucTimerStatus |= (TRUE << TimerID);						}

#define mVIRTUAL_TIMER_CLEAR(stVirtualTimer,TimerID)		{ stVirtualTimer.Timeout.ucTimerStatus &=  ~( TRUE << TimerID ); }

typedef enum
{
	FALSE,
	TRUE
}eBool_t;

typedef union
{
	uint8_t ucTimerStatus;
	struct
	{
		uint8_t timer1 : 1;
		uint8_t timer2 : 1;
		uint8_t timer3 : 1;
		uint8_t timer4 : 1;
		uint8_t timer5 : 1;
		uint8_t timer6 : 1;
		uint8_t timer7 : 1;
		uint8_t timer8 : 1;
	};
}stTimerStatus_t;

typedef enum
{
	TimerID_50ms,
	TimerID_100ms,
	TimerID_200ms,
	TimerID_300ms,
	TimerID_500ms,
	TimerID_1s,
	TimerID_7,
	TimerID_8,

	TimerID_Max=0xFF
}eTimerIDs_t;

typedef struct
{
	uint32_t CurrentTime;
	uint32_t SetTime;
}stTimer_t;

typedef struct
{
	stTimer_t tstVirtualTimer[ TIMER_SIZE_MAX ];
	stTimerStatus_t Activate;
	stTimerStatus_t Timeout;
}stVirtualTimer_t;

stVirtualTimer_t stVirtualTimer;

void VirtualTimer_ISR( void );

#endif /* INC_VIRTUALTIMER_H_ */
