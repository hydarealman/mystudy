// 头文件保护
#ifndef __MYDMA_H // 检查是否未定义宏__MYDMA_H
#define __MYDMA_H // 条件1成立时:定义宏__MYDMA_H

void MyDMA_Init(uint32_t AddrA,uint32_t AddrB, uint16_t Size);
void MyDMA_Transfer(void);


#endif // 结束条件1

