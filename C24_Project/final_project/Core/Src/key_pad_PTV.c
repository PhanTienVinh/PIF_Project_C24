#include "key_pad_PTV.h"
#include "main.h"

uint8_t key_pad()
{

    HAL_GPIO_WritePin (GPIOA,GPIO_PIN_0, GPIO_PIN_RESET);  //Pull the R1 low
	  HAL_GPIO_WritePin (GPIOA, GPIO_PIN_1, GPIO_PIN_SET);  // Pull the R2 High
	  HAL_GPIO_WritePin (GPIOA, GPIO_PIN_2, GPIO_PIN_SET);  // Pull the R3 High
	  HAL_GPIO_WritePin (GPIOA, GPIO_PIN_3, GPIO_PIN_SET);  // Pull the R4 High

	  if (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12)))   // if the Col 1 is low
	  {
	  	while (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12)));   // wait till the button is pressed
            return '1';
	  }

	  if (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_13)))   // if the Col 2 is low
	  {
	  	while (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_13)));   // wait till the button is pressed
	  	return '2';
	  }

	  if (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_14)))   // if the Col 3 is low
	  {
	  	while (!(HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_14)));   // wait till the button is pressed
	  	return '3';
	  }

	  if (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_15)))   // if the Col 4 is low
	  {
	  	while (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_15)));   // wait till the button is pressed
	  	return 'A';
	  }
	  // second row set to 0
	  HAL_GPIO_WritePin (GPIOA,GPIO_PIN_0, GPIO_PIN_SET);  //Pull the R1 low
	  	  HAL_GPIO_WritePin (GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);  // Pull the R2 High
	  	  HAL_GPIO_WritePin (GPIOA, GPIO_PIN_2, GPIO_PIN_SET);  // Pull the R3 High
	  	  HAL_GPIO_WritePin (GPIOA, GPIO_PIN_3, GPIO_PIN_SET);  // Pull the R4 High

	  	  if (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12)))   // if the Col 1 is low
	  	  {
	  	  	while (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12)));   // wait till the button is pressed
	  	  	return '4';
	  	  }

	  	  if (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_13)))   // if the Col 2 is low
	  	  {
	  	  	while (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_13)));   // wait till the button is pressed
	  	  	return '5';
	  	  }

	  	  if (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_14)))   // if the Col 3 is low
	  	  {
	  	  	while (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_14)));   // wait till the button is pressed
	  	  	return '6';
	  	  }

	  	  if (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_15)))   // if the Col 4 is low
	  	  {
	  	  	while (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_15)));   // wait till the button is pressed
	  	  	return 'B';
	  	  }
	  // Third row to 0
	  	HAL_GPIO_WritePin (GPIOA,GPIO_PIN_0, GPIO_PIN_SET);  //Pull the R1 low
	  	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_1, GPIO_PIN_SET);  // Pull the R2 High
	  	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);  // Pull the R3 High
	  	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_3, GPIO_PIN_SET);  // Pull the R4 High

	  		if (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12)))   // if the Col 1 is low
	  		  {
	  		  	while (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12)));   // wait till the button is pressed
	  		  	return '7';
	  		  }

	  		  if (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_13)))   // if the Col 2 is low
	  		  {
	  		  	while (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_13)));   // wait till the button is pressed
	  		  	return '8';
	  		  }

	  		  if (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_14)))   // if the Col 3 is low
	  		  {
	  		  	while (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_14)));   // wait till the button is pressed
	  		  	return '9';
	  		  }

	  		  if (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_15)))   // if the Col 4 is low
	  		  {
	  		  	while (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_15)));   // wait till the button is pressed
	  		  	return 'C';
	  		  }
	  	// Fourth row to 0
	  		HAL_GPIO_WritePin (GPIOA,GPIO_PIN_0, GPIO_PIN_SET);  //Pull the R1 low
	  		HAL_GPIO_WritePin (GPIOA, GPIO_PIN_1, GPIO_PIN_SET);  // Pull the R2 High
	  		HAL_GPIO_WritePin (GPIOA, GPIO_PIN_2, GPIO_PIN_SET);  // Pull the R3 High
	  		HAL_GPIO_WritePin (GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);  // Pull the R4 High

	  			  if (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12)))   // if the Col 1 is low
	  			  {
	  			  	while (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12)));   // wait till the button is pressed
	  			  	return '*';
	  			  }

	  			  if (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_13)))   // if the Col 2 is low
	  			  {
	  			  	while (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_13)));   // wait till the button is pressed
	  			  	return '0';
	  			  }

	  			  if (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_14)))   // if the Col 3 is low
	  			  {
	  			  	while (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_14)));   // wait till the button is pressed
	  			  	return '#';
	  			  }

	  			  if (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_15)))   // if the Col 4 is low
	  			  {
	  			  	while (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_15)));   // wait till the button is pressed
	  			  	return 'D';
	  			  }

	  			  return 0xFF;

}
