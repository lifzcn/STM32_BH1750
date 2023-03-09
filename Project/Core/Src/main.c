/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "oled.h"
#include "bh1750.h"
#include "steeringengine.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t x = 0;
	uint8_t y = 0;
	uint16_t lightValue = 0;
	uint8_t rxData[1];
	uint8_t cmdNum = 0;
	uint8_t lightLimit = 50;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_I2C2_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	OLED_Init();
	OLED_Clear();
	OLED_ShowChinese(x + 32, y, 0);
	OLED_ShowChinese(x + 32 + 16 * 1, y, 1);
	OLED_ShowChinese(x + 32 + 16 * 2, y, 2);
	OLED_ShowChinese(x + 32 + 16 * 3, y, 3);
	OLED_ShowChinese(x + 32, y + 2 * 1, 4);
	OLED_ShowChinese(x + 32 + 16 * 1, y + 2 * 1, 5);
	OLED_ShowChinese(x + 32 + 16 * 2, y + 2 * 1, 6);
	OLED_ShowChinese(x + 32 + 16 * 3, y + 2 * 1, 7);
	
	OLED_ShowChinese(x, y + 2 * 2, 8);
	OLED_ShowChinese(x + 16 * 1, y + 2 * 2, 9);
	OLED_ShowChinese(x, y + 2 * 3, 10);
	OLED_ShowChinese(x + 16 * 1, y + 2 * 3, 11);
	
	OLED_ShowChinese(x + 16 * 3 + 8, y + 2 * 3, 12);
	OLED_ShowChinese(x + 16 * 4 + 8, y + 2 * 3, 13);
	OLED_ShowChar(x + 16 * 5 + 8, y + 2 * 3, ':', 16);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		HAL_UART_Receive_IT(&huart1, rxData, 1);
		cmdNum = rxData[0];
		
		lightValue = Get_BH1750_Value();
		OLED_ShowNum(x + 16 * 2, y + 2 * 2, lightValue, 8, 16);
		OLED_ShowChar(x + 16 * 6 + 8 * 1, y + 2 * 2, 'L', 16);
		OLED_ShowChar(x + 16 * 6 + 8 * 2, y + 2 * 2, 'u', 16);
		OLED_ShowChar(x + 16 * 6 + 8 * 3, y + 2 * 2, 'x', 16);
		if(HAL_GPIO_ReadPin(Key_Auto_GPIO_Port, Key_Auto_Pin) == GPIO_PIN_RESET)
		{
			OLED_ShowChar(x + 96 + 8 * 0, y + 2 * 3, 'A', 16);
			OLED_ShowChar(x + 96 + 8 * 1, y + 2 * 3, 'u', 16);
			OLED_ShowChar(x + 96 + 8 * 2, y + 2 * 3, 't', 16);
			OLED_ShowChar(x + 96 + 8 * 3, y + 2 * 3, 'o', 16);
			if(lightValue<lightLimit)
			{
				HAL_Delay(200);
				closeCurtain();
			}
			else if(lightValue>lightLimit)
			{
				HAL_Delay(200);
				openCurtain();
			}
		}
		else if(HAL_GPIO_ReadPin(Key_Hand_GPIO_Port, Key_Hand_Pin) == GPIO_PIN_RESET)
		{
			OLED_ShowChar(x + 96 + 8 * 0, y + 2 * 3, 'H', 16);
			OLED_ShowChar(x + 96 + 8 * 1, y + 2 * 3, 'a', 16);
			OLED_ShowChar(x + 96 + 8 * 2, y + 2 * 3, 'n', 16);
			OLED_ShowChar(x + 96 + 8 * 3, y + 2 * 3, 'd', 16);
			if(HAL_GPIO_ReadPin(Key_Open_GPIO_Port, Key_Open_Pin) == GPIO_PIN_RESET || cmdNum == 1)
			{
				HAL_Delay(100);
				openCurtain();
			}
			else if(HAL_GPIO_ReadPin(Key_Close_GPIO_Port, Key_Close_Pin) == GPIO_PIN_RESET || cmdNum == 0)
			{
				HAL_Delay(100);
				closeCurtain();
			}
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
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
