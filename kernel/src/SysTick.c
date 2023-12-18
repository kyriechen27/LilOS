/********************************** (C) COPYRIGHT ******************************
 * File Name          : SysTick.c
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.6.29
 * Description        : SysTick function
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#include "Systick.h"
#include "swtimer.h"
#include "task.h"
#include "sys_time.h"
#if CHIP_MODEL == CH32V203
unsigned int TIME_1MS = 0;
void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void SysTick_init(void)
{

  NVIC_InitTypeDef NVIC_InitStructure                  = {0};
  NVIC_InitStructure.NVIC_IRQChannel                   = SysTicK_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  SysTick->CTLR = 0;
  SysTick->SR   = 0;
  SysTick->CNT  = 0;
  SysTick->CMP  = SystemCoreClock / 1000;
  SysTick->CTLR = 0xf;
}

void SysTick_Handler(void)
{
  static unsigned int time = 0;

  SysTick->SR = 0;
  if (TIME_1MS) {
    TIME_1MS--;
  }

    if (time++ >= 1000) {
    time = 0;
    sys_time_count();
  }

  swTIMER_Delay();
  TASK_TIME_COUNT();
}

#elif CHIP_MODEL == PY003
unsigned int TIME_1MS = 0;
void SysTick_Handler(void)
{
  HAL_IncTick();
  if (TIME_1MS) {
    TIME_1MS--;
  }
  swTIMER_Delay();
  TASK_TIME_COUNT();
}

#endif
