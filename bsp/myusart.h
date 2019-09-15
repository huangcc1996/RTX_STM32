#ifndef __MYUSART_H
#define __MYUSART_H

#include "myheader.h"

extern void uart_init(u32 bound);
extern void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);

#endif
