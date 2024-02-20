/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "key_pad_PTV.h"
#include "lcd_i2c.h"
#include "stdio.h"
#include "string.h"
#include "stm32f1_rc522.h"
#include "flash.h"
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
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
uint8_t status;
uint8_t str[16];
uint8_t serNum[5];
uint8_t status_1;
uint8_t str_1[16];
uint8_t serNum_1[5];
uint8_t keycard_1[]={5, 24, 0, 42, 55};
uint8_t keycard_2[]={-125, 98, 52, -9, 34};
uint8_t keycard_main[5][5];
static uint8_t so_the=1;
int dem=0;

char temp;
char password[4]="7777"; //Max lenght of password is 16 charaters
char keypass[4];
int cnt=0;
int them=0;
int xoa=0;
int doi=0;
int dem_so_trung=0;

LCD_I2C_HandleTypeDef p_LCD;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t CheckPass(char *Str1, char *Str2)
{
	for(int i=0;i<5;i++)
	{
		if(Str1[i]!=Str2[i])
			return 0;
	}
	return 1;
}

void EnterPassWord(void)
{
	HAL_Delay(25);
	do
	{
		temp = key_pad();
		if(temp != 0XFF && temp!='*'&& temp!='#')
		{
			HAL_Delay(25);
			keypass[cnt++] = temp;
			lcd_set_cursor(&p_LCD, 0, 1);
			lcd_send_string(&p_LCD, &temp);
			while(temp!= 0xFF) {temp = key_pad();}
			HAL_Delay(10);
		}
	}	while(temp!='*'); //while dk dung
	while(temp!= 0xFF) {temp = key_pad();}
	HAL_Delay(10);

	cnt=0;
	if(CheckPass(password,keypass)== 1)
	{
//		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,1);
		lcd_clear(&p_LCD);
		lcd_set_cursor(&p_LCD, 0, 0);
		lcd_send_string(&p_LCD, "Thanh Cong!");
		HAL_Delay(1000);
		  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,30);
		  HAL_Delay(1000);
		  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,100);
		  HAL_Delay(1000);
//		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,0);
		lcd_clear(&p_LCD);
	}
	else
	{
//		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,0);
		lcd_clear(&p_LCD);
		lcd_set_cursor(&p_LCD, 0, 0);
		lcd_send_string(&p_LCD, "MK sai!");
		HAL_Delay(1000);
		lcd_clear(&p_LCD);
	}
}

int hang_0(uint8_t mang[5])
{
    for(int i=0;i<5;i++)
    {
        if(mang[i]!=0)
            return 0;
    }
    return 1;
}

int vi_tri(uint8_t mang[5][5], int so_the)
{
    for(int i=0;i<so_the;i++)
    {
        if(hang_0(mang[i]))
            return i;
    }
    return 7;
}

