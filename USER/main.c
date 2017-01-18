/******************** ��ʢ���ӹ����� ********************
 * �ļ���  ��main.c
 * ����    �������ϵ�LED1��LED2��LED3������˸��         
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103VET6
 * ��汾  ��ST3.0.0  																										  
 * �Ա��꣺http://shop66177872.taobao.com
*********************************************************/	

#include "stm32f10x.h"
#include "port_init.h"
#include "usart1.h"
#include "adc.h"
#include "can.h"
#include "exti.h"

extern __IO u16 ADC_ConvertedValue;	 
extern __IO uint16_t ADCConvertedValue[5];  
extern __IO u8 usart1_receive_array[8];  

void Delay(__IO u32 nCount); 

int main(void)
{
	u32 AD_value;	    
	SystemInit();	// ����ϵͳʱ��Ϊ72M 	
	LED_GPIO_Config(); //LED �˿ڳ�ʼ�� 
	LED_GPIO_Config_1()	;
	OUTPUT_GPIOC_Config();	
	CAN_GPIO_Config();//CAN�ܽų�ʼ��
	CAN_NVIC_Configuration(); //CAN�жϳ�ʼ��   
	CAN_INIT();//CAN��ʼ��ģ��	
	USART1_Config(); //USART1 ���� 
	ADC1_Init();
  EXTI_PC4_Config(); //����PB1���ж϶˿���
	
  while (1)
  {
		//heart_beat_led_on();			  // ��
		Delay(0x200000);
		close_MAIN_CONT_relay();
		//heart_beat_led_off();			  // ��  
		Delay(0x200000);
    //open_MAIN_CONT_relay();		
		
		if(UART1GetByte())
		{
			USART_SendData(USART1,98);
		}
		
		can_tx(0X99,0Xbb); 	
		
		
		AD_value  = 3300000/4096*ADCConvertedValue[0]/1000;
	  printf("IN_VOLT = %d mV  \r\n", AD_value);
		
		AD_value  = 3300000/4096*ADCConvertedValue[1]/1000;
	  printf("IN_CURR = %d mV  \r\n", AD_value);
		
		AD_value  = 3300000/4096*ADCConvertedValue[2]/1000;
	  printf("OUT_VOLT = %d mV  \r\n", AD_value);
		
		AD_value  = 3300000/4096*ADCConvertedValue[3]/1000;
	  printf("OUT_CURR = %d mV  \r\n", AD_value);
		
		AD_value  = 3300000/4096*ADCConvertedValue[4]/1000;
	  printf("MEAS_REF = %d mV  \r\n", AD_value);
		
  }
}

void Delay(__IO u32 nCount)
{
  for(; nCount != 0; nCount--);
} 



