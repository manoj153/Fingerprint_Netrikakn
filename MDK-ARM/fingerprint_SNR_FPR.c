/*Author	: Manojkumar
  Mobile	: +60173304029
	Compiler: MDK ARM uV5
	Netrikkan
*/
/*Include all required header file*/
#include "fingerprint_SNR_FPR.h"


/*Function Protypes*/


/*Variable Declaration*/
uint8_t gRsBuf[9];			
uint8_t gTxBuf[9];				 
uint8_t gRsLength;



void TxByte(uint8_t temp)
{
	HAL_UART_Transmit_IT(&huart1, &temp, 1);
	
}

uint8_t TxAndRsCmd(uint8_t Scnt, uint8_t Rcnt, uint8_t Delay)
{
   uint8_t  i, j, CheckSum;
	 uint32_t RsTimeCnt;
	 TxByte(CMD_HEAD);	 //0xF5 start bit 
	 CheckSum = 0;
	 for (i = 0; i < Scnt; i++)
	 {
			TxByte(gTxBuf[i]);		 
			CheckSum ^= gTxBuf[i];
	 }	
	 TxByte(CheckSum); 
	 TxByte(CMD_TAIL); //0xF5  
	 gRsLength = 0; // Length of received bytes 
	 RsTimeCnt = Delay * 120000;
	 HAL_UART_Receive_IT(&huart1, gRsBuf, Rcnt);
	 //while (gRsLength < Rcnt && RsTimeCnt > 0)// Delay for wait for DATA tranfer completion
			//RsTimeCnt--;
		HAL_Delay(100);
		while (Rcnt != gRsLength)
		{
			// wait for rs Length size 
		}
	 if (Rcnt == gRsLength)
	 {
		if (UART_Rx_Cmplt_Flag == 55)
		{
	 //if (gRsLength != Rcnt)return ACK_TIMEOUT;
		if (gRsBuf[0] != CMD_HEAD) return ACK_FAIL;
		if (gRsBuf[Rcnt - 1] != CMD_TAIL) return ACK_FAIL;
		if (gRsBuf[1] != (gTxBuf[0])) return ACK_FAIL;
	 
		CheckSum = 0;
		for (j = 1; j < gRsLength - 1; j++) CheckSum ^= gRsBuf[j];
		if (CheckSum != 0) return ACK_FAIL; 	  

		return ACK_SUCCESS;
		}
		return 100;
	} 
	else 
	 {
		printf("Failed Receiption\n");
		return ACK_TIMEOUT;
	 } 
}



uint8_t VerifyUser(void)
{
	uint8_t m;
	
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


uint8_t IsMasterUser(uint8_t UserID)
{
    if ((UserID == 1) || (UserID == 2) || (UserID == 3)) return TRUE;
			else  return FALSE;
}	 


	