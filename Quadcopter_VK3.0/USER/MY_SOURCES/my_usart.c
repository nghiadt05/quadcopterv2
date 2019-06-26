#include "my_usart.h"

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
	
//----- variables -----	
uint8_t usart_port=1;
//---------------------	

void usart_putchar(USART_TypeDef* USARTx, uint16_t Data)
{    
  /* Transmit Data */
  USARTx->DR = (Data & (uint16_t)0x01FF);
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}
}

#ifdef usart_1
void USART1_Config(uint32_t baudrate)
{
	//---type define -------
	GPIO_InitTypeDef GPIOA_InitStructure;
	USART_InitTypeDef USART1_InitStructure;
	NVIC_InitTypeDef  USART1_NVIC_InitStructure;
	//----------------------
	
	//---- enable clock for all relative components -----------
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//---------------------------------------------------------
	
	//--- config pa10(rx) as input_pp_pin, pa9(tx) as output_pp_pin----
	GPIOA_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIOA_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIOA_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;
	GPIOA_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIOA_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIOA_InitStructure);	
		
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	//---------------------------------------------------------
	
	//---- config the specific operation of the usart1 --------
	USART1_InitStructure.USART_BaudRate=baudrate;
	USART1_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART1_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART1_InitStructure.USART_Parity=USART_Parity_No;
	USART1_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_Init(USART1,&USART1_InitStructure);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//enable received complet interrupt
	USART_ITConfig(USART1,USART_IT_TC,DISABLE);
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);//clear received complete intr flag for the first detection
	//---------------------------------------------------------
	
	//---- config the NVIC for received interrupt -------------
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	USART1_NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	USART1_NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	USART1_NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	USART1_NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&USART1_NVIC_InitStructure);
	//---------------------------------------------------------
		
	//------ enable USART1--------
	USART_Cmd(USART1, ENABLE);
	//----------------------------
}
#endif

#ifdef usart_2
void USART2_Config(uint32_t baudrate)
{
	//---type define -------
	GPIO_InitTypeDef GPIOA_InitStructure;
	USART_InitTypeDef USART2_InitStructure;
	NVIC_InitTypeDef  USART2_NVIC_InitStructure;
	//----------------------
	
	//---- enable clock for all relative components -----------
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//---------------------------------------------------------
	
	//--- config pa3(rx) as input_pp_pin, do not use pa2(tx) as output_pp_pin----
	GPIOA_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIOA_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIOA_InitStructure.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_2;
	GPIOA_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIOA_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIOA_InitStructure);	
		
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
	//---------------------------------------------------------
	
	//---- config the specific operation of the usart1 --------	
	USART2_InitStructure.USART_BaudRate=baudrate;
	USART2_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART2_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART2_InitStructure.USART_Parity=USART_Parity_Even;
	USART2_InitStructure.USART_StopBits=USART_StopBits_2;
	USART_Init(USART2,&USART2_InitStructure);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//enable received complet interrupt
	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	//---------------------------------------------------------
	
	//---- config the NVIC for received interrupt -------------
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	USART2_NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	USART2_NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	USART2_NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	USART2_NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&USART2_NVIC_InitStructure);
	//---------------------------------------------------------
	
	//------ enable USART2--------
	USART_Cmd(USART2, ENABLE);
	//----------------------------
}

//move to FUTABA_SBUS.h
//void USART2_IRQHandler(void)
//{
//	if(USART_GetITStatus(USART2,USART_IT_RXNE))//receive complete
//	{
//		char rx = USART2->DR;
//		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
//	}
//}
#endif

#ifdef usart_3
void USART3_Config(uint32_t baudrate)
{
	//---type define -------
	GPIO_InitTypeDef GPIOB_InitStructure;
	USART_InitTypeDef USART3_InitStructure;
	NVIC_InitTypeDef  USART3_NVIC_InitStructure;
	//----------------------
	
	//---- enable clock for all relative components -----------
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	//---------------------------------------------------------
	
	//--- config pb10(tx) as input_pp_pin, pb11(rx) as output_pp_pin----
	GPIOB_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIOB_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIOB_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIOB_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIOB_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&GPIOB_InitStructure);	
		
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);
	//---------------------------------------------------------
	
	//---- config the specific operation of the usart3 --------
	USART3_InitStructure.USART_BaudRate=baudrate;
	USART3_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART3_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART3_InitStructure.USART_Parity=USART_Parity_No;
	USART3_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_Init(USART3,&USART3_InitStructure);	
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//enable received complet interrupt
	USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	//---------------------------------------------------------
	
	//---- config the NVIC for received interrupt -------------
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	USART3_NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;
	USART3_NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	USART3_NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	USART3_NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&USART3_NVIC_InitStructure);
	//---------------------------------------------------------
	
	//------enable USART3--------
	USART_Cmd(USART3,ENABLE);
	//----------------------------
}
/*
//move to file "GPS_6MV2.h"
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3,USART_IT_RXNE))//receive complete
	{
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	}
}
*/
#endif


#ifdef usart_6

void USART6_Config(uint32_t baudrate)
{
	//---type define -------
	GPIO_InitTypeDef GPIOC_InitStructure;
	USART_InitTypeDef USART6_InitStructure;
	NVIC_InitTypeDef  USART6_NVIC_InitStructure;
	//----------------------
	
	//---- enable clock for all relative components -----------
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);
	//---------------------------------------------------------
	
	//--- config pc6(tx) as input_pp_pin, pc7(rx) as output_pp_pin----
	GPIOC_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIOC_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIOC_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIOC_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIOC_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIOC_InitStructure);	
		
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6);
	//---------------------------------------------------------
	
	//---- config the specific operation of the usart1 --------
	USART6_InitStructure.USART_BaudRate=baudrate;
	USART6_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART6_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART6_InitStructure.USART_Parity=USART_Parity_No;
	USART6_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_Init(USART6,&USART6_InitStructure);
	USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);
	USART_ClearFlag(USART6,USART_FLAG_RXNE);
	USART_ClearITPendingBit(USART6,USART_IT_RXNE);
	//---------------------------------------------------------
	
	//---- config the NVIC for received interrupt -------------
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	USART6_NVIC_InitStructure.NVIC_IRQChannel=USART6_IRQn;
	USART6_NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	USART6_NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	USART6_NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&USART6_NVIC_InitStructure);
	//---------------------------------------------------------
	
	//------ enable USART6--------
	USART_Cmd(USART6, ENABLE);
	//----------------------------
}
#endif

PUTCHAR_PROTOTYPE
{
	switch(usart_port)
	{
		case 1:
				USART_SendData(USART1,(uint8_t)ch);
				while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){}
				break;
		case 2:
				USART2->DR = ((uint16_t)ch & (uint16_t)0x01FF);
				while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){}		
				break;
		case 3:
				USART3->DR = ((uint16_t)ch & (uint16_t)0x01FF);
				while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET){}		
				break;
		case 6:
				USART6->DR = ((uint16_t)ch & (uint16_t)0x01FF);
				while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET){}		
				break;
	}
	return ch;	
} 

