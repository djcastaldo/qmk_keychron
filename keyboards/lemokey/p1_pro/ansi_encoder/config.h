/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef RGB_MATRIX_ENABLE
/* RGB Matrix driver configuration */
#    define DRIVER_COUNT 2
#    define RGB_MATRIX_LED_COUNT 81

#    define SPI_SCK_PIN A5
#    define SPI_MISO_PIN A6
#    define SPI_MOSI_PIN A7

#    define DRIVER_CS_PINS \
        { B15, C6 }
#    define SNLED23751_SPI_DIVISOR 16
#    define SPI_DRIVER SPIDQ

/* Scan phase of led driver set as MSKPHASE_9CHANNEL(defined as 0x03 in CKLED2001.h) */
#    define SNLED27351_PHASE_CHANNEL MSKPHASE_9CHANNEL

/* Set LED driver current */
#    define SNLED27351_CURRENT_TUNE \
        { 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C }

/* Set to infinit, which is use in USB mode by default */
#    define RGB_MATRIX_TIMEOUT RGB_MATRIX_TIMEOUT_INFINITE

/* Allow shutdown of led driver to save power */
#    define RGB_MATRIX_DRIVER_SHUTDOWN_ENABLE
/* Turn off backlight on low brightness to save power */
#    define RGB_MATRIX_BRIGHTNESS_TURN_OFF_VAL 0

/* Caps lock indicating led */
#    define CAPS_LOCK_INDEX 44
#    define DIM_CAPS_LOCK
#    define SPACE_KEY_LOW_BAT_IND { 74 }
#    define WINLOCK_LED_LIST { 72 }

#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS

/* rgb settings */
#    define RGB_MATRIX_DEFAULT_ON true
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_BAND_VAL
#    define RGB_MATRIX_DEFAULT_HUE 170
#    define RGB_MATRIX_DEFAULT_SAT 235
#    define RGB_MATRIX_DEFAULT_VAL 255
#    define RGB_MATRIX_DEFAULT_SPD 80

#endif

/* increase layer count above the default of 4 */
#    define DYNAMIC_KEYMAP_LAYER_COUNT 16

/* force enable NKRO */
#    define FORCE_NKRO

/* tap time for tap dancing */
#    define TAPPING_TERM 250
#    define TAPPING_TERM_PER_KEY

/* enable caps word when both shift keys are tapped */
#    define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

/* do not allow dynamic macros to nest (can cause infinite loop) */
#    define DYNAMIC_MACRO_NO_NESTING

/* allow setting constant mode mouse cursor and wheel speeds */
#    define MK_3_SPEED
#    define MK_C_OFFSET_0 1
#    define MK_C_INTERVAL_0 6
#    define MK_C_OFFSET_1 4
#    define MK_C_INTERVAL_1 8

/* leader key settings */
#    define LEADER_TIMEOUT 250
#    define LEADER_PER_KEY_TIMING
#    define LEADER_NO_TIMEOUT

/* for send_string delays */
#    define TMUX_DELAY 35
#    define CONFIG_VS_LAYR_SEND_STRING_DELAY 35
#    define CONFIG_RDP_DELAY_KEY 15
#    define CONFIG_RDP_DELAY_MOD 20

/* monitored base layers for macos */
#    define CONFIG_MACOS_BASE_LAYERS { MAC_BASE }
#    define CONFIG_MACOS_BASE_LAYERS_COUNT 1

/* monitored base layers for macos */
#    define CONFIG_ALL_BASE_LAYERS { MAC_BASE, WIN_BASE }
#    define CONFIG_ALL_BASE_LAYERS_COUNT 2

/* key indexes that changed to shifted version when caps is used */
#    define CONFIG_CAPSLOCK_SHIFTED ((i > 29 && i < 40) || (i > 44 && i < 54) || (i > 58 && i < 66))
#    define CONFIG_CAPSWORD_EXTRA (i == 25)

/* keyfade settings */
#    define CONFIG_KEYFADE_START_DELAY 10
#    define CONFIG_KEYFADE_START_VAL 119
#    define CONFIG_KEYFADE_CALLBACK_INTERVAL 12

/* rgb_matrix_indicators_advanced_user settings */
#    define CONFIG_HAS_LLOCK_KEY
#    define CONFIG_RGB_LAYER_INDICATORS { I_INDICATOR }
#    define CONFIG_RGB_LAYER_INDICATORS_COUNT 1
#    define CONFIG_HAS_KCLK_BATTERY
#    define CONFIG_FN_LAYR_COLOR RGB_GREEN
#    define CONFIG_MREC_KEY_COLOR RGB_MAGENTA
#    define CONFIG_SHIFT_LAYR_COLOR RGB_ORANGE
#    define CONFIG_KCTL_LAYR_COLOR RGB_RED
#    define CONFIG_TMUX_LAYR_COLOR RGB_CYAN
#    define CONFIG_VS_LAYR_COLOR RGB_PURPLE
#    define CONFIG_SYM_LAYR_COLOR RGB_BLUE
#    define CONFIG_WIDE_LAYR_COLOR RGB_PURPLE
#    define CONFIG_CIRC_LAYR_COLOR RGB_CORAL
#    define CONFIG_EMO_LAYR_COLOR RGB_YELLOW
#    define CONFIG_DEFUALT_LAYR_COLOR 0x77,0x77,0x77
#    define CONFIG_EXTRA_BASE_LAYR_COLORS \
     { \
         { I_CAPS, RGB_BLUE }, \
         { I_FN, RGB_BLUE }, \
         { I_TAB, 0x77, 0x77, 0x77 }, \
         { I_BSLS, 0x77, 0x77, 0x77 }, \
     }
#    define CONFIG_EXTRA_BASE_LAYR_COLORS_COUNT 4

#    define CONFIG_ACCENT_KEY_COLOR RGB_YELLOW
#    define CONFIG_CAPS_WORD_SHIFT_COLOR 0x77,0x77,0x77
#    define CONFIG_HROWLIGHT_COLOR RGB_GREEN
#    define CONFIG_FJLIGHT_COLOR RGB_WHITE
#    define CONFIG_LEADER_COLORA RGB_TURQUOISE
#    define CONFIG_LEADER_COLORB RGB_CYAN
#    define CONFIG_KEYLIGHT_STD_COLOR RGB_WHITE
#    define CONFIG_KCLK_24G_HOST_IDX 24
#    define CONFIG_KCLK_BT_KEY_START_IDX 14
#    define CONFIG_EEPROM_RESET_DEFAULT_LAYER WIN_BASE
#    define CONFIG_EEPROM_RESET_DEFAULT_IS_LINUX
#    define CONFIG_LOCK_ANIMATION_TIMEOUT 120000
#    define CONFIG_LOCK_RESTORE_ANIMATION_FROM_SUSPEND_MS 100
#    define CONFIG_LOCK_ANIMATION_COLOR_HSV 10,255,255

/* custom sleep setup */
#    define CONFIG_CUSTOM_SLEEP_TIMEOUT 300000
#    define CONFIG_CUSTOM_SLEEP_WARNING 5000
#    define CONFIG_CUSTOM_BLINK_INTERVAL 250
#    define CONFIG_CUSTOM_BT_TURN_OFF_DELAY 10000
