
#include<string.h>

#include "Encoder.h"
#include "Decoder.h"
#include "Encoder.c"
#include "Decoder.c"
#include <stdlib.h>


/* Private macro */

/* Private variables */
char rx_data[3];
char buffer[6];
char buffer2[4];
char *eptr;
int temp1;
int temp2[16];
int temp3[16];
int temp4[16];
int table;
int state;
int Out_Data;
int EFM_Encoder1_Data;
int TO_Decoder[2];
int to_conv;
int Conv_data[16];

void To_String(char* _buffer, unsigned int data);
void To_String2(char* _buffer, unsigned int data);
void To_Binary(int n, int binaryN[]);

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{


	int j=0,i=0,k=0;

 	while(1)
 	{
// 		//************ UART Receiver**********************
		rx_data[j];

 		// String/ASCII TO int converting

 		temp1 = strtol(rx_data, &eptr, 10);  // 10->decimal / 16-> Hex / 2-> Binary

 		//************* EFMPlus Encoder 1******************
 		EFM_Encoder1_Data= Encoder(temp1);

 		// Int to Binary array
 		To_Binary(EFM_Encoder1_Data,temp2);

 		//************* Conv Encoder***********************
 		for(j =0;j<16;++j)
 		{
 			to_conv =temp2[j];
 			Conv_data[j] = Conv_Encoder(to_conv);
 		}

 		// Integer  TO String/ASCII converting
 		To_String(buffer, EFM_Encoder1_Data);

 //**===================================================================================================================
//           CHANNEL            CHANNEL              CHANNEL              CHANNEL              CHANNEL
 //**===================================================================================================================

 		//**************EFMPlus Decoder 2**********************
 		//TO_Decoder[2] = {0x4480,0x2120};

 		TO_Decoder[0] =EFM_Encoder1_Data;
 		// Int to Binary array
 		if(i>=1)
 		{
				To_Binary(TO_Decoder[0],temp3);
				To_Binary(TO_Decoder[1],temp4);

				state = State_Detector(temp4) ;   // check InputData[t] -next    input "binary"
				table = Table_Detector(temp4,temp3) ;   // check InputData[t] and [t+1]
				Out_Data = EFM_Decoder(state, table, TO_Decoder[1]);
				++k;
				//************* UART Transmitter********
				To_String(buffer, Out_Data);

				USART_PutString(buffer);

 		}//END IF

  		i=i+1;
 		TO_Decoder[1] =TO_Decoder[0];
 	} // END OF WHILE


}// END OF MAIN




/**************************************************************************************/

void To_String(char* _buffer, unsigned int data)
{
  // we make our string assuming all hex digits are 0 to 9
  // string will be of the form 0xabcd
  // where a,b,c,d are the individual hex digits
  _buffer[0] = '0';
  _buffer[1] = 'x';
  _buffer[2] = ( (data>>12) & 0x0F) + '0';
  _buffer[3] = ( (data>>8)  & 0x0F) + '0';
  _buffer[4] = ( (data>>4)  & 0x0F) + '0';
  _buffer[5] = ( (data)     & 0x0F) + '0';
  _buffer[6] = 0;

  // now we correct for the case where a digit
  // is A to F:
  if (_buffer[2] > '9') _buffer[2] += 7;
  if (_buffer[3] > '9') _buffer[3] += 7;
  if (_buffer[4] > '9') _buffer[4] += 7;
  if (_buffer[5] > '9') _buffer[5] += 7;

}

void To_String2(char* _buffer, unsigned int data)
{
  // we make our string assuming all hex digits are 0 to 9
  // string will be of the form 0xabcd
  // where a,b,c,d are the individual hex digits
  _buffer[0] = ( (data>>12) & 0x0F) + '0';
  _buffer[1] = ( (data>>8)  & 0x0F) + '0';
  _buffer[2] = ( (data>>4)  & 0x0F) + '0';
  _buffer[3] = ( (data)     & 0x0F) + '0';
  _buffer[4] = 0;

  // now we correct for the case where a digit
  // is A to F:
  if (_buffer[0] > '9') _buffer[2] += 7;
  if (_buffer[1] > '9') _buffer[3] += 7;
  if (_buffer[2] > '9') _buffer[4] += 7;
  if (_buffer[3] > '9') _buffer[5] += 7;

}



void To_Binary(int n, int binaryNum[] )
{
    // counter for binary array
    int i = 0 ;
    while (n > 0) {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
}
