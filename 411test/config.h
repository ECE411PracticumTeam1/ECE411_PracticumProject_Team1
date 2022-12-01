// Copyright 2022 Yusanagi (@Yusanagi)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
#define RGB_DI_PIN B6
#define RGBLED_NUM 6
#define RGBLIGHT_DEFAULT_HUE 180
void change_tap(void);
