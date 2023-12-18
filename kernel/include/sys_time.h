/********************************** (C) COPYRIGHT ******************************
 * File Name          : sys_time.c
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.11.21
 * Description        : system time function header
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#ifndef __SYS_TIME_H__
#define __SYS_TIME_H__

typedef struct {
  unsigned int year;
  unsigned char month;
  unsigned char day;
  unsigned char hour;
  unsigned char min;
  unsigned char sec;
} sys_time_t;

void sys_time_count(void);
void sys_time_init(void);
void sys_time_ret(sys_time_t *time);
void sys_time_set(sys_time_t time);
#endif
