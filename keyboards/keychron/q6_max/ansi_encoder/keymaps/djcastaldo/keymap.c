// 2025 @davex keymap.c for Keychron Q6 Max
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

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "wireless/battery.h"
#include "wireless/bat_level_animation.h"
#include "wireless/wireless.h"
#include "features/layer_lock.h"

#define NEWFINDER LOPT(LCMD(KC_SPC))            // open new Finder search window
#define FHOME LCMD(LSFT(KC_H))                  // open new Finder home dir 
#define FAPPS LCMD(LSFT(KC_A))                  // open new Finder apps dir 
#define FDOCS LCMD(LSFT(KC_O))                  // open new Finder docs dir 
#define FDOWNL LCMD(LOPT(KC_L))                 // open new Finder downloads dir 
#define CMDGRAVE LCMD(KC_GRV)                   // switch to next app window 
#define SCMDGRAVE LSFT(LCMD(KC_GRV))            // switch to prev app window 
#define FINSPECT LCMD(KC_I)                     // open inspector
#define FVHIDDEN LCMD(LSFT(KC_DOT))             // show Finder hidden files
#define FQLOOK LCMD(KC_Y)                       // open Finder quick look
#define FDELETE LCMD(KC_BSPC)                   // Finder move selection to trash 
#define FSTATBAR LCMD(KC_SLSH)                  // show Finder status bar
#define TOVERVIEW LSFT(LCMD(KC_BSLS))           // show Terminal tab overview
#define FORCEQUIT LOPT(LCMD(KC_ESC))            // force quit an app
#define TIMESTAMP LCTL(LOPT(LCMD(KC_T)))        // command to gen timestamp 
#define SOC1 LSFT(LOPT(LCMD(KC_1)))             // snap dock app switching 
#define SOC2 LSFT(LOPT(LCMD(KC_2)))             // snap dock app switching 
#define SOC3 LSFT(LOPT(LCMD(KC_3)))             // snap dock app switching 
#define SOC4 LSFT(LOPT(LCMD(KC_4)))             // snap dock app switching 
#define SOC5 LSFT(LOPT(LCMD(KC_5)))             // snap dock app switching 
#define SOC6 LSFT(LOPT(LCMD(KC_6)))             // snap dock app switching 
#define SOC7 LSFT(LOPT(LCMD(KC_7)))             // snap dock app switching 
#define SOC8 LSFT(LOPT(LCMD(KC_8)))             // snap dock app switching 
#define SOC9 LSFT(LOPT(LCMD(KC_9)))             // snap dock app switching 
#define SOC0 LSFT(LOPT(LCMD(KC_0)))             // snap dock app switching 
#define UNICODE LCTL(LCMD(KC_SPC))              // open unicode input menu
#define V_WSPC_NXT LCTL(LSFT(KC_PGUP))          // vivaldi workspace next
#define V_WSPC_PRV LCTL(LSFT(KC_PGDN))          // vivaldi workspace prev
#define V_TAB_NXT LCTL(KC_TAB)                  // vivaldi tab next
#define V_TAB_PRV LCTL(LSFT(KC_TAB))            // vivaldi tab prev
#define F_ZOOMI LCMD(KC_EQL)                    // form zoom in
#define F_ZOOMO LCMD(KC_MINS)                   // form zoom out 
#define F_ZOOMR LCMD(KC_0)                      // form zoom reset 
#define MOD_SIRI HYPR(KC_S)                     // customized siri launch 

__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}
__attribute__ ((weak))
bool process_leader_secrets(void) {
  return true;
}

enum layers {
    MAC_BASE,
    FN_LAYER,
    WIN_BASE,
    SFT_LAYER,
    CTL_LAYER,
    OPT_LAYER,
    TMUX_LAYER,
    SYMB_LAYER,
    WIDE_TEXT_LAYR,
    CIRCLE_TEXT_LAYR,
    LOCK_LAYER
};

enum custom_keycodes {
    CALCPRO = NEW_SAFE_RANGE,
    LOCKSCR,
    BACKDIR,
    HOMEDIR,
    LSLTRAH,
    LLOCK,
    FNLAYER,
    SFTLAYER,
    FJLIGHT,
    HROWLIGHT,
    KTRACK,
    WAVE,
    ARROW,
    BSPCFAST,
    DUAL_F13,
    DUAL_F14,
    DUAL_PMNS,
    E_SMILE,
    E_SMIRK,
    E_ASTON,
    E_SAD,
    E_CAR,
    E_BUS,
    E_TRAIN,
    E_TAXI,
    E_FLAGUS,
    E_FLAGPI,
    E_GLOBE,
    E_PIZZA,
    E_BURGER,
    E_CHICKEN,
    E_TACO,
    E_SNAIL,
    E_NINJA,
    E_STOP,
    E_HAND,
    E_SHH,
    E_PACKAGE,
    E_POINTU,
    E_POINTD,
    E_POINTL,
    E_POINTR,
    E_DRINK,
    E_EMARK,
    E_QMARK,
    E_CMARK,
    E_BULB,
    E_SSHOT,
    E_MIC,
    E_TRASH,
    E_I,
    E_K0,
    E_K1,
    E_K2,
    E_K3,
    E_K4,
    E_K5,
    E_K6,
    E_K7,
    E_K8,
    E_K9,
    E_STAR,
    E_HASH,
    E_MINS,
    E_PLUS,
    E_DIV,
    E_GRIM,
    E_KB,
    E_OK,
    E_SGLASS,
    E_BOTTLE,
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
    GNEWS,
    SSMENU,
    GIT_ADD,
    GIT_COMMIT,
    GIT_PUSH,
    GIT_CHKOUT,
    GIT_LOG,
    CURSORL,
    CURSORR,
    MK_HOLD,
    OPT_HOLD,
    MK_ACCEL0,
    MK_ACCEL2,
    DUAL_ENCPUSH,
    DUAL_ENCL,
    DUAL_ENCR,
    DUAL_ENCPUSH2,
    DUAL_ENCL2,
    DUAL_ENCR2,
    DUAL_UNIPUSH,
    DUAL_NAVL,
    DUAL_NAVR,
    PENT_ENCPUSH,
    PENT_ENCL,
    PENT_ENCR,
    VI_REPLACE,
    DUAL_SNAP,
    AP_GLOB,
    KB_RESET,
    TMUXLKEY,
    TMUXLCMD,
    TMONON,
    TMONOF,
    TVISON,
    TVISOF,
    TWINLFT,
    TWINRGT,
    TJPANE,
    ENC_TSIZEL,
    ENC_TSIZER,
    ENC_TMON,
    LTRANS,
    STHRU,
    UNDERLN,
    BARTEXT,
    BBRTEXT,
    COLORTEST,
    FLASH_KB,
    BOOTLDR
};

// custom tap dances
enum {
   CAPS_LAYR = 0,
   FN_OSL = 1,
   ROPT_OSL = 2,
   RCTL_OSL = 3,
   RSFT_OSL = 4,
   MOUSE_ACCEL = 5,
   KB_UNLOCK = 6
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//  [MAC_BASE]
//,-------------------------------------------------------------------------------------------------------------------------------------,
//: ____   ______________________   ______________________   ______________________   ,---.   ________________   ______________________ :
//:|Esc | | F1 || F2 || F3 || F4 | | F5 || F6 || F7 || F8 | | F9 || F10|| F11|| F12| : Vol : |Snap||Siri||Glob| |F13 ||DF14||Calc||Lock|:
//:|____| |____||____||____||____| |____||____||____||____| |____||____||____||____| `.___.  |____||____||____| |____||____||____||____|:
//: _______________________________________________________________________________________   ________________   ______________________ :
//:| `  || 1  || 2  || 3  || 4  || 5  || 6  || 7  || 8  || 9  || 0  || -  || =  || Bkspace | |Ins ||Home||PgUp| |Num || /  || *  || D- |:
//:|____||____||____||____||____||____||____||____||____||____||____||____||____||_________| |____||____||____| |____||____||____||____|:
//:|LT(Tab)|| Q  || W  || E  || R  || T  || Y  || U  || I  || O  || P  || [  || ]  || \    | |Del ||End ||PgDn| | 7  || 8  || 9  ||    |:
//:|_______||____||____||____||____||____||____||____||____||____||____||____||____||______| |____||____||____| |____||____||____|| +  |:
//:|TD(Caps)|| A  || S  || D  || F  || G  || H  || J  || K  || L  || ;  || '  || Enter     |                    | 4  || 5  || 6  ||    |:
//:|________||____||____||____||____||____||____||____||____||____||____||____||___________|        ____        |____||____||____||____|:
//:| Shift     || Z  || X  || C  || V  || B  || N  || M  || ,  || .  || /  ||TD(SFT_OSL)   |       |Up  |       | 1  || 2  || 3  ||    |:
//:|___________||____||____||____||____||____||____||____||____||____||____||______________|  ____ |____| ____  |____||____||____||Ent |:
//:|Ctrl ||Opt  || Cmd ||                Space                || Cmd ||TDOpt||TDFn ||TDCtrl| |Left||Down||Rigt| |    0     || .  ||    |:
//:|_____||_____||_____||_____________________________________||_____||_____||_____||______| |____||____||____| |__________||____||____|:
//`-------------------------------------------------------------------------------------------------------------------------------------`

