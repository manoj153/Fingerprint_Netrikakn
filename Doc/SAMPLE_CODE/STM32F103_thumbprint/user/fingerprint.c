#include "fingerprint.h"


u8 gRsBuf[9];			
u8 gTxBuf[9];				 
u8 gRsLength;

static void delay()
{
	u16 i, j;
	for (i = 0; i < 1000; i++)
		for(j = 0; j < 10000; j++);
}


void TxByte(u8 temp)
{
	USART_SendData(FG_UART,temp);
	while (USART_GetFlagStatus(FG_UART, USART_FLAG_TXE) == RESET);
}

u8 TxAndRsCmd(u8 Scnt, u8 Rcnt, u8 Delay)
{
	 /*Rcnt stands for how many byte will be received*/
   u8  i, j, CheckSum;
	 u32 RsTimeCnt;
	 TxByte(CMD_HEAD);	 //0xF5 start bit 
	 CheckSum = 0;
	 for (i = 0; i < Scnt; i++)
	 {
			TxByte(gTxBuf[i]);		 
			CheckSum ^= gTxBuf[i];
	 }	
	 TxByte(CheckSum);
	 TxByte(CMD_TAIL);  
	 gRsLength = 0; // Very importance to make it zero // This variable is incriment by UART interupt for calculating nu. of bytes revceived
	 RsTimeCnt = Delay * 120000; // implimenting a delay like 
	 while (gRsLength < Rcnt && RsTimeCnt > 0)
			RsTimeCnt--; 

	 if (gRsLength != Rcnt)return ACK_TIMEOUT;
	 if (gRsBuf[0] != CMD_HEAD) return ACK_FAIL;
	 if (gRsBuf[Rcnt - 1] != CMD_TAIL) return ACK_FAIL;
	 if (gRsBuf[1] != (gTxBuf[0])) return ACK_FAIL;
	 
	 CheckSum = 0;
	 for (j = 1; j < gRsLength - 1; j++) CheckSum ^= gRsBuf[j];
	 if (CheckSum != 0) return ACK_FAIL; 	  // if == Ox00 then ACK sucess 

 	 return ACK_SUCCESS;
}	 


u8 GetUserCount(void)
{
  u8 m;
	
	gTxBuf[0] = CMD_USER_CNT;
	gTxBuf[1] = 0;
	gTxBuf[2] = 0;
	gTxBuf[3] = 0;
	gTxBuf[4] = 0;	
	
	m = TxAndRsCmd(5, 8, 10);
		
	if (m == ACK_SUCCESS && gRsBuf[4] == ACK_SUCCESS)
	{
	    return gRsBuf[3];
	}
	else
	{
	 	return 0xFF;
	}
}

u8 GetcompareLevel(void)
{
	u8 m;
	
	gTxBuf[0] = CMD_COM_LEV;
	gTxBuf[1] = 0;
	gTxBuf[2] = 0;
	gTxBuf[3] = 1;
	gTxBuf[4] = 0;	
	
	m = TxAndRsCmd(5, 8, 10);
		
	if (m == ACK_SUCCESS && gRsBuf[4] == ACK_SUCCESS)
	{
	    return gRsBuf[3];
	}
	else
	{
	 	return 0xFF;
	}
}

u8 SetcompareLevel(u8 temp)
{
	u8 m;
	
	gTxBuf[0] = CMD_COM_LEV;
	gTxBuf[1] = 0;
	gTxBuf[2] = temp;
	gTxBuf[3] = 0;
	gTxBuf[4] = 0;	
	
	m = TxAndRsCmd(5, 8, 10);
		
	if (m == ACK_SUCCESS && gRsBuf[4] == ACK_SUCCESS)
	{
	    return gRsBuf[3];
	}
	else
	{
	 	return 0xFF;
	}
}

u8 GetTimeOut(void)
{
	u8 m;
	
	gTxBuf[0] = CMD_TIMEOUT;
	gTxBuf[1] = 0;
	gTxBuf[2] = 0;
	gTxBuf[3] = 1;
	gTxBuf[4] = 0;	
	
	m = TxAndRsCmd(5, 8, 10);
		
	if (m == ACK_SUCCESS && gRsBuf[4] == ACK_SUCCESS)
	{
	    return gRsBuf[3];
	}
	else
	{
	 	return 0xFF;
	}
}

u8 AddUser(u8 k)
{
	u8 m;
	
	m = GetUserCount();
	if (m >= USER_MAX_CNT)
		return ACK_FULL;


	gTxBuf[0] = CMD_ADD_1;
	gTxBuf[1] = 0;
	gTxBuf[2] = k;
	gTxBuf[3] = 3;
	gTxBuf[4] = 0;	
	
	LED1_ON;
	m = TxAndRsCmd(5, 8, 200);
	LED1_OFF;
	
	if (m == ACK_SUCCESS && gRsBuf[4] == ACK_SUCCESS)
	{
	    gTxBuf[0] = CMD_ADD_2;
			LED1_ON;
			m = TxAndRsCmd(5, 8, 200);
			LED1_OFF;
			if (m == ACK_SUCCESS && gRsBuf[4] == ACK_SUCCESS)
			{
					gTxBuf[0] = CMD_ADD_3;
					LED1_ON;
					m = TxAndRsCmd(5, 8, 200);
					LED1_OFF;
					if (m == ACK_SUCCESS && gRsBuf[4] == ACK_SUCCESS)
					{
							return ACK_SUCCESS;
					}
					else
						return ACK_FAIL;
			}
			else
				return ACK_FAIL;
	}
	else
		return ACK_FAIL;
}

void ClearAllUser(void)
{
 	u8 m;
	
	gTxBuf[0] = CMD_DEL_ALL;
	gTxBuf[1] = 0;
	gTxBuf[2] = 0;
	gTxBuf[3] = 0;
	gTxBuf[4] = 0;
	
	m = TxAndRsCmd(5, 8, 50);
	
	if (m == ACK_SUCCESS && gRsBuf[4] == ACK_SUCCESS)
	{	    
		LED2_ON;
		delay();
		LED2_OFF;
	}
	else
	{
	 	LED3_ON;
		delay();
		LED3_OFF;
	}
}


u8 IsMasterUser(u8 UserID)
{
    if ((UserID == 1) || (UserID == 2) || (UserID == 3)) return TRUE;
			else  return FALSE;
}	 


u8 VerifyUser(void)
{
	u8 m;
	
	gTxBuf[0] = CMD_MATCH;
	gTxBuf[1] = 0;
	gTxBuf[2] = 0;
	gTxBuf[3] = 0;
	gTxBuf[4] = 0;
	
	m = TxAndRsCmd(5, 8, 150);
	
	if ((m == ACK_SUCCESS) && (IsMasterUser(gRsBuf[4]) == TRUE))
	{	
		 return ACK_SUCCESS;
	}
	else if(gRsBuf[4] == ACK_NO_USER)
	{
		return ACK_NO_USER;
	}
	else if(gRsBuf[4] == ACK_TIMEOUT)
	{
		return ACK_TIMEOUT;
	}
	else
	{
			return ACK_GO_OUT;
	}
}

