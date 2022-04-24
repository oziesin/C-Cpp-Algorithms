/* File Name    : drvST25DV.c		                                      			 */
/* Description  : 																													 */
/* Must be use @ref mEE_NFC_I2C_WAIT_ACTIVE macro after any write operations.*/
/* Must be use @ref mEE_NFC_I2C_BUSY_WAIT macro before all operations.       */
/* Author       : Ozi Esin           		                                 		 */
/* Initial Date : 07.09.2021                                               	 */
/* Version      : 1.0                                                      	 */
/*****************************************************************************/

#include "drvST25DV.h"

/* External variables --------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static int32_t nop ( void );
static int32_t DrvNFC_IsReady ( uint16_t ulTrials, uint32_t usTimeout );
/* Global variables ----------------------------------------------------------*/
volatile NFC_StatusFlag_Bits_t stNFC_StatusFlag_Bits = { 0 };
ST25DV_Object_t stNFC_Obj;
volatile uint8_t ucGPOStatus;
/* Private functions ---------------------------------------------------------*/

/* nop function */
/**
 * @brief  Returns 0.
 * @return int32_t 0 value.
 */
static int32_t nop ( )
{
	return 0;
}
/* NFC_GetTick function */
/**
 * @brief  Returns tick count.
 * @return uint32_t tick count value.
 */
uint32_t NFC_GetTick(void)
{
	return uwTick;
}

/* NFC i2c isReady function */
/**
 * @brief  Controls is device ready to i2c communication.
 * @param  ulTrials try limit
 * @param  usTimeout	Timeout counter
 * @return int32_t enum status.
 */
static int32_t DrvNFC_IsReady ( uint16_t ulTrials, uint32_t usTimeout )
{
	FlagStatus stTmp1, stTmp2;
	uint32_t ulTickstart;
	uint32_t usI2C_Trials = 0;

	if ( LL_I2C_IsActiveFlag_BUSY ( NFC_ST25DV_I2Cx ) )
	{
		return NFCTAG_ERROR;
	}

	do
	{
		/* Generate Start */
		LL_I2C_GenerateStartCondition ( NFC_ST25DV_I2Cx );
		/* No need to Check TC flag, with AUTOEND mode the stop is automatically generated */
		/* Wait until STOPF flag is set or a NACK flag is set*/
		ulTickstart = NFC_GetTick();

		stTmp1 = LL_I2C_IsActiveFlag_STOP ( NFC_ST25DV_I2Cx );
		stTmp2 = LL_I2C_IsActiveFlag_NACK ( NFC_ST25DV_I2Cx );

		while ( (stTmp1 == RESET) && (stTmp2 == RESET) )
		{
			if ( ((NFC_GetTick() - ulTickstart) > usTimeout) || (usTimeout == 0U) )
			{
				return NFCTAG_TIMEOUT;
			}
			stTmp1 = LL_I2C_IsActiveFlag_STOP ( NFC_ST25DV_I2Cx );
			stTmp2 = LL_I2C_IsActiveFlag_NACK ( NFC_ST25DV_I2Cx );
		}
		/* Check if the NACKF flag has not been set */
		if ( !LL_I2C_IsActiveFlag_NACK ( NFC_ST25DV_I2Cx ) )
		{
			LL_I2C_ClearFlag_STOP ( NFC_ST25DV_I2Cx );
			return NFCTAG_OK;
		}
		else
		{
			LL_I2C_ClearFlag_NACK ( NFC_ST25DV_I2Cx );
			LL_I2C_ClearFlag_STOP ( NFC_ST25DV_I2Cx );

		}
		if ( usI2C_Trials == ulTrials )
		{
			LL_I2C_GenerateStopCondition ( NFC_ST25DV_I2Cx );
			LL_I2C_ClearFlag_STOP ( NFC_ST25DV_I2Cx );
		}
		++usI2C_Trials;
	}
	while ( usI2C_Trials < ulTrials );
	return NFCTAG_ERROR;
}

/* Public functions ----------------------------------------------------------*/
/*	NFC Initialise function	*/
/**
 * @brief  Initialise NFC functions and linking st25dv.h library
 * @return int32_t enum status.
 */