    [MAC_BASE] = LAYOUT_109_ansi(
        KC_ESC,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,DUAL_ENCPUSH,
                                                                             DUAL_SNAP,KC_SIRI,AP_GLOB,DUAL_F13,DUAL_F14,CALCPRO,LOCKSCR,
        KC_GRV,KC_1,KC_2,KC_3,KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, BSPCFAST,
                                                                                 KC_INS,KC_HOME,KC_PGUP,KC_NUM,KC_PSLS,KC_PAST,DUAL_PMNS,
        LT(TMUX_LAYER,KC_TAB),KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_LBRC,KC_RBRC,KC_BSLS,
                                                                                                 KC_DEL,KC_END,KC_PGDN,KC_P7,KC_P8,KC_P9,
        TD(CAPS_LAYR),KC_A,KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L,KC_SCLN,KC_QUOT, KC_ENT,                 KC_P4, KC_P5, KC_P6, KC_PPLS,
        KC_LSFT, KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMM,KC_DOT,KC_SLSH, TD(RSFT_OSL),         KC_UP,        KC_P1, KC_P2, KC_P3,
        KC_LCTL,KC_LOPT,KC_LCMD,  KC_SPC, KC_RCMD,TD(ROPT_OSL),TD(FN_OSL),TD(RCTL_OSL),KC_LEFT,KC_DOWN,KC_RGHT, KC_P0, KC_PDOT, KC_PENT),
//  [FN_LAYER]
//,-------------------------------------------------------------------------------------------------------------------------------------,
//: ____   ______________________   ______________________   ______________________   ,---.   ________________   ______________________ :
//:|    | |    ||    ||VRep||    | |CkOt||    ||    ||GLog| |Add ||Cmit||    ||Push| :Zoom : |KLck||    ||Find| |Home||Apps||Docs||DLs |:
//:|____| |____||____||____||____| |____||____||____||____| |____||____||____||____| `.___.  |____||____||____| |____||____||____||____|:
//: _______________________________________________________________________________________   ________________   ______________________ :
//:|    ||    ||    ||    ||    ||    ||    ||    ||    ||    ||    ||Arro||Wave||         | |LLck||TPrv||WPrv| |Rout||Acct||DPW ||SFCU|:
//:|____||____||____||____||____||____||____||____||____||____||____||____||____||_________| |____||____||____| |____||____||____||____|:
//:|M(TMUX)||WMa2||WMa1||Mail||RPho||WPho||    ||Uni ||    ||    ||    ||    ||    ||      | |    ||TNxt||WNxt| |Mail||WMa1||WMa2||    |:
//:|_______||____||____||____||____||____||____||____||____||____||____||____||____||______| |____||____||____| |____||____||____||    |:
//:|        ||Addr||City||ZIP ||Phon||    ||    ||    ||    ||Lead||    ||    ||           |                    |Addr||City||ZIP ||    |:
//:|________||____||____||____||____||____||____||____||____||____||____||____||___________|        ____        |____||____||____||____|:
//:|MO(SFT_L)  ||    ||Rout||Acct||    ||    ||    ||    ||    ||    ||    ||MO(SFT_LAYER) |       |    |       |Phon||RPho||WPho||    |:
//:|___________||____||____||____||____||____||____||____||____||____||____||______________|  ____ |____| ____  |____||____||____||    |:
//:|MOCtl||MOOpt||     ||                                     ||     ||MOOpt||     ||MOCtrl| |    ||    ||    | |Timestamp ||    ||    |:
//:|_____||_____||_____||_____________________________________||_____||_____||_____||______| |____||____||____| |__________||____||____|:
//`-------------------------------------------------------------------------------------------------------------------------------------`
    [FN_LAYER] = LAYOUT_109_ansi(
        _______,_______,_______,VI_REPLACE,_______,GIT_CHKOUT,_______,_______,GIT_LOG,GIT_ADD,GIT_COMMIT,_______,GIT_PUSH,F_ZOOMR,
                                                                                  SSMENU,MOD_SIRI,GNEWS, DM_REC1,DM_REC2,DM_PLY1,DM_PLY2,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______, _______, ARROW, WAVE, _______,
                                                                          LLOCK,V_TAB_PRV,V_WSPC_PRV,SECRET10,SECRET11,SECRET12,SECRET13,
        MO(TMUX_LAYER),SECRET3,SECRET2,SECRET1,SECRET8,SECRET9,_______,UNICODE,_______,_______,_______,_______,_______, _______,
                                                                           _______,V_TAB_NXT,V_WSPC_NXT,SECRET1,SECRET2,SECRET3,
        _______,SECRET4,SECRET5,SECRET6,SECRET7,_______,_______,_______,_______, QK_LEAD, _______, _______,      _______,
                                                                                                         SECRET4,SECRET5,SECRET6,_______,
        SFTLAYER, _______, SECRET10, SECRET11, _______,_______,_______,_______,_______,_______,_______, SFTLAYER,
                                                                                                      _______,   SECRET7,SECRET8,SECRET9,
        MO(CTL_LAYER),MO(OPT_LAYER), _______,          _______,          _______, MO(OPT_LAYER), _______, MO(CTL_LAYER),
                                                                                  _______, _______, _______, TIMESTAMP, _______,_______),
//  [WIN_BASE]
//,-------------------------------------------------------------------------------------------------------------------------------------,
//: ____   ______________________   ______________________   ______________________   ,---.   ________________   ______________________ :
//:|Esc | | F1 || F2 || F3 || F4 | | F5 || F6 || F7 || F8 | | F9 || F10|| F11|| F12| : Vol : |PScr||Ctan||RGB | |    ||    ||    ||    |:
//:|____| |____||____||____||____| |____||____||____||____| |____||____||____||____| `.___.  |____||____||____| |____||____||____||____|:
//: _______________________________________________________________________________________   ________________   ______________________ :
//:| `  || 1  || 2  || 3  || 4  || 5  || 6  || 7  || 8  || 9  || 0  || -  || =  || Bkspace | |Ins ||Home||PgUp| |Num || /  || *  || -  |:
//:|____||____||____||____||____||____||____||____||____||____||____||____||____||_________| |____||____||____| |____||____||____||____|:
//:| Tab   || Q  || W  || E  || R  || T  || Y  || U  || I  || O  || P  || [  || ]  || \    | |Del ||End ||PgDn| | 7  || 8  || 9  ||    |:
//:|_______||____||____||____||____||____||____||____||____||____||____||____||____||______| |____||____||____| |____||____||____|| +  |:
//:| Caps   || A  || S  || D  || F  || G  || H  || J  || K  || L  || ;  || '  || Enter     |                    | 4  || 5  || 6  ||    |:
//:|________||____||____||____||____||____||____||____||____||____||____||____||___________|        ____        |____||____||____||____|:
//:| Shift     || Z  || X  || C  || V  || B  || N  || M  || ,  || .  || /  ||    Shift     |       |Up  |       | 1  || 2  || 3  ||    |:
//:|___________||____||____||____||____||____||____||____||____||____||____||______________|  ____ |____| ____  |____||____||____||Ent |:
//:|LCtrl||LWin ||LAlt ||                Space                ||RAlt ||RWin ||MOSft||RCtrl | |Left||Down||Rigt| |    0     || .  ||    |:
//:|_____||_____||_____||_____________________________________||_____||_____||_____||______| |____||____||____| |__________||____||____|:
//`-------------------------------------------------------------------------------------------------------------------------------------`
    [WIN_BASE] = LAYOUT_109_ansi(
        KC_ESC,KC_F1,KC_F2,KC_F3,KC_F4, KC_F5,KC_F6,KC_F7,KC_F8, KC_F9,KC_F10,KC_F11,KC_F12,KC_MUTE,
                                                                              KC_PSCR,KC_CTANA,RGB_MOD,  _______,_______,_______,_______,
        KC_GRV,KC_1,KC_2,KC_3,KC_4,KC_5,KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINS,KC_EQL,KC_BSPC,KC_INS,KC_HOME,KC_PGUP,
                                                                                                          KC_NUM,KC_PSLS,KC_PAST,KC_PMNS,
        KC_TAB,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_LBRC,KC_RBRC, KC_BSLS, KC_DEL, KC_END, KC_PGDN,  KC_P7, KC_P8, KC_P9,
        KC_CAPS,KC_A,KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L, KC_SCLN, KC_QUOT,   KC_ENT,                   KC_P4, KC_P5, KC_P6, KC_PPLS,
        KC_LSFT,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMM,KC_DOT,KC_SLSH,         KC_RSFT,        KC_UP,     KC_P1, KC_P2, KC_P3,
        KC_LCTL, KC_LWIN, KC_LALT,     KC_SPC,    KC_RALT,KC_RWIN,MO(SFT_LAYER),KC_RCTL, KC_LEFT,KC_DOWN,KC_RGHT, KC_P0,KC_PDOT,KC_PENT),
//  [SFT_LAYER]
//,-------------------------------------------------------------------------------------------------------------------------------------,
//: ____   ______________________   ______________________   ______________________   ,---.   ________________   ______________________ :
//:|    | |    ||    ||    ||    | |    ||    ||    ||    | |    ||    ||    ||    | : Uni : |EScr||EMic||EBul| |ESmi||Eirk||EAst||ESad|:
//:|____| |____||____||____||____| |____||____||____||____| |____||____||____||____| `.___.  |____||____||____| |____||____||____||____|:
//: _______________________________________________________________________________________   ________________   ______________________ :
//:|    || E1 || E2 || E3 || E4 || E5 || E6 || E7 || E8 || E9 || E0 || E- || E+ ||         | |LLck||EDri||EMrk| |Car ||Bus ||Trai||Taxi|:
//:|____||____||____||____||____||____||____||____||____||____||____||____||____||_________| |____||____||____| |____||____||____||____|:
//:|       ||    ||    ||    ||    ||    ||    ||    || EI ||EOK ||    ||    ||    ||      | |EDel||ECMk||EQMk| |US  ||PI  ||Glob||    |:
//:|_______||____||____||____||____||____||____||____||____||____||____||____||____||______| |____||____||____| |____||____||____||Taco|:
//:|        ||Star||SunG||    ||    ||    ||Hash||    ||Keyb||    ||    ||    ||           |                    |Piza||Burg||Chik||    |:
//:|________||____||____||____||____||____||____||____||____||____||____||____||___________|        ____        |____||____||____||____|:
//:|           ||    ||    ||    ||    ||Botl||    ||    ||    ||Grim||Div ||              |       |EUp |       |Snai||Ninj||Stop||    |:
//:|___________||____||____||____||____||____||____||____||____||____||____||______________|  ____ |____| ____  |____||____||____||Pack|:
//:|     ||     ||     ||                                     ||     ||     ||     ||      | |ELft||EDwn||ERgt| |  EHand   ||Shh ||    |:
//:|_____||_____||_____||_____________________________________||_____||_____||_____||______| |____||____||____| |__________||____||____|:
//`-------------------------------------------------------------------------------------------------------------------------------------`
    [SFT_LAYER] = LAYOUT_109_ansi(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, DUAL_UNIPUSH,
                                                                                E_SSHOT, E_MIC, E_BULB, E_SMILE, E_SMIRK, E_ASTON, E_SAD,
        _______,E_K1,E_K2,E_K3,E_K4,E_K5,E_K6,E_K7,E_K8,E_K9,E_K0,E_MINS,E_PLUS,_______,LLOCK,E_DRINK,E_EMARK,E_CAR,E_BUS,E_TRAIN,E_TAXI,
        _______,_______,_______,_______,_______,_______,_______,_______,E_I,E_OK,_______,_______,_______,_______,
                                                                               E_TRASH,E_CMARK,E_QMARK, E_FLAGUS,E_FLAGPI,E_GLOBE,
        _______,E_STAR,E_SGLASS,_______,_______,_______,E_HASH,_______,E_KB,_______,_______,_______,_______,
                                                                                                       E_PIZZA,E_BURGER,E_CHICKEN,E_TACO,
        _______,_______,_______,_______,_______,E_BOTTLE,_______,_______,_______,E_GRIM,E_DIV,_______, E_POINTU,  E_SNAIL,E_NINJA,E_STOP,
        _______,_______,_______,       _______,       _______,_______,_______,_______,E_POINTL,E_POINTD,E_POINTR,E_HAND,E_SHH,E_PACKAGE),
//  [CTL_LAYER]
//,-------------------------------------------------------------------------------------------------------------------------------------,
//: ____   ______________________   ______________________   ______________________   ,---.   ________________   ______________________ :
//:|    | |    ||    ||    ||    | |RSet||    ||    ||    | |    ||    ||CTst||Debg| : RGB : |KLck||KTrk||RGBM| |    ||Log ||    ||    |:
//:|____| |____||____||____||____| |____||____||____||____| |____||____||____||____| `.___.  |____||____||____| |____||____||____||____|:
//: _______________________________________________________________________________________   ________________   ______________________ :
//:|    ||BT1 ||BT2 ||BT3 ||2.4G||    ||    ||    ||    ||    ||    ||    ||    ||         | |LLck||FJLi||    | |    ||    ||    ||    |:
//:|____||____||____||____||____||____||____||____||____||____||____||____||____||_________| |____||____||____| |____||____||____||____|:
//:|       ||    ||    ||    ||Rebt||    ||    ||    ||    ||    ||    ||    ||    ||      | |    ||HRLi||    | |    ||    ||    ||    |:
//:|_______||____||____||____||____||____||____||____||____||____||____||____||____||______| |____||____||____| |____||____||____||    |:
//:|        ||    ||    ||    ||Flsh||    ||    ||    ||    ||    ||    ||    ||           |                    |    ||    ||    ||    |:
//:|________||____||____||____||____||____||____||____||____||____||____||____||___________|        ____        |____||____||____||____|:
//:|           ||    ||    ||EClr||    ||Boot||    ||    ||    ||    ||    ||              |       |RMo+|       |    ||    ||    ||    |:
//:|___________||____||____||____||____||____||____||____||____||____||____||______________|  ____ |____| ____  |____||____||____||    |:
//:|     ||     ||     ||          Battery Level              ||     ||     ||     ||      | |RSp-||RMo-||RSp+| |          ||    ||    |:
//:|_____||_____||_____||_____________________________________||_____||_____||_____||______| |____||____||____| |__________||____||____|:
//`-------------------------------------------------------------------------------------------------------------------------------------`
    [CTL_LAYER] = LAYOUT_109_ansi(
        _______,_______,_______,_______,_______,KB_RESET,_______,_______,_______,_______,_______,COLORTEST,DB_TOGG, PENT_ENCPUSH,
                                                                             QK_LOCK, KTRACK, RGB_MOD, _______, SECRET0, _______,_______,
        _______,BT_HST1,BT_HST2,BT_HST3,P2P4G,_______,_______,_______,_______,_______,_______,_______,_______,_______,
                                                                                  LLOCK,FJLIGHT,_______, _______,_______,_______,_______,
        _______,_______,_______,_______,QK_RBT,_______,_______,_______,_______,_______,_______,_______,_______,_______,
                                                                                       _______,HROWLIGHT,_______,_______,_______,_______,
        _______,_______,_______,_______,FLASH_KB,_______,_______,_______,_______,_______,KTRACK,FJLIGHT,HROWLIGHT,
                                                                                                         _______,_______,_______,_______,
        _______,_______,_______, EE_CLR,_______,BOOTLDR,_______,_______,_______,_______,_______, _______,  RGB_MOD,
                                                                                                         _______,_______,_______,
        _______,_______,_______,      BAT_LVL,     _______,_______,_______,_______, RGB_SPD,RGB_RMOD,RGB_SPI, _______, _______, _______),
//  [OPT_LAYER]
//,-------------------------------------------------------------------------------------------------------------------------------------,
//: ____   ______________________   ______________________   ______________________   ,---.   ________________   ______________________ :
//:|    | |    ||    ||MCtl||LPad| |    ||    ||MPrv||MPly| |MNxt||    ||    ||    | :Scrol: |Snap||Siri||News| |Rec1||Rec2||Ply1||Ply2|:
//:|____| |____||____||____||____| |____||____||____||____| |____||____||____||____| `.___.  |____||____||____| |____||____||____||____|:
//: _______________________________________________________________________________________   ________________   ______________________ :
//:|Quit||SOC1||SOC2||SOC3||SOC4||SOC5||SOC6||SOC7||SOC8||SOC9||SOC0||    ||    ||         | |LLck||TPrv||APrv| |QLok||Insp||Hide||Stat|:
//:|____||____||____||____||____||____||____||____||____||____||____||____||____||_________| |____||____||____| |____||____||____||____|:
//:|MAcel2 ||QLok||    ||    ||    ||Time||    ||Btn1||MSUp||OHld||    ||    ||    ||OverVw| |FDel||TNxt||ANxt| |    ||    ||    ||    |:
//:|_______||____||____||____||____||____||____||____||____||____||____||____||____||______| |____||____||____| |____||____||____||    |:
//:|        ||    ||    ||    ||    ||    ||    ||MLft||MSDn||MRgt||TDAc||    ||           |                    |cd..||cd ~||cQMK||    |:
//:|________||____||____||____||____||____||____||____||____||____||____||____||___________|        ____        |____||____||____||____|:
//:|MAcel0     ||MAc2||    ||    ||    ||    ||    ||MHld||CsrL||CsrR||Stat||              |       |    |       |ls  ||log ||rsnc||    |:
//:|___________||____||____||____||____||____||____||____||____||____||____||______________|  ____ |____| ____  |____||____||____||    |:
//:|     ||     ||     ||                                     ||     ||     ||     ||      | |    ||    ||    | |Timestamp ||    ||    |:
//:|_____||_____||_____||_____________________________________||_____||_____||_____||______| |____||____||____| |__________||____||____|:
//`-------------------------------------------------------------------------------------------------------------------------------------`
    [OPT_LAYER] = LAYOUT_109_ansi(
        _______,_______,_______,KC_MCTRL,KC_LNPAD,_______,_______,KC_MPRV,KC_MPLY,KC_MNXT,_______,_______,_______, DUAL_ENCPUSH2,
                                                                                      QK_LOCK,_______,NEWFINDER,FHOME,FAPPS,FDOCS,FDOWNL,
        FORCEQUIT,SOC1,SOC2,SOC3,SOC4,SOC5,SOC6,SOC7,SOC8,SOC9,SOC0,_______,_______,_______,
                                                                             LLOCK,V_TAB_PRV,SCMDGRAVE,FQLOOK,FINSPECT,FVHIDDEN,FSTATBAR,
        MK_ACCEL2,FQLOOK,_______,_______,_______,TIMESTAMP,_______,KC_MS_BTN1,KC_MS_UP,OPT_HOLD,_______,_______,_______,TOVERVIEW,
                                                                                      FDELETE,V_TAB_NXT,CMDGRAVE,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,TD(MOUSE_ACCEL),_______,_______,
                                                                                                        BACKDIR,HOMEDIR,SECRET22,_______,
        MK_ACCEL0,MK_ACCEL2,_______,_______,_______,_______,_______,MK_HOLD,CURSORL,CURSORR,FSTATBAR,_______,_______,
                                                                                                        LSLTRAH,GIT_LOG,SECRET25,
        _______,_______,_______,      _______,     _______,_______,_______,_______, _______,_______,_______,  TIMESTAMP,_______,_______),
//  [TMUX_LAYER]
//,-------------------------------------------------------------------------------------------------------------------------------------,
//: ____   ______________________   ______________________   ______________________   ,---.   ________________   ______________________ :
//:|    | |LKey||LCmd||    ||    | |MOn ||MOff||VOn ||Voff| |    ||    ||WLef||WRgt| :Resiz: |Join||    ||    | |    ||    ||    ||    |:
//:|____| |____||____||____||____| |____||____||____||____| |____||____||____||____| `.___.  |____||____||____| |____||____||____||____|:
//: _______________________________________________________________________________________   ________________   ______________________ :
//:|    ||PFix||PFix||PFix||PFix||PFix||PFix||PFix||PFix||PFix||PFix||PFix||PFix||         | |LLck||    ||PFix| |    ||    ||    ||    |:
//:|____||____||____||____||____||____||____||____||____||____||____||____||____||_________| |____||____||____| |____||____||____||____|:
//:|       ||PFix||PFix||    ||    ||PFix||    ||    ||    ||PFix||PFix||PFix||PFix||      | |    ||    ||    | |PFix||PFix||PFix||    |:
//:|_______||____||____||____||____||____||____||____||____||____||____||____||____||______| |____||____||____| |____||____||____||    |:
//:|        ||    ||PFix||PFix||    ||    ||    ||    ||    ||PFix||PFix||PFix||           |                    |PFix||PFix||PFix||    |:
//:|________||____||____||____||____||____||____||____||____||____||____||____||___________|        ____        |____||____||____||____|:
//:|           ||PFix||PFix||PFix||    ||    ||PFix||    ||PFix||PFix||PFix||              |       |PFix|       |PFix||PFix||PFix||    |:
//:|___________||____||____||____||____||____||____||____||____||____||____||______________|  ____ |____| ____  |____||____||____||    |:
//:|LCtl ||LAlt ||     ||               PFix                  ||     ||LAlt ||     ||RCtl  | |PFix||PFix||PFix| |   PFix   ||PFix||    |:
//:|_____||_____||_____||_____________________________________||_____||_____||_____||______| |____||____||____| |__________||____||____|:
//`-------------------------------------------------------------------------------------------------------------------------------------`
    [TMUX_LAYER] = LAYOUT_109_ansi(
        _______,TMUXLKEY,TMUXLCMD,_______,_______,TMONON,TMONOF,TVISON,TVISOF,_______,_______,TWINLFT,TWINRGT, ENC_TMON,
                                                                              TJPANE,_______,_______,  _______, _______, _______,_______,
        _______,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,_______,
                                                                                   LLOCK,_______,LTRANS, _______,_______,_______,_______,
        _______,LTRANS,LTRANS,_______,_______,LTRANS,_______,_______,_______,LTRANS,LTRANS,LTRANS,LTRANS,_______,
                                                                                            _______,_______,_______,LTRANS,LTRANS,LTRANS,
        _______,_______,LTRANS,LTRANS,_______,_______,_______,_______,_______,LTRANS,LTRANS,LTRANS,_______,
                                                                                                             LTRANS,LTRANS,LTRANS,LTRANS,
        _______,LTRANS,LTRANS,LTRANS,_______,_______,LTRANS,_______,LTRANS,LTRANS,LTRANS, _______,  LTRANS,  LTRANS,LTRANS,LTRANS,
        KC_LCTL,KC_LALT,_______,         LTRANS,        _______,KC_LALT,_______,KC_RCTL, LTRANS,LTRANS,LTRANS,  LTRANS, LTRANS, _______),
//  [SYMB_LAYER] 
//,-------------------------------------------------------------------------------------------------------------------------------------,
//: ____   ______________________   ______________________   ______________________   ,---.   ________________   ______________________ :
//:|    | |SUP1||SUP2||SUP3||    | |SUTH||SUTD||SUTC||SUTS| |CRCI||    ||    ||NBSP| : Vol : |    ||    ||    | |    ||    ||    ||    |:
//:|____| |____||____||____||____| |____||____||____||____| |____||____||____||____| `.___.  |____||____||____| |____||____||____||____|:
//: _______________________________________________________________________________________   ________________   ______________________ :
//:|LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||         | |LLck||    ||    | |    ||    ||    ||    |:
//:|____||____||____||____||____||____||____||____||____||____||____||____||____||_________| |____||____||____| |____||____||____||____|:
//:|       ||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN  | |    ||    ||    | |    ||    ||    ||    |:
//:|_______||____||____||____||____||____||____||____||____||____||____||____||____||______| |____||____||____| |____||____||____||    |:
//:|        ||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||           |                    |    ||    ||    ||    |:
//:|________||____||____||____||____||____||____||____||____||____||____||____||___________|        ____        |____||____||____||____|:
//:|LShift     ||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||RShift        |       |    |       |    ||    ||    ||    |:
//:|___________||____||____||____||____||____||____||____||____||____||____||______________|  ____ |____| ____  |____||____||____||    |:
//:|     ||     ||     ||                                     ||     ||     ||     ||      | |    ||    ||    | |          ||    ||    |:
//:|_____||_____||_____||_____________________________________||_____||_____||_____||______| |____||____||____| |__________||____||____|:
//`-------------------------------------------------------------------------------------------------------------------------------------`
    [SYMB_LAYER] = LAYOUT_109_ansi(
        _______, SUP1, SUP2, SUP3, _______, SUITH, SUITD, SUITC, SUITS,  CIRCLI, _______, _______, NBSP, KC_MUTE,
                                                                             _______,_______,_______,  _______, _______, _______,_______,
        LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,_______,
                                                                                  LLOCK,_______,_______, _______,_______,_______,_______,
        _______,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,
                                                                                         _______,_______,_______,_______,_______,_______,
        _______,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,_______,
                                                                                                         _______,_______,_______,_______,
        KC_LSFT,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS, KC_RSFT,     _______,     _______,_______,_______,
        _______,_______,_______,      _______,      _______,_______,_______,_______, _______,_______,_______, _______, _______, _______),
//  [WIDE_TEXT_LAYR]
//,-------------------------------------------------------------------------------------------------------------------------------------,
//: ____   ______________________   ______________________   ______________________   ,---.   ________________   ______________________ :
//:|    | |    ||    ||    ||    | |    ||    ||    ||    | |    ||    ||    ||    | : Vol : |    ||    ||    | |    ||    ||    ||    |:
//:|____| |____||____||____||____| |____||____||____||____| |____||____||____||____| `.___.  |____||____||____| |____||____||____||____|:
//: _______________________________________________________________________________________   ________________   ______________________ :
//:|LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||         | |LLck||BBTx||SThr| |    ||    ||    ||    |:
//:|____||____||____||____||____||____||____||____||____||____||____||____||____||_________| |____||____||____| |____||____||____||____|:
//:|       ||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN  | |    ||BTxt||ULin| |    ||    ||    ||    |:
//:|_______||____||____||____||____||____||____||____||____||____||____||____||____||______| |____||____||____| |____||____||____||    |:
//:|        ||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||           |                    |    ||    ||    ||    |:
//:|________||____||____||____||____||____||____||____||____||____||____||____||___________|        ____        |____||____||____||____|:
//:|           ||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||LTRN||              |       |    |       |    ||    ||    ||    |:
//:|___________||____||____||____||____||____||____||____||____||____||____||______________|  ____ |____| ____  |____||____||____||    |:
//:|     ||     ||     ||              LTRANS                 ||     ||     ||     ||      | |    ||    ||    | |          ||    ||    |:
//:|_____||_____||_____||_____________________________________||_____||_____||_____||______| |____||____||____| |__________||____||____|:
//`-------------------------------------------------------------------------------------------------------------------------------------`
    [WIDE_TEXT_LAYR] = LAYOUT_109_ansi(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, KC_MUTE,
                                                                             _______,_______,_______,  _______, _______, _______,_______,
        LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,_______,
                                                                                    LLOCK,BBRTEXT,STHRU, _______,_______,_______,_______,
        _______,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,
                                                                                         _______,BARTEXT,UNDERLN,_______,_______,_______,
        _______,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,_______,
                                                                                                         _______,_______,_______,_______,
        _______,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS,LTRANS, _______,     _______,     _______,_______,_______,
        _______,_______,_______,       LTRANS,      _______,_______,_______,_______, _______,_______,_______, _______, _______, _______),
//  [CIRCLE_TEXT_LAYR]
//,-------------------------------------------------------------------------------------------------------------------------------------,
//: ____   ______________________   ______________________   ______________________   ,---.   ________________   ______________________ :
//:|    | |    ||    ||    ||    | |    ||    ||    ||    | |    ||    ||    ||    | : Vol : |    ||    ||    | |    ||    ||    ||    |:
//:|____| |____||____||____||____| |____||____||____||____| |____||____||____||____| `.___.  |____||____||____| |____||____||____||____|:
//: _______________________________________________________________________________________   ________________   ______________________ :
//:|    ||CIR1||CIR2||CIR3||CIR4||CIR5||CIR6||CIR7||CIR8||CIR9||CIR0||    ||    ||         | |LLck||    ||    | |    ||    ||    ||    |:
//:|____||____||____||____||____||____||____||____||____||____||____||____||____||_________| |____||____||____| |____||____||____||____|:
//:|       ||CIRQ||CIRW||CIRE||CIRR||CIRT||CIRY||CIRU||CIRI||CIRO||CIRP||    ||    ||      | |    ||    ||    | |    ||    ||    ||    |:
//:|_______||____||____||____||____||____||____||____||____||____||____||____||____||______| |____||____||____| |____||____||____||    |:
//:|        ||CIRA||CIRS||CIRD||CIRF||CIRG||CIRH||CIRJ||CIRK||CIRL||    ||    ||           |                    |    ||    ||    ||    |:
//:|________||____||____||____||____||____||____||____||____||____||____||____||___________|        ____        |____||____||____||____|:
//:|           ||CIRZ||CIRX||CIRC||CIRV||CIRB||CIRN||CIRM||    ||    ||    ||              |       |    |       |    ||    ||    ||    |:
//:|___________||____||____||____||____||____||____||____||____||____||____||______________|  ____ |____| ____  |____||____||____||    |:
//:|     ||     ||     ||                                     ||     ||     ||     ||      | |    ||    ||    | |          ||    ||    |:
//:|_____||_____||_____||_____________________________________||_____||_____||_____||______| |____||____||____| |__________||____||____|:
//`-------------------------------------------------------------------------------------------------------------------------------------`
    [CIRCLE_TEXT_LAYR] = LAYOUT_109_ansi(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, KC_MUTE,
                                                                             _______,_______,_______,  _______, _______, _______,_______,
        _______,CIRCL1,CIRCL2,CIRCL3,CIRCL4,CIRCL5,CIRCL6,CIRCL7,CIRCL8,CIRCL9,CIRCL0,_______,_______,_______,
                                                                                  LLOCK,_______,_______, _______,_______,_______,_______,
        _______,CIRCLQ,CIRCLW,CIRCLE,CIRCLR,CIRCLT,CIRCLY,CIRCLU,CIRCLI,CIRCLO,CIRCLP,_______,_______,_______,
                                                                                         _______,_______,_______,_______,_______,_______,
        _______,CIRCLA,CIRCLS,CIRCLD,CIRCLF,CIRCLG,CIRCLH,CIRCLJ,CIRCLK,CIRCLL,_______,_______,_______,
                                                                                                         _______,_______,_______,_______,
        _______,CIRCLZ,CIRCLX,CIRCLC,CIRCLV,CIRCLB,CIRCLN,CIRCLM,_______,_______,_______, _______,   _______,    _______,_______,_______,
        _______,_______,_______,      _______,      _______,_______,_______,_______, _______,_______,_______, _______, _______, _______),
//  [LOCK_LAYER]
//,-------------------------------------------------------------------------------------------------------------------------------------,
//: ____   ______________________   ______________________   ______________________   ,---.   ________________   ______________________ :
//:| No | | No || No || No || No | | No || No || No || No | | No || No || No || No | :UnLck: | No || No || No | | No || No || No || No |:
//:|____| |____||____||____||____| |____||____||____||____| |____||____||____||____| `.___.  |____||____||____| |____||____||____||____|:
//: _______________________________________________________________________________________   ________________   ______________________ :
//:| No || No || No || No || No || No || No || No || No || No || No || No || No ||   No    | | No || No || No | | No || No || No || No |:
//:|____||____||____||____||____||____||____||____||____||____||____||____||____||_________| |____||____||____| |____||____||____||____|:
//:|  No   || No || No || No || No || No || No || No || No || No || No || No || No ||  No  | | No || No || No | | No || No || No ||    |:
//:|_______||____||____||____||____||____||____||____||____||____||____||____||____||______| |____||____||____| |____||____||____|| No |:
//:|   No   || No || No || No || No || No || No || No || No || No || No || No ||    No     |                    | No || No || No ||    |:
//:|________||____||____||____||____||____||____||____||____||____||____||____||___________|        ____        |____||____||____||____|:
//:|    No     || No || No || No || No || No || No || No || No || No || No ||      No      |       | No |       | No || No || No ||    |:
//:|___________||____||____||____||____||____||____||____||____||____||____||______________|  ____ |____| ____  |____||____||____|| No |:
//:| No  || No  || No  ||                 No                  || No  || No  || No  ||  No  | | No || No || No | |    No    || No ||    |:
//:|_____||_____||_____||_____________________________________||_____||_____||_____||______| |____||____||____| |__________||____||____|:
//`-------------------------------------------------------------------------------------------------------------------------------------`
    [LOCK_LAYER] = LAYOUT_109_ansi(
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,TD(KB_UNLOCK),KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
                                                                                                                                   KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,  KC_NO,KC_NO,KC_NO, KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,  KC_NO,KC_NO,KC_NO, KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                           KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,  KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,          KC_NO,        KC_NO,       KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,                  KC_NO,                  KC_NO,KC_NO,KC_NO,KC_NO,  KC_NO,KC_NO,KC_NO, KC_NO,     KC_NO,KC_NO),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE]         = {ENCODER_CCW_CW(DUAL_ENCL, DUAL_ENCR)},
    [FN_LAYER]         = {ENCODER_CCW_CW(F_ZOOMO, F_ZOOMI)},
    [WIN_BASE]         = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [SFT_LAYER]        = {ENCODER_CCW_CW(DUAL_NAVL, DUAL_NAVR)},
    [CTL_LAYER]        = {ENCODER_CCW_CW(PENT_ENCL, PENT_ENCR)},
    [OPT_LAYER]        = {ENCODER_CCW_CW(DUAL_ENCL2, DUAL_ENCR2)},
    [TMUX_LAYER]       = {ENCODER_CCW_CW(ENC_TSIZEL, ENC_TSIZER)},
    [SYMB_LAYER]       = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIDE_TEXT_LAYR]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [CIRCLE_TEXT_LAYR] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LOCK_LAYER]       = {ENCODER_CCW_CW(KC_NO, KC_NO)},
};

