#include "pstwo.h"
/*********************************************************
Copyright (C), 2015-2025, YFRobot.
www.yfrobot.com
File：PS2驱动程序
Author：pinggai    Version:1.1     Data:2015/10/20
Description: PS2驱动程序
             增加功能：
			 1、软件设置“红灯模式”、“绿灯模式”，并可以设置“保存”，通过手柄“模式按键”无法改变
			 2、设置手柄震动：通过数值的设置，改变左侧大震动电机震动频率。
			                  通过数值的设置，开关右侧小震动电机。
History:  
V1.0: 	2015/05/16
1、手柄解码，识别按键值，读取模拟值。       
**********************************************************/	 
#define DELAY_TIME  SysTick_Delay_Us(5); 
u16 Handkey;	// 按键值读取，零时存储。
u8 Comd[2]={0x01,0x42};	//开始命令。请求数据
u8 Data[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //数据存储数组
u16 MASK[]={
    PSB_SELECT,
    PSB_L3,
    PSB_R3 ,
    PSB_START,
    PSB_PAD_UP,
    PSB_PAD_RIGHT,
    PSB_PAD_DOWN,
    PSB_PAD_LEFT,
    PSB_L2,
    PSB_R2,
    PSB_L1,
    PSB_R1 ,
    PSB_GREEN,
    PSB_RED,
    PSB_BLUE,
    PSB_PINK
	};	//按键值与按键明

//手柄接口初始化    输入  DI->PB12 
//                  输出  DO->PB13    CS->PB14  CLK->PB15
void PS2_Init(void)
{
    //输入  DI->PB12
	RCC->APB2ENR|=1<<3;     //使能PORTB时钟
	GPIOB->CRH&=0XFFF0FFFF;//PB12设置成输入	默认下拉  
	GPIOB->CRH|=0X00080000;   

    //  DO->PB13    CS->PB14  CLK->PB15
	RCC->APB2ENR|=1<<3;    //使能PORTB时钟  	   	  	 
	GPIOB->CRH&=0X000FFFFF; 
	GPIOB->CRH|=0X33300000;//PB13、PB14、PB15 推挽输出   	 											  
}

//向手柄发送命令
void PS2_Cmd(u8 CMD)
{
	volatile u16 ref=0x01;
	Data[1] = 0;
	for(ref=0x01;ref<0x0100;ref<<=1)
	{
		if(ref&CMD)
		{
			DO_H;                   //输出一位控制位
		}
		else DO_L;

		CLK_H;                        //时钟拉高
		DELAY_TIME;
		CLK_L;
		DELAY_TIME;
		CLK_H;
		if(DI)
			Data[1] = ref|Data[1];
	}
	SysTick_Delay_Us(16);
}
//判断是否为红灯模式,0x41=模拟绿灯，0x73=模拟红灯
//返回值；0，红灯模式
//		  其他，其他模式
u8 PS2_RedLight(void)
{
	CS_L;
	PS2_Cmd(Comd[0]);  //开始命令
	PS2_Cmd(Comd[1]);  //请求数据
	CS_H;
	if( Data[1] == 0X73)   return 0 ;
	else return 1;

}
//读取手柄数据
void PS2_ReadData(void)
{
	volatile u8 byte=0;
	volatile u16 ref=0x01;
	CS_L;
	PS2_Cmd(Comd[0]);  //开始命令
	PS2_Cmd(Comd[1]);  //请求数据
	for(byte=2;byte<9;byte++)          //开始接受数据
	{
		for(ref=0x01;ref<0x100;ref<<=1)
		{
			CLK_H;
			DELAY_TIME;
			CLK_L;
			DELAY_TIME;
			CLK_H;
		      if(DI)
		      Data[byte] = ref|Data[byte];
		}
        SysTick_Delay_Us(16);
	}
	CS_H;
}


//对读出来的PS2的数据进行处理,只处理按键部分  
//只有一个按键按下时按下为0， 未按下为1
u16 LastHandkey = 0xFFFF;
u8 PS2_DataKey()
{
	u8 index;

	PS2_ClearData();
	PS2_ReadData();
	LastHandkey = Handkey;
	Handkey=(Data[4]<<8)|Data[3];     //这是16个按键  按下为0， 未按下为1
	for(index=0;index<16;index++)
	{	    
		if((Handkey&(1<<(MASK[index]-1)))==0)
		return index+1;
	}
	return 0;          //没有任何按键按下
}

bool PS2_NewButtonState( u16 button )
{
  button = 0x0001u << ( button - 1 );  //输入的button的值是 该按键在数据中所在bit的值+1， 例如 PSB_SELECT 宏的值 是 1， 在数据中的位是0位， 如此类推，
  return ( ( ( LastHandkey ^ Handkey ) & button ) > 0 );  //将上次的按键数据和这次的按键数据进行异或运算，结果就是两次不同的部分会是1，就得到了状态发生了变化的按键
	                                                    //然后在与我们想要检测的按键进行与运算，如果这个按键发生了变化，那么结果就是1， 大于0，所以返回就是true
}

bool PS2_Button( u16 button )
{
  button = 0x0001u << ( button - 1 );  //输入的button的值是 该按键在数据中所在bit的值+1， 例如 PSB_SELECT 宏的值 是 1， 在数据中的位是0位， 如此类推，
  return ( ( (~Handkey) & button ) > 0 );  //按键按下则对应位为0，没按下为1， 将按键数据取反之后，就变成了按键为1，没按下为0
	                                         //再与我们想要检测的按键做与运算，若这个按键被按下，对应位就是1，没按下就是0，返回与0比较的结果，
}

bool PS2_ButtonPressed( u16 button )
{
  return (PS2_NewButtonState( button ) && PS2_Button( button ));  //按键被按住，并且这个是按键的一个新的状态，那么就是按键刚被按下
}

bool PS2_ButtonReleased( u16 button )
{
  return ( PS2_NewButtonState( button ) && !PS2_Button( button )); //按键没被按住，并且这个是按键的一个新的状态，那么就是按键刚被松开
}


//得到一个摇杆的模拟量	 范围0~256
u8 PS2_AnologData(u8 button)
{
	return Data[button];
}

//清除数据缓冲区
void PS2_ClearData()
{
	u8 a;
	for(a=0;a<9;a++)
		Data[a]=0x00;
}
/******************************************************
Function:    void PS2_Vibration(u8 motor1, u8 motor2)
Description: 手柄震动函数，
Calls:		 void PS2_Cmd(u8 CMD);
Input: motor1:右侧小震动电机 0x00关，其他开
	   motor2:左侧大震动电机 0x40~0xFF 电机开，值越大 震动越大
******************************************************/
void PS2_Vibration(u8 motor1, u8 motor2)
{
	CS_L;
	SysTick_Delay_Us(16);
    PS2_Cmd(0x01);  //开始命令
	PS2_Cmd(0x42);  //请求数据
	PS2_Cmd(0X00);
	PS2_Cmd(motor1);
	PS2_Cmd(motor2);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	CS_H;
	SysTick_Delay_Us(16);  
}
//short poll
void PS2_ShortPoll(void)
{
	CS_L;
	SysTick_Delay_Us(16);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x42);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	CS_H;
	SysTick_Delay_Us(16);	
}
//进入配置
void PS2_EnterConfing(void)
{
    CS_L;
	SysTick_Delay_Us(16);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x43);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x01);
	PS2_Cmd(0x00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	CS_H;
	SysTick_Delay_Us(16);
}
//发送模式设置
void PS2_TurnOnAnalogMode(void)
{
	CS_L;
	PS2_Cmd(0x01);  
	PS2_Cmd(0x44);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x01); //analog=0x01;digital=0x00  软件设置发送模式
	PS2_Cmd(0xEE); //Ox03锁存设置，即不可通过按键“MODE”设置模式。
				   //0xEE不锁存软件设置，可通过按键“MODE”设置模式。
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	CS_H;
	SysTick_Delay_Us(16);
}
//振动设置
void PS2_VibrationMode(void)
{
	CS_L;
	SysTick_Delay_Us(16);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x4D);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x00);
	PS2_Cmd(0X01);
	CS_H;
	SysTick_Delay_Us(16);	
}
//完成并保存配置
void PS2_ExitConfing(void)
{
    CS_L;
	SysTick_Delay_Us(16);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x43);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	CS_H;
	SysTick_Delay_Us(16);
}
//手柄配置初始化
void PS2_SetInit(void)
{
	PS2_ShortPoll();
	PS2_ShortPoll();
	PS2_ShortPoll();
	PS2_EnterConfing();		//进入配置模式
	PS2_TurnOnAnalogMode();	//“红绿灯”配置模式，并选择是否保存
	PS2_VibrationMode();	//开启震动模式
	PS2_ExitConfing();		//完成并保存配置
}



