/********************************** (C) COPYRIGHT ******************************
 * File Name          : SysTick.h
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.6.29
 * Description        : SysTick heander
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/

#ifndef __SYSTICK_H__
#define __SYSTICK_H__
#include "LilOS_Config.h"

#if CHIP_MODEL == CH32V203
#include "ch32V20x_conf.h"
void SysTick_init(void);
#elif CHIP_MODEL == PY003
#include "py32f0xx_hal.h"
void SysTick_Handler(void);
#endif

#endif