#endif // ENCODER_MAP_ENABLE

//  <~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>
//  ~=~=~=~=~=~=~=~=~=~=~=~ LED Indexes ~=~=~=~=~=~=~=~=~=~=~=~
//,-------------------------------------------------------------------------------------------------------------------------------------,
//: ____   ______________________   ______________________   ______________________   ,---.   ________________   ______________________ :
//:|0   | |1:F1||2:F2||3:F3||4:F4| |5:F5||6:F6||7:F7||8:F8| |9:F9||10  ||11  ||12  | :     : |13  ||14  ||15  | |16  ||17  ||18  ||72:X|:
//:|____| |____||____||____||____| |____||____||____||____| |____||____||____||____| `.___.  |____||____||____| |____||____||____||____|:
//: _______________________________________________________________________________________   ________________   ______________________ :
//:|19:`||20:1||21:2||22:3||23:4||24:5||25:6||26:7||27:8||28:9||29:0||30:-||31:=||32:Bkspce| |33  ||34  ||35  | |36  ||37  ||38  ||73:-|:
//:|____||____||____||____||____||____||____||____||____||____||____||____||____||_________| |____||____||____| |____||____||____||____|:
//:|39:Tab ||40:Q||41:W||42:E||43:R||44:T||45:Y||46:U||47:I||48:O||49:P||50:[||51:]||52:\  | |53  ||54  ||55  | |56:7||57:8||58:9||    |:
//:|_______||____||____||____||____||____||____||____||____||____||____||____||____||______| |____||____||____| |____||____||____||74:+|:
//:|59:Caps ||60:A||61:S||62:D||63:F||64:G||65:H||66:J||67:K||68:L||69:;||70:'||71:Enter   |                    |76:4||77:5||78:6||    |:
//:|________||____||____||____||____||____||____||____||____||____||____||____||___________|        ____        |____||____||____||____|:
//:|79:Shift   ||80:Z||81:X||82:C||83:V||84:B||85:N||86:M||87:,||88:.||89:/||90:Shift      |       |91  |       |92:1||93:2||94:3||    |:
//:|___________||____||____||____||____||____||____||____||____||____||____||______________|  ____ |____| ____  |____||____||____||75:E|:
//:|95:Ct||96:Op||97:C ||             98:Space                ||99:C ||100:O||101:F||102:Ct| |103 ||104 ||105 | |  106:0   ||107 ||    |:
//:|_____||_____||_____||_____________________________________||_____||_____||_____||______| |____||____||____| |__________||____||____|:
//`-------------------------------------------------------------------------------------------------------------------------------------`
// useful key indexes
enum key_indexes {
    I_INDICATOR = 0,
    I_ESC = 0,
    I_F1 = 1,
    I_F2 = 2,
    I_F3 = 3,
    I_F4 = 4,
    I_F5 = 5,
    I_F6 = 6,
    I_F7 = 7,
    I_F8 = 8,
    I_F9 = 9,
    I_F10 = 10,
    I_F11 = 11,
    I_F12 = 12,
    I_SSHOT = 13,
    I_KLOCK = 13,
    I_SIRI = 14,
    I_KTRACK = 14,
    I_RGB = 15,
    I_CIRC = 16,
    I_TRI = 17,
    I_SQR = 18,
    I_GRV = 19,
    I_EKS = 72,
    I_MREC1 = 16,
    I_MREC2 = 17,
    I_MPLY1 = 18,
    I_N1 = 20,
    I_N4 = 23,
    I_MPLY2 = 72,
    I_LLOCK = 33,
    I_INS = 33,
    I_HOME = 34,
    I_FJLIGHT = 34,
    I_BBRTEXT = 34,
    I_PGUP = 35,
    I_STHRU = 35,
    I_NUMLOCK = 36,
    I_TAB = 39,
    I_Q = 40,
    I_W = 41,
    I_E = 42,
    I_R = 43,
    I_T = 44,
    I_Y = 45,
    I_U = 46,
    I_I = 47,
    I_O = 48,
    I_P = 49,
    I_HROWLIGHT = 54,
    I_END = 54,
    I_BARTEXT = 54,
    I_PGDN = 55,
    I_UNDERLN = 55,
    I_CAPS = 59,
    I_A = 60,
    I_S = 61,
    I_D = 62,
    I_F = 63,
    I_G = 64,
    I_H = 65,
    I_J = 66,
    I_K = 67,
    I_L = 68,
    I_SEMI = 69,
    I_APOS = 70,
    I_ENT = 71,
    I_PMINS = 73,
    I_LSFT = 79,
    I_N = 85,
    I_M = 86,
    I_RSFT = 90,
    I_LCTL = 95,
    I_LALT = 96,
    I_LOPT = 96,
    I_LGUI = 97,
    I_LCMD = 97,
    I_SPACE = 98,
    I_RGUI = 99,
    I_RCMD = 99,
    I_RALT = 100,
    I_ROPT = 100,
    I_FN = 101,
    I_RCTL = 102,
};

// led indexes for keys that get capitalized when caps lock is on
bool is_capslock_shifted(uint8_t i) {
    if ((i > 39 && i < 50) || (i > 59 && i < 69) || (i > 79 && i < 87)) {
        return true;
    }
    return false;
}
// led indexes for keys that get shifted when caps word is on
bool is_capsword_shifted(uint8_t i) {
    if (i == 30 || is_capslock_shifted(i)) {
        return true;
    }
    return false;
}

// for tracking whether to highlight home row keys f and j
bool fj_light;
// and for tracking if the full home row light is on
bool hrow_light;
// for disabling the keytracker, which will also disable key-reactive fade
bool enable_keytracker = true;

// for tracking whether to blink an led as an indicator
bool is_led_on;
static uint16_t layer_timer;

// for storing the last rgb_mode to return to after returning from LOCK_LAYER
uint8_t saved_rgb_mode;

// for tracking cmd-tab app switching
bool is_cmd_tab_active;
bool is_cmd_shift_tab_active;
bool app_switch_active(void); 

// for tracking a recording macro
int8_t macro_direction;
bool macro_recording;
bool is_macro_led_on;
static uint16_t macro_timer;
// and a delayed callback after playing a macro from osl
static deferred_token osl_macro_token = INVALID_DEFERRED_TOKEN;

// for tracking key lock blinking
bool is_key_lock_led_on;
static uint16_t key_lock_timer;

// for tracking if leader sequence is started
bool is_in_leader_sequence;
bool is_leader_led_on;
static uint16_t leader_timer;
bool is_leader_error;
bool is_leader_error_led_on;
static uint16_t leader_error_timer;

// for tracking if oneshot layer is active
bool oneshot_layer_active;

// if rgb color-test is requested, set this bool
bool color_test;
// and use a timer so that it can be turned off after a delay even if no further key is pressed
static uint16_t color_test_timer;

// this was originally a static declaration in the switch case for MK_HOLD, but I also want to use it outside of
// that switch case to do rgb change, so am moving it here.
bool ms_btn_held = false;
bool is_lopt_held = false;

// for tracking wide-text options for the WIDE_TEXT_LAYR
enum {
    WIDE_STANDARD,
    WIDE_STHRU,
    WIDE_UNDERLN,
    WIDE_BARTEXT,
    WIDE_BBRTEXT
};
uint8_t wide_text_mode = WIDE_STANDARD;
bool wide_firstchar = false;

// tap dance setup
typedef struct {
    bool is_press_action;
    int state;
} tap;
// tap dance states
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    TRIPLE_TAP = 4,
    QUAD_TAP = 5,
    PENT_TAP = 6
};
// functions associated with all tap dances
int cur_dance (tap_dance_state_t *state);
// functions associated with individual tap dances
void caps_finished (tap_dance_state_t *state, void *user_data);
void caps_reset (tap_dance_state_t *state, void *user_data);
void fn_finished (tap_dance_state_t *state, void *user_data);
void fn_reset (tap_dance_state_t *state, void *user_data);
void ropt_finished (tap_dance_state_t *state, void *user_data);
void ropt_reset (tap_dance_state_t *state, void *user_data);
void rctl_finished (tap_dance_state_t *state, void *user_data);
void rctl_reset (tap_dance_state_t *state, void *user_data);
void rsft_finished (tap_dance_state_t *state, void *user_data);
void rsft_reset (tap_dance_state_t *state, void *user_data);
void macl_finished (tap_dance_state_t *state, void *user_data);
void macl_reset (tap_dance_state_t *state, void *user_data);
void kbunlock_finished (tap_dance_state_t *state, void *user_data);
void kbunlock_reset (tap_dance_state_t *state, void *user_data);

// key tracker
typedef struct {
    uint8_t index;
    bool press;
    int fade;
} keytracker;

// setup keytracker
static deferred_token key_token = INVALID_DEFERRED_TOKEN;
static keytracker tracked_keys[20]; 
static int tk_length = sizeof(tracked_keys) / sizeof(tracked_keys[0]);

// function for determining if a key should fade
bool key_should_fade(keytracker key, uint8_t layer);

// funciton to send an alternate key if a modifier is being held
void dual_key(uint16_t std_keycode, uint16_t alt_keycode, uint8_t mod_mask);

// function to send symbols normally requiring unicode input in macos
void symbol_key_mac(const char *unicode, const char *shift_unicode);

// funciton to send emoji
void send_emoji(const char *emoji_code, const char *alt_emoji_code);

// setup mouse jiggler
static deferred_token jiggler_token = INVALID_DEFERRED_TOKEN;
static report_mouse_t jiggler_report = {0};

// setup cmd-tab app switching 
static deferred_token cmd_tab_token = INVALID_DEFERRED_TOKEN;
uint32_t cmd_tab_callback(uint32_t trigger_time, void* cb_arg) {
    unregister_code(KC_LCMD);
    unregister_code(KC_LSFT);
    is_cmd_tab_active = false;
    is_cmd_shift_tab_active = false;
    return 0;
}
bool app_switch_active(void) {
    return is_cmd_tab_active || is_cmd_shift_tab_active;
}
// setup leader sequence error blinking callback 
static deferred_token leader_error_token = INVALID_DEFERRED_TOKEN;
uint32_t leader_error_callback(uint32_t trigger_time, void* cb_arg) {
    is_leader_error = false;
    is_leader_error_led_on = false;
    return 0;
}

// callback for when a mcaro on osl is run (to turn off the layer) 
uint32_t osl_macro_callback(uint32_t trigger_time, void *cb_arg) {
    layer_off(FN_LAYER);
    return 0;
}

// setup this token to be used to create a delay from when wireless mode is changed until when key fade turns back on
// to see the wireless status indicator
static deferred_token wireless_mode_token = INVALID_DEFERRED_TOKEN;
uint32_t wireless_mode_callback(uint32_t trigger_time, void *cb_arg) {
    enable_keytracker = true;
    return 0;
}

// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;
    // stop color test if active and a key is pressed
    if (color_test && record->event.pressed) {
        color_test = false;
        return false;
    }

    // stop mouse jiggler
    if (jiggler_token && record->event.pressed) {
	// If jiggler is currently running, stop when any key is pressed.
        cancel_deferred_exec(jiggler_token);
        jiggler_token = INVALID_DEFERRED_TOKEN;
        jiggler_report = (report_mouse_t){};  // Clear the mouse.
        host_mouse_send(&jiggler_report);
    }
    // record key index pressed for rgb reactive changes
    if (enable_keytracker && !is_macro_playing && keycode != QK_LEAD) {
        int key_idx = g_led_config.matrix_co[record->event.key.row][record->event.key.col];
        if (record->event.pressed) {
            dprintf("%u \n", key_idx); // added to figure out where the leds are on q6 max
       	    for (int i = tk_length - 1; i > 0; i--) {
                tracked_keys[i] = tracked_keys[i-1];
                if (tracked_keys[i].index == key_idx) {
	            tracked_keys[i].press = true;
	            tracked_keys[i].fade = 255;
	        }
       	    }
       	    tracked_keys[0].press = true;
       	    tracked_keys[0].fade = 255;
       	    tracked_keys[0].index = key_idx; 
        }
        else {
       	    for (int i = 0; i < tk_length; i++) {
                if (tracked_keys[i].index == key_idx) { 
 	            tracked_keys[i].press = false;
	            tracked_keys[i].fade = 250;
                }
       	    }
            // setup the key fade
            if (key_token) {
                cancel_deferred_exec(key_token);
                key_token = INVALID_DEFERRED_TOKEN;
            }
            uint32_t keytracker_callback(uint32_t trigger_time, void* cb_arg) {
                bool fade_changed = false;
                for (int i = 0; i < tk_length; i++) {
                    if (!tracked_keys[i].press && tracked_keys[i].fade > 0) {
                        tracked_keys[i].fade--; 
		        fade_changed = true;
               	    }
                }
                if (fade_changed) {
                    return 15;  // Call the callback every 15 ms.
                }
                else {
                    return 0;
                }
       	    }
       	    key_token = defer_exec(16, keytracker_callback, NULL);  // Schedule callback.
        }
    }

    // keychron common
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }

    // layer lock
    if (!process_layer_lock(keycode, record, LLOCK)) {
       return false;
    }

    switch (keycode) {
    // this is a custom version of KC_TRANS to press a key on default layer
    // setup so that I can use LTRANS in the keymap to denote which fallthrough keys get lit up on the layer
    case LTRANS:
        if (record->event.pressed) {
            uint8_t layer = get_highest_layer(layer_state);
            const uint8_t mods = get_mods();
            // prefix to send for the TMUX_LAYR
            // standard KC_TRANS keycodes will not get this prefix which is good for
            // stuff like shift and alt and control
            if (layer == TMUX_LAYER) {
                unregister_mods(mods); // temp remove mods
                tap_code16(C(KC_B));   // send ctrl-b before keycode processing
                register_mods(mods);   // reapply mods
            }
            // for some wide modes, should start with the spacing char
            if (layer == WIDE_TEXT_LAYR && wide_firstchar) {
                unregister_mods(mods); // temp remove mods
                switch (wide_text_mode) {
                case WIDE_STHRU:
                    tap_code16(KC_MINS);
                    break;
                case WIDE_UNDERLN:
                    tap_code16(KC_UNDS);
                    break;
                case WIDE_BARTEXT:
                    tap_code16(KC_PIPE);
                    break;
                case WIDE_BBRTEXT:
                    symbol_key_mac("00a6","");
                    break;
                default:
                    break;
                }
                register_mods(mods);   // reapply mods
                wide_firstchar = false;
            }
            // send keydown from the default layer
            register_code(keymap_key_to_keycode(biton32(default_layer_state), record->event.key));
            // if WIDE_TEXT_LAYER, add the extra spacing char
            if (layer == WIDE_TEXT_LAYR) {
                unregister_mods(mods); // temp remove mods
                switch (wide_text_mode) {
                case WIDE_STHRU:
                    tap_code16(KC_MINS);
                    break;
                case WIDE_UNDERLN:
                    tap_code16(KC_UNDS);
                    break;
                case WIDE_BARTEXT:
                    tap_code16(KC_PIPE);
                    break;
                case WIDE_BBRTEXT:
                    symbol_key_mac("00a6","");
                    break;
                default:
                    tap_code16(KC_SPC);
                    break;
                }
                register_mods(mods);   // reapply mods
            }
        }
        else {
            unregister_code(keymap_key_to_keycode(biton32(default_layer_state), record->event.key));
        }
        return false;
        break;
    // tmux bound key list
    case TMUXLKEY:
        if (record->event.pressed) {
           send_string(SS_LCTL("b") "?");
        }
        break;
    // tmux command list
    case TMUXLCMD:
        if (record->event.pressed) {
           send_string_with_delay(SS_LCTL("b") ":",25);
           send_string("list-commands\n");
        }
        break;
    // tmux monitor window activity on
    case TMONON:
        if (record->event.pressed) {
           send_string_with_delay(SS_LCTL("b") ":",25);
           send_string("setw monitor-activity on\n");
        }
        break;
    // tmux monitor window activity off
    case TMONOF:
        if (record->event.pressed) {
           send_string_with_delay(SS_LCTL("b") ":",25);
           send_string("setw monitor-activity off\n");
        }
        break;
    // tmux visual activity alerts on
    case TVISON:
        if (record->event.pressed) {
           send_string_with_delay(SS_LCTL("b") ":",25);
           send_string("setw -g visual-activity on\n");
        }
        break;
    // tmux visual activity alerts off
    case TVISOF:
        if (record->event.pressed) {
           send_string_with_delay(SS_LCTL("b") ":",25);
           send_string("setw -g visual-activity off\n");
        }
        break;
    // tmux move window left 1 position
    case TWINLFT:
        if (record->event.pressed) {
           send_string_with_delay(SS_LCTL("b") ":",25);
           send_string("swap-window -t -1\n");
           send_string_with_delay(SS_LCTL("b") "p",10);
        }
        break;
    // tmux move window right 1 position
    case TWINRGT:
        if (record->event.pressed) {
           send_string_with_delay(SS_LCTL("b") ":",25);
           send_string("swap-window -t +1\n");
           send_string_with_delay(SS_LCTL("b") "n",10);
        }
        break;
    case TJPANE:
        if (record->event.pressed) {
           send_string_with_delay(SS_LCTL("b") ":",25);
           send_string("join-pane -t ");
        }
        break;
    // tmux encoder control
    // set this up to do resize l/r or u/d if control is held
    // on mac, control arrow conflicts with mission control, so using alt resizing instead
    case ENC_TSIZEL:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            if (mods & MOD_MASK_CTRL) {
                unregister_mods(MOD_MASK_CTRL);                                      // remove control
                if (mods & MOD_MASK_SHIFT) {
                    unregister_mods(MOD_MASK_SHIFT);                                 // remove shift
                    send_string_with_delay(SS_LCTL("b") ":", 25);                    // prefix with delay 
                    send_string("resize-pane -U 1\n");                               // size up by 1
                }
                else {
                    send_string_with_delay(SS_LCTL("b") SS_LALT(SS_TAP(X_UP)),10);   // size up
                }
                register_mods(mods);                                                 // add back mods
            }
            else {
                if (mods & MOD_MASK_SHIFT) {
                    unregister_mods(MOD_MASK_SHIFT);                                 // remove shift
                    send_string_with_delay(SS_LCTL("b") ":", 25);                    // prefix with delay
                    send_string("resize-pane -L 1\n");                               // size left by 1
                    register_mods(mods);                                             // add back mods
                }
                else {
                    send_string_with_delay(SS_LCTL("b") SS_LALT(SS_TAP(X_LEFT)),10); // size left
                }
            }
        }
        break;
    case ENC_TSIZER:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            if (mods & MOD_MASK_CTRL) {
                unregister_mods(MOD_MASK_CTRL);                                       // remove control
                if (mods & MOD_MASK_SHIFT) {
                    unregister_mods(MOD_MASK_SHIFT);                                  // remove shift
                    send_string_with_delay(SS_LCTL("b") ":", 25);                     // prefix with delay
                    send_string("resize-pane -D 1\n");                                // size down by 1
                }
                else {  
                    send_string_with_delay(SS_LCTL("b") SS_LALT(SS_TAP(X_DOWN)),10);  // size down
                }
                register_mods(mods);                                                  // add back mods
            }
            else {
                if (mods & MOD_MASK_SHIFT) {
                    unregister_mods(MOD_MASK_SHIFT);                                  // remove shift
                    send_string_with_delay(SS_LCTL("b") ":", 25);                     // prefix with delay
                    send_string("resize-pane -R 1\n");                                // size right by 1
                    register_mods(mods);                                              // add back mods
                }
                else {
                    send_string_with_delay(SS_LCTL("b") SS_LALT(SS_TAP(X_RIGHT)),10); // size right
                }
            }
        }
        break;
    // when encoder is pushed, either enable or disable window activity monitor
    case ENC_TMON:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            if (mods & MOD_MASK_CTRL) {
                unregister_mods(MOD_MASK_CTRL);             // remove control
                // turn on window actiivty monitor
                send_string_with_delay(SS_LCTL("b") ":",25);
                send_string("setw monitor-activity on\n");
                register_mods(mods);                        // add back mods
            }
            else {
                // turn off window actiivty monitor
                send_string_with_delay(SS_LCTL("b") ":",25);
                send_string("setw monitor-activity off\n");
            }
        }
        break;
    case AP_GLOB:
        // setup for apple globe key to work
        host_consumer_send(record->event.pressed ? AC_NEXT_KEYBOARD_LAYOUT_SELECT : 0);
        break;
    case CALCPRO:
    	if (record->event.pressed) {
	   // send command + control + * then delay and then h
    	   send_string(SS_LCTL(SS_LCMD(SS_TAP(X_PAST))) SS_DELAY(20) "h");
	}
    	break;
    case LOCKSCR:
    	if (record->event.pressed) {
    	   // send control + command + q
    	   send_string(SS_LCTL(SS_LCMD("q")) SS_DELAY(300) SS_LCTL(SS_LCMD("q")));
    	}
    	break;
    case BACKDIR:
	if (record->event.pressed) {
	  // command to go back a dir in terminal
	  send_string("cd .." SS_TAP(X_ENT));
	}
	break;
    case HOMEDIR:
	if (record->event.pressed) {
	  // command to go home in terminal
	  send_string("cd ~" SS_TAP(X_ENT));
	}
	break;
    case LSLTRAH:
	if (record->event.pressed) {
	  // command to ls -ltrah in terminal
	  send_string("ls -ltrah" SS_TAP(X_ENT));
	}
	break;
    case FNLAYER: // this prevents keyboard reset without first switching the hardware switch to WIN_BASE
    	if (record->event.pressed) {
    	   layer_on(FN_LAYER); 
	}
        else if (!is_layer_locked(FN_LAYER)) {
           layer_off(FN_LAYER);
        }
    	break;
    case SFTLAYER: // this prevents keyboard reset without first switching the hardware switch to WIN_BASE
    	if (record->event.pressed) {
    	   layer_on(SFT_LAYER); 
	}
        else if (!is_layer_locked(SFT_LAYER)) {
           layer_off(SFT_LAYER);
        }
    	break;
    case FJLIGHT:
    	if (record->event.pressed) {
	   // update the var used for f and j home key highlighting 
	   fj_light = !fj_light;
	}
    	break;
    case HROWLIGHT:
    	if (record->event.pressed) {
	   // update the var used for full home row keys highlighting 
	   hrow_light = !hrow_light;
	}
    	break;
    case KTRACK:
        if (record->event.pressed) {
           // update the var used to enable/disable keytracker and per-key fade
           enable_keytracker = !enable_keytracker;
        }
        break;
    case WAVE:  // Types ~=~=~=~=~=~ or <~>~<~>~<~>~<~>
        static deferred_token wave_token = INVALID_DEFERRED_TOKEN;
        static uint8_t wave_phase = 0;
        if (!record->event.pressed) {  // On release.
            const uint8_t mods = get_mods();
            cancel_deferred_exec(wave_token);
            wave_token = INVALID_DEFERRED_TOKEN;
            // Ensure the pattern always ends on a ">".
            if (mods & MOD_MASK_GUI) {  // Is cmd held?
                unregister_mods(MOD_MASK_GUI); // temp remove cmd 
                if ((wave_phase & 1) == 0) { 
                    send_string("<~>"); 
                }
                else {
                    tap_code16(KC_RABK);
                }
                register_mods(mods);           // Restore mods.
            }
            else {
                if ((wave_phase & 1) == 0) { tap_code16(KC_TILD); }
            } 
            wave_phase = 0;
        } 
        else if (!wave_token) {  // On press.
            uint32_t wave_callback(uint32_t trigger_time, void* cb_arg) {
                const uint8_t mods = get_mods();
                const uint8_t oneshot_mods = get_oneshot_mods();
                if ((mods | oneshot_mods) & MOD_MASK_GUI) {  // Is cmd held?
                    del_oneshot_mods(MOD_MASK_GUI); // remove cmd
                    unregister_mods(MOD_MASK_GUI);  // remove cmd
                    tap_code16((++wave_phase & 1) ? KC_LABK : KC_RABK);
                    tap_code16(KC_TILD);
                    register_mods(mods);            // Restore mods.
                }
                else {
                    tap_code16((++wave_phase & 1) ? KC_TILD : KC_EQL);
                }
                return 16;  // Call the callback every 16 ms.
            }
            wave_token = defer_exec(1, wave_callback, NULL);
        }
	break;    
    case ARROW:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_GUI) {  // Is cmd held?
                // Temporarily delete cmd.
                del_oneshot_mods(MOD_MASK_GUI);
                unregister_mods(MOD_MASK_GUI);  
                SEND_STRING("=>");
                register_mods(mods);            // Restore mods.
            } else {
                SEND_STRING("->");
            }
        }
    	break;
    case BSPCFAST:  // Backspace with exponential repeating.
        // Initial delay before the first repeat.
        static const uint8_t INIT_DELAY_MS = 250;
        // This array customizes the rate at which the Backspace key
        // repeats. The delay after the ith repeat is REP_DELAY_MS[i].
        // Values must be between 1 and 255.
        static const uint8_t REP_DELAY_MS[] PROGMEM = {
            99, 79, 65, 57, 49, 43, 40, 35, 33, 30, 28, 26, 25, 23, 22, 20,
            20, 19, 18, 17, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10};
        static deferred_token bspc_token = INVALID_DEFERRED_TOKEN;
        static uint8_t rep_count = 0;
        if (!record->event.pressed) {  // Backspace released: stop repeating.
            cancel_deferred_exec(bspc_token);
            bspc_token = INVALID_DEFERRED_TOKEN;
        } 
        else if (!bspc_token) {  // Backspace pressed: start repeating.
            tap_code(KC_BSPC);  // Initial tap of Backspace key.
            rep_count = 0;
            uint32_t bspc_callback(uint32_t trigger_time, void* cb_arg) {
              tap_code(KC_BSPC);
              if (rep_count < sizeof(REP_DELAY_MS)) { ++rep_count; }
              return pgm_read_byte(REP_DELAY_MS - 1 + rep_count); 
            }
            bspc_token = defer_exec(INIT_DELAY_MS, bspc_callback, NULL); 
        }
        break;
    // this allows a running macro to be stopped using the macro key 
    case DUAL_F13:
    	if (record->event.pressed) {
           if (!macro_recording) {
    	       // send F13 
    	       tap_code(KC_F13);
           }
           else {
               // if macro is recording, stop it
               dynamic_macro_stop_recording();
           }
    	}
    	break;
    case DUAL_F14:
    	if (record->event.pressed) {
           if (!macro_recording) {
    	       // send F14 
    	       tap_code(KC_F14);
           }
           else {
               // if macro is recording, stop it
               dynamic_macro_stop_recording();
           }
    	}
    	break;
    // this is setup so I can use numpad - to insert a delay while recording a macro
    case DUAL_PMNS:
    	if (record->event.pressed) {
           if (!macro_recording && !is_macro_playing) {
    	       // send PMNS 
    	       register_code(KC_PMNS);
           }
           else {
               // if macro is recording or playing, insert a delay 
               // wait_ms(150); // this only works when wired
    	       send_string(SS_DELAY(150)); // this works wired and wireless
           }
    	}
	else {
           if (!macro_recording && !is_macro_playing) {
               unregister_code(KC_PMNS);
	   }
        }  
    	break;
    case E_SMILE:
    	if (record->event.pressed) {
            //send_emoji("d83dde00","d83dde0e");
            send_emoji("d83dde00","d83dde06");
    	}
    	break;
    case E_SMIRK:
    	if (record->event.pressed) {
            send_emoji("d83dde0f","d83dde09");
    	}
    	break;
    case E_ASTON:
    	if (record->event.pressed) {
            send_emoji("d83dde32","d83dde27");
    	}
    	break;
    case E_SAD:
    	if (record->event.pressed) {
            send_emoji("d83dde1f","d83dde1e");
    	}
    	break;
    case E_CAR:
    	if (record->event.pressed) {
            send_emoji("d83dde99","d83ddea2");
    	}
    	break;
    case E_BUS:
    	if (record->event.pressed) {
            send_emoji("d83dde8e","d83ddee9");
    	}
    	break;
    case E_TRAIN:
    	if (record->event.pressed) {
            send_emoji("d83dde8a","d83ddeb2");
    	}
    	break;
    case E_TAXI:
    	if (record->event.pressed) {
            send_emoji("d83dde95","d83ddef4");
    	}
    	break;
    case E_FLAGUS:
    	if (record->event.pressed) {
            send_emoji("d83cddfad83cddf8","d83cddeed83cddf9");
    	}
    	break;
    case E_FLAGPI:
    	if (record->event.pressed) {
            send_emoji("d83cddf5d83cdded","d83cdde8d83cddf3");
    	}
    	break;
    case E_GLOBE:
    	if (record->event.pressed) {
            send_emoji("d83cdf0e","d83cdf10");
    	}
    	break;
    case E_PIZZA:
    	if (record->event.pressed) {
            send_emoji("d83cdf55","d83cdf69");
    	}
    	break;
    case E_BURGER:
    	if (record->event.pressed) {
            send_emoji("d83cdf54","d83cdf5f");
    	}
    	break;
    case E_CHICKEN:
    	if (record->event.pressed) {
            send_emoji("d83cdf57","d83cdf2d");
    	}
    	break;
    case E_TACO:
    	if (record->event.pressed) {
            send_emoji("d83cdf2e","d83cdf66");
    	}
    	break;
    case E_SNAIL:
    	if (record->event.pressed) {
            send_emoji("d83ddc0c","26a1");
    	}
    	break;
    case E_NINJA:
    	if (record->event.pressed) {
            send_emoji("d83edd77","d83ddc88");
    	}
    	break;
    case E_STOP:
    	if (record->event.pressed) {
            send_emoji("d83dded1","270a");
    	}
    	break;
    case E_HAND:
    	if (record->event.pressed) {
            send_emoji("d83ddd90","270c");
    	}
    	break;
    case E_SHH:
    	if (record->event.pressed) {
            send_emoji("d83edd2b","d83dde34");
    	}
    	break;
    case E_PACKAGE:
    	if (record->event.pressed) {
            send_emoji("d83ddce6","d83ddcec");
    	}
    	break;
    case E_POINTU:
    	if (record->event.pressed) {
            send_emoji("d83ddc46","2b06fe0f");
    	}
    	break;
    case E_POINTD:
    	if (record->event.pressed) {
            send_emoji("d83ddc47","2b07fe0f");
    	}
    	break;
    case E_POINTL:
    	if (record->event.pressed) {
            send_emoji("d83ddc48","2b05fe0f");
    	}
    	break;
    case E_POINTR:
    	if (record->event.pressed) {
            send_emoji("d83ddc49","27a1fe0f");
    	}
    	break;
    case E_DRINK:
    	if (record->event.pressed) {
            send_emoji("2615","d83cdf7a");
    	}
    	break;
    case E_CMARK:
    	if (record->event.pressed) {
            send_emoji("2705","2714");
    	}
    	break;
    case E_EMARK:
    	if (record->event.pressed) {
            send_emoji("2757","2755");
    	}
    	break;
    case E_QMARK:
    	if (record->event.pressed) {
            send_emoji("2753","2754");
    	}
    	break;
    case E_BULB:
    	if (record->event.pressed) {
            send_emoji("d83ddca1","d83edeab");
    	}
    	break;
    case E_SSHOT:
    	if (record->event.pressed) {
            send_emoji("d83dddbc","d83ddcf8");
    	}
    	break;
    case E_MIC:
    	if (record->event.pressed) {
            send_emoji("d83cdf99","d83cdfa4");
    	}
    	break;
    case E_TRASH:
    	if (record->event.pressed) {
            send_emoji("d83dddd1","267bfe0f");
    	}
    	break;
    case E_I:
    	if (record->event.pressed) {
            send_emoji("2139fe0f","2139");
    	}
    	break;
    case E_K0:
    	if (record->event.pressed) {
            send_emoji("0030fe0f20e3","D83DDD59");
    	}
    	break;
    case E_K1:
    	if (record->event.pressed) {
            send_emoji("0031fe0f20e3","D83DDD50");
    	}
    	break;
    case E_K2:
    	if (record->event.pressed) {
            send_emoji("0032FE0F20E3","D83DDD51");
    	}
    	break;
    case E_K3:
    	if (record->event.pressed) {
            send_emoji("0033FE0F20E3","D83DDD52");
    	}
    	break;
    case E_K4:
    	if (record->event.pressed) {
            send_emoji("0034FE0F20E3","D83DDD53");
    	}
    	break;
    case E_K5:
    	if (record->event.pressed) {
            send_emoji("0035FE0F20E3","D83DDD54");
    	}
    	break;
    case E_K6:
    	if (record->event.pressed) {
            send_emoji("0036FE0F20E3","D83DDD55");
    	}
    	break;
    case E_K7:
    	if (record->event.pressed) {
            send_emoji("0037FE0F20E3","D83DDD56");
    	}
    	break;
    case E_K8:
    	if (record->event.pressed) {
            send_emoji("0038FE0F20E3","D83DDD57");
    	}
    	break;
    case E_K9:
    	if (record->event.pressed) {
            send_emoji("0039FE0F20E3","D83DDD58");
    	}
    	break;
    case E_STAR:
    	if (record->event.pressed) {
            send_emoji("002AFE0F20E3","2731");
    	}
    	break;
    case E_HASH:
    	if (record->event.pressed) {
            send_emoji("0023FE0F20E3","d83ddcf1");
    	}
    	break;
    case E_MINS:
    	if (record->event.pressed) {
            send_emoji("2796","D83DDD5A");
    	}
    	break;
    case E_PLUS:
    	if (record->event.pressed) {
            send_emoji("2795","D83DDD5B");
    	}
    	break;
    case E_DIV:
    	if (record->event.pressed) {
            send_emoji("2797","2716FE0F");
    	}
    	break;
    case E_GRIM:
    	if (record->event.pressed) {
            send_emoji("d83dde2c","d83dde16");
    	}
    	break;
    case E_KB:
    	if (record->event.pressed) {
            send_emoji("2328FE0F","D83DDDA5FE0F");
    	}
    	break;
    case E_OK:
    	if (record->event.pressed) {
            send_emoji("d83ddc4c","d83ddc4d");
    	}
    	break;
    case E_SGLASS:
    	if (record->event.pressed) {
            send_emoji("d83dde0e","D83DDD76FE0F");
    	}
    	break;
    case E_BOTTLE:
    	if (record->event.pressed) {
            send_emoji("d83cdf7c","d83cdf7e");
    	}
    	break;
    case SUITH:
        if (record->event.pressed) {
            symbol_key_mac("2665","2661");
        }
        break;
    case SUITD:
        if (record->event.pressed) {
            symbol_key_mac("2666","2662");
        }
        break;
    case SUITC:
        if (record->event.pressed) {
            symbol_key_mac("2663","2667");
        }
        break;
    case SUITS:
        if (record->event.pressed) {
            symbol_key_mac("2660","2664");
        }
        break;
    case SUP1:
        if (record->event.pressed) {
            symbol_key_mac("00b9","2074");
        }
        break;
    case SUP2:
        if (record->event.pressed) {
            symbol_key_mac("00b2","2075");
        }
        break;
    case SUP3:
        if (record->event.pressed) {
            symbol_key_mac("00b3","2076");
        }
        break;
    case NBSP:
        if (record->event.pressed) {
            symbol_key_mac("00a0","00a6");
        }
        break;
    case CIRCL1:
        if (record->event.pressed) {
            // check mods first so can do a double-cirled number if alt is held
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                symbol_key_mac("24f5","24f5");
                register_mods(mods);
            } else {
                symbol_key_mac("2460","246a");
            }
        }
        break;
    case CIRCL2:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                symbol_key_mac("24f6","24f6");
                register_mods(mods);
            } else {
                symbol_key_mac("2461","246b");
            }
        }
        break;
    case CIRCL3:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                symbol_key_mac("24f7","24f7");
                register_mods(mods);
            } else {
                symbol_key_mac("2462","246c");
            }
        }
        break;
    case CIRCL4:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                symbol_key_mac("24f8","24f8");
                register_mods(mods);
            } else {
                symbol_key_mac("2463","246d");
            }
        }
        break;
    case CIRCL5:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                symbol_key_mac("24f9","24f9");
                register_mods(mods);
            } else {
                symbol_key_mac("2464","246e");
            }
        }
        break;
    case CIRCL6:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                symbol_key_mac("24fa","24fa");
                register_mods(mods);
            } else {
                symbol_key_mac("2465","246f");
            }
        }
        break;
    case CIRCL7:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                symbol_key_mac("24fb","24fb");
                register_mods(mods);
            } else {
                symbol_key_mac("2466","2470");
            }
        }
        break;
    case CIRCL8:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                symbol_key_mac("24fc","24fc");
                register_mods(mods);
            } else {
                symbol_key_mac("2467","2471");
            }
        }
        break;
    case CIRCL9:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                symbol_key_mac("24fd","24fd");
                register_mods(mods);
            } else {
                symbol_key_mac("2468","2472");
            }
        }
        break;
    case CIRCL0:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                symbol_key_mac("24fe","2473");
                register_mods(mods);
            } else {
                symbol_key_mac("24ea","2469");
            }
        }
        break;
    case CIRCLQ:
        if (record->event.pressed) {
            symbol_key_mac("24e0","24c6");
        }
        break;
    case CIRCLW:
        if (record->event.pressed) {
            symbol_key_mac("24e6","24cc");
        }
        break;
    case CIRCLE:
        if (record->event.pressed) {
            symbol_key_mac("24d4","24ba");
        }
        break;
    case CIRCLR:
        if (record->event.pressed) {
            symbol_key_mac("24e1","24c7");
        }
        break;
    case CIRCLT:
        if (record->event.pressed) {
            symbol_key_mac("24e3","24c9");
        }
        break;
    case CIRCLY:
        if (record->event.pressed) {
            symbol_key_mac("24e8","24ce");
        }
        break;
    case CIRCLU:
        if (record->event.pressed) {
            symbol_key_mac("24e4","24ca");
        }
        break;
    case CIRCLI:
        if (record->event.pressed) {
            symbol_key_mac("24d8","24be");
        }
        break;
    case CIRCLO:
        if (record->event.pressed) {
            symbol_key_mac("24de","24c4");
        }
        break;
    case CIRCLP:
        if (record->event.pressed) {
            symbol_key_mac("24df","24c5");
        }
        break;
    case CIRCLA:
        if (record->event.pressed) {
            symbol_key_mac("24d0","24b6");
        }
        break;
    case CIRCLS:
        if (record->event.pressed) {
            symbol_key_mac("24e2","24c8");
        }
        break;
    case CIRCLD:
        if (record->event.pressed) {
            symbol_key_mac("24d3","24b9");
        }
        break;
    case CIRCLF:
        if (record->event.pressed) {
            symbol_key_mac("24d5","24bb");
        }
        break;
    case CIRCLG:
        if (record->event.pressed) {
            symbol_key_mac("24d6","24bc");
        }
        break;
    case CIRCLH:
        if (record->event.pressed) {
            symbol_key_mac("24d7","24bd");
        }
        break;
    case CIRCLJ:
        if (record->event.pressed) {
            symbol_key_mac("24d9","24bf");
        }
        break;
    case CIRCLK:
        if (record->event.pressed) {
            symbol_key_mac("24da","24c0");
        }
        break;
    case CIRCLL:
        if (record->event.pressed) {
            symbol_key_mac("24db","24c1");
        }
        break;
    case CIRCLZ:
        if (record->event.pressed) {
            symbol_key_mac("24e9","24cf");
        }
        break;
    case CIRCLX:
        if (record->event.pressed) {
            symbol_key_mac("24e7","24cd");
        }
        break;
    case CIRCLC:
        if (record->event.pressed) {
            symbol_key_mac("24d2","24b8");
        }
        break;
    case CIRCLV:
        if (record->event.pressed) {
            symbol_key_mac("24e5","24cb");
        }
        break;
    case CIRCLB:
        if (record->event.pressed) {
            symbol_key_mac("24d1","24b7");
        }
        break;
    case CIRCLN:
        if (record->event.pressed) {
            symbol_key_mac("24dd","24c3");
        }
        break;
    case CIRCLM:
        if (record->event.pressed) {
            symbol_key_mac("24dc","24c2");
        }
        break;
    case SSMENU:
    	if (record->event.pressed) {
    	   // send shift + command + 5 (for screenshot with options menus) 
    	   send_string(SS_LSFT(SS_LCMD("5")));
    	}
    	break;
    case GNEWS:
    	if (record->event.pressed) {
	   // open browser tab to google news 
    	   send_string_with_delay(SS_LCMD(SS_TAP(X_L)) SS_DELAY(150) "news.google.com" SS_DELAY(50) SS_LOPT(SS_TAP(X_ENT)),5);
	}
    	break;
    case GIT_ADD:
    	if (record->event.pressed) {
    	   // add updates to git commit 
    	   send_string("git add -A" SS_TAP(X_ENT));
    	}
    	break;
    case GIT_COMMIT:
    	if (record->event.pressed) {
    	   // commit changes 
    	   send_string("git commit -m \"\"" SS_TAP(X_LEFT));
    	}
    	break;
    case GIT_PUSH:
    	if (record->event.pressed) {
    	   // push commit to git repo 
           send_string("git push" SS_TAP(X_ENT));
    	}
    	break;
    case GIT_CHKOUT:
    	if (record->event.pressed) {
    	   // checkout last commit from git repo 
    	   send_string("git checkout ." SS_TAP(X_ENT));
    	}
    	break;
    case GIT_LOG:
    	if (record->event.pressed) {
    	   // show the git log 
    	   send_string("git log" SS_TAP(X_ENT));
    	}
    	break;
    // move mouse cursor for per-monitor mission control
    case KC_UP:
    case KC_LEFT:
    case KC_RIGHT:
    	if (record->event.pressed) {
    	   // check which control is being held and mouse mouse to monitor with CatchMouse 
           if (get_mods() == MOD_BIT(KC_LCTL)) {
               send_string(SS_LOPT(SS_LCMD(SS_LSFT(SS_TAP(X_P1)))));
           }
           else if (get_mods() == MOD_BIT(KC_RCTL)) {
               send_string(SS_LOPT(SS_LCMD(SS_LSFT(SS_TAP(X_P2)))));
           }
    	}
    	break;
    // custom keycode to move cursor to left mon with CatchMouse
    case CURSORL:
    	if (record->event.pressed) {
           send_string(SS_LCTL(SS_LOPT(SS_LCMD(SS_LSFT(SS_TAP(X_P1))))));
    	}
    	break;
    // custom keycode to move cursor to right mon with CatchMouse
    case CURSORR:
    	if (record->event.pressed) {
           send_string(SS_LCTL(SS_LOPT(SS_LCMD(SS_LSFT(SS_TAP(X_P2))))));
    	}
    	break;
    case MK_HOLD:
        if (record->event.pressed) {
            if (!ms_btn_held) {
                register_code(KC_MS_BTN1);
                ms_btn_held = true;
            }
            else {
                unregister_code(KC_MS_BTN1);
                ms_btn_held = false;
            }
        }
        break;
    case KC_MS_BTN1:
        ms_btn_held = record->event.pressed;
        break;
    case OPT_HOLD:
        if (record->event.pressed) {
            if (!is_lopt_held) {
                register_code(KC_LOPT);
                is_lopt_held = true;
            }
            else {
                unregister_code(KC_LOPT);
                is_lopt_held = false;
            }
        }
        break;
    case MK_ACCEL0:
        tap_code(record->event.pressed ? KC_MS_ACCEL0 : KC_MS_ACCEL1);
        break;
    case MK_ACCEL2:
        tap_code(record->event.pressed ? KC_MS_ACCEL2 : KC_MS_ACCEL1);
        break;
    case DUAL_ENCPUSH:
    	if (record->event.pressed) {
            // standard: mute, while command is held: play/pause
            dual_key(KC_MUTE,KC_MPLY,MOD_MASK_GUI);
        }
        break;
    case DUAL_ENCL:
    	if (record->event.pressed) {
            // standard: volume down, while command is held: keypad up 
            dual_key(KC_VOLD,KC_UP,MOD_MASK_GUI);
        }
        break;
    case DUAL_ENCR:
    	if (record->event.pressed) {
            // standard: volume up, while command is held: keypad down 
            dual_key(KC_VOLU,KC_DOWN,MOD_MASK_GUI);
        }
        break;
    case DUAL_UNIPUSH:
    	if (record->event.pressed) {
            // standard: unicode menu, while command is held: enter 
            dual_key(UNICODE,KC_ENT,MOD_MASK_GUI);
        }
        break;
    case DUAL_NAVL:
    	if (record->event.pressed) {
            // standard: key up, while command is held: keypad left 
            dual_key(KC_UP,KC_LEFT,MOD_MASK_GUI);
        }
        break;
    case DUAL_NAVR:
    	if (record->event.pressed) {
            // standard: key down, while command is held: keypad right 
            dual_key(KC_DOWN,KC_RIGHT,MOD_MASK_GUI);
        }
        break;
    case DUAL_ENCPUSH2:
    	if (record->event.pressed) {
            // standard: h (hide app windows), while cmd is held: mouse jiggler
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if (((mods | oneshot_mods) & MOD_MASK_GUI) && !app_switch_active()) {
	       uint32_t jiggler_callback(uint32_t trigger_time, void* cb_arg) {
                 // Deltas to move in a circle of radius 20 pixels over 32 frames.
                 static const int8_t deltas[32] = {
                   0, -1, -2, -2, -3, -3, -4, -4, -4, -4, -3, -3, -2, -2, -1, 0,
                   0, 1, 2, 2, 3, 3, 4, 4, 4, 4, 3, 3, 2, 2, 1, 0};
                 static uint8_t phase = 0;
                 // Get x delta from table and y delta by rotating a quarter cycle.
                 jiggler_report.x = deltas[phase];
                 jiggler_report.y = deltas[(phase + 8) & 31];
                 phase = (phase + 1) & 31;
                 host_mouse_send(&jiggler_report);
                 return 16;  // Call the callback every 16 ms.
               }
	       jiggler_token = defer_exec(1, jiggler_callback, NULL);  // Schedule callback.
	    }
            else {
	        // If token is already waiting to exec, cancel it.
                if (cmd_tab_token && app_switch_active()) {
                    cancel_deferred_exec(cmd_tab_token);
                    tap_code(KC_H);
	            cmd_tab_token = defer_exec(1000, cmd_tab_callback, NULL);  // Schedule callback.
                }
                else {   // if the button was pushed and appswitcher is not running, hide current app windows
    	            send_string(SS_LCMD(SS_TAP(X_H)));
                }
            }
        }
        break;
    case DUAL_ENCL2:
    	if (record->event.pressed) {
            // with command: app switch, standard: mouse down 
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_GUI) {
	        // If token is already waiting to exec, cancel it.
                if (cmd_tab_token) {
                    cancel_deferred_exec(cmd_tab_token);
                }
                if (!is_cmd_shift_tab_active) {
                    is_cmd_shift_tab_active = true;
                    is_cmd_tab_active = false;
                    register_code(KC_LCMD);
                    register_code(KC_LSFT);
                }
                tap_code(KC_TAB);
	        cmd_tab_token = defer_exec(1000, cmd_tab_callback, NULL);  // Schedule callback.
            }
            else {
                tap_code16(KC_MS_WH_DOWN);
            }
        }
        break;
    case DUAL_ENCR2:
    	if (record->event.pressed) {
            // with command: app switch, standard: mouse up 
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_GUI) {  // Is cmd held?
	        // If token is already waiting to exec, cancel it.
                if (cmd_tab_token) {
                    cancel_deferred_exec(cmd_tab_token);
                }
                if (!is_cmd_tab_active) {
                    is_cmd_tab_active = true;
                    is_cmd_shift_tab_active = false;
                    register_code(KC_LCMD);
                    unregister_code(KC_LSFT);
                }
                tap_code(KC_TAB);
	        cmd_tab_token = defer_exec(1000, cmd_tab_callback, NULL);  // Schedule callback.
            }
            else {
                tap_code16(KC_MS_WH_UP);
            }
        }
        break;
    case PENT_ENCPUSH:
    	if (record->event.pressed) {
            // standard: rgb toggle, if command is held: hue defualt, 
            // if opt held: sat default, if shift is held: speed defualt 
            // get current mod states
            const uint8_t mods = get_mods();
            if (mods & MOD_MASK_SHIFT) {
                rgblight_set_speed(UINT8_MAX / 2);
            }
            else if ((mods & MOD_MASK_GUI) && (mods & MOD_MASK_ALT)) {
                rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), RGB_MATRIX_MAXIMUM_BRIGHTNESS);
                rgblight_mode(RGB_MATRIX_SOLID_COLOR);
            }
            else if (mods & MOD_MASK_GUI) {
                rgblight_sethsv(170, rgblight_get_sat(), RGB_MATRIX_MAXIMUM_BRIGHTNESS);
            }
            else if (mods & MOD_MASK_ALT) {
                rgblight_sethsv(rgblight_get_hue(), 235, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
            }
            // otherwise do toggle 
            else {
                rgblight_toggle(); 
            }
        }
        break;
    // these have been further adjusted to do max brightness if anything other than brightness is
    // being adjusted.  This is good to best see the changes since the backlights are dimmed when
    // not on the base layer.
    case PENT_ENCL:
    	if (record->event.pressed) {
            // standard: bri down, if command is held: hue down, 
            // if opt is held: sat down, if shift is held: speed down
            // get current mod states
            const uint8_t mods = get_mods();
            if (mods & MOD_MASK_SHIFT) {
                rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), RGB_MATRIX_MAXIMUM_BRIGHTNESS);
                rgblight_decrease_speed();
            }
            else if ((mods & MOD_MASK_GUI) && (mods & MOD_MASK_ALT)) {
                rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), RGB_MATRIX_MAXIMUM_BRIGHTNESS);
                rgblight_step_reverse();
            }
            else if (mods & MOD_MASK_GUI) {
                rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), RGB_MATRIX_MAXIMUM_BRIGHTNESS);
                rgblight_decrease_hue();
            }
            else if (mods & MOD_MASK_ALT) {
                rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), RGB_MATRIX_MAXIMUM_BRIGHTNESS);
                rgblight_decrease_sat();
            }
            else {
                rgblight_decrease_val(); 
            }
        }
        break;
    case PENT_ENCR:
    	if (record->event.pressed) {
            // standard: bri up, while command is held: hue up, while opt is held: sat up 
            // get current mod states
            const uint8_t mods = get_mods();
            if (mods & MOD_MASK_SHIFT) {
                rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), RGB_MATRIX_MAXIMUM_BRIGHTNESS);
                rgblight_increase_speed();
            }
            else if ((mods & MOD_MASK_GUI) && (mods & MOD_MASK_ALT)) {
                rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), RGB_MATRIX_MAXIMUM_BRIGHTNESS);
                rgblight_step();
            }
            else if (mods & MOD_MASK_GUI) {
                rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), RGB_MATRIX_MAXIMUM_BRIGHTNESS);
                rgblight_increase_hue();
            }
            else if (mods & MOD_MASK_ALT) {
                rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), RGB_MATRIX_MAXIMUM_BRIGHTNESS);
                rgblight_increase_sat();
            }
            else {
                rgblight_increase_val(); 
            }
        }
        break;
    // switch rgb modes with max brightness, since the CTL_LAYER auto dims when initally switching to it
    case RGB_MOD:
    case RGB_RMOD:
    case RGB_SPD:
    case RGB_SPI:
    	if (record->event.pressed)
            rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), RGB_MATRIX_MAXIMUM_BRIGHTNESS);
        break;
    case VI_REPLACE:
    	if (record->event.pressed) {
    	   // start syntax for vi search and replace 
    	   send_string(":%s///g" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
    	}
    	break;
    // use cmd + esc as alternate leader start 
    case KC_ESC:
    	if (record->event.pressed) {
            if (get_mods() & MOD_MASK_GUI) { 
                leader_start();
                return false;
            }
    	}
    	break;
    // use cmd + screenshot as key lock start 
    case DUAL_SNAP:
    	if (record->event.pressed) {
            if (get_mods() & MOD_MASK_GUI) 
                set_key_lock_watching();
            else
                send_string(SS_LSFT(SS_LCMD(SS_TAP(X_4)))); // KC_SNAP wasn't working here
    	}
    	break;
    // attempt to get dynamic macros to work even with oneshot layers
    case DM_REC1:
    case DM_REC2:
    case DM_PLY1:
    case DM_PLY2:
        if (record->event.pressed) {
            if (oneshot_layer_active) {
                reset_oneshot_layer();
                osl_macro_token = defer_exec(100, osl_macro_callback, NULL);
            }
        }
        break;
    // functionality for opt keys with holds for OPT_LAYER and SYMB_LAYER
    case KC_LOPT:
        if (!record->event.pressed) {
            is_lopt_held = false;
        }
    // intentionally no break here
    case KC_ROPT:
        if (record->event.pressed) {
            if (get_highest_layer(layer_state) < 3) {
                layer_on(SYMB_LAYER);
            }
        }
        else {
            if (is_layer_locked(SYMB_LAYER)) {
                return false;
            }
            else {
                layer_off(SYMB_LAYER);
            }
        }
        break;
    case STHRU:
        if (record->event.pressed) {
            if (wide_text_mode == WIDE_STHRU) {
                wide_text_mode = WIDE_STANDARD;
                wide_firstchar = false;
            }
            else {
                wide_text_mode = WIDE_STHRU;
                wide_firstchar = true;
            }
        }
        break;
    case UNDERLN:
        if (record->event.pressed) {
            if (wide_text_mode == WIDE_UNDERLN) {
                wide_text_mode = WIDE_STANDARD;
                wide_firstchar = false;
            }
            else {
                wide_text_mode = WIDE_UNDERLN;
                wide_firstchar = true;
            }
        }
        break;
    case BARTEXT:
        if (record->event.pressed) {
            if (wide_text_mode == WIDE_BARTEXT) {
                wide_text_mode = WIDE_STANDARD;
                wide_firstchar = false;
            }
            else {
                wide_text_mode = WIDE_BARTEXT;
                wide_firstchar = true;
            }
        }
        break;
    case BBRTEXT:
        if (record->event.pressed) {
            if (wide_text_mode == WIDE_BBRTEXT) {
                wide_text_mode = WIDE_STANDARD;
                wide_firstchar = false;
            }
            else {
                wide_text_mode = WIDE_BBRTEXT;
                wide_firstchar = true;
            }
        }
        break;
    // for bt mode change, stop fade for a little while so can see the connection status lights
    case BT_HST1:
    case BT_HST2:
    case BT_HST3:
    case P2P4G:
        if (record->event.pressed) {
            if (wireless_mode_token) {
                cancel_deferred_exec(wireless_mode_token);
                wireless_mode_token = INVALID_DEFERRED_TOKEN;
            }
        }
        else if (enable_keytracker) {
            enable_keytracker = false;
            wireless_mode_token = defer_exec(3000, wireless_mode_callback, NULL);
        }
        break;
    // show all the named colors on different keys
    case COLORTEST:
        if (record->event.pressed) {
            color_test_timer = timer_read();
            color_test = true;
        }
        break;
    case FLASH_KB:
        if (record->event.pressed) {
           // command to flash this keyboard
           send_string("qmk flash -kb keychron/q6_max/ansi_encoder -km djcastaldo\n");
        }
        break;
    case KB_RESET:
    	if (record->event.pressed) {
	   // reset the keyboard
           eeconfig_init();
           soft_reset_keyboard();
	}
    	break;
    case BOOTLDR:
        if (record->event.pressed) {
            key_timer = timer_read32();
        } else if (timer_elapsed32(key_timer) >= 500) {
            reset_keyboard();
        }
        break;
    }
    return process_record_secrets(keycode, record);
}


