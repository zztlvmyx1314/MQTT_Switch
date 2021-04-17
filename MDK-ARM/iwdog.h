
#ifndef _IWDOG_H_
#define _IWDOG_H_

#include "main.h"

#define IDG 0
#define WDG 1
#define PRE WWDG_PRESCALER_8
#define WVAL 0x5f
#define CVAL 0x7f

void IWDOG_Init(uint8_t f,uint16_t reload);

void IWDOG_Feed(uint8_t f);


#endif