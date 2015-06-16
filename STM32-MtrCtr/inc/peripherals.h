/*
 * peripherals.h
 *
 *  Created on: May 20, 2015
 *      Author: patels
 */

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_


#include <stm32f4xx.h>
#include <misc.h>
#include <stm32f4xx_usart.h>
#include "stm32f4_discovery.h"
#include <stdio.h>
#include <stdint.h>



/* Private function prototypes -----------------------------------------------*/

void PWM_TIM3_Config(void);
void TIM1_Config(void);
void Stepper_Drive_Control_GPIO_Config(void);
void ENCR_Config(void);
void GPIO_Config(void);
void I2C_Config(void);
void LED_Config(void);
void UART_Config(int baudrate);


#endif /* PERIPHERALS_H_ */
