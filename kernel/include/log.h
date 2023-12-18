/********************************** (C) COPYRIGHT ******************************
 * File Name          : log.h
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.7.1
 * Description        : log heand file
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#ifndef __LOG_H__
#define __LOG_H__
#include "LilOS_Config.h"
#include <stdio.h>
#ifndef LOS_OK
#define LOS_OK 0U
#endif

#ifndef LOS_NOK
#define LOS_NOK 1U
#endif

#define LOG_EMG_LEVEL    0

#define LOG_COMMON_LEVEL (LOG_EMG_LEVEL + 1)

#define LOG_ERR_LEVEL    (LOG_COMMON_LEVEL + 1)

#define LOG_WARN_LEVEL   (LOG_ERR_LEVEL + 1)

#define LOG_INFO_LEVEL   (LOG_WARN_LEVEL + 1)

#define LOG_DEBUG_LEVEL  (LOG_INFO_LEVEL + 1)

#ifdef BUILD_DEBUG
#define PRINT_LEVEL LOG_DEBUG_LEVEL
#endif

#ifndef PRINT_LEVEL
#define PRINT_LEVEL LOG_ERR_LEVEL
#endif

unsigned char log_leve_check(unsigned int level);
#define LOG_Printf(type, level, fmt, args...) \
  do {                                        \
    if (!log_leve_check(level)) {            \
      printf(fmt, ##args);                    \
      fflush(stdout);                         \
    }                                         \
  } while (0)

#define PRINT_DEBUG(fmt, args...) LOG_Printf(LOG_MODULE_KERNEL, LOG_DEBUG_LEVEL, fmt, ##args)
#define PRINT_INFO(fmt, args...)  LOG_Printf(LOG_MODULE_KERNEL, LOG_INFO_LEVEL, fmt, ##args)
#define PRINT_WARN(fmt, args...)  LOG_Printf(LOG_MODULE_KERNEL, LOG_WARN_LEVEL, fmt, ##args)
#define PRINT_ERR(fmt, args...)   LOG_Printf(LOG_MODULE_KERNEL, LOG_ERR_LEVEL, fmt, ##args)
#define PRINTK(fmt, args...)      LOG_Printf(LOG_MODULE_KERNEL, LOG_COMMON_LEVEL, fmt, ##args)
#define PRINT_EMG(fmt, args...)   LOG_Printf(LOG_MODULE_KERNEL, LOG_EMG_LEVEL, fmt, ##args)




#endif // !__LOG_H__
