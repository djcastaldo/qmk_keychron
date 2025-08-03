/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

#include "stdint.h"

// clang-format off
enum {
    KC_LOPTN = QK_KB_0,
    KC_ROPTN,
    KC_LCMMD,
    KC_RCMMD,
    KC_MCTRL,
    KC_LNPAD,
    KC_TASK_VIEW,
    KC_FILE_EXPLORER,
    KC_SCREEN_SHOT,
    KC_CORTANA,
#ifdef WIN_LOCK_SCREEN_ENABLE
    KC_WIN_LOCK_SCREEN,
    __KC_WIN_LOCK_SCREEN_NEXT,
#else
    __KC_WIN_LOCK_SCREEN_NEXT = KC_CORTANA + 1,
#endif
#ifdef MAC_LOCK_SCREEN_ENABLE
    KC_MAC_LOCK_SCREEN = __KC_WIN_LOCK_SCREEN_NEXT,
    __KC_MAC_LOCK_SCREEN_NEXT,
#else
    __KC_MAC_LOCK_SCREEN_NEXT = __KC_WIN_LOCK_SCREEN_NEXT,
#endif
    KC_SIRI = __KC_MAC_LOCK_SCREEN_NEXT,
#ifdef LK_WIRELESS_ENABLE
    BT_HST1,
    BT_HST2,
    BT_HST3,
    P2P4G,
    BAT_LVL,
#endif
#ifdef ANANLOG_MATRIX
    PROF1,
    PROF2,
    PROF3,
#endif
    SECRET0,
    SECRET1,
    SECRET2,
    SECRET3,
    SECRET4,
    SECRET5,
    SECRET6,
    SECRET7,
    SECRET8,
    SECRET9,
    SECRET10,
    SECRET11,
    SECRET12,
    SECRET13,
    SECRET14,
    SECRET15,
    SECRET16,
    SECRET17,
    SECRET18,
    SECRET19,
    SECRET20,
    SECRET21,
    SECRET22,
    SECRET23,
    SECRET24,
    SECRET25,
    SECRET26,
    SECRET27,
    SECRET28,
    SECRET29,
    SECRET30,
    SECRET31,
    JIGGLE,
    FJLIGHT,
    HROWLIGHT,
    KTRACK,
    WAVE,
    ARROW,
    BSPCFAST,
    TMUXLKEY,
    TMUXLCMD,
    TMONON,
    TMONOF,
    TVISON,
    TVISOF,
    TWINLFT,
    TWINRGT,
    TJPANE,
    ENC_TMON,
    DUAL_PLUSMIN,
    DUAL_MULTDIV,
    VI_REPLACE,
    GIT_ADD,
    GIT_COMMIT,
    GIT_PUSH,
    GIT_CHKOUT,
    GIT_LOG,
    COLORTEST,
    OPT2,
    OPT3,
    OPT4,
    OPT5,
    OPT6,
    OPT7,
    OPT8,
    OPT9,
    OPT0,
    OPTMIN,
    OPTEQ,
    OPTQ,
    OPTW,
    OPTR,
    OPTT,
    OPTY,
    OPTO,
    OPTP,
    OPTLBR,
    OPTRBR,
    OPTBSL,
    OPTA,
    OPTS,
    OPTD,
    OPTF,
    OPTG,
    OPTH,
    OPTJ,
    OPTK,
    OPTL,
    OPTSEM,
    OPTAPO,
    OPTZ,
    OPTX,
    OPTC,
    OPTV,
    OPTB,
    OPTM,
    OPTCOM,
    OPTDOT,
    OPTSLS,
    SUITH,
    SUITD,
    SUITC,
    SUITS,
    SUP1,
    SUP2,
    SUP3,
    NBSP,
    CIRCL1,
    CIRCL2,
    CIRCL3,
    CIRCL4,
    CIRCL5,
    CIRCL6,
    CIRCL7,
    CIRCL8,
    CIRCL9,
    CIRCL0,
    CIRCLQ,
    CIRCLW,
    CIRCLE,
    CIRCLR,
    CIRCLT,
    CIRCLY,
    CIRCLU,
    CIRCLI,
    CIRCLO,
    CIRCLP,
    CIRCLA,
    CIRCLS,
    CIRCLD,
    CIRCLF,
    CIRCLG,
    CIRCLH,
    CIRCLJ,
    CIRCLK,
    CIRCLL,
    CIRCLZ,
    CIRCLX,
    CIRCLC,
    CIRCLV,
    CIRCLB,
    CIRCLN,
    CIRCLM,
    NEW_SAFE_RANGE,
};

#ifndef LK_WIRELESS_ENABLE
    #define BT_HST1     KC_TRANS
    #define BT_HST2     KC_TRANS
    #define BT_HST3     KC_TRANS
    #define P2P4G       KC_TRANS
    #define BAT_LVL     KC_TRANS
#endif
#ifndef ANANLOG_MATRIX
    #define PROF1 KC_TRANS
    #define PROF2 KC_TRANS
    #define PROF3 KC_TRANS
#endif

#define KC_TASK KC_TASK_VIEW
#define KC_FILE KC_FILE_EXPLORER
#define KC_SNAP KC_SCREEN_SHOT
#define KC_CTANA KC_CORTANA
#define KC_WLCK KC_WIN_LOCK_SCREEN
#define KC_MLCK KC_MAC_LOCK_SCREEN

typedef struct PACKED {
    uint8_t len;
    uint8_t keycode[3];
} key_combination_t;

bool process_record_keychron_common(uint16_t keycode, keyrecord_t *record);
void keychron_common_task(void);

#ifdef ENCODER_ENABLE
void encoder_cb_init(void);
#endif

