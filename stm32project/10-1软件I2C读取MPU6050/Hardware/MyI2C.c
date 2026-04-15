#include "stm32f10x.h"                  // Device header
#include "Delay.h"

// SCL(时钟线)控制
// 设置SCL引脚电平并延时10ms
void MyI2C_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
	Delay_us(10);
}

// SDA(数据线)控制
// 设置SDA引脚电平并延时10ms
void MyI2C_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
	Delay_us(10);
}

// SDA读取
uint8_t MyI2C_R_SDA(void)
{
	uint8_t BitValue = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(10);
	return BitValue;
}

// I2C初始化
// 开漏输出: 可以输出低电平,但不能主动输出高电平
// 高电平由上拉电阻提供,允许多个设备共享总线
// 符合I2C总线的线与特性
void MyI2c_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; // 开漏输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						//将PA1和PA2引脚初始化为推挽输出
	
	/*设置GPIO初始化后的默认电平*/
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);				//设置PA1和PA2引脚为高电平
}

// 起始条件
void MyI2C_start(void)
{
	// 起始条件定义: 在SCL高电平期间,SDA从高电平跳变到低电平
	// 表示一次传输的开始,由主机发起
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
}

// 终止条件
void MyI2C_Stop(void)
{
	// 终止条件定义: 在SCL为高电平期间,SDA从低电平跳变到高电平
	// 表示一次传输的结束,由主机发起
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

// SCL低电平释放数据写数据,高电平读数据
// 读写分离的设计
// 发送数据

// 如果破坏这个游戏规则就变成起始条件和终止条件了
// 发送数据
void MyI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++) {
		// 1.主机在SCL低电平期间设置SDA数据
		MyI2C_W_SDA(Byte & (0x80 >> i));
		// 2.拉高SCL,从机在SCL高电平期间读取SDA
		MyI2C_W_SCL(1);
		// 3.拉低SCL,为下一位数据做准备
		MyI2C_W_SCL(0);
	}
}

// 接收数据
uint8_t MyI2C_ReceiveByte(void){
	uint8_t i,Byte = 0x00;
	MyI2C_W_SDA(1);
	for (i = 0; i < 8; i++) {
		MyI2C_W_SCL(1);
		if (MyI2C_R_SDA() == 1){Byte |= (0x80 >> i);}
		MyI2C_W_SCL(0);
	}
	return Byte;
}

// 应答: 
// 0低电平: 表示正常应答(ACK)
// 1高电平: 表示非应答(NACK)

// 发送应答
void MyI2C_SendAck(uint8_t ACKBit)
{
	MyI2C_W_SDA(ACKBit);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);
}

// 接收应答
uint8_t MyI2C_ReceiveAck(void)
{
	uint8_t AckBit;
	MyI2C_W_SDA(1);			 // 主机释放SDA
	MyI2C_W_SCL(1);			 // 拉高SCL 
	// 读取从机发送的应答位
	AckBit = MyI2C_R_SDA();
	
	MyI2C_W_SCL(0);			 // 拉低SCL
	return AckBit;		     // 返回应答位
}
