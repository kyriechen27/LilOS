/********************************** (C) COPYRIGHT ******************************
 * File Name          : swtimer.c
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.7.3
 * Description        : timer function
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#include "swtimer.h"
#include "log.h"
#ifndef BUILD_KEIL
#include <malloc.h>
#endif
static unsigned char Timer_Task_NUM;
static unsigned char Timer_ID_NUM;

typedef struct TIMER_INITTypeDef {
  unsigned char TIME_STATE;
  unsigned char mode;
  unsigned int timecount;
  unsigned int set_time;
  TIMER_CallBack TimeCallBack;
} TIMER_INIT;

TIMER_INIT *TIMER_TASK[MAX_TIMER_TASK + 1] = {NULL};

static void swTimer_mode_choice(unsigned int num)
{
  if (TIMER_TASK[num]->mode == SWTIME_ONE_TIME) {
    Delete_swTimer(num);
  } else if (TIMER_TASK[num]->mode == SWTIME_LOOP_TIME) {
    TIMER_TASK[num]->timecount = 0;
    if (TIMER_TASK[num]->TIME_STATE != TIME_STOP) {
      TIMER_TASK[num]->TIME_STATE = TIME_START;
    }
  } else if (TIMER_TASK[num]->mode == SWTIME_ONE_TIME_NOT_DELETE) {
    TIMER_TASK[num]->timecount = 0;
    TIMER_TASK[num]->TIME_STATE = TIME_STOP;
  }
}

unsigned char Creat_swTimer(unsigned char mode, unsigned int time, TIMER_CallBack Task, unsigned int *ID)
{
  int i;
  for (i = 1; i <= MAX_TIMER_TASK + 1; i++) {
    if (TIMER_TASK[i] == NULL) {
      *ID = i;
      TIMER_TASK[i] = malloc(sizeof(TIMER_INIT));
      TIMER_TASK[i]->set_time = time;
      TIMER_TASK[i]->TimeCallBack = Task;
      TIMER_TASK[i]->mode = mode;
      TIMER_TASK[i]->timecount = 0;
      TIMER_TASK[i]->TIME_STATE = TIME_STOP;
      PRINT_DEBUG("Creat_Timer Success ID:%d\n", i);
      return LOS_OK;
    }
  }
  PRINT_ERR("Creat_Timer NO FREE\n");
  return LOS_NOK;
}

unsigned char Start_swTimer(unsigned int ID)
{
  if (TIMER_TASK[ID] == NULL) {
    PRINT_ERR("SW TIMER NOT EXIST\n");
    return SW_TIMER_NOT_EXIST;
  }

  if (ID > 0 && ID <= MAX_TIMER_TASK) {
    TIMER_TASK[ID]->TIME_STATE = TIME_START;
    return LOS_OK;
  }

  PRINT_ERR("START TIMER ID ERROR\n");
  return SW_TIMER_OVER_MAX_ID;
}

unsigned char Stop_swTimer(unsigned int ID)
{
  if (TIMER_TASK[ID] == NULL) {
    PRINT_ERR("SW TIMER NOT EXIST\n");
    return SW_TIMER_NOT_EXIST;
  }

  if (ID > 0 && ID <= MAX_TIMER_TASK && TIMER_TASK[ID] != NULL) {
    TIMER_TASK[ID]->TIME_STATE = TIME_STOP;
    return LOS_OK;
  }
  PRINT_ERR("STOP TIMER ID ERROR\n");
  return SW_TIMER_OVER_MAX_ID;
}

unsigned char Delete_swTimer(unsigned int ID)
{
  if (TIMER_TASK[ID] == NULL) {
    PRINT_WARN("SW TIMER NOT EXIST\n");
    return SW_TIMER_NOT_EXIST;
  }

  if (ID > 0 && ID <= MAX_TIMER_TASK) {
    free(TIMER_TASK[ID]);
    TIMER_TASK[ID] = NULL;
    PRINT_DEBUG("Delete_Timer ID %d\n", ID);
    return LOS_OK;
  }
  PRINT_ERR("Delete_Timer ID ERROR\n");
  return SW_TIMER_OVER_MAX_ID;
}

void swTIMER_Delay(void)
{
  for (Timer_ID_NUM = 1; Timer_ID_NUM < MAX_TIMER_TASK; Timer_ID_NUM++) {
    if (TIMER_TASK[Timer_ID_NUM] != NULL) {
      if (TIMER_TASK[Timer_ID_NUM]->TIME_STATE == TIME_START) {
        TIMER_TASK[Timer_ID_NUM]->timecount++;
        if (TIMER_TASK[Timer_ID_NUM]->timecount >= TIMER_TASK[Timer_ID_NUM]->set_time) {
          TIMER_TASK[Timer_ID_NUM]->TIME_STATE = TIME_PROCESS;
        }
      }
    }
  }
}

void swTIMER_Handler(void)
{
  for (Timer_Task_NUM = 1; Timer_Task_NUM < MAX_TIMER_TASK; Timer_Task_NUM++) {
    if (TIMER_TASK[Timer_Task_NUM] != NULL) {
      if (TIMER_TASK[Timer_Task_NUM]->TIME_STATE == TIME_PROCESS) {
        TIMER_TASK[Timer_Task_NUM]->TimeCallBack();
        swTimer_mode_choice(Timer_Task_NUM);
      }
    }
  }
}
