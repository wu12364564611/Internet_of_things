#include "HWT_Gyroscope.h"

static unsigned char TxBuffer[256];
static unsigned char TxCounter=0;
static unsigned char count=0; 
extern void CopeSerial2Data(unsigned char ucData);
struct SAngle 	stcAngle;
struct SGyro 	stcGyro;
char ZERO[5] = {0xFF,0xAA,0x76,0x00,0x00};//Z轴清零
int tlyflag=0;

/*开启串口2与陀螺仪通信*/
void usart2_init(void)
{
	//定义初始化结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//开启外设的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;

	USART_Init(USART2, &USART_InitStructure);
	
	USART_Cmd(USART2, ENABLE);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
}


void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
  {   
    USART_SendData(USART2, TxBuffer[TxCounter++]); 
    USART_ClearITPendingBit(USART2, USART_IT_TXE);
    if(TxCounter == count) USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
  }
  else if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
		CopeSerial2Data((unsigned char)USART2->DR);//处理数据
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
  }
	USART_ClearITPendingBit(USART2,USART_IT_ORE);

}

void CopeSerial2Data(unsigned char ucData)
{
	static  unsigned char ucRxBuffer[256];
	static unsigned char ucRxCnt = 0;	
	
	
	
						
	ucRxBuffer[ucRxCnt++]=ucData;	//将收到的数据存入缓冲区中
	
	if (ucRxBuffer[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
	{ 
		ucRxCnt=0;
		return;
		
	}	
	else if(ucRxBuffer[0]==0x55 && ucRxBuffer[1]==0x53) //检测到角读数据
	{
	
		if (ucRxCnt<11) {return;}//数据不满11个，则返回
		if (ucRxCnt>=11)
		{
			tlyflag++;
			memcpy(&stcAngle,&ucRxBuffer[2],8);
			ucRxCnt=0;
			return;
			
		}
	}
	else if(ucRxBuffer[0]==0x55 && ucRxBuffer[1]!=0x53 && ucRxCnt!=1) //数据头不对，则重新开始寻找0x55数据头
	{	
		ucRxBuffer[0]=0x00;
		ucRxCnt=0;
		return;
		
	}

}


void USART2_Put_Char(unsigned char DataToSend)
{
	TxBuffer[count++] = DataToSend;  
  USART_ITConfig(USART2, USART_IT_TXE, ENABLE);  
}


void sendcmd(char cmd[])
{
	char i;
	for(i=0;i<5;i++)
	USART2_Put_Char(cmd[i]);
}
 


