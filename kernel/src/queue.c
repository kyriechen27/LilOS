/********************************** (C) COPYRIGHT ******************************
 * File Name          : queue.c
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.7.3
 * Description        : bsp_can process
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#include "queue.h"
#include "log.h"
#ifndef BUILD_KEIL
#include <malloc.h>
#endif
typedef struct QUEUE_HandleTypeDef {
  unsigned int head;
  unsigned int tail;
  unsigned int buf_len;
  char* data;
}QUEUE_HandleTypeDef;

QUEUE_HandleTypeDef* QUEUE_TASK[MAX_QUEUE_NUM + 1] = { NULL };

QUEUE_Status Creat_Queue(unsigned int* ID, unsigned int buf_len)
{
  int i;
  for (i = 1; i <= MAX_QUEUE_NUM + 1; i++) {
    if (QUEUE_TASK[i] == NULL) {
      *ID = i;
      QUEUE_TASK[i] = malloc(sizeof(QUEUE_HandleTypeDef));
      QUEUE_TASK[i]->head = 0;
      QUEUE_TASK[i]->tail = 0;
      QUEUE_TASK[i]->data = malloc(buf_len * sizeof(char));
      QUEUE_TASK[i]->buf_len = buf_len;
      PRINT_DEBUG("Creat_Queue Success ID:%d\n", i);
      return QUEUE_OK;
    }
  }
  PRINT_ERR("Creat_Queue NO FREE\n");
  return QUEUE_ERROR;
}

void Queue_Clear(unsigned int ID)
{
  if (QUEUE_TASK[ID] != NULL)
  {
    QUEUE_TASK[ID]->head = 0;
    QUEUE_TASK[ID]->tail = 0;
  }
}

QUEUE_Status Delete_Queue(unsigned int ID)
{
  if (QUEUE_TASK[ID] == NULL)
  {
    return QUEUE_EXIST;
  }
  if (ID > 0 && ID <= MAX_QUEUE_NUM) {
    free(QUEUE_TASK[ID]);
    QUEUE_TASK[ID] = NULL;
    PRINT_DEBUG("Delete_Queue ID %d\n", ID);
    return QUEUE_OK;
  }

  PRINT_ERR("Delete_Queue ID ERROR\n");
  return QUEUE_ERROR;
}

QUEUE_Status Queue_Write(unsigned int ID, unsigned char data)
{
  unsigned int len;
  len = (QUEUE_TASK[ID]->tail + 1) % QUEUE_TASK[ID]->buf_len;
  if (len == QUEUE_TASK[ID]->head)
  {
    return QUEUE_OVERLOAD;
  }
  QUEUE_TASK[ID]->data[QUEUE_TASK[ID]->tail] = data;
  QUEUE_TASK[ID]->tail = len;
  return QUEUE_OK;
}

QUEUE_Status Queue_Read(unsigned int ID, unsigned char* data)
{
  if (QUEUE_TASK[ID] == NULL)
  {
    return QUEUE_EXIST;
  }
  if (QUEUE_TASK[ID]->head == QUEUE_TASK[ID]->tail)
  {
    return QUEUE_FREE;
  }
  *data = QUEUE_TASK[ID]->data[QUEUE_TASK[ID]->head];
  QUEUE_TASK[ID]->head = (QUEUE_TASK[ID]->head + 1) % QUEUE_TASK[ID]->buf_len;
  if(QUEUE_TASK[ID]->head == QUEUE_TASK[ID]->buf_len)
  {
    Queue_Clear(ID);
  }
  return QUEUE_OK;
}

QUEUE_Status Queue_Write_Arry(unsigned int ID, unsigned char* data, unsigned int len)
{
  if (QUEUE_TASK[ID] == NULL)
  {
    return QUEUE_FREE;
  }
  unsigned int i;
  for (i = 0;i < len;i++)
  {
    if (Queue_Write(ID, data[i]) == QUEUE_OVERLOAD)
    {
      return QUEUE_OVERLOAD;
    }
  }
  return QUEUE_OK;
}

QUEUE_Status Queue_Read_Arry(unsigned int ID, unsigned char* data, unsigned int* len)
{
  if (QUEUE_TASK[ID] == NULL)
  {
    return QUEUE_EXIST;
  }
  unsigned int i;
  if (QUEUE_TASK[ID]->head == QUEUE_TASK[ID]->tail)
  {
    return QUEUE_FREE;
  }
  *len = QUEUE_TASK[ID]->tail - QUEUE_TASK[ID]->head;
  for (i = 0;i < *len;i++)
  {
    data[i] = QUEUE_TASK[ID]->data[QUEUE_TASK[ID]->head + i];
  }

  Queue_Clear(ID);
  
  return QUEUE_OK;
}
