#include "headfile.h"
uint8_t DHT11_date[2]; //接送的dht11的数据humi:date[0] temp:date[1]
uint32_t SGP30_date[2]; //接收SGP30读取的甲醛信息（formaldehyde）co2:SGP30_date[0]  tvoc:SGP30_date[1]
uint16_t BH1750_date; //接收BH1750D的光照数据
int main(void)
{ 
	/*初始化串口1做调试程序的串口（PA9 PA10 给pwm占用）*/
//	usart1_init();
	/*初始化串口2获取陀螺仪数据*/
	usart2_init();
	/*初始化串口3用于与esp8266通信*/
	usart3_init();
	/*初始化串口4用于与机械臂通信*/
  usart4_init();
	

	/*初始化DHT11的GPIO*/
	DHT11_GPIO_Init();
	/*初始化SGP30的GPIO*/
  SGP30_IIC_Init();
	/*初始化BH1750的GPIO*/
	BH1750_IIC_Init();
	
	/*pwm输出初始化*/
	TIM1_PWM_Init(500,71);
	/*舵机pwm初始化*/
	TIM8_PWM_Init(199,7199);
	
	
	
	/*电机驱动初始化*/
	Driver_Init();
	/*编码器初始化*/
	Encoder_Init_TIM2();
	Encoder_Init_TIM3();
	Encoder_Init_TIM4();
	Encoder_Init_TIM5();
	
	/*定时器中断初始化*/
	TIM6_Timer_Init(99,7199);
	
	/*z轴清零并初始化*/
	sendcmd(ZERO);
	SysTick_Delay_Ms(1000);
	
	/*ps2手柄初始化*/
	PS2_Init();
	PS2_SetInit();
	SysTick_Delay_Ms(1000);
	
	/*初始化与jetson nano通讯的io口*/
  Jetson_nano_io_init();
	
	while(1)
	{

		/*获取环境信息*/
		SGP30_Read(SGP30_date);
		BH1750_date=BH1750_IIC_Read();
		DHT11_Read_Data(DHT11_date);
		/*打印环境信息*/
		printf("\t#%d#%d#%d#%d#%d\n",SGP30_date[0],SGP30_date[1],BH1750_date,DHT11_date[0],DHT11_date[1]);
//		/*设置打印频率*/
//		SysTick_Delay_Ms(200);
		
//		/*手柄控制旋转,用此控制时将角度环关闭off*/
//		My_Ps2_Control_1();
		/*手柄不控制旋转,用此控制时将角度环开启on*/
		My_Ps2_Control_2();
		
		/*读取jetson nano的电平信号,如果为高电平表示采摘结束*/
		if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9)==SET)
		{
			GPIO_WriteBit(GPIOD,GPIO_Pin_8,Bit_RESET);
			flag=0;
		}
	}

}


