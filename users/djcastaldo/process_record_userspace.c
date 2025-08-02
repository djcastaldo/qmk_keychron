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
#include "config.h"
#include "layers.h"

const uint8_t monitored_macos_base_layers[] = MONITORED_MACOS_BASE_LAYERS;
const uint8_t monitored_macos_base_count = MONITORED_MACOS_BASE_COUNT;

user_config_t user_config;

// for tracking if base is mac
bool is_mac_base(void) {
    for (uint8_t i = 0; i < monitored_macos_base_count; i++) {
        if (IS_LAYER_ON(monitored_macos_base_layers[i])) {
            return true;
        }
    }
    return false;
}

// setup mouse jiggler
deferred_token jiggler_token = INVALID_DEFERRED_TOKEN;
report_mouse_t jiggler_report = {0};
// for tracking whether to highlight home row keys f and j
bool fj_light;
// and for tracking if the full home row light is on
bool hrow_light;
// for disabling the keytracker, which will also disable key-reactive fade
bool enable_keytracker = true;
// if rgb color-test is requested, set this bool
bool color_test;
// and use a timer so that it can be turned off after a delay even if no further key is pressed
uint16_t color_test_timer;

bool process_record_userspace(uint16_t keycode, keyrecord_t *record) {
    // stop color test if active and a key is pressed
    if (color_test && record->event.pressed) {
        color_test = false;
        return false;
    }
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
    case WAVE:  // Types ~=~=~=~=~=~ or <~>~<~>~<~>~<~>
        static deferred_token wave_token = INVALID_DEFERRED_TOKEN;
        static uint8_t wave_phase = 0;
        if (!record->event.pressed) {  // On release.
            const uint8_t mods = get_mods();
            cancel_deferred_exec(wave_token);
            wave_token = INVALID_DEFERRED_TOKEN;
            // ensure the pattern always ends on a ">"
            if (mods & (MOD_MASK_GUI | MOD_MASK_CTRL)) {  // cmd/ctl held?
                clear_mods();                  // remove mods
                if ((wave_phase & 1) == 0) {
                    send_string("<~>");
                }
                else {
                    tap_code16(KC_RABK);
                }
                register_mods(mods);           // restore mods
            }
            else {
                if ((wave_phase & 1) == 0) { tap_code16(KC_TILD); }
            }
            wave_phase = 0;
        }
        else if (!wave_token) {  // on press
            uint32_t wave_callback(uint32_t trigger_time, void* cb_arg) {
                const uint8_t mods = get_mods();
                const uint8_t oneshot_mods = get_oneshot_mods();
                if ((mods | oneshot_mods) & (MOD_MASK_GUI | MOD_MASK_CTRL)) {  // cmd/ctl held?
                    clear_mods();                    // remove mods
                    clear_oneshot_mods();            // remove oneshot mods
                    tap_code16((++wave_phase & 1) ? KC_LABK : KC_RABK);
                    tap_code16(KC_TILD);
                    register_mods(mods);             // restore mods
                }
                else {
                    tap_code16((++wave_phase & 1) ? KC_TILD : KC_EQL);
                }
                return 16;  // call the callback every 16 ms
            }
            wave_token = defer_exec(1, wave_callback, NULL);
        }
        return false;
    case ARROW:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & (MOD_MASK_GUI | MOD_MASK_CTRL)) {  // cmd/ctl held?
                clear_mods();                   // remove mods
                clear_oneshot_mods();           // remove oneshot mods
                SEND_STRING("=>");
                register_mods(mods);            // restore mods
            } else {
                SEND_STRING("->");
            }
        }
        return false;
    case BSPCFAST:  // backspace with exponential repeating
        // initial delay before the first repeat
        static const uint8_t INIT_DELAY_MS = 250;
        // This array customizes the rate at which the Backspace key
        // repeats. The delay after the ith repeat is REP_DELAY_MS[i].
        // Values must be between 1 and 255.
        static const uint8_t REP_DELAY_MS[] PROGMEM = {
            99, 79, 65, 57, 49, 43, 40, 35, 33, 30, 28, 26, 25, 23, 22, 20,
            20, 19, 18, 17, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10};
        static deferred_token bspc_token = INVALID_DEFERRED_TOKEN;
        static uint8_t rep_count = 0;
        if (!record->event.pressed) {  // Backspace released: stop repeating
            cancel_deferred_exec(bspc_token);
            bspc_token = INVALID_DEFERRED_TOKEN;
        }
        else if (!bspc_token) {  // Backspace pressed: start repeating
            tap_code(KC_BSPC);  // Initial tap of Backspace key
            rep_count = 0;
            uint32_t bspc_callback(uint32_t trigger_time, void* cb_arg) {
              tap_code(KC_BSPC);
              if (rep_count < sizeof(REP_DELAY_MS)) { ++rep_count; }
              return pgm_read_byte(REP_DELAY_MS - 1 + rep_count);
            }
            bspc_token = defer_exec(INIT_DELAY_MS, bspc_callback, NULL);
        }
        return false;
    // tmux bound key list
    case TMUXLKEY:
        if (record->event.pressed) {
           //send_string(SS_LCTL("b") ":list-keys" SS_TAP(X_ENT));
           send_string(SS_LCTL("b") "?");
        }
        return false;
    // tmux command list
    case TMUXLCMD:
        if (record->event.pressed) {
           send_string_with_delay(SS_LCTL("b") ":",TMUX_DELAY);
           send_string("list-commands\n");
        }
        return false;
    // tmux monitor window activity on
    case TMONON:
        if (record->event.pressed) {
           send_string_with_delay(SS_LCTL("b") ":",TMUX_DELAY);
           send_string("setw monitor-activity on\n");
        }
        return false;
    // tmux monitor window activity off
    case TMONOF:
        if (record->event.pressed) {
           send_string_with_delay(SS_LCTL("b") ":",TMUX_DELAY);
           send_string("setw monitor-activity off\n");
        }
        return false;
    // tmux visual activity alerts on
    case TVISON:
        if (record->event.pressed) {
           send_string_with_delay(SS_LCTL("b") ":",TMUX_DELAY);
           send_string("setw -g visual-activity on\n");
        }
        return false;
    // tmux visual activity alerts off
    case TVISOF:
        if (record->event.pressed) {
           send_string_with_delay(SS_LCTL("b") ":",TMUX_DELAY);
           send_string("setw -g visual-activity off\n");
        }
        return false;
    // tmux move window left 1 position
    case TWINLFT:
        if (record->event.pressed) {
           send_string_with_delay(SS_LCTL("b") ":",TMUX_DELAY);
           send_string("swap-window -t -1\n");
           send_string_with_delay(SS_LCTL("b") "p",TMUX_DELAY);
        }
        return false;
    // tmux move window right 1 position
    case TWINRGT:
        if (record->event.pressed) {
           send_string_with_delay(SS_LCTL("b") ":",TMUX_DELAY);
           send_string("swap-window -t +1\n");
           send_string_with_delay(SS_LCTL("b") "n",TMUX_DELAY);
        }
        return false;
    case TJPANE:
        if (record->event.pressed) {
           send_string_with_delay(SS_LCTL("b") ":",TMUX_DELAY);
           send_string("join-pane -t" SS_TAP(X_SPACE));
        }
        return false;
    // when encoder is pushed, either enable or disable window activity monitor
    case ENC_TMON:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            if (mods & MOD_MASK_CTRL) {
                unregister_mods(MOD_MASK_CTRL);             // remove control
                // turn on window actiivty monitor
                send_string_with_delay(SS_LCTL("b") ":",TMUX_DELAY);
                send_string("setw monitor-activity on\n");
                register_mods(mods);                        // add back mods
            }
            else {
                // turn off window actiivty monitor
                send_string_with_delay(SS_LCTL("b") ":",TMUX_DELAY);
                send_string("setw monitor-activity off\n");
            }
        }
        return false;
    }
    return true;
}

