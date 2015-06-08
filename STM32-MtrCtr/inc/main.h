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


void UART_Config(int baudrate);


#endif /* MAIN_H_ */
