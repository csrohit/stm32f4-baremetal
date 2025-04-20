#include <stdint.h>
#include "stm32f4xx.h"

#ifndef USART_H
#define USART_H

void usart_init(uint32_t baud);

void usart_txchar(char);

void usart_txbuf(const char *);



#endif // USART_H