int32_t NFC_Init ( void )
{
	ST25DV_IO_t io;
	int32_t slReturnVal;
	ST25DV_EH_CTRL EH_Ctrl;
	ST25DV_I2CSSO_STATUS i2csso = ST25DV_SESSION_CLOSED;
	uint8_t ucST25DV_GPO_Config;

	slReturnVal = NFCTAG_OK;
	/* Initialize ST25DV_Object_t */
	io.Init = nop;
	io.DeInit = NULL;
	io.IsReady = DrvNFC_IsReady;
	io.Write = DrvNfc_I2C_Write;
	io.Read = DrvNfc_I2C_Read;
	io.GetTick =  (int32_t(*) ( void )) NFC_GetTick;
	slReturnVal = ST25DV_RegisterBusIO ( &stNFC_Obj, &io );
//	printf("ST25DV_RegisterBusIO : %ld\n",slReturnVal );
	TRACE_ASSERT( slReturnVal != NFCTAG_OK );
	/*		Read VCC Status		*/

	mEE_NFC_I2C_BUSY_WAIT();
	slReturnVal = ST25DV_ReadEHCtrl_Dyn ( &stNFC_Obj, &EH_Ctrl );
//	printf("ST25DV_ReadEHCtrl_Dyn : %ld\n",slReturnVal );
	TRACE_ASSERT( slReturnVal != NFCTAG_OK );

	if ( !EH_Ctrl.VCC_on )
	{
		return NFCTAG_ERROR;
	}
	/* Open I2CSS Security Session on ST25DV */

	mEE_NFC_I2C_BUSY_WAIT();
	slReturnVal = ST25DV_ReadI2CSecuritySession_Dyn ( &stNFC_Obj, &i2csso );
//	printf("ST25DV_ReadI2CSecuritySession_Dyn : %ld\n",slReturnVal );

	TRACE_ASSERT( slReturnVal != NFCTAG_OK );

	while (i2csso == ST25DV_SESSION_CLOSED)
	{
		mEE_NFC_I2C_BUSY_WAIT();
		slReturnVal = ST25DV_PresentI2CPassword (&stNFC_Obj, ( ST25DV_PASSWD ) { 0, 0 } );
		mEE_NFC_I2C_WAIT_ACTIVE( 5,stI2c_Timer.usTimerGoal  );

		mEE_NFC_I2C_BUSY_WAIT();
		slReturnVal = ST25DV_ReadI2CSecuritySession_Dyn ( &stNFC_Obj, &i2csso );
	}
	/* Setting GPO interrupt sources */
	mEE_NFC_I2C_BUSY_WAIT();
	ucST25DV_GPO_Config = ST25DV_GPO_RFACTIVITY_MASK | ST25DV_GPO_FIELDCHANGE_MASK | ST25DV_GPO_RFWRITE_MASK | ST25DV_GPO_ENABLE_MASK;
	slReturnVal = ST25DV_SetGPO_ALL ( &stNFC_Obj.Ctx, (uint8_t*) &ucST25DV_GPO_Config );
	mEE_NFC_I2C_WAIT_ACTIVE( 1,stI2c_Timer.usTimerGoal  );
//	printf("ST25DV_SetGPO_ALL : %ld\n",slReturnVal );

	TRACE_ASSERT( slReturnVal != NFCTAG_OK );



	printf( "NFC_INIT Done\n" );

	return slReturnVal;
}

/*	NFC i2c write function	*/
/**
 * @brief  Writes usLen bytes of Data, starting from the specified I2C address.
 * @param  usDevAddr I2C device address user memory or system memory.
 * @param  usReg I2C memory address to write.
 * @param  pucData Pointer used to write data.
 * @param  usLen  Number of bytes to be write.
 * @return int32_t enum status.
 */
