#ifndef __PORT_INIT_H
#define	__PORT_INIT_H

#include "stm32f10x.h"


#define heart_beat_led_on() GPIO_SetBits(GPIOE,GPIO_Pin_2)

#define heart_beat_led_off() GPIO_ResetBits(GPIOE,GPIO_Pin_2)
					
#define close_MAIN_CONT_relay() GPIO_SetBits(GPIOC,GPIO_Pin_1)

#define	open_MAIN_CONT_relay()	GPIO_ResetBits(GPIOC,GPIO_Pin_1)
					
#define close_error1_relay() GPIO_SetBits(GPIOC,GPIO_Pin_2)

#define	open_error1_relay()	GPIO_ResetBits(GPIOC,GPIO_Pin_2)
					
#define close_error2_relay() GPIO_SetBits(GPIOC,GPIO_Pin_3)

#define	open_error2_relay()	GPIO_ResetBits(GPIOC,GPIO_Pin_3)

void LED_GPIO_Config(void);
void OUTPUT_GPIOC_Config(void);
void LED_GPIO_Config_1(void)	;
					
#endif /* __LED_H */
