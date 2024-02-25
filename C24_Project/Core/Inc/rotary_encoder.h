#ifndef  ROTARY_ENCODER_H
#define	 ROTARY_ENCODER_H

#include "stm32f1xx_hal.h"


typedef struct __RE_t {
	TIM_HandleTypeDef *re_htim;
	volatile int16_t re_cur_value;
	volatile int16_t re_pre_value;
}RE_t;


void RE_Init(RE_t *p_re, TIM_HandleTypeDef *htim);
void RE_Handle(RE_t *p_re);
#endif
