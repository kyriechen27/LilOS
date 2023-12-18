/********************************** (C) COPYRIGHT ******************************
 * File Name          : c
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.11.21
 * Description        : system time function
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#include "sys_time.h"

static sys_time_t sys_time;


void sys_time_count(void)
{
  sys_time.sec++;
  if (sys_time.sec >= 60) {
    sys_time.sec = 0;
    sys_time.min++;
    if (sys_time.min >= 60) {
      sys_time.min = 0;
      sys_time.hour++;
      if (sys_time.hour >= 24) {
        sys_time.hour = 0;
        sys_time.day++;
        if (sys_time.day >= 30) {
          sys_time.day = 0;
          sys_time.month++;
          if (sys_time.month >= 12) {
            sys_time.month = 0;
            sys_time.year++;
          }
        }
      }
    }
  }
}

void sys_time_ret(sys_time_t *time)
{
  time->year = sys_time.year;
  time->month = sys_time.month;
  time->day = sys_time.day;
  time->hour = sys_time.hour;
  time->min = sys_time.min;
  time->sec = sys_time.sec;
}

void sys_time_set(sys_time_t time)
{
  sys_time.year = time.year;
  sys_time.month = time.month;
  sys_time.day = time.day;
  sys_time.hour = time.hour;
  sys_time.min = time.min;
  sys_time.sec = time.sec;
}

void sys_time_init(void)
{
  sys_time.year = 2020;
  sys_time.month = 06;
  sys_time.day = 01;
  sys_time.hour = 0;
  sys_time.min = 0;
  sys_time.sec = 0;
}