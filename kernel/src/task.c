/********************************** (C) COPYRIGHT ******************************
 * File Name          : task.c
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.7.1
 * Description        : lilstar OS task handler
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#include "task.h"
#include "Systick.h"
#include "swtimer.h"
#include "log.h"
#ifndef BUILD_KEIL
#include <malloc.h>
#endif

extern unsigned int TIME_1MS;
static TASK_INIT *TASK_LIST[MAX_TASK + 1]         = {NULL};
CALL_BACK_INIT *CALL_BACK_LIST[MAX_CALL_BACK + 1] = {NULL};
TASK_STATE Creat_Task(unsigned int *task_id, TASK_CallBack TaskCallBack, unsigned int time)
{
  static int i;
  for (i = 1; i <= MAX_TASK; i++) {
    if (TASK_LIST[i] == NULL) {
      *task_id                   = i;
      TASK_LIST[i]               = malloc(sizeof(TASK_INIT));
      TASK_LIST[i]->TaskCallBack = TaskCallBack;
      TASK_LIST[i]->state        = TASK_STOP;
      TASK_LIST[i]->settime      = time;
      TASK_LIST[i]->time         = 0;
      PRINT_DEBUG("Creat_Task Success ID:%d\n", i);
      return TASK_OK;
    }
  }
  PRINT_ERR("Creat_Task NO FREE\n");
  return TASK_ERROR;
}

TASK_STATE Delete_Task(unsigned int task_id)
{
  if (TASK_LIST[task_id] == NULL) {
    return TASK_ERROR;
  }
  if (task_id > 0 && task_id <= MAX_TASK) {
    free(TASK_LIST[task_id]);
    TASK_LIST[task_id] = NULL;
    PRINT_DEBUG("Delete_Task ID %d\n", task_id);
    return TASK_OK;
  } else {
    PRINT_ERR("Delete_Task ID ERROR\n");
    return TASK_ERROR;
  }
}

TASK_STATE Start_Task(unsigned int task_id)
{
  if (TASK_LIST[task_id] == NULL) {
    return TASK_ERROR;
  }
  if (task_id > 0 && task_id <= MAX_TASK) {
    TASK_LIST[task_id]->state = TASK_START;
    PRINT_DEBUG("Start_Task ID %d\n", task_id);
    return TASK_OK;
  } else {
    PRINT_ERR("Start_Task ID ERROR\n");
    return TASK_ERROR;
  }
}

TASK_STATE Stop_Task(unsigned int task_id)
{
  if (TASK_LIST[task_id] == NULL) {
    return TASK_ERROR;
  }
  if (task_id > 0 && task_id <= MAX_TASK) {
    TASK_LIST[task_id]->state = TASK_STOP;
    PRINT_DEBUG("Stop_Task ID %d\n", task_id);
    return TASK_OK;
  } else {
    PRINT_ERR("Stop_Task ID ERROR\n");
    return TASK_ERROR;
  }
}

TASK_STATE Call_Back_Task(TASK_CallBack TaskCallBack)
{
  static int i;
  for (i = 1; i <= MAX_CALL_BACK; i++) {
    if (CALL_BACK_LIST[i] == NULL) {
      CALL_BACK_LIST[i]               = malloc(sizeof(CALL_BACK_INIT));
      CALL_BACK_LIST[i]->TaskCallBack = TaskCallBack;
      CALL_BACK_LIST[i]->state        = TASK_START;
      PRINT_DEBUG("CALL BACK Success ID:%d\n", i);
      return TASK_OK;
    }
  }
  PRINT_ERR("Call_Back NO FREE\n");
  return TASK_ERROR;
}

void CallBack_Handler(void)
{
  static int i;
  for (i = 1; i <= MAX_CALL_BACK; i++) {
    if (CALL_BACK_LIST[i] != NULL) {
      if (CALL_BACK_LIST[i]->state == TASK_START) {
        CALL_BACK_LIST[i]->state = TASK_STOP;
        CALL_BACK_LIST[i]->TaskCallBack();
        free(CALL_BACK_LIST[i]);
        CALL_BACK_LIST[i] = NULL;
      }
    }
  }
}

void TASK_Handler(void)
{
  static int i;
  for (i = 1; i <= MAX_TASK; i++) {
    if (TASK_LIST[i] != NULL) {
      if (TASK_LIST[i]->state == TASK_START) {
        TASK_LIST[i]->TaskCallBack();
        if (TASK_LIST[i]->settime != TASK_NO_DELAY) {
          TASK_LIST[i]->state = TASK_STOP;
        }
      }
    }
  }
}

void TASK_TIME_COUNT(void)
{
  static int i;
  for (i = 1; i <= MAX_TASK; i++) {
    if (TASK_LIST[i] != NULL) {
      if (TASK_LIST[i]->state == TASK_STOP) {
        TASK_LIST[i]->time++;
        if (TASK_LIST[i]->time >= TASK_LIST[i]->settime) {
          TASK_LIST[i]->time  = 0;
          TASK_LIST[i]->state = TASK_START;
        }
      }
    }
  }
}

void Lil_Os_Start(void)
{
#if CHIP_MODEL == CH32V203
  SysTick_init();
#endif
  PRINTK("Lil_Os_Start\n");
  while (1) {
    if (!TIME_1MS) {
      TIME_1MS = 1;
      swTIMER_Handler();
      TASK_Handler();
      CallBack_Handler();
    }
  }
}
