#include "main.h"
#include "VirtualTimer.h"

void SystemClock_Config ( void );
static void MX_GPIO_Init ( void );

uint32_t Test_counters[6];


void SysTick_Handler ( void )
{
	VirtualTimer_ISR();
}

int main ( void )
{

	HAL_Init ();
	SystemClock_Config ();
	MX_GPIO_Init ();

	mVIRTUAL_TIMER_SET( stVirtualTimer, TimerID_50ms, 55 );
	mVIRTUAL_TIMER_SET( stVirtualTimer, TimerID_100ms, 105 );
	mVIRTUAL_TIMER_SET( stVirtualTimer, TimerID_200ms, 205 );
	mVIRTUAL_TIMER_SET( stVirtualTimer, TimerID_300ms, 305 );
	mVIRTUAL_TIMER_SET( stVirtualTimer, TimerID_500ms, 505 );
	mVIRTUAL_TIMER_SET( stVirtualTimer, TimerID_1s, 1005 );



	while ( 1 )
	{
		switch ( stVirtualTimer.Timeout.ucTimerStatus )		// Timer events control
		{
			case (TRUE << TimerID_50ms):
			{
				mVIRTUAL_TIMER_RESET(stVirtualTimer,TimerID_50ms);
				++Test_counters [ TimerID_50ms ];
			}
				break;
			case (TRUE << TimerID_100ms):
			{
				mVIRTUAL_TIMER_RESET(stVirtualTimer,TimerID_100ms);

				++Test_counters [ TimerID_100ms ];

			}
				break;
			case (TRUE << TimerID_200ms):
			{
				mVIRTUAL_TIMER_RESET(stVirtualTimer,TimerID_200ms);

				++Test_counters [ TimerID_200ms ];

			}
				break;
			case (TRUE << TimerID_300ms):
			{
				mVIRTUAL_TIMER_RESET(stVirtualTimer,TimerID_300ms);

				++Test_counters [ TimerID_300ms ];

			}
				break;
			case (TRUE << TimerID_500ms):
			{
				mVIRTUAL_TIMER_RESET(stVirtualTimer,TimerID_500ms);

				++Test_counters [ TimerID_500ms ];

			}
				break;
			case (TRUE << TimerID_1s):
			{
				mVIRTUAL_TIMER_RESET(stVirtualTimer,TimerID_1s);

				++Test_counters [ TimerID_1s ];

			}
				break;
		}
	}
}

void SystemClock_Config ( void )
{
	RCC_OscInitTypeDef RCC_OscInitStruct =
	{ 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct =
	{ 0 };

	__HAL_PWR_VOLTAGESCALING_CONFIG( PWR_REGULATOR_VOLTAGE_SCALE1 );

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_8;
	RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
	if ( HAL_RCC_OscConfig ( &RCC_OscInitStruct ) != HAL_OK )
	{
		Error_Handler ();
	}
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if ( HAL_RCC_ClockConfig ( &RCC_ClkInitStruct, FLASH_LATENCY_1 ) != HAL_OK )
	{
		Error_Handler ();
	}
}

static void MX_GPIO_Init ( void )
{
	GPIO_InitTypeDef GPIO_InitStruct =
	{ 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE()
	;
	__HAL_RCC_GPIOH_CLK_ENABLE()
	;
	__HAL_RCC_GPIOA_CLK_ENABLE()
	;

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin ( LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET );

	/*Configure GPIO pin : BUTTON_Pin */
	GPIO_InitStruct.Pin = BUTTON_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init ( BUTTON_GPIO_Port, &GPIO_InitStruct );

	/*Configure GPIO pin : LED_Pin */
	GPIO_InitStruct.Pin = LED_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init ( LED_GPIO_Port, &GPIO_InitStruct );

}

void Error_Handler ( void )
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq ();
	while ( 1 )
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
