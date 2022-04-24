/* File Name    : drvST25DV.h                                      			 */
/* Description  : 													         */
/* Author       : Ozi Esin                                                   */
/* Initial Date : 07.09.2021                                               	 */
/* Version      : 1.0                                                      	 */
/*****************************************************************************/

#include "Main.h"


#if ( USE_NFC & NFC_ST25DV )

#ifndef __drvST25DV_H
#define __drvST25DV_H
/* Private Libraries ---------------------------------------------------------*/

#include "st25dv.h"
/* Private defines -----------------------------------------------------------*/
#ifndef I2C_MEMADD_SIZE_8BIT
	#define I2C_MEMADD_SIZE_8BIT            (0x00000001U)
#endif
#ifndef I2C_MEMADD_SIZE_16BIT
	#define I2C_MEMADD_SIZE_16BIT           (0x00000002U)
#endif


#define NFC_ST25DV_I2Cx									I2C2
#define NFC_HW_TIM											TIM6

#define EXIT_CNT_VALUE 								( 1000000UL )			//  Timeout begining value that count down
#define	TIM_PRESCALER_DEFAULT					( 320 - 1 )				//	Timer prescaler for 5 ms interval (SYSCLK 64000000)
#define TIM_ARR_DEFAULT								( 1000 - 1 )			//	Timer autoreload value for 1ms interval (SYSCLK 64000000)

#define	EE_NFC_WRITE_PAGE_SIZE			  ( 4 )


/* Private macros ------------------------------------------------------------*/
#define mNFC_TIMER_RELOAD( a )        {  LL_TIM_SetAutoReload( NFC_HW_TIM, ((a) - 1 ) ); LL_TIM_SetCounter( NFC_HW_TIM,0); }

#define	mHW_TIM6_INT_ENABLE(  )				{	 LL_TIM_SetCounter(NFC_HW_TIM , 0); LL_TIM_ClearFlag_UPDATE(  NFC_HW_TIM ); LL_TIM_EnableIT_UPDATE( NFC_HW_TIM ); LL_TIM_EnableCounter( NFC_HW_TIM ); }

#define	mHW_TIM6_INT_DISABLE(  )			{	LL_TIM_DisableIT_UPDATE( NFC_HW_TIM ); LL_TIM_DisableCounter( NFC_HW_TIM ); }

#define mEE_NFC_I2C_WAIT_ACTIVE( PageSize ,TmrGoalVar )			{ stNFC_StatusFlag_Bits.b2NFC_I2CBsy = 1; TmrGoalVar = PageSize ; mHW_TIM6_INT_ENABLE();}		// Have to wait after write function with efficiency.


#define mEE_NFC_I2C_BUSY_WAIT()															{ while( stNFC_StatusFlag_Bits.b2NFC_I2CBsy ); }			// Have to wait before any operations , if write operations called.

#if ( defined USE_FULL_ASSERT )
	#define TRACE_ASSERT(Condition) 	{ assert_param( ! Condition ); }
#else
	#define TRACE_ASSERT(Condition) 	{}
#endif /* ( defined USE_FULL_ASSERT ) */
/* Private typedef -----------------------------------------------------------*/
typedef union
{
	struct
	{
		uint16_t b0												:1;
		uint16_t b1NFC_I2CRfField					:1;
		uint16_t b2NFC_I2CBsy							:1;
		uint16_t b5					 							:1;
		uint16_t b6 				            	:1;
		uint16_t b7 				            	:1;
		uint16_t b8 				            	:1;
		uint16_t b9 				            	:1;
		uint16_t b10 				              :1;
		uint16_t b11 				              :1;
		uint16_t b12 				              :1;
		uint16_t b13 				              :1;
		uint16_t b14 				              :1;
		uint16_t b15 				              :1;
	};
	uint16_t usNFC_FlagReg;

}NFC_StatusFlag_Bits_t;

typedef struct
{
	 __IO uint16_t usTimerCounter;
	 __IO uint16_t usTimerGoal;

}stI2c_Timer_t;

/* External variables --------------------------------------------------------*/
stI2c_Timer_t 													stI2c_Timer;
extern ST25DV_Object_t 									stNFC_Obj;
extern __IO NFC_StatusFlag_Bits_t		stNFC_StatusFlag_Bits;
__IO uint32_t uwTick;

extern int32_t ST25DV_ReadData(ST25DV_Object_t* pObj,  uint8_t * const pData, const uint16_t TarAddr, const uint16_t NbByte );
extern int32_t ST25DV_WriteData(ST25DV_Object_t* pObj,  const uint8_t * const pData, const uint16_t TarAddr, const uint16_t NbByte );
extern int32_t ST25DV_ReadReg (ST25DV_Ctx_t *ctx, uint16_t Reg, uint8_t* Data, uint16_t len);
/* Public functions bodies ----------------------------------------------------*/

//void NFC_HwTimerIntervalUpdate( TIM_TypeDef* stTIMx , uint16_t ucArray_Length );
uint32_t NFC_GetTick(void);
int32_t NFC_Init(void);
int32_t DrvNfc_I2C_Write( uint16_t usDevAddr, uint16_t usReg, const uint8_t* pucData, uint16_t ucLen);
int32_t DrvNfc_I2C_Read( uint16_t usDevAddr, uint16_t usReg, uint8_t* pucData, uint16_t ucLen);
void drvEE_I2C_ReadArray ( uint16_t usAddress, uint8_t *pucData, uint16_t ucByteCount );
uint8_t drvEE_I2C_CompareArray ( uint16_t usAddress, uint8_t *pucData, uint16_t ucByteCount );
void 			drvEE_I2C_WriteArray ( uint16_t usAddress, uint8_t *pucData, uint16_t ucByteCount );


#endif /* __drvST25DV_H*/

#endif /* ( USE_NFC & NFC_ST25DV ) */
