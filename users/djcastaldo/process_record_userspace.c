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
