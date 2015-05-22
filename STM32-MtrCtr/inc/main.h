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
#include "peripherals.h"
#include "uartserial.h"

#include <stm32f4xx.h>
#include <misc.h>
#include <stm32f4xx_usart.h>
#include <stdio.h>
#include <stdint.h>


/* Private typedef -----------------------------------------------------------*/



I2C_TypeDef I2C_1;
GPIO_InitTypeDef GPIO_InitStructureuart;
USART_InitTypeDef USART_InitStructure;

/* Private define ------------------------------------------------------------*/

#define BUFFER_SIZE 32

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


//notice the use of the volatile keyword this is important as without it the compiler may make
//optimisations assuming the value of this variable hasnt changed
volatile char received_buffer[BUFFER_SIZE+1];

static uint8_t DataReceivedCounter = 0; //tracks the number of characters received so far, reset after each command



/* Private function prototypes -----------------------------------------------*/

void USARTCommandReceived(char * command);
void ClearCommand();
void Delay(int nCount);
void UART_Config(int baudrate);


#endif /* MAIN_H_ */
