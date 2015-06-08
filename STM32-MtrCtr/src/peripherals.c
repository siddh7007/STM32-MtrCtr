/*
 * peripherals.c
 *
 *  Created on: May 20, 2015
 *      Author: patels
 */
#include "peripherals.h"

/*================ LEDs and Button Configuration ================================  */

LED_Config(void)

{
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);
	STM_EVAL_PBInit(BUTTON_USER , BUTTON_MODE_GPIO);
}

/*================ TIM3 Configuration ============================================  */

void TIM_Config(void)

{
	GPIO_InitTypeDef GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/* GPIOC and GPIOB clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOA, ENABLE);

	/* GPIOC Configuration: TIM3 CH1 (PC6) and TIM3 CH2 (PC7) */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN ;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	  /* Configure the GPIOB pin 4*/
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* Connect TIM3 pins to AF2 */
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);

	/* Enable the TIM3 gloabal Interrupt */
	 NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Init(&NVIC_InitStructure);


}

/*================ UART Configuration ==============================================  */

void UART_Config(int baudrate)

{
	//structures used configure the hardware
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;

	//enable the clocks for the GPIOB and the USART
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	//Initialize pins GPIOB 6 and GPIOB 7
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; //we are setting the pin to be alternative function
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	//Connect the TX and RX pins to their alternate function pins
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1); //
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

	//configure USART
	USART_InitStruct.USART_BaudRate = baudrate;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //enable send and receive (Tx and Rx)
	USART_Init(USART1, &USART_InitStruct);

	//Enable the interrupt
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// finally this enables the complete USART1 peripheral
	USART_Cmd(USART1, ENABLE);
}

/*================ Encoder TIM Configuration =========================================  */

void ENCR_Config(void)

{


	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM2, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;


	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);



	  // set both inputs to rising polarity to let it use both edges
	  TIM_EncoderInterfaceConfig (TIM2, TIM_EncoderMode_TI12,
	                              TIM_ICPolarity_Rising,
	                              TIM_ICPolarity_Rising);

	  TIM_SetAutoreload (TIM2, 0xffff);

	  TIM_Cmd (TIM2, ENABLE);
}
