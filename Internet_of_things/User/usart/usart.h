#ifndef _usart_h
#define _usart_h
#include "headfile.h"
#include <stdio.h>
void usart1_init(void);
void Usart_sendByte(USART_TypeDef* USARTx,uint8_t Data);
void Usart_send_twoBytes(USART_TypeDef* USARTx,uint16_t Data);
void Usart_sentArray(USART_TypeDef* USARTx,uint8_t *array,uint8_t num);
void Usart_sendStr(USART_TypeDef* USARTx,char *str);
void usart3_init(void);
void usart4_init(void);


#endif



