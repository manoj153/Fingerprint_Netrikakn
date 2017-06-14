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
	 TxByte(CMD_TAIL);  
	 gRsLength = 0;
	 RsTimeCnt = Delay * 120000;
	 while (gRsLength < Rcnt && RsTimeCnt > 0)
			RsTimeCnt--;

	 if (gRsLength != Rcnt)return ACK_TIMEOUT;
	 if (gRsBuf[0] != CMD_HEAD) return ACK_FAIL;
	 if (gRsBuf[Rcnt - 1] != CMD_TAIL) return ACK_FAIL;
	 if (gRsBuf[1] != (gTxBuf[0])) return ACK_FAIL;
	 
	 CheckSum = 0;
	 for (j = 1; j < gRsLength - 1; j++) CheckSum ^= gRsBuf[j];
	 if (CheckSum != 0) return ACK_FAIL; 	  

 	 return ACK_SUCCESS;
}	 



	