void dual_key(uint16_t std_keycode, uint16_t alt_keycode, uint8_t mod_mask) {
    // if mod is being held, send mod_keycode 
    // get current mod states
    const uint8_t mods = get_mods();
    if (mods & mod_mask) {
        unregister_mods(mod_mask);  // remove mod
        tap_code16(alt_keycode);
        register_mods(mods); // restore original mods
    }
    // otherwise send std_keycode 
    else {
        tap_code16(std_keycode);
    }
}

void send_emoji(const char *emoji_code, const char *alt_emoji_code) {
    // get current mod and one-shot mod states.
    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();
    if ((mods | oneshot_mods) & MOD_MASK_GUI) { // if command is being held
        del_oneshot_mods(MOD_MASK_GUI); // temporarily delete command mod
        unregister_mods(MOD_MASK_GUI);  // temporarily delete command mod
        send_string(SS_LCTL(SS_LOPT(SS_LCMD(SS_TAP(X_SPC))))); // switch os keybaord input to unicode
	add_mods(MOD_MASK_ALT); // hold down option
	send_string(alt_emoji_code); // send alt emoji code
	del_mods(MOD_MASK_ALT); // release option
        send_string_with_delay(SS_LCTL(SS_LOPT(SS_LCMD(SS_LSFT(SS_TAP(X_SPC))))),10); // switch os keyboard input back to language
        register_mods(mods); // restore original mods
    } else {
        send_string(SS_LCTL(SS_LOPT(SS_LCMD(SS_TAP(X_SPC))))); // switch os keybaord input to unicode
	add_mods(MOD_MASK_ALT); // hold down option
	send_string(emoji_code); // send emoji code
	del_mods(MOD_MASK_ALT); // release option
        send_string_with_delay(SS_LCTL(SS_LOPT(SS_LCMD(SS_LSFT(SS_TAP(X_SPC))))),10); // switch os keyboard input back to language
    }
}

