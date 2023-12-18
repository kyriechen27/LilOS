/********************************** (C) COPYRIGHT ******************************
 * File Name          : swtimer.h
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.7.3
 * Description        : timer function
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#ifndef __TIMER_H__
#define __TIMER_H__
#include "LilOS_Config.h"

#ifndef MAX_TIMER_TASK
#define MAX_TIMER_TASK 10
#endif

typedef void (*TIMER_CallBack)(void);
enum TIME_STATE_Enum {
  TIME_END,
  TIME_START,
  TIME_STOP,
  TIME_PROCESS
};

enum SWTIME_ERR_Enum {
  SW_TIMER_NOT_EXIST = 0xE0,
  SW_TIMER_OVER_MAX_ID,
};

#define SWTIME_ONE_TIME            1
#define SWTIME_LOOP_TIME           2
#define SWTIME_ONE_TIME_NOT_DELETE 3

unsigned char Delete_swTimer(unsigned int ID);
unsigned char Stop_swTimer(unsigned int ID);
unsigned char Start_swTimer(unsigned int ID);
unsigned char Creat_swTimer(unsigned char mode, unsigned int time, TIMER_CallBack Task, unsigned int *ID);
void swTIMER_Delay(void);
void swTIMER_Handler(void);
#endif
