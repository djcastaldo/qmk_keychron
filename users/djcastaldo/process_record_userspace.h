// process_record_userspace.h
// @djcastaldo 07/30/2025
#pragma once

#include "deferred_exec.h"    // required for deferred_token
#include "report.h"           // required for report_mouse_t

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
#define MOD_SIRI HYPR(KC_S)                     // customized siri launch

typedef union {
    uint32_t raw;
    struct {
        bool is_linux_base : 1;
    };
} user_config_t;

extern user_config_t user_config;

// key tracker
typedef struct {
    uint8_t index;
    bool press;
    int fade;
} keytracker;

// setup keytracker
extern deferred_token key_token;
extern keytracker tracked_keys[20];
extern uint8_t tk_length;

// for tracking wide-text options for the WIDE_TEXT_LAYR
enum {
    WIDE_STANDARD,
    WIDE_STHRU,
    WIDE_UNDERLN,
    WIDE_BARTEXT,
    WIDE_BBRTEXT
};
extern uint8_t wide_text_mode;
extern bool wide_firstchar;

extern deferred_token jiggler_token;
extern report_mouse_t jiggler_report;
extern bool ms_btn_held;
extern bool fj_light;
extern bool hrow_light;
extern bool enable_keytracker;
extern bool color_test;
extern uint16_t color_test_timer;
extern const uint8_t monitored_macos_base_layers[];
extern const uint8_t monitored_macos_base_count;
extern int8_t macro_direction;
extern bool macro_recording;
extern bool is_macro_led_on;
extern uint16_t macro_timer;
extern deferred_token osl_macro_token;
extern bool oneshot_layer_active;
extern bool is_cmd_tab_active;
extern bool is_cmd_shift_tab_active;
extern deferred_token cmd_tab_token;

bool process_record_userspace(uint16_t keycode, keyrecord_t *record);
bool process_leader_userspace(void);
bool is_mac_base(void);
void jiggle_mouse(void);
void dual_key(uint16_t std_keycode, uint16_t alt_keycode, uint8_t mod_mask);
void symbol_key_mac(const char *unicode, const char *shift_unicode);
void symbol_key_win(const char *alt_code, const char *shift_alt_code);
void symbol_key_linux(const char *hex_code, const char *shift_hex_code);
void type_numpad_keys_from_string(const char *stringnum);
uint32_t osl_macro_callback(uint32_t trigger_time, void *cb_arg);
bool app_switch_active(void);
uint32_t cmd_tab_callback(uint32_t trigger_time, void* cb_arg);
