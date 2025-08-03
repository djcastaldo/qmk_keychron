// process_record_userspace.h
// @djcastaldo 07/30/2025
#pragma once

#include "deferred_exec.h"    // required for deferred_token
#include "report.h"           // required for report_mouse_t

typedef union {
    uint32_t raw;
    struct {
        bool is_linux_base : 1;
    };
} user_config_t;

extern user_config_t user_config;

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
extern bool fj_light;
extern bool hrow_light;
extern bool enable_keytracker;
extern bool color_test;
extern uint16_t color_test_timer;
extern const uint8_t monitored_macos_base_layers[];
extern const uint8_t monitored_macos_base_count;

bool process_record_userspace(uint16_t keycode, keyrecord_t *record);
bool process_leader_userspace(void);
bool is_mac_base(void);
void jiggle_mouse(void);
void dual_key(uint16_t std_keycode, uint16_t alt_keycode, uint8_t mod_mask);
void symbol_key_mac(const char *unicode, const char *shift_unicode);
void symbol_key_win(const char *alt_code, const char *shift_alt_code);
void symbol_key_linux(const char *hex_code, const char *shift_hex_code);
void type_numpad_keys_from_string(const char *stringnum);