/*手柄控制旋转,用此控制时将角度环关闭off*/
void My_Ps2_Control_1(void)
{
	u8 key;
	int x_y_speed=50,z_speed=20;
	key=PS2_DataKey();

	if(key!=0)  //有按键按下
	{
	
		/*判断是不是前后左右*/
		if(key==PSB_PAD_UP)  //前进
		{
			Forward(x_y_speed);
		
		}
		else if(key==PSB_PAD_DOWN)  //后退
		{
			Back(x_y_speed);
		
		}
		else if(key==PSB_PAD_RIGHT)  //右移
		{
			Right_Move(x_y_speed);
		
		}
		else if(key==PSB_PAD_LEFT)		//左移
		{
			Left_Move(x_y_speed);
		}
		
		/*判断是不是旋转*/
		if(key==PSB_PINK)  //逆时针转动
		{
			Final_Z=z_speed;
		}
		else if(key==PSB_RED)  //顺时针转动
		{
			Final_Z=-z_speed;
		}
		
		/*判断是不是给机械臂发送指令*/
		if(PS2_ButtonPressed(PSB_L1))
		{
			USART_SendData(UART4,'1');
			
		}
		/*判断是否打开存储舱门*/
		if(PS2_ButtonPressed(PSB_GREEN))
		{
			
			TIM_SetCompare1(TIM8,5);  //打开
			
		}
		else if(PS2_ButtonPressed(PSB_BLUE))
		{
			TIM_SetCompare1(TIM8,25);  //关闭
		}
		/*模拟单片机给jetson nano 发送高电平表示我到达位置*/
		if(PS2_ButtonPressed(PSB_R1))
		{
			GPIO_WriteBit(GPIOD,GPIO_Pin_8,Bit_SET);
		}
		
	}
	else
	{
		/*没有按下则停止*/
		stop();
		Final_Z=0;
	}
	

}