bool process_leader_userspace(void) {
    bool continue_leader_process = false;
    if (leader_sequence_five_keys(KC_C, KC_O, KC_L, KC_O, KC_R)) { // start the color test
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
    else if (leader_sequence_three_keys(KC_P, KC_O, KC_C)) {  // insert test POC data for template
        send_string_with_delay("Firstname" SS_TAP(X_TAB) "Lastname" SS_TAP(X_TAB) "123-456-7890" SS_TAP(X_TAB) "first.last@mail.mil" SS_TAP(X_TAB),10);
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
    else if (leader_sequence_two_keys(KC_U, KC_R)) {          // restart unifi
        SEND_STRING("sudo service unifi restart" SS_TAP(X_ENT));
    }
    else if (leader_sequence_two_keys(KC_U, KC_U)) {          // update unifi
        if (is_mac_base()) {
          SEND_STRING("wget https://get.glennr.nl/unifi/update/unifi-update.sh && sudo bash unifi-update.sh --custom-url " SS_LCMD(SS_TAP(X_V)) SS_TAP(X_ENT));
        }
        else {
          SEND_STRING("wget https://get.glennr.nl/unifi/update/unifi-update.sh && sudo bash unifi-update.sh --custom-url " SS_LCTL(SS_TAP(X_V)) SS_TAP(X_ENT));
        }
    }
    else if (leader_sequence_two_keys(KC_V, KC_H)) {          // open hosts file in vi
        SEND_STRING("sudo vi /etc/hosts" SS_TAP(X_ENT));
    }
    else if (leader_sequence_two_keys(KC_V, KC_A)) {          // open tb authorized in vi
        SEND_STRING("sudo vi /sys/bus/thunderbolt/devices/0-3/authorized" SS_TAP(X_ENT));
    }
    else if (leader_sequence_two_keys(KC_W, KC_C)) {          // automator script to get word count for selected text
        if (is_mac_base()) {
            SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_W))));
        }
        else {
            continue_leader_process = true;
        }
    }
    else if (leader_sequence_two_keys(KC_M, KC_R)) {          // numbers move cell contents right (and 0 current cell)
        if (is_mac_base()) {
            SEND_STRING(SS_LCMD(SS_TAP(X_C)) SS_TAP(X_0) SS_TAP(X_RIGHT) SS_LCMD(SS_TAP(X_V)));
        }
        else {
            continue_leader_process = true;
        }
    }
    else if (leader_sequence_two_keys(KC_M, KC_L)) {          // numbers move cell contents left (and 0 current cell)
        if (is_mac_base()) {
            SEND_STRING(SS_LCMD(SS_TAP(X_C)) SS_TAP(X_0) SS_TAP(X_LEFT) SS_LCMD(SS_TAP(X_V)));
        }
        else {
            continue_leader_process = true;
        }
    }
    else if (leader_sequence_two_keys(KC_S, KC_W)) {          // select word
        if (is_mac_base()) {
            SEND_STRING(SS_LOPT(SS_TAP(X_LEFT) SS_LSFT(SS_TAP(X_RIGHT))));
        }
        else {
            SEND_STRING(SS_LCTL(SS_TAP(X_LEFT) SS_LSFT(SS_TAP(X_RIGHT))));
        }
    }
    else if (leader_sequence_two_keys(KC_S, KC_L)) {          // select line
        SEND_STRING(SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END)));
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
        SEND_STRING("qmk compile -j 0 -kb shortcut/bridge75 -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_three_keys(KC_Q, KC_F, KC_B)) {  // qmk flash shortcutstudio bridge75 firmware
        SEND_STRING("qmk flash -j 0 -kb shortcut/bridge75 -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_three_keys(KC_Q, KC_C, KC_Y)) {  // qmk compile yunzii firmware
        SEND_STRING("qmk compile -j 0 -kb yunzii/al68 -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_three_keys(KC_Q, KC_F, KC_Y)) {  // qmk flash yunzii firmware
        SEND_STRING("qmk flash -j 0 -kb yunzii/al68 -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_three_keys(KC_Q, KC_C, KC_L)) {  // qmk compile lemokey p1 firmware
        SEND_STRING("qmk compile -j 0 -kb lemokey/p1_pro/ansi_encoder -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_three_keys(KC_Q, KC_F, KC_L)) {  // qmk flash lemokey p1 firmware
        SEND_STRING("qmk flash -j 0 -kb lemokey/p1_pro/ansi_encoder -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_four_keys(KC_Q, KC_C, KC_K, KC_V)) {  // qmk compile keychron V6 firmware
        SEND_STRING("qmk compile -j 0 -kb keychron/v6_max/ansi_encoder -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_four_keys(KC_Q, KC_F, KC_K, KC_V)) {  // qmk flash keychron V6 firmware
        SEND_STRING("qmk flash -j 0 -kb keychron/v6_max/ansi_encoder -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_four_keys(KC_Q, KC_C, KC_K, KC_Q)) {  // qmk compile keychron Q6 firmware
        SEND_STRING("qmk compile -j 0 -kb keychron/q6_max/ansi_encoder -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_four_keys(KC_Q, KC_F, KC_K, KC_Q)) {  // qmk flash keychron Q6 firmware
        SEND_STRING("qmk flash -j 0 -kb keychron/q6_max/ansi_encoder -km djcastaldo" SS_TAP(X_ENT));
    }
    else if (leader_sequence_five_keys(KC_A, KC_S, KC_P, KC_D, KC_C)) {  // asp.net decrypt connectionStrings path from clipboard
        send_string_with_delay("C:\\Windows\\Microsoft.NET\\Framework64\\v4.0.30319\\aspnet_regiis -pdf connectionStrings " SS_LCTL(SS_TAP(X_V)) SS_TAP(X_ENT),9);
    }
    else if (leader_sequence_five_keys(KC_A, KC_S, KC_P, KC_E, KC_C)) {  // asp.net encrypt connectionStrings path from clipboard
        send_string_with_delay("C:\\Windows\\Microsoft.NET\\Framework64\\v4.0.30319\\aspnet_regiis -pef connectionStrings " SS_LCTL(SS_TAP(X_V)) SS_TAP(X_ENT),9);
    }
    else if (leader_sequence_five_keys(KC_A, KC_S, KC_P, KC_D, KC_S)) {  // asp.net decrypt sessionState path from clipboard
        send_string_with_delay("C:\\Windows\\Microsoft.NET\\Framework64\\v4.0.30319\\aspnet_regiis -pdf system.web/sessionState " SS_LCTL(SS_TAP(X_V)) SS_TAP(X_ENT),9);
    }
    else if (leader_sequence_five_keys(KC_A, KC_S, KC_P, KC_E, KC_S)) {  // asp.net encrypt sessionState path from clipboard
        send_string_with_delay("C:\\Windows\\Microsoft.NET\\Framework64\\v4.0.30319\\aspnet_regiis -pef system.web/sessionState " SS_LCTL(SS_TAP(X_V)) SS_TAP(X_ENT),9);
    }
    else if (leader_sequence_four_keys(KC_B, KC_O, KC_O, KC_T)) {  // reset to bootloader
        reset_keyboard();
    }
    else {
        continue_leader_process = true;
    }
    return continue_leader_process;
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

void dual_key(uint16_t std_keycode, uint16_t alt_keycode, uint8_t mod_mask) {
    // if mod is being held, send mod_keycode
    // get current mod states
    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();
    if ((mods | oneshot_mods) & mod_mask) {
        unregister_mods(mod_mask);  // remove mod
        tap_code16(alt_keycode);
        register_mods(mods); // restore original mods
    }
    // otherwise send std_keycode
    else {
        tap_code16(std_keycode);
    }
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

void symbol_key_win(const char *alt_code, const char *shift_alt_code) {
    // get current mod states
    const uint8_t mods = get_mods();
    const uint8_t weak_mods = get_weak_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();
    const char *ucode = ((mods | weak_mods | oneshot_mods) & MOD_MASK_SHIFT) ? shift_alt_code : alt_code;
    bool numlockChanged; // this numlock stuff lets this work in all scenarios
    numlockChanged = false;
    clear_mods();
    clear_weak_mods();
    if (ucode == NULL || *ucode == '\0') { // null or empty string
        return;
    }
    if (!host_keyboard_led_state().num_lock) {
         tap_code(KC_NUM);
         numlockChanged = true;
    }
    register_code(KC_LALT); // hold down alt
    type_numpad_keys_from_string(ucode); // send to fn to type numpad keys
    unregister_code(KC_LALT); // release alt
    if (numlockChanged) {
        tap_code(KC_NUM);
    }
    register_mods(mods);
}

void symbol_key_linux(const char *hex_code, const char *shift_hex_code) {
    // get current mod states
    const uint8_t mods = get_mods();
    const uint8_t weak_mods = get_weak_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();
    const char *ucode = ((mods | weak_mods | oneshot_mods) & MOD_MASK_SHIFT) ? shift_hex_code : hex_code;
    if (ucode == NULL || *ucode == '\0') { // null or empty string
        return;
    }
    clear_mods();
    clear_weak_mods();
    tap_code16(C(S(KC_U))); // start the unicode sequence
    // type the hex chars
    send_string_with_delay(ucode,5);
    // finish sequence
    tap_code(KC_SPC);
    register_mods(mods); // add back mods
}

// send_string doesn't use the numpad, so this fn was created to type numbers using the numpad
void type_numpad_keys_from_string(const char *stringnum) {
    // now need to loop through each char in the char pointer until a null terminator
    const char *ptr = stringnum;
    while (*ptr != '\0') {
        switch (*ptr) {
        case '0':
            dprintf("0 tap\n");
            tap_code(KC_P0);
            break;
        case '1':
            dprintf("1 tap\n");
            tap_code(KC_P1);
            break;
        case '2':
            dprintf("2 tap\n");
            tap_code(KC_P2);
            break;
        case '3':
            dprintf("3 tap\n");
            tap_code(KC_P3);
            break;
        case '4':
            dprintf("4 tap\n");
            tap_code(KC_P4);
            break;
        case '5':
            dprintf("5 tap\n");
            tap_code(KC_P5);
            break;
        case '6':
            dprintf("6 tap\n");
            tap_code(KC_P6);
            break;
        case '7':
            dprintf("7 tap\n");
            tap_code(KC_P7);
            break;
        case '8':
            dprintf("8 tap\n");
            tap_code(KC_P8);
            break;
        case '9':
            dprintf("9 tap\n");
            tap_code(KC_P9);
            break;
        default:
            dprintf("no number\n");
            break;
        }
    ptr++;
    }
}
