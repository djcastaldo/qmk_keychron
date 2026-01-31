/* Copyright 2021 @ Keychron (https://www.keychron.com)
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
#    define RGB_MATRIX_LED_COUNT 72

#    define SPI_SCK_PIN A5
#    define SPI_MISO_PIN A6
#    define SPI_MOSI_PIN A7

#    define DRIVER_CS_PINS \
        { B9, B8 }
#    define SNLED23751_SPI_DIVISOR 16
#    define SPI_DRIVER SPID1

/* Scan phase of led driver set as MSKPHASE_9CHANNEL(defined as 0x03 in snled27351.h) */
#    define PHASE_CHANNEL MSKPHASE_9CHANNEL

/* Set LED driver current */
#    define SNLED27351_CURRENT_TUNE \
        { 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40 }

/* Set to infinit, which is use in USB mode by default */
#    define RGB_MATRIX_TIMEOUT RGB_MATRIX_TIMEOUT_INFINITE

/* Allow shutdown of led driver to save power */
#    define RGB_MATRIX_DRIVER_SHUTDOWN_ENABLE
/* Turn off backlight on low brightness to save power */
#    define RGB_MATRIX_BRIGHTNESS_TURN_OFF_VAL 0

/* Indications */
#    define CAPS_LOCK_INDEX 32
#    define LOW_BAT_IND_INDEX \
        { 65 }

#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS

/* rgb settings */
#    define RGB_MATRIX_DEFAULT_ON true
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_BAND_VAL
#    define RGB_MATRIX_DEFAULT_HUE 170
#    define RGB_MATRIX_DEFAULT_SAT 255
#    define RGB_MATRIX_DEFAULT_VAL 255
#    define RGB_MATRIX_DEFAULT_SPD 70

#endif

/* force enable NKRO */
#    define FORCE_NKRO

/* increase layer count above the default of 5 */
#    define DYNAMIC_KEYMAP_LAYER_COUNT 16

/* tap time for tap dancing */
#    define TAPPING_TERM 250

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

/* for tmux send_string delays */
#    define TMUX_DELAY 25
#    define CONFIG_VS_LAYR_SEND_STRING_DELAY 35

/* monitored base layers for macos */
#    define CONFIG_MACOS_BASE_LAYERS { MAC_BASE }
#    define CONFIG_MACOS_BASE_LAYERS_COUNT 1
#    define CONFIG_DEFAULT_MAC_LAYR MAC_BASE
#    define CONFIG_DEFAULT_WIN_LAYR WIN_BASE

/* monitored base layers */
#    define CONFIG_ALL_BASE_LAYERS { MAC_BASE, WIN_BASE }
#    define CONFIG_ALL_BASE_LAYERS_COUNT 2
/* key indexes that changed to shifted version when caps is used */
#    define CONFIG_CAPSLOCK_SHIFTED ((i > 16 && i < 27) || (i > 32 && i < 42) || (i > 47 && i < 55))
#    define CONFIG_CAPSWORD_EXTRA (i == 11)

/* any nonstandard condition for keys that should not fade when pressed */
//#    define CONFIG_CUSTOM_DO_NOT_FADE (key.index < 19 || key.index == 72)

/* keyfade settings */
#    define CONFIG_KEYFADE_START_DELAY 16
#    define CONFIG_KEYFADE_START_VAL 250
#    define CONFIG_KEYFADE_CALLBACK_INTERVAL 15

