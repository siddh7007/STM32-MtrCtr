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

int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f4xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f4xx.c file
     */

  /* TIM Configuration */
  LED_Config();
  TIM_Config();
  UART_Config(9600); // setup usart 1 with a baudrate of 9600
  pwm_initconfig();

SendData(USART1, " <<<<<<<<<<<<<<<<<<< STM32 USART >>>>>>>>>>>>>>>>>>>>\n \r ");
SendData(USART1, "             USART3 connection initialised \n \r ");

while (1){
	  Delay(900000);
	  STM_EVAL_LEDOn(LED6);
	  STM_EVAL_LEDOn(LED5);
	  STM_EVAL_LEDOn(LED4);
	  STM_EVAL_LEDOn(LED3);
}


}


//writes out a string to the passed in usart. The string is passed as a pointer
void SendData(USART_TypeDef* USARTx, volatile char *s){

	while(*s){
		// wait until data register is empty
		while( !(USARTx->SR & 0x00000040) );
		USART_SendData(USARTx, *s);
		(*s)++;
	}
}


//This method is executed when data is received on the RX line (this is the interrupt), this method can process the
//data thats been received and decide what to do. It is executed for each character received, it reads each character
//and checks to see if it received the enter key (ascii code 13) or if the total number of characters received is greater
//that the buffer size.
//Note that there is no reference to this method in our setup code, this is because the name of this method is defined in the
//startup_stm32f4xx.S (you can find this in the startup_src folder). When listening for interrupts from USART 2 or 3 you would
//define methods named USART2_IRQHandler or USART3_IRQHandler
void USART1_IRQHandler(void){
	//check the type of interrupt to make sure we have received some data.
	if( USART_GetITStatus(USART1, USART_IT_RXNE) ){
		char t = USART1->DR; //Read the character that we have received

		if( (DataReceivedCounter < BUFFER_SIZE) && t != 13 ){
			received_buffer[DataReceivedCounter] = t;
			DataReceivedCounter++;
		}
		else{ // otherwise reset the character counter and print the received string
			DataReceivedCounter = 0;
			//only raise a command event if the enter key was pressed otherwise just clear
			if(t == 13){
				USARTCommandReceived(received_buffer);
			}

			ClearCommand();

		}
	}
}

//this method is called when a command is received from the USART, a command is only received when enter
//is pressed, if the buffer length is exceeded the buffer is cleared without raising a command
void USARTCommandReceived(char * command){
	SendData(USART1, received_buffer);

	if        (compare(command, "L5ON") == 0){
		STM_EVAL_LEDOn(LED5);
	}else 	if(compare(command, "L5OFF") == 0){
		STM_EVAL_LEDOff(LED5);

	}else 	if(compare(command, "L6ON") == 0){
		STM_EVAL_LEDOn(LED6);
	}else 	if(compare(command, "L6OFF") == 0){
		STM_EVAL_LEDOff(LED6);

	}else 	if(compare(command, "L3ON") == 0){
		STM_EVAL_LEDOn(LED3);
	}else 	if(compare(command, "L3OFF") == 0){
		STM_EVAL_LEDOff(LED3);

	}else 	if(compare(command, "L4ON") == 0){
		STM_EVAL_LEDOn(LED4);
	}else 	if(compare(command, "L4OFF") == 0){
		STM_EVAL_LEDOff(LED4);
	}

	SendData(USART1, "             NO MATCH \n \r ");
	STM_EVAL_LEDOn(LED6);
}
void ClearCommand(){
	int i =0;
	for(i=0;i < BUFFER_SIZE; i++){
		received_buffer[i] = 0;
	}

}

void Delay(int nCount) {
  while(nCount--) {
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

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
