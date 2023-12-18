/********************************** (C) COPYRIGHT ******************************
 * File Name          : log.c
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.7.1
 * Description        : log process
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#include "log.h"
static const char* g_logString[] = {
    "EMG",
    "COMMON",
    "ERR",
    "WARN",
    "INFO",
    "DEBUG",
};

unsigned char log_leve_check(unsigned int level)
{
  if (level > PRINT_LEVEL) {
    return LOS_NOK;
  }

  if ((level != LOG_COMMON_LEVEL) && ((level > LOG_EMG_LEVEL) && (level <= LOG_DEBUG_LEVEL))) {
    PRINTK("[%s]", g_logString[level]);
  }

  return LOS_OK;
}
