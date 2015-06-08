#include "pwm_ctr.h"
#include "main.h"

//GLOBAL
volatile int16_t Codeur_count;
volatile int32_t Codeur_total;

//LOCAL
static volatile int16_t Codeur_old;
static volatile int16_t Codeur_actual;
char buffer[33];


int pwm_initconfig(int OutFreq)

{
	GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	TIM_Config();

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	uint16_t PrescalerValue = 0;
	  /* -----------------------------------------------------------------------
	    TIM3 Configuration: generate 4 PWM signals with 4 different duty cycles.

	    In this example TIM3 input clock (TIM3CLK) is set to 2 * APB1 clock (PCLK1),
	    since APB1 prescaler is different from 1.
	      TIM3CLK = 2 * PCLK1
	      PCLK1 = HCLK / 4
	      => TIM3CLK = HCLK / 2 = SystemCoreClock /2

	    To get TIM3 counter clock at 28 MHz, the prescaler is computed as follows:
	       Prescaler = (TIM3CLK / TIM3 counter clock) - 1
	       Prescaler = ((SystemCoreClock /2) /28 MHz) - 1

	    To get TIM3 output clock at 30 KHz, the period (ARR)) is computed as follows:
	       ARR = (TIM3 counter clock / TIM3 output clock) - 1
	           = 665

	           ARR will be 13 for 2MHz

	    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
	    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%
	    TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
	    TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%

	    Note:
	     SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
	     Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
	     function to update SystemCoreClock variable value. Otherwise, any configuration
	     based on this variable will be incorrect.
	  ----------------------------------------------------------------------- */

	  /* Compute the prescaler value */

	  int TimFreq, Period ;

	  TimFreq = 14000000 ;
	  //OutFreq = 5000 ;
	  Period  = 14000000/OutFreq ;

	  PrescalerValue = (uint16_t) ((SystemCoreClock /2) / TimFreq) - 1;

	  //PrescalerValue = (uint16_t) 0;
	  /* Time base configuration */
	  TIM_TimeBaseStructure.TIM_Period = Period - 1;
	  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned3;

	  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	  /* PWM1 Mode configuration: Channel1 */
	  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = Period / 2;
	  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

	  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);


	  TIM_ARRPreloadConfig(TIM3, ENABLE);

	   /* TIM IT enable */
	  //    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	  ENCR_Config() ;


	  /* TIM3 enable counter */
	  TIM_Cmd(TIM3, ENABLE);

 return 0 ;
}


int pwm_deinitconfig(void)

{

	TIM_Cmd(TIM3, DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, DISABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, DISABLE);
	GPIO_SetBits(GPIOB,GPIO_Pin_4);
	return 0 ;
}


void CODEUR_Read (void)
{
    Codeur_old = Codeur_actual;
    Codeur_actual = TIM_GetCounter (TIM2) ;
    Codeur_count = Codeur_actual - Codeur_old;
    Codeur_total += Codeur_count;
    itoa (Codeur_total,buffer,10);
    UART_write(USART1, buffer) ;
    UART_write(USART1, "\n \r ");
}


setpwm_freq_dutycycle(int freq,int dutycycle)

{


}
