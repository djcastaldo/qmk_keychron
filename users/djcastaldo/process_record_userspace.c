// process_record_userspace.c
// @davex 07/30/2025
// this is the start of moving some stuff to separate files to make it easier to move between keyboards 

#include QMK_KEYBOARD_H
#ifdef KEYBOARD_IS_KEYCHRON
#include "keychron_common.h"
#elif defined(KEYBOARD_IS_LEMOKEY)
#include "lemokey_common.h"
#endif
#include "process_record_userspace.h"

// setup mouse jiggler
deferred_token jiggler_token = INVALID_DEFERRED_TOKEN;
report_mouse_t jiggler_report = {0};
// for tracking whether to highlight home row keys f and j
bool fj_light;
// and for tracking if the full home row light is on
bool hrow_light;
// for disabling the keytracker, which will also disable key-reactive fade
bool enable_keytracker = true;


bool process_record_userspace(uint16_t keycode, keyrecord_t *record) {
    // stop mouse jiggler
    if (jiggler_token && record->event.pressed) {
        // if jiggler is currently running, stop when key is pressed
        cancel_deferred_exec(jiggler_token);
        jiggler_token = INVALID_DEFERRED_TOKEN;
        jiggler_report = (report_mouse_t){};  // clear the mouse
        host_mouse_send(&jiggler_report);
    }
    switch (keycode) {
    case JIGGLE:
        if (record->event.pressed) {
            jiggle_mouse();
        }
        return false;
    case FJLIGHT:
        if (record->event.pressed) {
	   // update the var used for f and j home key highlighting
	   fj_light = !fj_light;
	}
        return false;
    case HROWLIGHT:
        if (record->event.pressed) {
	   // update the var used for full home row keys highlighting
	   hrow_light = !hrow_light;
	}
        return false;
    case KTRACK:
        if (record->event.pressed) {
           // update the var used to enable/disable keytracker and per-key fade
           enable_keytracker = !enable_keytracker;
        }
        return false;
    }
    return true;
}

// jiggler to keep from screen timeout without adjusting power settings
void jiggle_mouse(void) {
    uint32_t jiggler_callback(uint32_t trigger_time, void* cb_arg) {
        // deltas to move in a circle of radius 20 pixels over 32 frames
        static const int8_t deltas[32] = {
          0, -1, -2, -2, -3, -3, -4, -4, -4, -4, -3, -3, -2, -2, -1, 0,
          0, 1, 2, 2, 3, 3, 4, 4, 4, 4, 3, 3, 2, 2, 1, 0};
        static uint8_t phase = 0;
        // get x delta from table and y delta by rotating a quarter cycle
        jiggler_report.x = deltas[phase];
        jiggler_report.y = deltas[(phase + 8) & 31];
        phase = (phase + 1) & 31;
        host_mouse_send(&jiggler_report);
        return 16;  // call the callback every 16 ms
    }
    jiggler_token = defer_exec(1, jiggler_callback, NULL);  // schedule callback
}

// send mac unicode
void symbol_key_mac(const char *unicode, const char *shift_unicode) {
    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();
    clear_mods();
    tap_code16(C(A(G(KC_SPC)))); // switch os keyboard to unicode
    add_mods(MOD_MASK_ALT);
    send_string(((mods | oneshot_mods) & (MOD_MASK_SHIFT | MOD_MASK_GUI)) ? shift_unicode : unicode);
    del_mods(MOD_MASK_ALT);
    tap_code16(C(A(G(KC_SPC)))); // switch back from unicode
    register_mods(mods);
}
