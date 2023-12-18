/********************************** (C) COPYRIGHT ******************************
 * File Name          : queue.h
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.7.3
 * Description        : queue header
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#ifndef __QUEUE_H__
#define __QUEUE_H__
#include "LilOS_Config.h"
#ifndef MAX_QUEUE_NUM
#define MAX_QUEUE_NUM 10
#endif

#ifndef MAX_QUEUE_MASSGAE_NUM
#define MAX_QUEUE_MASSGAE_NUM 128
#endif

typedef enum
{
    QUEUE_OK       = 0x00U,
    QUEUE_ERROR    = 0x01U,
    QUEUE_BUSY     = 0x02U,
    QUEUE_TIMEOUT  = 0x03U,
    QUEUE_OVERLOAD = 0x04U,
    QUEUE_FREE     = 0x05U,
    QUEUE_EXIST    = 0x06U,
} QUEUE_Status;

QUEUE_Status Creat_Queue(unsigned int *ID,unsigned int buf_len);
QUEUE_Status Delete_Queue(unsigned int ID);
QUEUE_Status Queue_Write(unsigned int ID,unsigned char data);
QUEUE_Status Queue_Read(unsigned int ID,unsigned char *data);
QUEUE_Status Queue_Write_Arry(unsigned int ID,unsigned char* data,unsigned int len);
QUEUE_Status Queue_Read_Arry(unsigned int ID,unsigned char* data,unsigned int* len);
void Queue_Clear(unsigned int ID);

#endif // !__QUEUE_H__
