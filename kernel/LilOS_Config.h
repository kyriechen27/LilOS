/********************************** (C) COPYRIGHT ******************************
 * File Name          : LilOS_Config.h
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.6.29
 * Description        : SysTick function
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#ifndef __LilOS_Config_H__
#define __LilOS_Config_H__
#include <stdlib.h>

#define BUILD_KEIL
#define CHIP_MODEL            CH32V203

#define Nomal                 0
#define CH32V203              1
#define PY003                 2

#define MAX_CALL_BACK         32
#define MAX_TASK              32
#define MAX_TIMER_TASK        32
#define MAX_QUEUE_NUM         10
#define MAX_QUEUE_MASSGAE_NUM 10

#endif