int32_t	DrvNfc_I2C_Write ( uint16_t usDevAddr, uint16_t usReg, const uint8_t* pucData, uint16_t usLen )
{
	uint32_t ulExitCount;

//		mEE_NFC_I2C_BUSY_WAIT(); Fonk icinde problem cikarir.
	TRACE_ASSERT( (usLen == 0) );
	/* Wait for I2C bus is free */

	ulExitCount = EXIT_CNT_VALUE;
	while ( LL_I2C_IsActiveFlag_BUSY ( NFC_ST25DV_I2Cx ) )
	{
		if ( --ulExitCount == 0 )
		{
//			mEE_NFC_I2C_WAIT_ACTIVE( usEE_PageSize,stI2c_Timer.usTimerGoal  ); Fonk icinde problem cikarir.

			return NFCTAG_ERROR;
		}
	}

	if ( !LL_I2C_IsEnabled ( NFC_ST25DV_I2Cx ) )
	{
		LL_I2C_Enable ( NFC_ST25DV_I2Cx );
	}

	// Write Address Operation
	LL_I2C_HandleTransfer ( NFC_ST25DV_I2Cx, usDevAddr, LL_I2C_ADDRSLAVE_7BIT, I2C_MEMADD_SIZE_16BIT, LL_I2C_MODE_RELOAD, LL_I2C_GENERATE_START_WRITE );

	ulExitCount = EXIT_CNT_VALUE;
	while ( !LL_I2C_IsActiveFlag_TXIS ( NFC_ST25DV_I2Cx ) )
	{
		if ( --ulExitCount == 0 )
		{
//			mEE_NFC_I2C_WAIT_ACTIVE( usEE_PageSize,stI2c_Timer.usTimerGoal  );
			return NFCTAG_ERROR;
		}
	}

	LL_I2C_TransmitData8 ( NFC_ST25DV_I2Cx, ((usReg & 0xFF00) >> 8) );	//MSB

	ulExitCount = EXIT_CNT_VALUE;
	while ( !LL_I2C_IsActiveFlag_TXIS ( NFC_ST25DV_I2Cx ) )
	{
		if ( --ulExitCount == 0 )
		{

//			mEE_NFC_I2C_WAIT_ACTIVE( usEE_PageSize,stI2c_Timer.usTimerGoal  );

			return NFCTAG_ERROR;
		}
	}
	LL_I2C_TransmitData8 ( NFC_ST25DV_I2Cx, (usReg & 0xFF) );	//LSB

	ulExitCount = EXIT_CNT_VALUE;
	while ( !LL_I2C_IsActiveFlag_TCR ( NFC_ST25DV_I2Cx ) )
	{
		if ( --ulExitCount == 0 )
		{
//			mEE_NFC_I2C_WAIT_ACTIVE( usEE_PageSize,stI2c_Timer.usTimerGoal  );

			return NFCTAG_ERROR;
		}
	}

	// Write Operation
	LL_I2C_HandleTransfer ( NFC_ST25DV_I2Cx, usDevAddr, LL_I2C_ADDRSLAVE_7BIT, usLen, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_NOSTARTSTOP );
	do
	{
		/* Wait until TXIS flag is set */

		ulExitCount = EXIT_CNT_VALUE;
		while ( !LL_I2C_IsActiveFlag_TXIS ( NFC_ST25DV_I2Cx ) )
		{
			if ( --ulExitCount == 0 )
			{
//				mEE_NFC_I2C_WAIT_ACTIVE( usEE_PageSize,stI2c_Timer.usTimerGoal  );

				return NFCTAG_ERROR;
			}
		}
		/* Write data to TXDR */
		LL_I2C_TransmitData8 ( NFC_ST25DV_I2Cx, *pucData );
		++pucData;
	}
	while ( --usLen );

	/* No need to Check TC flag, with AUTOEND mode the stop is automatically
	 * generated.
	 * Wait until STOPF flag is reset */
	while ( !LL_I2C_IsActiveFlag_STOP ( NFC_ST25DV_I2Cx ) );
	/* Clear NACKF Flag */
	LL_I2C_ClearFlag_NACK ( NFC_ST25DV_I2Cx );
	/* Clear STOP Flag */
	LL_I2C_ClearFlag_STOP ( NFC_ST25DV_I2Cx );

//	mEE_NFC_I2C_WAIT_ACTIVE( usEE_PageSize,stI2c_Timer.usTimerGoal  );
	return NFCTAG_OK;
}

/*	NFC i2c read function	*/
/**
 * @brief  Read usLen bytes of Data, starting from the specified I2C address.
 * @param  usDevAddr I2C device address user memory or system memory.
 * @param  usReg I2C memory address to read.
 * @param  pucData Pointer used to return read data.
 * @param  usLen  Number of bytes to be read.
 * @return int32_t enum status.
 */