void doi_hang(uint8_t mang[5][5], int so_the)
{
    int a=vi_tri(mang,so_the);
    if((a!=7)&&(a!=so_the))
    {
        for(int i=0;i<5;i++)
        {
            mang[a][i]=mang[so_the][i];
            mang[so_the][i]=0;
        }
    }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_SPI1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  MFRC522_Init();
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  lcd_i2c_init(&p_LCD, &hi2c1, 16, 2, 0x27<<1);
  lcd_clear(&p_LCD);
  lcd_set_cursor(&p_LCD, 0, 0);
  lcd_send_string(&p_LCD, "Moi quet the!");
  for(int i=0;i<5;i++)
  {
  	  keycard_main[0][i]=keycard_1[i];
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */





	  lcd_set_cursor(&p_LCD, 0, 0);
	  lcd_send_string(&p_LCD, "Moi quet the!");
	  temp = key_pad();

	  if(temp=='D')
	  {
		  Flash_Write_String(keycard_main[0],_PAGE_127_,5);
		  Flash_Write_String(keycard_main[1],_PAGE_126_,5);
		  Flash_Write_String(keycard_main[2],_PAGE_125_,5);
		  Flash_Write_String(keycard_main[3],_PAGE_124_,5);
		  Flash_Write_String(keycard_main[4],_PAGE_123_,5);
		  Flash_Write_Uint(so_the,_PAGE_122_);
	  }

	  if(temp=='0')
	  {
		  so_the=Flash_Read_Uint(_PAGE_122_);
		  Flash_Read_String(keycard_main[0],_PAGE_127_,5);
		  Flash_Read_String(keycard_main[1],_PAGE_126_,5);
		  Flash_Read_String(keycard_main[2],_PAGE_125_,5);
		  Flash_Read_String(keycard_main[3],_PAGE_124_,5);
		  Flash_Read_String(keycard_main[4],_PAGE_123_,5);
	  }

	  if(temp=='C')
	  {

		  HAL_Delay(25);

		do
		{
			temp = key_pad();
			if(temp != 0XFF && temp!='*'&& temp!='#')
			{
				HAL_Delay(25);
				keypass[doi++] = temp;
				lcd_set_cursor(&p_LCD, 0, 1);
				lcd_send_string(&p_LCD, &temp);
				while(temp!= 0xFF) {temp = key_pad();}
				HAL_Delay(10);
			}
		}	while(temp!='*'); //while dk dung
		while(temp!= 0xFF) {temp = key_pad();}
		HAL_Delay(10);

		doi=0;

		if(CheckPass(keypass,password))
		{
			do
			{
				temp = key_pad();
				if(temp != 0XFF && temp!='*'&& temp!='#')
				{
					HAL_Delay(25);
					password[doi++] = temp;
					lcd_set_cursor(&p_LCD, 0, 1);
					lcd_send_string(&p_LCD, &temp);
					while(temp!= 0xFF) {temp = key_pad();}
					HAL_Delay(10);
				}
			}	while(temp!='*'); //while dk dung
			while(temp!= 0xFF) {temp = key_pad();}
			HAL_Delay(10);
			doi=0;
		}
	  }

	  if (temp == 'A')
	  {
		  HAL_Delay(25);
		do
		{
			temp = key_pad();
			if(temp != 0XFF && temp!='*'&& temp!='#')
			{
				HAL_Delay(25);
				keypass[them++] = temp;
				lcd_set_cursor(&p_LCD, 0, 1);
				lcd_send_string(&p_LCD, &temp);
				while(temp!= 0xFF) {temp = key_pad();}
				HAL_Delay(10);
			}
		}	while(temp!='*'); //while dk dung
		while(temp!= 0xFF) {temp = key_pad();}
		HAL_Delay(10);

		them=0;
		if(CheckPass(keypass,password))
		{
			if(so_the!=5)
			{
				lcd_clear(&p_LCD);
				lcd_set_cursor(&p_LCD, 0, 0);
				lcd_send_string(&p_LCD, "The Moi!");

				for(int i=0;i<5;)
				{
					status_1 = MFRC522_Request(PICC_REQIDL, str_1);	//MFRC522_Request(0x26, str)
					status_1 = MFRC522_Anticoll(str_1);//Take a collision, look up 5 bytes
					if(status_1==0)
					{
						serNum_1[i]=str_1[i];
						keycard_main[so_the][i]=serNum_1[i];
						i++;
					}
				}

				so_the++;
				lcd_clear(&p_LCD);
				lcd_set_cursor(&p_LCD, 0, 0);
				lcd_send_string(&p_LCD, "Thanh cong!");
				for(int x=500000;x>0;x--);
				__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
				lcd_clear(&p_LCD);
			}
			else
			{
				lcd_clear(&p_LCD);
				lcd_set_cursor(&p_LCD, 0, 0);
				lcd_send_string(&p_LCD, "Hay xoa bot!");
				for(int x=500000;x>0;x--);
				__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
				lcd_clear(&p_LCD);
			}

		}
	  }
	  if (temp == 'B')
	  {
		  HAL_Delay(25);
		do
		{
			temp = key_pad();
			if(temp != 0XFF && temp!='*'&& temp!='#')
			{
				HAL_Delay(25);
				keypass[xoa++] = temp;
				lcd_set_cursor(&p_LCD, 0, 1);
				lcd_send_string(&p_LCD, &temp);
				while(temp!= 0xFF) {temp = key_pad();}
				HAL_Delay(10);
			}
		}	while(temp!='*'); //while dk dung
		while(temp!= 0xFF) {temp = key_pad();}
		HAL_Delay(10);

		xoa=0;
		if(CheckPass(keypass,password))
		{
			lcd_clear(&p_LCD);
			lcd_set_cursor(&p_LCD, 0, 0);
			lcd_send_string(&p_LCD, "Xoa the!");

			for(int i=0;i<5;)
			{
				status_1 = MFRC522_Request(PICC_REQIDL, str_1);	//MFRC522_Request(0x26, str)
				status_1 = MFRC522_Anticoll(str_1);//Take a collision, look up 5 bytes
				if(status_1==0)
				{
					serNum_1[i]=str_1[i];
					i++;
				}
//				for(int t=0;t<5;t++)
//				{
//					if(serNum_1[i]==keycard_main[t][i])
//						keycard_main[t][i]=0;
//				}
			}
			for(int i=0;i<5;i++)
			{
				for(int t=0;t<5;t++)
				{
					if(serNum_1[t]==keycard_main[i][t])
						dem_so_trung++;
				}
				if(dem_so_trung==5)
				{
					for(int m=0; m<5;m++)
					{
						keycard_main[i][m]=0;
					}
				}
				dem_so_trung=0;
			}
			so_the--;
			doi_hang(keycard_main,so_the);
			lcd_clear(&p_LCD);
			lcd_set_cursor(&p_LCD, 0, 0);
			lcd_send_string(&p_LCD, "Da xoa!");
			for(int x=500000;x>0;x--);
			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2);
			lcd_clear(&p_LCD);
			HAL_Delay(50);
		}
	  }


	  status = MFRC522_Request(PICC_REQIDL, str);	//MFRC522_Request(0x26, str)
	  status = MFRC522_Anticoll(str);//Take a collision, look up 5 bytes
	  for(int i=0;i<5;i++)
	  {
	  	if(status==0)
	  	{
	  		serNum[i]=str[i];
	  	}
	  }

	  for(int i=0;i<5;i++)
	  {
		  for(int t=0;t<5;t++)
		  {
			  if((serNum[t]==keycard_main[i][t])&&(status==0))
				  dem++;
			  else
				  dem--;
		  }
		  if(dem==5)
			  break;
		  dem=0;
	  }
	  if((dem==5))
	  {
	  	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,1);
	  	lcd_set_cursor(&p_LCD, 0, 1);
	  	lcd_send_string(&p_LCD, "Moi vao!");
		  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,30);
		  HAL_Delay(1000);
		  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,100);
		  HAL_Delay(1000);
	  	dem=0;
	  	status=2;
	  	HAL_Delay(1000);
	  	lcd_clear(&p_LCD);
	  	//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,0);
	  }
	  if((dem!=5)&&(status==MI_OK))
	  {
	  	//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,0);
	  	lcd_set_cursor(&p_LCD, 0, 1);
	  	lcd_send_string(&p_LCD, "Thu lai!");
	  	HAL_Delay(1000);
	  	lcd_clear(&p_LCD);
	  	dem=0;
	  }




		if(temp != 0xFF)
		{
			lcd_set_cursor(&p_LCD, 0, 1);
			lcd_send_string(&p_LCD, &temp);
			HAL_Delay(25);
			if(temp == '#')
			{
				EnterPassWord();
			}
			while(temp!= 0xFF) {temp = key_pad();}
		}

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 1439;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1000-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, R1_Pin|R2_Pin|R3_Pin|R4_Pin
                          |Chon_Slave_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Reset_GPIO_Port, Reset_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : R1_Pin R2_Pin R3_Pin R4_Pin
                           Chon_Slave_Pin */
  GPIO_InitStruct.Pin = R1_Pin|R2_Pin|R3_Pin|R4_Pin
                          |Chon_Slave_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : Reset_Pin */
  GPIO_InitStruct.Pin = Reset_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Reset_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : C1_Pin C2_Pin C3_Pin C4_Pin */
  GPIO_InitStruct.Pin = C1_Pin|C2_Pin|C3_Pin|C4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
