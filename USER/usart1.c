/******************** ��ʢ���ӹ����� ********************
 * �ļ���  ��usart1.c
 * ����    ������USART1         
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103VET6
 * Ӳ�����ӣ�------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
 * ��汾  ��ST3.0.0  
 * �Ա��꣺http://shop66177872.taobao.com
**********************************************************************************/

#include "usart1.h"
#include <stdarg.h>

__IO u8 usart1_receive_array[8];  

void Delay_n(__IO u32 nCount)
{
  for(; nCount != 0; nCount--);
} 


void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* ʹ�� USART1 ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); 

	/* USART1 ʹ��IO�˿����� */    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);    
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);   //��ʼ��GPIOA
	
	USART_InitStructure.USART_BaudRate = 115200;	//���������ã�115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//ֹͣλ���ã�1λ

	USART_InitStructure.USART_Parity = USART_Parity_No ;  //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�����뷢�Ͷ�ʹ��
	USART_Init(USART1, &USART_InitStructure);  //��ʼ��USART1
	USART_Cmd(USART1, ENABLE);// USART1ʹ��
	
} 

 /*����һ���ֽ�����*/
 void UART1SendByte(unsigned char SendData)
{	   
        USART_SendData(USART1,SendData);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	    
}  

//����һ���ֽ�����
/*
unsigned char UART1GetByte(unsigned char* GetData)
{   	   
        if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        {  return 0;//û���յ����� 
		}
        *GetData = USART_ReceiveData(USART1); 
        return 1;//�յ�����
}
*/
/*����һ���ֽ�����*/
unsigned char UART1GetByte(void)
{
		u8 usart1_receive_status = 0 ;
	
        if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
				{
					usart1_receive_status = 0 ;
				}
				else
				{
					usart1_receive_array[0] = USART_ReceiveData(USART1);
          usart1_receive_status = 1 ;
				}
				return usart1_receive_status ;
}


 /* ����  ���ض���c�⺯��printf��USART1*/ 
int fputc(int ch, FILE *f)
{
/* ��Printf���ݷ������� */
  USART_SendData(USART1, (unsigned char) ch);
  while (!(USART1->SR & USART_FLAG_TXE));
 
  return (ch);
}

