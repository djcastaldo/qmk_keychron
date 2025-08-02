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
#    define RGB_MATRIX_LED_COUNT 108
#    define DRIVER_CS_PINS \
        { B8, B9 }

/* Set LED driver current */
#    define SNLED27351_CURRENT_TUNE \
        { 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28 }

/* Set to infinit, which is use in USB mode by default */
#    define RGB_MATRIX_TIMEOUT RGB_MATRIX_TIMEOUT_INFINITE
/* Allow shutdown of led driver to save power */
#    define RGB_MATRIX_DRIVER_SHUTDOWN_ENABLE
/* Turn off backlight on low brightness to save power */
#    define RGB_MATRIX_BRIGHTNESS_TURN_OFF_VAL 32

/* Indications */
#    define NUM_LOCK_INDEX 36
#    define CAPS_LOCK_INDEX 59
#    define LOW_BAT_IND_INDEX \
        { 98 }

#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS

/* rgb settings */
#    define RGB_MATRIX_DEFAULT_ON true
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#    define RGB_MATRIX_DEFAULT_HUE 170
#    define RGB_MATRIX_DEFAULT_SAT 235
#    define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_MATRIX_DEFAULT_SPD 96

#endif

/* increase layer count above the default of 4 */
#    define DYNAMIC_KEYMAP_LAYER_COUNT 10

/* force enable NKRO */
#    define FORCE_NKRO

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
#    define LEADER_TIMEOUT 200
#    define LEADER_PER_KEY_TIMING
#    define LEADER_NO_TIMEOUT

/* for tmux send_string delays */
#    define TMUX_DELAY 25

/* monitored base layers for macos */
#    define MONITORED_MACOS_BASE_LAYERS { MAC_BASE }
#    define MONITORED_MACOS_BASE_COUNT 1
