#include <stdint.h>
#include "stm32f4xx.h"

#ifndef USART_H
#define USART_H

void USARTInit(uint32_t baud);

void USARTTxChar(char);

void USARTTxBuffer(const char *);



#endif // USART_H