int32_t	DrvNfc_I2C_Read ( uint16_t usDevAddr, uint16_t usReg, uint8_t* pucData, uint16_t usLen )
{
	uint32_t ulExitCount;
	TRACE_ASSERT( (usLen == 0) );
	//	mEE_NFC_I2C_BUSY_WAIT(); Fonk icinde problem cikarir.

	/* Wait for I2C bus is free */
	ulExitCount = EXIT_CNT_VALUE;
	while ( LL_I2C_IsActiveFlag_BUSY ( NFC_ST25DV_I2Cx ) )
	{
		if ( --ulExitCount == 0 )
		{
			return ( NFCTAG_ERROR);
		}
	}

	if ( !LL_I2C_IsEnabled ( NFC_ST25DV_I2Cx ) )
	{
		LL_I2C_Enable ( NFC_ST25DV_I2Cx );
	}
	// Write  Address Operation

	LL_I2C_HandleTransfer ( NFC_ST25DV_I2Cx, usDevAddr, LL_I2C_ADDRSLAVE_7BIT, I2C_MEMADD_SIZE_16BIT, LL_I2C_MODE_RELOAD, LL_I2C_GENERATE_START_WRITE );

	ulExitCount = EXIT_CNT_VALUE;
	while ( !LL_I2C_IsActiveFlag_TXIS ( NFC_ST25DV_I2Cx ) )
	{
		if ( --ulExitCount == 0 )
		{
			return ( NFCTAG_ERROR);
		}
	}

	LL_I2C_TransmitData8 ( NFC_ST25DV_I2Cx, ((usReg & 0xFF00) >> 8) );	//MSB

	ulExitCount = EXIT_CNT_VALUE;

	while ( !LL_I2C_IsActiveFlag_TXIS ( NFC_ST25DV_I2Cx ) )
	{
		if ( --ulExitCount == 0 )
		{
			return ( NFCTAG_ERROR);
		}
	}

	LL_I2C_TransmitData8 ( NFC_ST25DV_I2Cx, (usReg & 0xFF) );	//LSB

	ulExitCount = EXIT_CNT_VALUE;

	while ( !LL_I2C_IsActiveFlag_TXE ( NFC_ST25DV_I2Cx ) )
	{
		if ( --ulExitCount == 0 )
		{
			return ( NFCTAG_ERROR);
		}
	}

	// Read Operation
	LL_I2C_HandleTransfer ( NFC_ST25DV_I2Cx, usDevAddr, LL_I2C_ADDRSLAVE_7BIT, usLen, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ );

	do
	{
		/* Wait until RXNE flag is set */

		ulExitCount = EXIT_CNT_VALUE;

		while ( !LL_I2C_IsActiveFlag_RXNE ( NFC_ST25DV_I2Cx ) )
		{
			if ( --ulExitCount == 0 )
			{
				return ( NFCTAG_ERROR);
			}
		}

		/* Read data from RXDR */
		*pucData = LL_I2C_ReceiveData8 ( NFC_ST25DV_I2Cx );
		++pucData;
	}
	while ( --usLen );

	/* No need to Check TC flag, with AUTOEND mode the stop is automatically
	 * generated.
	 * Wait until STOPF flag is reset */
	while ( !LL_I2C_IsActiveFlag_STOP ( NFC_ST25DV_I2Cx ) );
	/* Clear NACKF Flag */
	LL_I2C_ClearFlag_NACK ( NFC_ST25DV_I2Cx );
	/* Clear STOP Flag */
	LL_I2C_ClearFlag_STOP ( NFC_ST25DV_I2Cx );

	return ( NFCTAG_OK);
}


