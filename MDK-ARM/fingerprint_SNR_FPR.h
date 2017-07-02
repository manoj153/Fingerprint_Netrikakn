#ifndef _FINGERPRINT_SNR_FPR_H
#define _FINGERPRINT_SNR_FPR_H
#include "stm32f7xx_hal.h"
/*includes*/
extern UART_HandleTypeDef huart6;
extern UART_HandleTypeDef huart1;
/*Function Prototypes*/
extern HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
extern void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
uint8_t VerifyUser(void);
uint8_t IsMasterUser(uint8_t UserID);
/*<<<<<<<<<<<<<<<<<<<<<<END FUNCTION PROTOTYPE>>>>>>>>>>>>>>>>>>>>>>>>>>*/

/*variable definiton*/
extern uint8_t UART_Rx_Cmplt_Flag; // declared in main.c 
/*<<<<<<<<<<<<End Variable Defination >>>>>>>*/

#define TRUE  1
#define FALSE 0
 
#define ACK_SUCCESS       0x00
#define ACK_FAIL          0x01
#define ACK_FULL          0x04
#define ACK_NO_USER		  	0x05
#define ACK_TIMEOUT       0x08
#define ACK_GO_OUT		  	0x0F

#define ACK_ALL_USER      0x00
#define ACK_GUEST_USER 	  0x01
#define ACK_NORMAL_USER		0x02
#define ACK_MASTER_USER		0x03

#define USER_MAX_CNT	   	40


//CMD 
#define CMD_HEAD		  			(uint8_t)0xF5
#define CMD_TAIL		  			(uint8_t)0xF5
#define CMD_ADD_1  		  		0x01 // adding user for first time 
#define CMD_ADD_2 		  		0x02 // adding user for second time 
#define CMD_ADD_3	  	  		0x03 // adding user for third time 
#define CMD_MATCH		  			0x0C 
#define CMD_DEL			  			0x04
#define CMD_DEL_ALL		  		0x05
#define CMD_USER_CNT    		0x09
#define CMD_COM_LEV					0x28
#define CMD_LP_MODE		  		0x2C
#define CMD_TIMEOUT		  		0x2E
#define CMD_FINGER_DETECTED 0x14


#endif /*_FINGERPRINT_H*/

