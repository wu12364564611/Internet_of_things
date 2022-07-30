#include "usart.h"

/*��ʼ������1���ڴ�ӡ������Ϣ*/
void usart1_init(void)
{
	//�����ʼ���ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//���������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;

	USART_Init(USART1, &USART_InitStructure);
	
	USART_Cmd(USART1, ENABLE);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
}

/*��ʼ������3������esp8266ͨ��*/
void usart3_init(void)
{
	//�����ʼ���ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//���������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;

	USART_Init(USART3, &USART_InitStructure);
	
	USART_Cmd(USART3, ENABLE);
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
}

/*��ʼ������4�������е��ͨ��*/
void usart4_init(void)
{
	//�����ʼ���ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//���������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;

	USART_Init(UART4, &USART_InitStructure);
	
	USART_Cmd(UART4, ENABLE);
	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel=UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
}


/*����һ���ֽ�*/
void Usart_sendByte(USART_TypeDef* USARTx,uint8_t Data)
{
	USART_SendData(USARTx,Data);
	/*�ж��������ݼĴ����е�������û�ж���������λ�Ĵ����У���ֹ���ݱ�����*/
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
}

/*���������ֽ�����*/
void Usart_send_twoBytes(USART_TypeDef* USARTx,uint16_t Data)
{
	uint8_t temp_h,temp_l;
	temp_h=(Data&0xff00)>>8;
	temp_l=Data&0xff;
	USART_SendData(USARTx,temp_h);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
	USART_SendData(USARTx,temp_l);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
	
}

/*����8λ������*/
void Usart_sentArray(USART_TypeDef* USARTx,uint8_t *array,uint8_t num)
{
	uint8_t i;
	for(i=0;i<num;i++)
	{
		Usart_sendByte(USARTx,*(array+i));
	}
	/*�ж�ȫ�������Ƿ񶼴ӷ�����λ�Ĵ����͵�tx������û���µ������͹���*/
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);
}

/*�����ַ���*/
void Usart_sendStr(USART_TypeDef* USARTx,char *str)
{
	uint8_t i=0;
	do
	{
		Usart_sendByte(USARTx,*(str+i));
		i++;
	}while(*(str+i)!='\0');
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);

}


///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(USART3, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

////�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
//int fputc(int ch, FILE *f)
//{
//		/* ����һ���ֽ����ݵ����� */
//		USART_SendData(USART1, (uint8_t) ch);
//		
//		/* �ȴ�������� */
//		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
//	
//		return (ch);
//}


///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}

void USART1_IRQHandler(void)
{
//	uint8_t temp;
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
	{
//	
//		temp = USART_ReceiveData(USART1);
//		USART_SendData(USART1,temp);
	
	}

}

void USART3_IRQHandler(void)
{
//	uint8_t temp;
	if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == SET)
	{
//	
//		temp = USART_ReceiveData(USART3);
//		USART_SendData(USART3,temp);
	
	}

}


void UART4_IRQHandler(void)
{
//	uint8_t temp;
	if(USART_GetFlagStatus(UART4, USART_FLAG_RXNE) == SET)
	{
//	
//		temp = USART_ReceiveData(UART4);
//		USART_SendData(UART4,temp);
	
	}

}
