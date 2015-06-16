/**
  ******************************************************************************
  * @file    TIM_PWM_Output/main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

#include "main.h"


  /*   At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f4xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f4xx.c file
  */

int main(void)

{

  LED_Config();
  Stepper_Drive_Control_GPIO_Config();
  Stepper_Control(DISABLE);          // Stepper-Drive Disable initially
  UART_Config(9600);                 // Setup USART1 with a baudrate of 9600
  ENCR_Config();

  UART_write(USART1, " <<<<<<<<<<<<<<<<<<< STM32 USART >>>>>>>>>>>>>>>>>>>>\n \r ");
  UART_write(USART1, "             USART17 connection initialized \n \r ");

  while (1){

	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
		{
			Encoder_Read();
		}
  	  }
}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  while (1)
  {}
}
#endif


/* ====================================== END OF FILE =============================================== */
