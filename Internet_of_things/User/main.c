#include "headfile.h"
uint8_t DHT11_date[2]; //���͵�dht11������humi:date[0] temp:date[1]
uint32_t SGP30_date[2]; //����SGP30��ȡ�ļ�ȩ��Ϣ��formaldehyde��co2:SGP30_date[0]  tvoc:SGP30_date[1]
uint16_t BH1750_date; //����BH1750D�Ĺ�������
int main(void)
{ 
	/*��ʼ������1�����Գ���Ĵ��ڣ�PA9 PA10 ��pwmռ�ã�*/
//	usart1_init();
	/*��ʼ������2��ȡ����������*/
	usart2_init();
	/*��ʼ������3������esp8266ͨ��*/
	usart3_init();
	/*��ʼ������4�������е��ͨ��*/
  usart4_init();
	

	/*��ʼ��DHT11��GPIO*/
	DHT11_GPIO_Init();
	/*��ʼ��SGP30��GPIO*/
  SGP30_IIC_Init();
	/*��ʼ��BH1750��GPIO*/
	BH1750_IIC_Init();
	
	/*pwm�����ʼ��*/
	TIM1_PWM_Init(500,71);
	/*���pwm��ʼ��*/
	TIM8_PWM_Init(199,7199);
	
	
	
	/*���������ʼ��*/
	Driver_Init();
	/*��������ʼ��*/
	Encoder_Init_TIM2();
	Encoder_Init_TIM3();
	Encoder_Init_TIM4();
	Encoder_Init_TIM5();
	
	/*��ʱ���жϳ�ʼ��*/
	TIM6_Timer_Init(99,7199);
	
	/*z�����㲢��ʼ��*/
	sendcmd(ZERO);
	SysTick_Delay_Ms(1000);
	
	/*ps2�ֱ���ʼ��*/
	PS2_Init();
	PS2_SetInit();
	SysTick_Delay_Ms(1000);
	
	/*��ʼ����jetson nanoͨѶ��io��*/
  Jetson_nano_io_init();
	
	while(1)
	{

		/*��ȡ������Ϣ*/
		SGP30_Read(SGP30_date);
		BH1750_date=BH1750_IIC_Read();
		DHT11_Read_Data(DHT11_date);
		/*��ӡ������Ϣ*/
		printf("\t#%d#%d#%d#%d#%d\n",SGP30_date[0],SGP30_date[1],BH1750_date,DHT11_date[0],DHT11_date[1]);
//		/*���ô�ӡƵ��*/
//		SysTick_Delay_Ms(200);
		
//		/*�ֱ�������ת,�ô˿���ʱ���ǶȻ��ر�off*/
//		My_Ps2_Control_1();
		/*�ֱ���������ת,�ô˿���ʱ���ǶȻ�����on*/
		My_Ps2_Control_2();
		
		/*��ȡjetson nano�ĵ�ƽ�ź�,���Ϊ�ߵ�ƽ��ʾ��ժ����*/
		if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9)==SET)
		{
			GPIO_WriteBit(GPIOD,GPIO_Pin_8,Bit_RESET);
			flag=0;
		}
	}

}


