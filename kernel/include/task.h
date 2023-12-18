/********************************** (C) COPYRIGHT ******************************
 * File Name          : task.h
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.7.1
 * Description        : lilstar OS task header file
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#ifndef __TASK_H__
#define __TASK_H__
#include "LilOS_Config.h"

typedef void (*TASK_CallBack)(void);
typedef struct TASK_INITTypeDef {
  unsigned char mode;
  unsigned int settime;
  unsigned int time;
  unsigned char state;
  TASK_CallBack TaskCallBack;
} TASK_INIT;

typedef struct CALL_BACK_INITTypeDef {
  unsigned char state;
  TASK_CallBack TaskCallBack;
} CALL_BACK_INIT;

enum TASK_STATE_Enum {
  TASK_END,
  TASK_START,
  TASK_STOP,
  TASK_PROCESS
};

typedef enum TASK_RETURN_Enum {
  TASK_OK,
  TASK_ERROR,
} TASK_STATE;

#ifndef MAX_TASK
#define MAX_TASK 32
#endif

#ifndef MAX_CALL_BACK
#define MAX_CALL_BACK 32
#endif

#define TASK_NO_DELAY 0

TASK_STATE Creat_Task(unsigned int *task_id, TASK_CallBack TaskCallBack, unsigned int time);
TASK_STATE Delete_Task(unsigned int task_id);
TASK_STATE Start_Task(unsigned int task_id);
TASK_STATE Stop_Task(unsigned int task_id);
TASK_STATE Call_Back_Task(TASK_CallBack TaskCallBack);
void Lil_Os_Start(void);
void TASK_TIME_COUNT(void);

#endif
