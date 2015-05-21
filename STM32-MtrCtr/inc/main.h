/*
 * main.h
 *
 *  Created on: May 20, 2015
 *      Author: patels
 */

#ifndef MAIN_H_
#define MAIN_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"
#include <stm32f4xx.h>
#include <misc.h>
#include <stm32f4xx_usart.h>
#include "stm32f4_discovery.h"
#include "UartSerial.h"
#include <stdio.h>
#include <stdint.h>

/** @addtogroup STM32F4_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup TIM_PWM_Output
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define BUFFER_SIZE 16
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


//notice the use of the volatile keyword this is important as without it the compiler may make
//optimisations assuming the value of this variable hasnt changed
volatile char received_buffer[BUFFER_SIZE+1];

static uint8_t DataReceivedCounter = 0; //tracks the number of characters received so far, reset after each command

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
I2C_TypeDef I2C_1;
GPIO_InitTypeDef GPIO_InitStructureuart;
USART_InitTypeDef USART_InitStructure;


uint16_t CCR1_Val = 466;
uint16_t CCR2_Val = 233;
uint16_t CCR3_Val = 116;
uint16_t CCR4_Val = 58;
uint16_t PrescalerValue = 0;



int buff = 55 ;

int dataRX;
int offset = 0 ;
int MSBdataRX = 0;
int dataAdd = 0;
int i = 0 ;

/* Private function prototypes -----------------------------------------------*/
void TIM_Config(void);
void I2C_Config(void);
void LED_Config(void);
void i2c_init2(void);

void USARTCommandReceived(char * command);
void ClearCommand();
void Delay(int nCount);
void ConfigureUsart(int baudrate);

//void USART_Configuration(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */



#endif /* MAIN_H_ */
