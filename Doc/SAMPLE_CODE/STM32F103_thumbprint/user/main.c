#include <stm32f10x.h>
#include "usart.h"
#include "timer.h"
#include "fingerprint.h"


/******************
LED1 Status indicator
LED2 Success indicator
LED3 Fail indicator
LED4 Full indicator
USER KEY		Add fingerprint
PRESS KEY 	Compare fingerprint
JOYSTICK C 	Delete all fingerprint
******************/
void delay()
{
	u16 i, j;
	for (i = 0; i < 1000; i++)
		for(j = 0; j < 10000; j++);
}

void USERGPIO_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG, ENABLE);	
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOF, &GPIO_InitStructure);					
 GPIO_ResetBits(GPIOF,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);						 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_8;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		
 GPIO_Init(GPIOG, &GPIO_InitStructure);				

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
 GPIO_Init(GPIOC, &GPIO_InitStructure);		
}

u8 key_scan(void)
{
	if(!USER_KEY||!PRESS_KEY||!DEL_KEY)
	{
		delay();
		if(!USER_KEY)	return 1;
		if(!PRESS_KEY) return 2;
		if(!DEL_KEY)	return 3;
	}
	return 0;
}

int main(void)
{
	int i = 5;
	SystemInit();
	USERGPIO_Init();
	usart_Configuration(19200,19200);	

	printf("Test Uart Fingerprint Reader\r\n");
 	SetcompareLevel(5);
	printf("Compare Level£º%d\r\n", GetcompareLevel());
	printf("Current timeout£º%d\r\n",GetTimeOut());
	printf("User:%d\r\n",GetUserCount());
	
	while(1)
	{	
		switch(key_scan())
		{
			case 1:
				printf("User:%d\r\n",GetUserCount());
				switch(AddUser(i))
				{
					case ACK_SUCCESS:
						i++;
						printf("Fingerprint is added successfully\r\n");
						LED2_ON;	
						delay();
						LED2_OFF;
						break;
					
					case ACK_FAIL: 			
						printf("Operation fails\r\n");
						LED3_ON;	
						delay();
						LED3_OFF;
						break;
					
					case ACK_FULL:			
						printf("Fingerprint is full\r\n");
						LED4_ON;
						delay();
						LED4_OFF;
						break;		
				}	
					break;
			case 2:
					switch(VerifyUser())
					{
						case ACK_SUCCESS:	
							printf("Match success\r\n");
							LED2_ON;	
							delay();
							LED2_OFF;
							break;
						case ACK_NO_USER:
							printf("No user\r\n");
							LED3_ON;	
							delay();
							LED3_OFF;
							break;
						case ACK_TIMEOUT:	
							printf("Timeout\r\n");
							LED3_ON;	
							delay();
							LED3_OFF;
							break;	
						case ACK_GO_OUT:
							printf("GO OUT\r\n");
							break;
					};
				break;
					
					
			case 3:
				ClearAllUser();
				printf("All users cleared\r\n");
				break;
		}
	}
}