void drvEE_I2C_WriteArray ( uint16_t usAddress, uint8_t *pucData, uint16_t ucByteCount )
{
	int32_t slStatus;
	uint8_t usEE_PageSize;
	uint8_t usTmpByteCnt;
	uint8_t ucIdx;

	ucIdx = ucByteCount / 256;

	do
	{
		if( ucIdx )
		{
			usTmpByteCnt = 255;
		}
		else
		{
			usTmpByteCnt = ucByteCount % 256;
		}
		usEE_PageSize = (usTmpByteCnt + EE_NFC_WRITE_PAGE_SIZE - 1) / EE_NFC_WRITE_PAGE_SIZE;


		mEE_NFC_I2C_BUSY_WAIT();

		slStatus = ST25DV_WriteData ( (ST25DV_Object_t*) &stNFC_Obj, (const uint8_t * const ) pucData, (const uint16_t) usAddress, (const uint16_t) usTmpByteCnt );

		TRACE_ASSERT( slStatus != NFCTAG_OK );

		mEE_NFC_I2C_WAIT_ACTIVE( usEE_PageSize, stI2c_Timer.usTimerGoal );

		ucByteCount -=usTmpByteCnt;
		usAddress += usTmpByteCnt;
		pucData	+= usTmpByteCnt;

	}while( ucIdx-- );


}

void drvEE_I2C_ReadArray ( uint16_t usAddress, uint8_t *pucData, uint16_t ucByteCount )
{
	int32_t slStatus;
	uint8_t usTmpByteCnt;
	uint8_t ucIdx;

	ucIdx = ucByteCount / 256;

	do
	{
		if( ucIdx )
		{
			usTmpByteCnt = 255;
		}
		else
		{
			usTmpByteCnt = ucByteCount % 256;
		}

		mEE_NFC_I2C_BUSY_WAIT();

		slStatus = ST25DV_ReadData ( (ST25DV_Object_t*) &stNFC_Obj, (uint8_t * const ) pucData, (const uint16_t) usAddress, (const uint16_t) usTmpByteCnt );

		TRACE_ASSERT( slStatus != NFCTAG_OK );

		ucByteCount -=usTmpByteCnt;
		usAddress += usTmpByteCnt;
		pucData	+= usTmpByteCnt;

	}while( ucIdx-- );



}

uint8_t drvEE_I2C_CompareArray ( uint16_t usAddress, uint8_t *pucData, uint16_t ucByteCount )
{
	uint8_t ucData;
	do
	{
		drvEE_I2C_ReadArray( usAddress, &ucData, 1 );

		if ( ucData != *pucData )
		{
			return 22;
		}

		if ( --ucByteCount == 0 )
		{
			break;
		}

		++pucData;
		++usAddress;
	}
	while ( 1 );

	return 0;
}


/*	Hardware timer interval selector function	*/
/**
 * @brief  Set stTIMx timer period according to usLen. Can be use while writing i2c concurrent programming algorithm.
 * @param  stTIMx Hw Timerx.
 * @param  usLen  Number of bytes.
 */
//void NFC_HwTimerIntervalUpdate ( TIM_TypeDef* stTIMx, uint16_t usLen )
//{
//	uint32_t ulPrescaler = TIM_PRESCALER_DEFAULT;
//	uint8_t ucPage;
//
//	ucPage = ( usLen + EE_NFC_WRITE_PAGE_SIZE - 1 ) / EE_NFC_WRITE_PAGE_SIZE ;
//
//	ulPrescaler = TIM_PRESCALER_DEFAULT * ucPage;
//
//	/* Enable and start hardware timer */
//
//	mHW_TIM6_INT_UPDATE_ENABLE( ulPrescaler );
//}



/*	Systick timer irq handler	*/
void SysTick_Handler(void)
{
	++uwTick;

	if (! (uwTick % 1000) )
	{
		LL_GPIO_TogglePin( LED_RELAY_COIL_GPIO_Port,LED_RELAY_COIL_Pin );
	}
}

/*	Hardware timer6 irq handler	*/
void TIM6_DAC_LPTIM1_IRQHandler ( void )
{
	if ( stNFC_StatusFlag_Bits.b2NFC_I2CBsy)
	{
		++stI2c_Timer.usTimerCounter;

		if ( stI2c_Timer.usTimerCounter > stI2c_Timer.usTimerGoal )
		{
			stI2c_Timer.usTimerCounter = 0;
			stNFC_StatusFlag_Bits.b2NFC_I2CBsy = 0;
			mHW_TIM6_INT_DISABLE();
		}
	}
	LL_TIM_ClearFlag_UPDATE ( TIM6 );
}