// this should replace send_emojii, but can work that out later
void symbol_key_mac(const char *unicode, const char *shift_unicode) {
    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();
    clear_mods();
    tap_code16(C(A(G(KC_SPC)))); // switch os keybaord to unicode
    add_mods(MOD_MASK_ALT);
    send_string(((mods | oneshot_mods) & MOD_MASK_SHIFT) ? shift_unicode : unicode);
    del_mods(MOD_MASK_ALT);
    tap_code16(C(A(G(KC_SPC)))); // switch back from unicode
    register_mods(mods);
}

void oneshot_layer_changed_user(uint8_t layer) {
    if (layer > 0) {
        oneshot_layer_active = true; 
    }
    if (!layer) {
        oneshot_layer_active = false;
    }
}

void leader_start_user(void) {
    is_in_leader_sequence = true;
}

void leader_end_user(void) {
    if (leader_sequence_two_keys(KC_L, KC_K)) {                // key lock watch for key to lock
        set_key_lock_watching();
    } 
    else if (leader_sequence_three_keys(KC_L, KC_L, KC_C)) {   // layer lock CTL_LAYER
        if (is_layer_locked(CTL_LAYER)) {
            layer_lock_off(CTL_LAYER);
        }
        else {
            layer_lock_on(CTL_LAYER);
        }
    }
    else if (leader_sequence_three_keys(KC_L, KC_L, KC_F)) {   // layer lock FN_LAYER
        if (is_layer_locked(FN_LAYER)) {
            layer_lock_off(FN_LAYER);
        }
        else {
            layer_lock_on(FN_LAYER);
        }
    }
    else if (leader_sequence_three_keys(KC_L, KC_L, KC_O)) {   // layer lock OPT_LAYER
        if (is_layer_locked(OPT_LAYER)) {
            layer_lock_off(OPT_LAYER);
        }
        else {
            layer_lock_on(OPT_LAYER);
        }
    }
    else if (leader_sequence_three_keys(KC_L, KC_L, KC_S)) {   // layer lock SFT_LAYER
        if (is_layer_locked(SFT_LAYER)) {
            layer_lock_off(SFT_LAYER);
        }
        else {
            layer_lock_on(SFT_LAYER);
        }
    }
    else if (leader_sequence_three_keys(KC_L, KC_L, KC_T)) {   // layer lock TMUX_LAYR
        if (is_layer_locked(TMUX_LAYER)) {
            layer_lock_off(TMUX_LAYER);
        }
        else {
            layer_lock_on(TMUX_LAYER);
        }
    }
    else if (leader_sequence_four_keys(KC_L, KC_O, KC_C, KC_K)) {   // switch to LOCK_LAYER
        // need to store current mode now, because a change to the band with no eeprom will not keep the effect
        // after wireless retuns from sleep
        saved_rgb_mode = rgb_matrix_get_mode();
        rgblight_mode(RGB_MATRIX_BAND_VAL);
        layer_on(LOCK_LAYER);
    } 
    else if (leader_sequence_five_keys(KC_C, KC_O, KC_L, KC_O, KC_R)) { // start the color test
        color_test_timer = timer_read();
        color_test = true;
    }
    else if (leader_sequence_two_keys(KC_R, KC_T)) {          // rpi temp monitor
        SEND_STRING("rpi/temperature.sh" SS_TAP(X_ENT));
    }
    else if (leader_sequence_two_keys(KC_R, KC_U)) {          // rpi uptime monitor
        SEND_STRING("rpi/uptime.sh" SS_TAP(X_ENT));
    }
    else if (leader_sequence_two_keys(KC_P, KC_R)) {          // restart pi-hole 
        SEND_STRING("sudo service pihole-FTL restart" SS_TAP(X_ENT));
    }
    else if (leader_sequence_two_keys(KC_M, KC_A)) {          // sudo mount -a
        SEND_STRING("sudo mount -a" SS_TAP(X_ENT));
    }
    else if (leader_sequence_two_keys(KC_N, KC_1)) {          // mac mini start nut upsdrvctl
        SEND_STRING("sudo /usr/local/opt/nut/sbin/upsdrvctl start" SS_TAP(X_ENT));
    }
    else if (leader_sequence_two_keys(KC_N, KC_2)) {          // mac mini start nut upsd
        SEND_STRING("sudo /usr/local/opt/nut/sbin/upsd" SS_TAP(X_ENT));
    }
    else if (leader_sequence_two_keys(KC_N, KC_R)) {          // restart nut 
        SEND_STRING("sudo service nut-server restart" SS_TAP(X_ENT));
    }
    else if (leader_sequence_two_keys(KC_W, KC_C)) {          // automator script to get word count for selected text
        SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_W))));
    }
    else if (leader_sequence_two_keys(KC_M, KC_R)) {          // numbers move cell contents right (and 0 current cell) 
        SEND_STRING(SS_LCMD(SS_TAP(X_C)) SS_TAP(X_0) SS_TAP(X_RIGHT) SS_LCMD(SS_TAP(X_V)));
    }
    else if (leader_sequence_two_keys(KC_M, KC_L)) {          // numbers move cell contents left (and 0 current cell) 
        SEND_STRING(SS_LCMD(SS_TAP(X_C)) SS_TAP(X_0) SS_TAP(X_LEFT) SS_LCMD(SS_TAP(X_V)));
    }
    else if (leader_sequence_two_keys(KC_U, KC_R)) {          // restart unifi 
        SEND_STRING("sudo service unifi restart" SS_TAP(X_ENT));
    }
    else if (leader_sequence_two_keys(KC_U, KC_U)) {          // update unifi 
        SEND_STRING("wget https://get.glennr.nl/unifi/update/unifi-update.sh && sudo bash unifi-update.sh --custom-url " SS_LCMD(SS_TAP(X_V)) SS_TAP(X_ENT));
    }
    else if (leader_sequence_two_keys(KC_V, KC_H)) {          // open hosts file in vi 
        SEND_STRING("sudo vi /etc/hosts" SS_TAP(X_ENT));
    }
    else if (leader_sequence_two_keys(KC_V, KC_A)) {          // open tb authorized in vi 
        SEND_STRING("sudo vi /sys/bus/thunderbolt/devices/0-3/authorized" SS_TAP(X_ENT));
    }
    else if (leader_sequence_two_keys(KC_S, KC_W)) {          // select word
        SEND_STRING(SS_LOPT(SS_TAP(X_LEFT) SS_LSFT(SS_TAP(X_RIGHT))));
    }
    else if (leader_sequence_two_keys(KC_S, KC_L)) {          // select line
        SEND_STRING(SS_LCTL(SS_TAP(X_A) SS_LSFT(SS_TAP(X_E) SS_TAP(X_F))));
    }
    else if (leader_sequence_two_keys(KC_T, KC_Y)) {          // thank you
        SEND_STRING("thank you");
    }
    else if (leader_sequence_two_keys(KC_N, KC_P)) {          // no problem
        SEND_STRING("no problem");
    }
    else if (leader_sequence_three_keys(KC_O, KC_M, KC_W)) {  // on my way
        SEND_STRING("on my way");
    }
    else if (leader_sequence_three_keys(KC_B, KC_R, KC_B)) {  // be right back 
        SEND_STRING("be right back");
    }
    else if (leader_sequence_three_keys(KC_H, KC_G, KC_E)) {  // have a good evening
        SEND_STRING("have a good evening");
    }
    else if (leader_sequence_three_keys(KC_H, KC_G, KC_N)) {  // have a good night
        SEND_STRING("have a good night");
    }
    else if (leader_sequence_four_keys(KC_T, KC_T, KC_Y, KC_L)) {  // talk to you later 
        SEND_STRING("talk to you later");
    }
    else if (leader_sequence_four_keys(KC_G, KC_I, KC_T, KC_L)) {        // git log
        SEND_STRING("git log\n");
    }
    else if (leader_sequence_four_keys(KC_G, KC_I, KC_T, KC_A)) {        // git add
        SEND_STRING("git add -A\n");
    }
    else if (leader_sequence_four_keys(KC_G, KC_I, KC_T, KC_C)) {        // git commit
        SEND_STRING("git commit -m \"\"" SS_TAP(X_LEFT));
    }
    else if (leader_sequence_four_keys(KC_G, KC_I, KC_T, KC_P)) {        // git push
        SEND_STRING("git push\n");
    }
    else if (leader_sequence_five_keys(KC_G, KC_I, KC_T, KC_C, KC_O)) {  // git checkout .
        SEND_STRING("git checkout .\n");
    }
    else if (leader_sequence_three_keys(KC_Q, KC_C, KC_B)) {  // qmk compile shortcutstudio bridge75 firmware
        SEND_STRING("qmk compile -kb shortcut/bridge75 -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_three_keys(KC_Q, KC_F, KC_B)) {  // qmk flash shortcutstudio bridge75 firmware
        SEND_STRING("qmk flash -kb shortcut/bridge75 -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_three_keys(KC_Q, KC_C, KC_Y)) {  // qmk compile yunzii firmware
        SEND_STRING("qmk compile -kb yunzii/al68 -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_three_keys(KC_Q, KC_F, KC_Y)) {  // qmk flash yunzii firmware
        SEND_STRING("qmk flash -kb yunzii/al68 -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_three_keys(KC_Q, KC_C, KC_L)) {  // qmk compile lemokey p1 firmware
        SEND_STRING("qmk compile -kb lemokey/p1_pro/ansi_encoder -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_three_keys(KC_Q, KC_F, KC_L)) {  // qmk flash lemokey p1 firmware
        SEND_STRING("qmk flash -kb lemokey/p1_pro/ansi_encoder -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_four_keys(KC_Q, KC_C, KC_K, KC_V)) {  // qmk compile keychron V6 firmware
        SEND_STRING("qmk compile -kb keychron/v6_max/ansi_encoder -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_four_keys(KC_Q, KC_F, KC_K, KC_V)) {  // qmk flash keychron V6 firmware
        SEND_STRING("qmk flash -kb keychron/v6_max/ansi_encoder -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_four_keys(KC_Q, KC_C, KC_K, KC_Q)) {  // qmk compile keychron Q6 firmware
        SEND_STRING("qmk compile -kb keychron/q6_max/ansi_encoder -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_four_keys(KC_Q, KC_F, KC_K, KC_Q)) {  // qmk flash keychron Q6 firmware
        SEND_STRING("qmk flash -kb keychron/q6_max/ansi_encoder -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_three_keys(KC_P, KC_O, KC_C)) {  // insert test POC data for template
        send_string_with_delay("Firstname" SS_TAP(X_TAB) "Lastname" SS_TAP(X_TAB) "123-456-7890" SS_TAP(X_TAB) "first.last@mail.mil" SS_TAP(X_TAB),10);
    }
    else if (leader_sequence_five_keys(KC_A, KC_S, KC_P, KC_D, KC_C)) {  // asp.net decrypt connectionStrings path from clipboard 
	send_string_with_delay("C:\\Windows\\Microsoft.NET\\Framework64\\v4.0.30319\\aspnet_regiis -pdf connectionStrings " SS_LCMD(SS_TAP(X_V)) SS_TAP(X_ENT),5);
    }
    else if (leader_sequence_five_keys(KC_A, KC_S, KC_P, KC_E, KC_C)) {  // asp.net encrypt connectionStrings path from clipboard 
	send_string_with_delay("C:\\Windows\\Microsoft.NET\\Framework64\\v4.0.30319\\aspnet_regiis -pef connectionStrings " SS_LCMD(SS_TAP(X_V)) SS_TAP(X_ENT),5);
    }
    else if (leader_sequence_five_keys(KC_A, KC_S, KC_P, KC_D, KC_S)) {  // asp.net decrypt sessionState path from clipboard 
	send_string_with_delay("C:\\Windows\\Microsoft.NET\\Framework64\\v4.0.30319\\aspnet_regiis -pdf system.web/sessionState " SS_LCMD(SS_TAP(X_V)) SS_TAP(X_ENT),5);
    }
    else if (leader_sequence_five_keys(KC_A, KC_S, KC_P, KC_E, KC_S)) {  // asp.net encrypt sessionState path from clipboard 
	send_string_with_delay("C:\\Windows\\Microsoft.NET\\Framework64\\v4.0.30319\\aspnet_regiis -pef system.web/sessionState " SS_LCMD(SS_TAP(X_V)) SS_TAP(X_ENT),5);
    }
    else if (leader_sequence_four_keys(KC_B, KC_O, KC_O, KC_T)) {  // reset to bootloader 
        reset_keyboard();
    }
    // if process_leader_secrets returns false, a secret leader sequence ran and leader matching should stop
    // if true, no secrets match and leader matching continues here.
    else if (process_leader_secrets()) {
        // if leader sequence failed, set var from rgb_matrix to blink the rgb red a few times
        is_leader_error = true;
        leader_error_token = defer_exec(1500, leader_error_callback, NULL);  // schedule callback to stop blinking
    }

    is_in_leader_sequence = false;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (!bat_level_animiation_actived() && !battery_is_empty()) {
        // if on a layer and the key is set, then make it light up in a different color
	uint8_t layer = get_highest_layer(layer_state);
        if (layer > 0) {
            for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
                for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                    uint8_t index = g_led_config.matrix_co[row][col];

                    if (index >= led_min && index < led_max && index != NO_LED &&
                    keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
		        switch (layer) {
		        case FN_LAYER:
			    if (index == I_MREC1 || index == I_MREC2) { // macro recording keys
                                rgb_matrix_set_color(index, RGB_CORAL);
			    }
			    else {
                                rgb_matrix_set_color(index, RGB_GREEN);
			    }
			    break;
		        case SFT_LAYER:
                            rgb_matrix_set_color(index, RGB_ORANGE);
			    break;
		        case CTL_LAYER:
                            rgb_matrix_set_color(index, RGB_RED);
			    break;
		        case OPT_LAYER:
                            rgb_matrix_set_color(index, RGB_YELLOW);
			    break;
		        case TMUX_LAYER:
                            rgb_matrix_set_color(index, RGB_CYAN);
			    break;
		        case SYMB_LAYER:
                            rgb_matrix_set_color(index, RGB_SPRINGGREEN);
			    break;
                        case WIDE_TEXT_LAYR:
                            rgb_matrix_set_color(index, RGB_TURQUOISE);
                            break;
                        case CIRCLE_TEXT_LAYR:
                            rgb_matrix_set_color(index, RGB_CORAL);
                            break;
		        case LOCK_LAYER:
			    break;
		        default:	
                            rgb_matrix_set_color(index, 0x77, 0x77, 0x77);
			    break;
		        }
                    }
                }    
            }
            // custom colors for layer keys on layer 1
	    if (layer == FN_LAYER) {
                rgb_matrix_set_color(I_LSFT, RGB_ORANGE);  // left shift 
                rgb_matrix_set_color(I_RSFT, RGB_ORANGE);  // right shift 
                rgb_matrix_set_color(I_LCTL, RGB_RED);     // left ctrl
                rgb_matrix_set_color(I_LOPT, RGB_YELLOW);  // left option
                rgb_matrix_set_color(I_ROPT, RGB_YELLOW);  // right option
                rgb_matrix_set_color(I_RCTL, RGB_RED);     // right ctrl
                rgb_matrix_set_color(I_TAB, RGB_CYAN);     // tab
	    }	
            // custom colors for tap dance keys on symbol layer
            else if (layer == SYMB_LAYER) {
              rgb_matrix_set_color(I_GRV, RGB_WHITE); // grave
              rgb_matrix_set_color(I_E, RGB_WHITE);   // e
              rgb_matrix_set_color(I_U, RGB_WHITE);   // u
              rgb_matrix_set_color(I_I, RGB_WHITE);   // i
              rgb_matrix_set_color(I_N, RGB_WHITE);   // n
            }
            // set up the layer blinking indicator
            if (!layer_timer) {
  	        is_led_on = true;
                layer_timer = timer_read();
            }
            // timer_elapsed() is a built-in function in qmk => it calculates in ms the time elapsed with timer_read()
            else if (timer_elapsed(layer_timer) > 500) 
            {
                is_led_on = !is_led_on;
                layer_timer = timer_read();
            }
            if (is_led_on)
            {
	        switch (layer) {
	        case FN_LAYER:
                    rgb_matrix_set_color(I_CAPS, RGB_GREEN);       // caps
                    rgb_matrix_set_color(I_FN, RGB_GREEN);         // fn
		    break;
	        case SFT_LAYER:
                    rgb_matrix_set_color(I_LSFT, RGB_ORANGE);      // lshift 
                    rgb_matrix_set_color(I_RSFT, RGB_ORANGE);      // rshift
		    break;
	        case CTL_LAYER:
                    rgb_matrix_set_color(I_LCTL, RGB_RED);         // lctrl
                    rgb_matrix_set_color(I_RCTL, RGB_RED);         // rctrl
		    break;
	        case OPT_LAYER:
                    rgb_matrix_set_color(I_LOPT, RGB_YELLOW);      // lopt
                    rgb_matrix_set_color(I_ROPT, RGB_YELLOW);      // ropt
		    break;
	        case TMUX_LAYER:
                    rgb_matrix_set_color(I_TAB, RGB_CYAN);         // Tab
		    break;
	        case SYMB_LAYER:
                    rgb_matrix_set_color(I_LOPT, RGB_SPRINGGREEN); // lopt
                    rgb_matrix_set_color(I_ROPT, RGB_SPRINGGREEN); // ropt
		    break;
                case WIDE_TEXT_LAYR:
                    rgb_matrix_set_color(I_RSFT, RGB_TURQUOISE);   // rshift
                    break;
                case CIRCLE_TEXT_LAYR:
                    rgb_matrix_set_color(I_RSFT, RGB_CORAL);      // rshift
                    break;
	        case LOCK_LAYER:
                    rgb_matrix_set_color(I_EKS, RGB_RED);          // X
                    rgb_matrix_set_color(I_INDICATOR, RGB_RED);    // indicator
		    break;
	        default:	
   		    break;
	        }
            } 
        }
        // default layer color settings
        else {
            rgb_matrix_set_color(I_ESC, 255, 255, 255);   // esc
    	    rgb_matrix_set_color(I_F1, 234, 234, 255);    // f1
    	    rgb_matrix_set_color(I_F2, 234, 234, 255);    // f2
    	    rgb_matrix_set_color(I_F3, 234, 234, 255);    // f3
    	    rgb_matrix_set_color(I_F4, 234, 234, 255);    // f4
    	    rgb_matrix_set_color(I_F5, 0, 255, 0);        // f5
    	    rgb_matrix_set_color(I_F6, 255, 255, 0);      // f6
    	    rgb_matrix_set_color(I_F7, 255, 255, 0);      // f7
    	    rgb_matrix_set_color(I_F8, 255, 255, 0);      // f8
    	    rgb_matrix_set_color(I_F9, 255, 255, 0);      // f9
    	    rgb_matrix_set_color(I_F10, 234, 234, 255);   // f10
    	    rgb_matrix_set_color(I_F11, 255, 0, 0);       // f11
    	    rgb_matrix_set_color(I_F12, 234, 234, 255);   // f12
    	    rgb_matrix_set_color(I_SSHOT, 234, 234, 255); // screenshot
    	    rgb_matrix_set_color(I_SIRI, 234, 234, 255);  // siri
    	    rgb_matrix_set_color(I_RGB, 234, 234, 255);   // rgb
    	    rgb_matrix_set_color(I_CIRC, 234, 234, 255);  // circle
    	    rgb_matrix_set_color(I_TRI, 234, 234, 255);   // triangle
    	    rgb_matrix_set_color(I_SQR, 234, 234, 255);   // square
    	    rgb_matrix_set_color(I_EKS, 255, 0, 0);       // X
            if (!host_keyboard_led_state().caps_lock) {
    	      rgb_matrix_set_color(I_CAPS, RGB_ORANGE);  // caps
	    }
            // if caps lock, color caps alpha keys
            else {
               for (uint8_t i = led_min; i < led_max; i++) {
                 if (is_capslock_shifted(i)) {
                    rgb_matrix_set_color(i, RGB_RED);
                 }
               }
            }
	    if (is_caps_word_on())
            {
              // set capitilized keys red when caps word is active
              for (uint8_t i = led_min; i < led_max; i++) {
                if (is_capsword_shifted(i)) {
                   rgb_matrix_set_color(i, RGB_RED);
                }
              }
    	      rgb_matrix_set_color(I_LSFT, 255, 255, 255);  // turn left shift white when caps_word is active
    	      rgb_matrix_set_color(I_RSFT, 255, 255, 255);  // turn right shift white when caps_word is active
	    }
            else if (!host_keyboard_led_state().caps_lock) { // if not caps word, nor caps lock, then f and j are lighter color 
	      if (hrow_light) {
    	          rgb_matrix_set_color(I_A, 0, 255, 0);     // a
    	          rgb_matrix_set_color(I_S, 0, 255, 0);     // s
    	          rgb_matrix_set_color(I_D, 0, 255, 0);     // d
    	          rgb_matrix_set_color(I_F, 0, 255, 0);     // f
    	          rgb_matrix_set_color(I_J, 0, 255, 0);     // j
    	          rgb_matrix_set_color(I_K, 0, 255, 0);     // k
    	          rgb_matrix_set_color(I_L, 0, 255, 0);     // l
    	          rgb_matrix_set_color(I_SEMI, 0, 255, 0);  // ;
	      }
	      if (fj_light) {
    	          rgb_matrix_set_color(I_F, 255, 255, 255); // f
    	          rgb_matrix_set_color(I_J, 255, 255, 255); // j
              }
            }
    	    rgb_matrix_set_color(I_ENT, 255, 255, 255);     // enter
    	    rgb_matrix_set_color(I_LCTL, 255, 0, 0);        // left ctrl
    	    rgb_matrix_set_color(I_LOPT, 0, 255, 255);      // left option
    	    rgb_matrix_set_color(I_LCMD, 75, 199, 255);     // left command
    	    rgb_matrix_set_color(I_RCMD, 75, 199, 255);     // right command
    	    rgb_matrix_set_color(I_ROPT, 0, 255, 255);      // right option
    	    rgb_matrix_set_color(I_FN, RGB_ORANGE);         // fn 
    	    rgb_matrix_set_color(I_RCTL, 255, 0, 0);        // right control
            rgb_matrix_set_color(I_TAB, 0x77,0x77,0x77);    // tab
        }
        // if layer locked, turn the lock key white
        if (is_layer_locked(layer)) {
    	    rgb_matrix_set_color(I_LLOCK, RGB_WHITE);   // ins (layer lock key)
        }	
        // if key lock is watching for next key, turn the key lock key red
        if (is_key_lock_watching()) {
    	    rgb_matrix_set_color(I_KLOCK, RGB_ORANGE);   // screenshot (key lock key)
        }
        // if key lock is activated, turn the key lock key white
        else if (is_key_locked) {
            // flash the key lock button if any key is locked 
            if (!key_lock_timer || timer_elapsed(key_lock_timer) > 500) {
  	        is_key_lock_led_on = !is_key_lock_led_on;;
                key_lock_timer = timer_read();
            }
            if (is_key_lock_led_on) {
    	        rgb_matrix_set_color(I_KLOCK, 255, 255, 255);   // screenshot (key lock key)
            } 
            else {
    	        rgb_matrix_set_color(I_KLOCK, 255, 0, 0);   // screenshot (key lock key)
            }   
            // and light up normal modifiers if they are locked
            if (lcmd_locked) {
    	        rgb_matrix_set_color(I_LCMD, 255, 255, 255);   // lcmd 
            }
            if (rcmd_locked) {
    	        rgb_matrix_set_color(I_RCMD, 255, 255, 255);   // rcmd 
            }
            if (rsft_locked) {
    	        rgb_matrix_set_color(I_RSFT, 255, 255, 255);   // rsft 
            }
            if (lsft_locked) {
    	        rgb_matrix_set_color(I_LSFT, 255, 255, 255);   // lsft 
            }
            if (lctl_locked) {
    	        rgb_matrix_set_color(I_LCTL, 255, 255, 255);   // lctl 
            }
            if (lopt_locked) {
    	        rgb_matrix_set_color(I_LOPT, 255, 255, 255);   // lopt 
            }
        }
        // if leader is activated, flash the esc and l keys red and white 
        if (is_in_leader_sequence) {
            // flash the key lock button if any key is locked 
            if (!leader_timer || timer_elapsed(leader_timer) > 500) {
  	        is_leader_led_on = !is_leader_led_on;
                leader_timer = timer_read();
            }
            if (is_leader_led_on) {
    	        rgb_matrix_set_color(I_ESC, 255, 255, 255);
    	        rgb_matrix_set_color(I_L, 255, 255, 255);
            } 
            else {
    	        rgb_matrix_set_color(I_ESC, 255, 0, 0);
    	        rgb_matrix_set_color(I_L, 255, 0, 0);
            }   
        }
        // if a leader sequence error occured, blink all leds red
        else if (is_leader_error) {
            if (!leader_error_timer || timer_elapsed(leader_error_timer) > 250) {
                is_leader_error_led_on = !is_leader_error_led_on;
                leader_error_timer = timer_read();
            }
            if (is_leader_error_led_on) {
                for (uint8_t i = led_min; i < led_max; i++) {
                    rgb_matrix_set_color(i, RGB_RED);
                }
            }
        }
        // if any rgb key highlights are on, turn the setting keys white on layer CTL_LAYER
	if (layer == CTL_LAYER)
	{
            if (fj_light) {
                rgb_matrix_set_color(I_FJLIGHT, 255, 255, 255);     // home (fj highlight key)
                rgb_matrix_set_color(I_APOS, 255, 255, 255);        // ' (fj highlight key)
            }
            if (hrow_light) {
                rgb_matrix_set_color(I_HROWLIGHT, 255, 255, 255);   // end (hrow highlight key)
                rgb_matrix_set_color(I_ENT, 255, 255, 255);         // enter (hrow highlight key)
            }
            if (enable_keytracker) {
                rgb_matrix_set_color(I_KTRACK, 255, 255, 255);      // mic (keytracker set key)
                rgb_matrix_set_color(I_SEMI, 255, 255, 255);        // ; (keytracker set key)
            }
	}
        // calculate the reactive rgb for keypresses
        if (enable_keytracker) {
            for (int i = 0; i < tk_length; i++) {
                if (tracked_keys[i].press) {
                    // esc, enter turn red
                    if (tracked_keys[i].index == I_ESC || tracked_keys[i].index == I_ENT) {
                        rgb_matrix_set_color(tracked_keys[i].index, 255, 0, 0);
                    }
                    // everything else is white
                    else {
                        rgb_matrix_set_color(tracked_keys[i].index, 255, 255, 255);
                    }
                }
                // do the key fade if key should fade
                else if (key_should_fade(tracked_keys[i], layer)) {
                    if (tracked_keys[i].fade > 255) {
                        rgb_matrix_set_color(tracked_keys[i].index, 255, 255, 255);
                    }
                    else if (tracked_keys[i].fade > 200) {
                        rgb_matrix_set_color(tracked_keys[i].index, tracked_keys[i].fade, tracked_keys[i].fade, 255);
                    } else if (tracked_keys[i].fade > 175) {
                        rgb_matrix_set_color(tracked_keys[i].index, tracked_keys[i].fade, tracked_keys[i].fade, tracked_keys[i].fade + 55);
                    } else if (tracked_keys[i].fade >  115) {
                        rgb_matrix_set_color(tracked_keys[i].index, tracked_keys[i].fade, tracked_keys[i].fade, tracked_keys[i].fade + 80);
                    } else if (tracked_keys[i].fade > 80) {
                        rgb_matrix_set_color(tracked_keys[i].index, tracked_keys[i].fade, tracked_keys[i].fade, tracked_keys[i].fade + 100);
                    } else if (tracked_keys[i].fade > 35) {
                        rgb_matrix_set_color(tracked_keys[i].index, tracked_keys[i].fade, tracked_keys[i].fade, tracked_keys[i].fade + 150);
                    } else {
                        rgb_matrix_set_color(tracked_keys[i].index, 35, 24, 189);
                    }
                }
            }
        }
        if (macro_recording) {
            // make the numpad - key a different color since that is used to insert delays
            rgb_matrix_set_color(I_PMINS, RGB_YELLOW); 

            // flash the macro button if macro is recording
            if (timer_elapsed(macro_timer) > 500) {
  	        is_macro_led_on = !is_macro_led_on;;
                macro_timer = timer_read();
            }
            if (is_macro_led_on) {
	        if (macro_direction == 1) {
	            rgb_matrix_set_color(I_MREC1, RGB_RED);
                } else {
	            rgb_matrix_set_color(I_MREC2, RGB_RED);
                }   
            } 
        }
        // if this is a color test, then light keys in each qmk named color
        if (color_test) {
            // turn off the color test if it has been going for 15 seconds
            if (timer_elapsed(color_test_timer) > 15000) {
                color_test = false;
            }
            else { // show the named colors defined in color.h, https://docs.qmk.fm/features/rgb_matrix
                rgb_matrix_set_color(I_Q, RGB_AZURE);
                rgb_matrix_set_color(I_W, RGB_BLACK);
                rgb_matrix_set_color(I_E, RGB_BLUE);
                rgb_matrix_set_color(I_R, RGB_CHARTREUSE);
                rgb_matrix_set_color(I_T, RGB_CORAL);
                rgb_matrix_set_color(I_Y, RGB_CYAN);
                rgb_matrix_set_color(I_U, RGB_GOLD);
                rgb_matrix_set_color(I_I, RGB_GOLDENROD);
                rgb_matrix_set_color(I_O, RGB_GREEN);
                rgb_matrix_set_color(I_P, RGB_MAGENTA);
                rgb_matrix_set_color(I_A, RGB_ORANGE);
                rgb_matrix_set_color(I_S, RGB_PINK);
                rgb_matrix_set_color(I_D, RGB_PURPLE);
                rgb_matrix_set_color(I_F, RGB_RED);
                rgb_matrix_set_color(I_G, RGB_SPRINGGREEN);
                rgb_matrix_set_color(I_H, RGB_TEAL);
                rgb_matrix_set_color(I_J, RGB_TURQUOISE);
                rgb_matrix_set_color(I_K, RGB_WHITE);
                rgb_matrix_set_color(I_L, RGB_YELLOW);
            }
        }
        // track button holds on OPT_LAYER
        if (layer == OPT_LAYER) {
            if (ms_btn_held) { // show if mouse btn is held
                rgb_matrix_set_color(I_M, RGB_WHITE);        // mouse btn1 hold key
            }
            if (is_lopt_held) { // show if lopt is held
                rgb_matrix_set_color(I_O, RGB_WHITE);        // opt hold key
            }
        }
        // track mode keys on WIDE_TEXT_LAYR
        if (layer == WIDE_TEXT_LAYR) {
            switch (wide_text_mode) {
            case WIDE_STHRU:
                rgb_matrix_set_color(I_STHRU, RGB_WHITE);    // sthru toggle
                break;
            case WIDE_UNDERLN:
                rgb_matrix_set_color(I_UNDERLN, RGB_WHITE);  // underln toggle
                break;
            case WIDE_BARTEXT:
                rgb_matrix_set_color(I_BARTEXT, RGB_WHITE);  // bartext toggle
                break;
            case WIDE_BBRTEXT:
                rgb_matrix_set_color(I_BBRTEXT, RGB_WHITE);  // bbrtext toggle
                break;
            default:
                break;
            }
        }
        // show wireless connection on CTL_LAYER if in bt or 2.4g modes
	if (layer == CTL_LAYER)
	{
            if (wireless_get_state() == WT_CONNECTED) {
                // host_index is set to 24 for 2.4g, bt is 1,2,3
                rgb_matrix_set_color(wireless_get_host_index() == 24 ? I_N4 : wireless_get_host_index() + 19, RGB_WHITE);
            }
        }
    }
    return false;
}

// a function to check for if a key press should fade the rgb
bool key_should_fade(keytracker key, uint8_t layer) {
    bool should_fade = true;
    if ((key.fade < 1) ||
       (key.index < 19) || (key.index == 72) ||                                                                     // top row
       (key.index == I_TAB) ||                                                                                      // tab
       (layer < 2 && key.index == I_CAPS) ||                                                                        // caps lock
       (key.index == I_INS || key.index == I_ENT) ||                                                                // ins, enter
       ((layer == 1 || layer == 3 || layer == WIDE_TEXT_LAYR || layer == CIRCLE_TEXT_LAYR || is_caps_word_on()) &&
         (key.index == I_LSFT || key.index == I_RSFT)) ||                                                           // shift
       (layer == WIDE_TEXT_LAYR && (key.index == I_BARTEXT || key.index == I_STHRU ||
         key.index == I_UNDERLN || key.index == I_BBRTEXT)) ||                                                      // wide-text toggles
       (layer == CTL_LAYER && (key.index >= I_N1 && key.index <= I_N4)) ||                                          // wireless mode keys
       (layer < 2 && key.index > 94 && key.index < 103) ||                                                          // bottom row mods
       (layer == 4 && (key.index == I_LCTL || key.index == I_RCTL || key.index == I_HOME || key.index == I_END ||
         key.index == I_SEMI || key.index == I_APOS)) ||                                                            // ctrl, mode keys 
       ((layer == 5 || layer == SYMB_LAYER) && (key.index == I_LOPT || key.index == I_ROPT))) {                     // option
 	 should_fade = false;
       }
    return should_fade; 
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (get_highest_layer(state) == 0) {
        rgb_matrix_reload_from_eeprom();
    }
    else if (get_highest_layer(state) != LOCK_LAYER) {
        HSV hsv = rgb_matrix_get_hsv();
        if (hsv.v >= 180) {
            rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, 180);
        }
    }
    return state;
}

//Determine the current tap dance state
int cur_dance (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD;
    }
  } else if (state->count == 2) {
    return DOUBLE_TAP;
  } else if (state->count == 3) {
    return TRIPLE_TAP;
  } else if (state->count == 4) {
    return QUAD_TAP;
  } else if (state->count == 5) {
    return PENT_TAP;
  }
  else return 8;
}

//Initialize tap structure associated with example tap dance key
static tap caps_tap_state = {
  .is_press_action = true,
  .state = 0
};
static tap fn_tap_state = {
  .is_press_action = true,
  .state = 0
};
static tap ropt_tap_state = {
  .is_press_action = true,
  .state = 0
};
static tap rctl_tap_state = {
  .is_press_action = true,
  .state = 0
};
static tap rsft_tap_state = {
  .is_press_action = true,
  .state = 0
};
static tap macl_tap_state = {
  .is_press_action = true,
  .state = 0
};
static tap kbunlock_tap_state = {
  .is_press_action = true,
  .state = 0
};

// caps tap dance key function
void caps_finished (tap_dance_state_t *state, void *user_data) {
  caps_tap_state.state = cur_dance(state);
  switch (caps_tap_state.state) {
    case SINGLE_TAP: 
      tap_code(KC_CAPS); 
      break;
    case SINGLE_HOLD: 
      layer_on(FN_LAYER); 
      break;
    case DOUBLE_TAP: 
      if (layer_state_is(FN_LAYER)) {
        //if already set, then switch it off
        layer_lock_off(FN_LAYER);
      } else { 
        //if not already set, then switch the layer on
        layer_lock_on(FN_LAYER);
      }
      break;
    case TRIPLE_TAP: 
      if (layer_state_is(CTL_LAYER)) {
        //if already set, then switch it off
        layer_lock_off(CTL_LAYER);
      } else { 
        //if not already set, then switch the layer on
        layer_lock_on(CTL_LAYER);
      }
      break;
    case QUAD_TAP: 
      if (layer_state_is(OPT_LAYER)) {
        //if already set, then switch it off
        layer_lock_off(OPT_LAYER);
      } else { 
        //if not already set, then switch the layer on
        layer_lock_on(OPT_LAYER);
      }
      break;
    case PENT_TAP:
      if (layer_state_is(TMUX_LAYER)) {
        //if already set, then switch it off
        layer_lock_off(TMUX_LAYER);
      } else {
        //if not already set, then switch the layer on
        layer_lock_on(TMUX_LAYER);
      }
      break;
  }
}

void caps_reset (tap_dance_state_t *state, void *user_data) {
  //if the key was held down and now is released then switch off the layer
  if (caps_tap_state.state==SINGLE_HOLD && !is_layer_locked(FN_LAYER)) {
    layer_off(FN_LAYER);
  }
  caps_tap_state.state = 0;
}

// function for fn tap dance
// this is used instead of just standard OSL because its easier to
// hold it down and run multiple dynamic macros, which are otherwise
// setup to turn of the layer if OSL is detected as active
void fn_finished (tap_dance_state_t *state, void *user_data) {
  fn_tap_state.state = cur_dance(state);
  switch (fn_tap_state.state) {
    case SINGLE_TAP: 
      set_oneshot_layer(FN_LAYER, ONESHOT_START); 
      clear_oneshot_layer_state(ONESHOT_PRESSED);
      break;
    case SINGLE_HOLD: 
      layer_on(FN_LAYER); 
      break;
  }
}

void fn_reset (tap_dance_state_t *state, void *user_data) {
  switch (fn_tap_state.state) {
    case SINGLE_TAP:
      break;
    case SINGLE_HOLD:
      if (!is_layer_locked(FN_LAYER)) {
        layer_off(FN_LAYER);
      }
      break;
  }
  fn_tap_state.state = 0;
}

// function for ropt tap dance
void ropt_finished (tap_dance_state_t *state, void *user_data) {
  ropt_tap_state.state = cur_dance(state);
  switch (ropt_tap_state.state) {
    case SINGLE_TAP: 
      set_oneshot_layer(OPT_LAYER, ONESHOT_START); 
      clear_oneshot_layer_state(ONESHOT_PRESSED);
      break;
    case SINGLE_HOLD: 
      register_code(KC_ROPT); 
      if (get_highest_layer(layer_state) < 3) {
          layer_on(SYMB_LAYER);
      }
      break;
  }
}

void ropt_reset (tap_dance_state_t *state, void *user_data) {
  switch (ropt_tap_state.state) {
    case SINGLE_TAP:
      break;
    case SINGLE_HOLD:
      unregister_code(KC_ROPT);
      if (!is_layer_locked(SYMB_LAYER)) {
          layer_off(SYMB_LAYER);
      }
      break;
  }
  ropt_tap_state.state = 0;
}

// function for rctl tap dance
void rctl_finished (tap_dance_state_t *state, void *user_data) {
  rctl_tap_state.state = cur_dance(state);
  switch (rctl_tap_state.state) {
    case SINGLE_TAP: 
      set_oneshot_layer(CTL_LAYER, ONESHOT_START); 
      clear_oneshot_layer_state(ONESHOT_PRESSED);
      break;
    case SINGLE_HOLD: 
      register_code(KC_RCTL); 
      break;
    case DOUBLE_TAP:
      leader_start();
      break;
  }
}

void rctl_reset (tap_dance_state_t *state, void *user_data) {
  switch (rctl_tap_state.state) {
    case SINGLE_TAP:
      break;
    case SINGLE_HOLD:
      unregister_code(KC_RCTL);
      break;
  }
  rctl_tap_state.state = 0;
}

// function for each press of rsft
void rsft_each(tap_dance_state_t *state, void *user_data) {
    if (get_mods() & MOD_BIT(KC_LSFT)) {
        caps_word_on();
    }
}

// function for rsft tap dance
void rsft_finished (tap_dance_state_t *state, void *user_data) {
  rsft_tap_state.state = cur_dance(state);
  switch (rsft_tap_state.state) {
    case SINGLE_TAP: 
      // check if this is caps word activation, otherwise set the osl
      if (!is_caps_word_on()) {
          set_oneshot_layer(SFT_LAYER, ONESHOT_START); 
          clear_oneshot_layer_state(ONESHOT_PRESSED);
      }
      break;
    case SINGLE_HOLD:
      // check if this is caps word activation, otherwise regular shift
      if (get_mods() & MOD_BIT(KC_LSFT)) {
          caps_word_on();
      }
      else {
          register_code(KC_RSFT);
      }
      break;
    case DOUBLE_TAP:
      // activate WIDE_TEXT_LAYR
      if (IS_LAYER_ON(WIDE_TEXT_LAYR)) {
          layer_lock_off(WIDE_TEXT_LAYR);
      }
      else {
          layer_lock_on(WIDE_TEXT_LAYR);
          wide_firstchar = true;
      }
      break;
    case TRIPLE_TAP:
      // activate CIRCLE_TEXT_LAYR
      if (IS_LAYER_ON(CIRCLE_TEXT_LAYR)) {
          layer_lock_off(CIRCLE_TEXT_LAYR);
      }
      else {
          layer_lock_on(CIRCLE_TEXT_LAYR);
      }
      break;
  }
}

void rsft_reset (tap_dance_state_t *state, void *user_data) {
  switch (rsft_tap_state.state) {
    case SINGLE_TAP:
      // check if this is caps word activation  
      if (get_mods() & MOD_BIT(KC_LSFT)) {
          reset_oneshot_layer();
          caps_word_on();
      }
      break;
    case SINGLE_HOLD:
      if (get_mods() & MOD_BIT(KC_LSFT)) {
          caps_word_on(); 
      }
      else {
          unregister_code(KC_RSFT);
      } 
      break;
    case DOUBLE_TAP:
      break;
    case TRIPLE_TAP:
      break;
  }
  rsft_tap_state.state = 0;
}

// function for macl tap dance
void macl_finished (tap_dance_state_t *state, void *user_data) {
  macl_tap_state.state = cur_dance(state);
  switch (macl_tap_state.state) {
    case SINGLE_TAP: 
    case SINGLE_HOLD:
      tap_code(KC_MS_ACCEL0);
      break;
    case DOUBLE_TAP: 
      tap_code(KC_MS_ACCEL1);
      break;
    case TRIPLE_TAP: 
      tap_code(KC_MS_ACCEL2);
      break;
  }
}

void macl_reset (tap_dance_state_t *state, void *user_data) {
  if (macl_tap_state.state == SINGLE_HOLD) {
      tap_code(KC_MS_ACCEL1);
  }
  macl_tap_state.state = 0;
}

// function for kbunlock tap dance
void kbunlock_finished (tap_dance_state_t *state, void *user_data) {
  kbunlock_tap_state.state = cur_dance(state);
  switch (kbunlock_tap_state.state) {
    case SINGLE_TAP:
      break;
    case DOUBLE_TAP:
      break;
    case TRIPLE_TAP:
      layer_off(LOCK_LAYER);
      rgblight_mode(saved_rgb_mode);
      break;
    case SINGLE_HOLD:
      break;
  }
}
void kbunlock_reset (tap_dance_state_t *state, void *user_data) {
  kbunlock_tap_state.state = 0;
}

// associate the tap dance keys with their funcitons 
tap_dance_action_t tap_dance_actions[] = {
  [CAPS_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, caps_finished, caps_reset),
  [FN_OSL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fn_finished, fn_reset),
  [ROPT_OSL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ropt_finished, ropt_reset),
  [RCTL_OSL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rctl_finished, rctl_reset),
  [RSFT_OSL] = ACTION_TAP_DANCE_FN_ADVANCED(rsft_each, rsft_finished, rsft_reset),
  [MOUSE_ACCEL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, macl_finished, macl_reset),
  [KB_UNLOCK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, kbunlock_finished, kbunlock_reset),
};

// this is needed to prevent CAPS_WORD from breaking when some custom key commands are used
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case BSPCFAST:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

// use this for special layer lock handling
void layer_lock_set_user(layer_state_t locked_layers) {
    static bool opt_is_held_for_symbol = false;
    if (is_layer_locked(SYMB_LAYER)) {
        register_code(KC_LOPT);
        opt_is_held_for_symbol = true;
    }
    else if (opt_is_held_for_symbol) {
        unregister_code(KC_LOPT);
        opt_is_held_for_symbol = false;
    }
}

// setup to store vars when macro recording starts or ends. then can flash some rgb
void dynamic_macro_record_start_user(int8_t direction) {
	macro_direction = direction;
	macro_recording = true;
        macro_timer = timer_read();
}
void dynamic_macro_record_end_user(int8_t direction) {
	macro_direction = direction;
	macro_recording = false;
        is_macro_led_on = false;
        for (int i = 0; i < tk_length; i++) {
            if ((tracked_keys[i].index > 15 && tracked_keys[i].index < 19) || (tracked_keys[i].index == 72)) {
	        tracked_keys[i].press = false;
	        tracked_keys[i].fade = 0;
	    }
        }
}
// this is so the macro key lights don't get stuck when i play the macro
void dynamic_macro_play_user(int8_t direction) {
        for (int i = 0; i < tk_length; i++) {
	    if ((tracked_keys[i].index > 15 && tracked_keys[i].index < 19) || (tracked_keys[i].index == 72)) {
                tracked_keys[i].press = false;
                tracked_keys[i].fade = 0;
            }
        }
}