/* rgb_matrix_indicators_advanced_user settings */
#    define CONFIG_HAS_LLOCK_KEY
#    define CONFIG_HAS_KLOCK_KEY
#    define CONFIG_HAS_SECOND_KTRACK_KEY
#    define CONFIG_HAS_SECOND_HROWLIGHT_KEY
#    define CONFIG_HAS_SECOND_FJLIGHT_KEY
#    define CONFIG_HAS_FKEY_LAYR
#    define CONFIG_HAS_KCLK_BATTERY
#    define CONFIG_BLINK_LAYR_EVEN_WITH_KEYCODE_ASSIGNED
#    define CONFIG_KEY_INDEX_MAX 71
/* this was the original indicator config
#    define CONFIG_RGB_LAYER_INDICATORS \
     { \
        I_INDICATOR1, \
        I_INDICATOR2, \
        I_INDICATOR3, \
        I_INDICATOR4, \
        I_INDICATOR5, \
        I_INDICATOR6, \
        I_INDICATOR7, \
        I_INDICATOR8 \
     }
*/
// single indicator config
#    define CONFIG_RGB_LAYER_INDICATORS { I_INDICATOR1 }
#    define CONFIG_RGB_LAYER_INDICATORS_COUNT 1
/* original multi-indicator config 
#    define I_INDICATOR I_INDICATOR1, I_INDICATOR2, I_INDICATOR3, I_INDICATOR4, \
                        I_INDICATOR5, I_INDICATOR6, I_INDICATOR7, I_INDICATOR8
*/
// single indicator config
#    define I_INDICATOR I_INDICATOR1
#    define CONFIG_FLASH_CAPS_ON_ALL_LAYERS
#    define CONFIG_LOCKED_LAYERS_STOP_FLASHING
#    define CONFIG_FN_LAYR_COLOR RGB_GREEN
#    define CONFIG_MREC_KEY_COLOR RGB_MAGENTA
#    define CONFIG_SHIFT_LAYR_COLOR RGB_ORANGE
#    define CONFIG_KCTL_LAYR_COLOR RGB_RED
#    define CONFIG_TMUX_LAYR_COLOR RGB_CYAN
#    define CONFIG_VS_LAYR_COLOR RGB_PURPLE
#    define CONFIG_SYM_LAYR_COLOR RGB_BLUE
#    define CONFIG_WIDE_LAYR_COLOR RGB_TURQUOISE
#    define CONFIG_CIRC_LAYR_COLOR RGB_CORAL
#    define CONFIG_EMO_LAYR_COLOR RGB_PURPLE
#    define CONFIG_FKEY_LAYR_COLOR 0x90,0x90,0x90 
#    define CONFIG_DEFUALT_LAYR_COLOR 0x77,0x77,0x77
#    define CONFIG_EXTRA_BASE_LAYR_COLORS \
     { \
         { I_CAPS, RGB_BLUE }, \
         { I_FN, RGB_BLUE }, \
         { I_TAB, 0x77,0x77,0x77 }, \
         { I_BSLS, 0x77,0x77,0x77 }, \
         { I_FKEY, 0x77,0x77,0x77 }, \
     }
#    define CONFIG_EXTRA_BASE_LAYR_COLORS_COUNT 5
#    define CONFIG_ACCENT_KEY_COLOR RGB_YELLOW
#    define CONFIG_CAPS_WORD_SHIFT_COLOR 0x77,0x77,0x77
#    define CONFIG_HROWLIGHT_COLOR RGB_GREEN
#    define CONFIG_FJLIGHT_COLOR RGB_WHITE
#    define CONFIG_LEADER_COLORA RGB_TURQUOISE
#    define CONFIG_LEADER_COLORB RGB_CYAN
#    define CONFIG_KEYLIGHT_STD_COLOR RGB_WHITE
#    define CONFIG_EEPROM_RESET_DEFAULT_LAYER MAC_BASE
#    define CONFIG_KCLK_24G_HOST_IDX 24
#    define CONFIG_KCLK_BT_KEY_START_IDX 0
#    define CONFIG_HAS_BASE_LAYER_TOGGLE
#    define CONFIG_SWITCH_PIN B12
#    define CONFIG_LOCK_ANIMATION_TIMEOUT 120000
#    define CONFIG_LOCK_RESTORE_ANIMATION_FROM_SUSPEND_MS 50
#    define CONFIG_LOCK_ANIMATION_COLOR_HSV HSV_RED
#    define CONFIG_LOCK_LAYR_EXTRA_FLASH_KEYS { I_LLOCK }
#    define CONFIG_LOCK_LAYR_EXTRA_FLASH_KEYS_COUNT 1

/* custom sleep setup */
#    define CONFIG_CUSTOM_SLEEP_TIMEOUT 540000
#    define CONFIG_CUSTOM_SLEEP_WARNING 5000
#    define CONFIG_CUSTOM_BLINK_INTERVAL 250
#    define CONFIG_CUSTOM_BT_TURN_OFF_DELAY 10000

// add for more accurate battery tracking on q max boards
#    define FULL_VOLTAGE_VALUE     4100
#    define EMPTY_VOLTAGE_VALUE    3700
#    define SHUTDOWN_VOLTAGE_VALUE 3550