int flag=0;

/*手柄不控制旋转,用此控制时将角度环开启on*/
void My_Ps2_Control_2(void)
{
	u8 key;
	int x_y_speed=10;
	key=PS2_DataKey();
	
	if(key!=0)  //有按键按下
	{
		
		if(key==PSB_PAD_UP)  //前进
		{
			Forward(x_y_speed);
		
		}
		else if(key==PSB_PAD_DOWN)  //后退
		{
			Back(x_y_speed);
		
		}
		else if(key==PSB_PAD_RIGHT)  //右移
		{
			Right_Move(x_y_speed);
		
		}
		else if(key==PSB_PAD_LEFT)		//左移
		{
			Left_Move(x_y_speed);
		}
		/*判断是不是给机械臂发送指令*/
		if(PS2_ButtonPressed(PSB_L1))
		{
			USART_SendData(UART4,'1');
			
		}
		/*判断是否打开存储舱门*/
		if(PS2_ButtonPressed(PSB_GREEN))
		{
			
			TIM_SetCompare1(TIM8,5);  //打开
			
		}
		else if(PS2_ButtonPressed(PSB_BLUE))
		{
			TIM_SetCompare1(TIM8,25);  //关闭
		}
		/*模拟单片机给jetson nano 发送高电平表示我到达位置*/
		if(PS2_ButtonPressed(PSB_R1))
		{
			GPIO_WriteBit(GPIOD,GPIO_Pin_8,Bit_SET);
			flag=1;
		}
		
	}
	else
	{
		stop();

	}

}













