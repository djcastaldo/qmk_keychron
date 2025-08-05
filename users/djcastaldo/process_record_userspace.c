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

uint8_t wide_text_mode = WIDE_STANDARD;
bool wide_firstchar = false;

// setup mouse jiggler
deferred_token jiggler_token = INVALID_DEFERRED_TOKEN;
report_mouse_t jiggler_report = {0};
// this was originally a static declaration in the switch case for MK_HOLD, but I also want to use it outside of
// that switch case to do rgb change, so am moving it here.
bool ms_btn_held = false;
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
    static uint32_t key_timer;

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
    // this is a custom version of KC_TRANS to press a key on default layer
    // setup so that I can use LTRANS in the keymap to denote which fallthrough keys get lit up on the layer
    case LTRANS:
        if (record->event.pressed) {
            uint8_t layer = get_highest_layer(layer_state);
            const uint8_t mods = get_mods();
            // prefix to send for the TMUX_LAYR
            if (layer == TMUX_LAYR) {
                unregister_mods(mods); // temp remove mods
                tap_code16(C(KC_B));   // send ctrl-b before keycode processing
                register_mods(mods);   // reapply mods
            }

            // for some wide modes, should start with the spacing char
            if (layer == WIDE_LAYR && wide_firstchar) {
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
                    if (is_mac_base()) {
                        symbol_key_mac("00a6","");
                    }
                    else if (user_config.is_linux_base) {
                        symbol_key_linux("00a6","");
                    }
                    else {
                        symbol_key_win("0166","");
                    }
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
            if (layer == WIDE_LAYR) {
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
                    if (is_mac_base()) {
                        symbol_key_mac("00a6","");
                    }
                    else if (user_config.is_linux_base) {
                        symbol_key_linux("00a6","");
                    }
                    else {
                        symbol_key_win("0166","");
                    }
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
        return false;
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
        return false;
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
        return false;
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
        return false;
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
    case DUAL_PLUSMIN:
        if (record->event.pressed) {
            // standard: plus symbol, while control is held: minus
            dual_key(KC_PPLS, KC_PMNS, MOD_MASK_CTRL);
        }
        return false;
    case DUAL_MULTDIV:
        if (record->event.pressed) {
            // standard: asterisk, while control is held: divide
            dual_key(KC_PAST, KC_PSLS, MOD_MASK_CTRL);
        }
        return false;
    case VI_REPLACE:
        if (record->event.pressed) {
           // start syntax for vi search and replace
           send_string(":%s///g" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
        }
        return false;
    case GIT_ADD:
        if (record->event.pressed) {
           // add updates to git commit
           send_string("git add -A" SS_TAP(X_ENT));
        }
        return false;
    case GIT_COMMIT:
        if (record->event.pressed) {
           // commit changes
           send_string("git commit -m \"\"" SS_TAP(X_LEFT));
        }
        return false;
    case GIT_PUSH:
        if (record->event.pressed) {
           // push commit to git repo
           send_string("git push" SS_TAP(X_ENT));
        }
        return false;
    case GIT_CHKOUT:
        if (record->event.pressed) {
           // checkout last commit from git repo
           send_string("git checkout ." SS_TAP(X_ENT));
        }
        return false;
    case GIT_LOG:
        if (record->event.pressed) {
           // show the git log
           send_string("git log" SS_TAP(X_ENT));
        }
        return false;
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
        break; // this can continue processing
    case MK_ACCEL0:
        tap_code(record->event.pressed ? KC_MS_ACCEL0 : KC_MS_ACCEL1);
        return false;
    case MK_ACCEL2:
        tap_code(record->event.pressed ? KC_MS_ACCEL2 : KC_MS_ACCEL1);
        return false;
    case AP_GLOB:
        // setup for apple globe key to work
        host_consumer_send(record->event.pressed ? AC_NEXT_KEYBOARD_LAYOUT_SELECT : 0);
        return false;
    case KC_MYCM:
        if (is_mac_base() && record->event.pressed) {
            // open new Finder home dir
            tap_code16(LCMD(LSFT(KC_H)));
            return false;
        }
        break;
    case KC_CALC:
        if (is_mac_base() && record->event.pressed) {
            // send command + control + * then delay and then h (setup to open calculator pro)
            send_string(SS_LCTL(SS_LCMD(SS_TAP(X_PAST))) SS_DELAY(35) "h");
            return false;
        }
        break;
    case KC_APP:
        if (is_mac_base() && record->event.pressed) {
            tap_code(KC_LPAD);
            return false;
        }
        break;
    case LOCKSCR:
        if (record->event.pressed) {
           // send control + command + q
           send_string(SS_LCTL(SS_LCMD("q")) SS_DELAY(300) SS_LCTL(SS_LCMD("q")));
        }
        return false;
    case BACKDIR:
        if (record->event.pressed) {
          // command to go back a dir in terminal
          send_string("cd .." SS_TAP(X_ENT));
        }
        return false;
    case HOMEDIR:
        if (record->event.pressed) {
          // command to go home in terminal
          send_string("cd ~" SS_TAP(X_ENT));
        }
        return false;
    case LSLTRAH:
        if (record->event.pressed) {
          // command to ls -ltrah in terminal
          send_string("ls -ltrah" SS_TAP(X_ENT));
        }
        return false;
    // form zoom reset
    case F_ZOOMR:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            clear_mods();
            tap_code16(is_mac_base() ? LCMD(KC_0) : LCTL(KC_0));
            register_mods(mods);
        }
        return false;
    // set up some different zoom (when control is used) so the zoom knob can be used with multiple apps
    // that support different ways to zoom
    case DUAL_ZOOMI:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                if (is_mac_base()) {
                    unregister_mods(MOD_MASK_CTRL);
                    tap_code16(LCMD(KC_EQL));
                    register_mods(mods);
                }
                else {
                    tap_code(KC_EQL);
                }
            }
            else {
                tap_code16(is_mac_base() ? LCMD(KC_MS_WH_DOWN) : LCTL(KC_MS_WH_UP));
            }
        }
        return false;
    case DUAL_ZOOMO:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                if (is_mac_base()) {
                    unregister_mods(MOD_MASK_CTRL);
                    tap_code16(LCMD(KC_MINS));
                    register_mods(mods);
                }
                else {
                    tap_code(KC_MINS);
                }
            }
            else {
                tap_code16(is_mac_base() ? LCMD(KC_MS_WH_UP) : LCTL(KC_MS_WH_DOWN));
            }
        }
        return false;
    case COLORTEST:
        if (record->event.pressed) {
            color_test_timer = timer_read();
            color_test = true;
        }
        return false;
    // the following OPT keycodes mimic a macos option os layer for symbols and accents
    // symbol_key_win() is a fn to type a windows alt code on the numpad
    // symbol_key_linux() uses hex codes to type the same symbols on linux
    case OPT2:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("2122","20ac");
            }
            else {
                symbol_key_win("0153","0128");
            }
        }
        return false;
    case OPT3:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("00a3","2039");
            }
            else {
                symbol_key_win("156","0139");
            }
        }
        return false;
    case OPT4:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("00a2","203a");
            }
            else {
                symbol_key_win("155","0155");
            }
        }
        return false;
    case OPT5:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("221e","fb01");
            }
            else {
                symbol_key_win("236","64257");
            }
        }
        return false;
    case OPT6:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("00a7","fb02");
            }
            else {
                symbol_key_win("21","64258");
            }
        }
        return false;
    case OPT7:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("00b6","2021");
            }
            else {
                symbol_key_win("20","0135");
            }
        }
        return false;
    case OPT8:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("2022","00b0");
            }
            else {
                symbol_key_win("7","248");
            }
        }
        return false;
    case OPT9:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("00aa","00b7");
            }
            else {
                symbol_key_win("166","9");
            }
        }
        return false;
    case OPT0:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("00ba","201a");
            }
            else {
                symbol_key_win("167","0164");
            }
        }
        return false;
    case OPTMIN:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("2013","2014");
            }
            else {
                symbol_key_win("0151","22");
            }
        }
        return false;
    case OPTEQ:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("2260","00b1");
            }
            else {
                symbol_key_win("8800","241");
            }
        }
        return false;
    case OPTQ:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("0153","0152");
            }
            else {
                symbol_key_win("0156","0140");
            }
        }
        return false;
    case OPTW:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("2211","201e");
            }
            else {
                symbol_key_win("228","0132");
            }
        }
        return false;
    case OPTR:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("00ae","2030");
            }
            else {
                symbol_key_win("0174","0137");
            }
        }
        return false;
    case OPTT:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("2020","02c7");
            }
            else {
                symbol_key_win("0134","259");
            }
        }
        return false;
    case OPTY:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("00a5","00c1");
            }
            else {
                symbol_key_win("157","0193");
            }
        }
        return false;
    case OPTO:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("00f8","00d8");
            }
            else {
                symbol_key_win("0248","0216");
            }
        }
        return false;
    case OPTP:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("03c0","03a0");
            }
            else {
                symbol_key_win("227","928");
            }
        }
        return false;
    case OPTLBR:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("201c","201d");
            }
            else {
                symbol_key_win("0147","0148");
            }
        }
        return false;
    case OPTRBR:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("2018","2019");
            }
            else {
                symbol_key_win("0145","0146");
            }
        }
        return false;
    case OPTBSL:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("00ab","00bb");
            }
            else {
                symbol_key_win("174","175");
            }
        }
        return false;
    case OPTA:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("00e5","00c5");
            }
            else {
                symbol_key_win("0229","0197");
            }
        }
        return false;
    case OPTS:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("00df","00cd");
            }
            else {
                symbol_key_win("225","0205");
            }
        }
        return false;
    case OPTD:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("2202","00ce");
            }
            else {
                symbol_key_win("8706","0206");
            }
        }
        return false;
    case OPTF:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("0192","00cf");
            }
            else {
                symbol_key_win("159","0207");
            }
        }
        return false;
    case OPTG:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("00a9","02dd");
            }
            else {
                symbol_key_win("0169","0180");
            }
        }
        return false;
    case OPTH:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("02d9","00d3");
            }
            else {
                symbol_key_win("0183","0211");
            }
        }
        return false;
    case OPTJ:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("2206","00d4");
            }
            else {
                symbol_key_win("30","0212");
            }
        }
        return false;
    case OPTK:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("02da","03f0");
            }
            else {
                symbol_key_win("0186","0208");
            }
        }
        return false;
    case OPTL:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("00ac","00d2");
            }
            else {
                symbol_key_win("170","0210");
            }
        }
        return false;
    case OPTSEM:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("2026","00da");
            }
            else {
                symbol_key_win("0133","0218");
            }
        }
        return false;
    case OPTAPO:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("00e6","00c6");
            }
            else {
                symbol_key_win("0230","0198");
            }
        }
        return false;
    case OPTZ:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("03a9","00b8");
            }
            else {
                symbol_key_win("234","0184");
            }
        }
        return false;
    case OPTX:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("2248","02db");
            }
            else {
                symbol_key_win("247","0215");
            }
        }
        return false;
    case OPTC:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("00e7","00c7");
            }
            else {
                symbol_key_win("0231","0199");
            }
        }
        return false;
    case OPTV:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("221a","25ca");
            }
            else {
                symbol_key_win("251","4");
            }
        }
        return false;
    case OPTB:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("222b","0131");
            }
            else {
                symbol_key_win("8747","0305");
            }
        }
        return false;
    case OPTM:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("03bc","00c2");
            }
            else {
                symbol_key_win("230","0194");
            }
        }
        return false;
    case OPTCOM:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("2264","00af");
            }
            else {
                symbol_key_win("243","0175");
            }
        }
        return false;
    case OPTDOT:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("2265","02d8");
            }
            else {
                symbol_key_win("242","0168");
            }
        }
        return false;
    case OPTSLS:
        if (record->event.pressed) {
            if (user_config.is_linux_base) {
                symbol_key_linux("00f7","00bf");
            }
            else {
                symbol_key_win("0247","168");
            }
        }
        return false;
    case SUITH:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("2665","2661");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("2665","2661");
            }
            else {
                symbol_key_win("3","3");
            }
        }
        return false;
    case SUITD:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("2666","2662");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("2666","2662");
            }
            else {
                symbol_key_win("4","4");
            }
        }
        return false;
    case SUITC:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("2663","2667");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("2663","2667");
            }
            else {
                symbol_key_win("5","5");
            }
        }
        return false;
    case SUITS:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("2660","2664");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("2660","2664");
            }
            else {
                symbol_key_win("6","6");
            }
        }
        return false;
    case SUP1:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("00b9","2074");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("00b9","2074");
            }
            else {
                symbol_key_win("0185","0185");
            }
        }
        return false;
    case SUP2:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("00b2","2075");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("00b2","2075");
            }
            else {
                symbol_key_win("0178","0178");
            }
        }
        return false;
    case SUP3:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("00b3","2076");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("00b3","2076");
            }
            else {
                symbol_key_win("0179","0179");
            }
        }
        return false;
    case NBSP:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("00a0","00a6");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("00a0","00a6");
            }
            else {
                symbol_key_win("0160","0166");
            }
        }
        return false;
    case CIRCL1:
        if (record->event.pressed) {
            // check mods first so can do a double-cirled number if alt is held
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                if (is_mac_base()) {
                    symbol_key_mac("24f5","24f5");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("24f5","24f5");
                }
                else {
                    symbol_key_win("9461","9461");
                }
                register_mods(mods);
            } else {
                if (is_mac_base()) {
                    symbol_key_mac("2460","246a");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("2460","246a");
                }
                else {
                    symbol_key_win("9312","9322");
                }
            }
        }
        return false;
    case CIRCL2:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                if (is_mac_base()) {
                    symbol_key_mac("24f6","24f6");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("24f6","24f6");
                }
                else {
                    symbol_key_win("9462","9462");
                }
                register_mods(mods);
            } else {
                if (is_mac_base()) {
                    symbol_key_mac("2461","246b");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("2461","246b");
                }
                else {
                    symbol_key_win("9313","9323");
                }
            }
        }
        return false;
    case CIRCL3:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                if (is_mac_base()) {
                    symbol_key_mac("24f7","24f7");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("24f7","24f7");
                }
                else {
                    symbol_key_win("9463","9463");
                }
                register_mods(mods);
            } else {
                if (is_mac_base()) {
                    symbol_key_mac("2462","246c");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("2462","246c");
                }
                else {
                    symbol_key_win("9314","9324");
                }
            }
        }
        return false;
    case CIRCL4:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                if (is_mac_base()) {
                    symbol_key_mac("24f8","24f8");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("24f8","24f8");
                }
                else {
                    symbol_key_win("9464","9464");
                }
                register_mods(mods);
            } else {
                if (is_mac_base()) {
                    symbol_key_mac("2463","246d");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("2463","246d");
                }
                else {
                    symbol_key_win("9315","9325");
                }
            }
        }
        return false;
    case CIRCL5:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                if (is_mac_base()) {
                    symbol_key_mac("24f9","24f9");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("24f9","24f9");
                }
                else {
                    symbol_key_win("9465","9465");
                }
                register_mods(mods);
            } else {
                if (is_mac_base()) {
                    symbol_key_mac("2464","246e");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("2464","246e");
                }
                else {
                    symbol_key_win("9316","9326");
                }
            }
        }
        return false;
    case CIRCL6:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                if (is_mac_base()) {
                    symbol_key_mac("24fa","24fa");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("24fa","24fa");
                }
                else {
                    symbol_key_win("9466","9466");
                }
                register_mods(mods);
            } else {
                if (is_mac_base()) {
                    symbol_key_mac("2465","246f");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("2465","246f");
                }
                else {
                    symbol_key_win("9317","9327");
                }
            }
        }
        return false;
    case CIRCL7:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                if (is_mac_base()) {
                    symbol_key_mac("24fb","24fb");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("24fb","24fb");
                }
                else {
                    symbol_key_win("9467","9467");
                }
                register_mods(mods);
            } else {
                if (is_mac_base()) {
                    symbol_key_mac("2466","2470");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("2466","2470");
                }
                else {
                    symbol_key_win("9318","9328");
                }
            }
        }
        return false;
    case CIRCL8:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                if (is_mac_base()) {
                    symbol_key_mac("24fc","24fc");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("24fc","24fc");
                }
                else {
                    symbol_key_win("9468","9468");
                }
                register_mods(mods);
            } else {
                if (is_mac_base()) {
                    symbol_key_mac("2467","2471");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("2467","2471");
                }
                else {
                    symbol_key_win("9319","9329");
                }
            }
        }
        return false;
    case CIRCL9:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                if (is_mac_base()) {
                    symbol_key_mac("24fd","24fd");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("24fd","24fd");
                }
                else {
                    symbol_key_win("9469","9469");
                }
                register_mods(mods);
            } else {
                if (is_mac_base()) {
                    symbol_key_mac("2468","2472");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("2468","2472");
                }
                else {
                    symbol_key_win("9320","9330");
                }
            }
        }
        return false;
    case CIRCL0:
        if (record->event.pressed) {
            const uint8_t mods = get_mods();
            const uint8_t oneshot_mods = get_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                del_oneshot_mods(MOD_MASK_CTRL);
                unregister_mods(MOD_MASK_CTRL);
                if (is_mac_base()) { // this one can do both double circle 10 and a circle 20
                    symbol_key_mac("24fe","2473");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("24fe","2473");
                }
                else {
                    symbol_key_win("9470","9331");
                }
                register_mods(mods);
            } else {
                if (is_mac_base()) {
                    symbol_key_mac("24ea","2469");
                }
                else if (user_config.is_linux_base) {
                    symbol_key_linux("24ea","2469");
                }
                else {
                    symbol_key_win("9450","9321");
                }
            }
        }
        return false;
    case CIRCLQ:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24e0","24c6");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24e0","24c6");
            }
            else {
                symbol_key_win("9440","9414");
            }
        }
        return false;
    case CIRCLW:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24e6","24cc");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24e6","24cc");
            }
            else {
                symbol_key_win("9446","9420");
            }
        }
        return false;
    case CIRCLE:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24d4","24ba");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24d4","24ba");
            }
            else {
                symbol_key_win("9428","9402");
            }
        }
        return false;
    case CIRCLR:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24e1","24c7");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24e1","24c7");
            }
            else {
                symbol_key_win("9441","9415");
            }
        }
        return false;
    case CIRCLT:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24e3","24c9");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24e3","24c9");
            }
            else {
                symbol_key_win("9443","9417");
            }
        }
        return false;
    case CIRCLY:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24e8","24ce");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24e8","24ce");
            }
            else {
                symbol_key_win("9448","9422");
            }
        }
        return false;
    case CIRCLU:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24e4","24ca");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24e4","24ca");
            }
            else {
                symbol_key_win("9444","9418");
            }
        }
        return false;
    case CIRCLI:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24d8","24be");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24d8","24be");
            }
            else {
                symbol_key_win("9432","9406");
            }
        }
        return false;
    case CIRCLO:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24de","24c4");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24de","24c4");
            }
            else {
                symbol_key_win("9438","9412");
            }
        }
        return false;
    case CIRCLP:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24df","24c5");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24df","24c5");
            }
            else {
                symbol_key_win("9439","9413");
            }
        }
        return false;
    case CIRCLA:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24d0","24b6");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24d0","24b6");
            }
            else {
                symbol_key_win("9424","9398");
            }
        }
        return false;
    case CIRCLS:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24e2","24c8");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24e2","24c8");
            }
            else {
                symbol_key_win("9442","9416");
            }
        }
        return false;
    case CIRCLD:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24d3","24b9");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24d3","24b9");
            }
            else {
                symbol_key_win("9427","9401");
            }
        }
        return false;
    case CIRCLF:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24d5","24bb");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24d5","24bb");
            }
            else {
                symbol_key_win("9429","9403");
            }
        }
        return false;
    case CIRCLG:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24d6","24bc");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24d6","24bc");
            }
            else {
                symbol_key_win("9430","9404");
            }
        }
        return false;
    case CIRCLH:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24d7","24bd");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24d7","24bd");
            }
            else {
                symbol_key_win("9431","9405");
            }
        }
        return false;
    case CIRCLJ:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24d9","24bf");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24d9","24bf");
            }
            else {
                symbol_key_win("9433","9407");
            }
        }
        return false;
    case CIRCLK:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24da","24c0");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24da","24c0");
            }
            else {
                symbol_key_win("9434","9408");
            }
        }
        return false;
    case CIRCLL:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24db","24c1");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24db","24c1");
            }
            else {
                symbol_key_win("9435","9409");
            }
        }
        return false;
    case CIRCLZ:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24e9","24cf");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24e9","24cf");
            }
            else {
                symbol_key_win("9449","9423");
            }
        }
        return false;
    case CIRCLX:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24e7","24cd");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24e7","24cd");
            }
            else {
                symbol_key_win("9447","9421");
            }
        }
        return false;
    case CIRCLC:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24d2","24b8");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24d2","24b8");
            }
            else {
                symbol_key_win("9426","9400");
            }
        }
        return false;
    case CIRCLV:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24e5","24cb");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24e5","24cb");
            }
            else {
                symbol_key_win("9445","9419");
            }
        }
        return false;
    case CIRCLB:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24d1","24b7");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24d1","24b7");
            }
            else {
                symbol_key_win("9425","9399");
            }
        }
        return false;
    case CIRCLN:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24dd","24c3");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24dd","24c3");
            }
            else {
                symbol_key_win("9437","9411");
            }
        }
        return false;
    case CIRCLM:
        if (record->event.pressed) {
            if (is_mac_base()) {
                symbol_key_mac("24dc","24c2");
            }
            else if (user_config.is_linux_base) {
                symbol_key_linux("24dc","24c2");
            }
            else {
                symbol_key_win("9436","9410");
            }
        }
        return false;
    case E_SMILE:
	if (record->event.pressed) {
            symbol_key_mac("d83dde00","d83dde06");
	}
	return false;
    case E_SMIRK:
	if (record->event.pressed) {
            symbol_key_mac("d83dde0f","d83dde09");
	}
	return false;
    case E_ASTON:
	if (record->event.pressed) {
            symbol_key_mac("d83dde32","d83dde27");
	}
	return false;
    case E_SAD:
	if (record->event.pressed) {
            symbol_key_mac("d83dde1f","d83dde1e");
	}
	return false;
    case E_CAR:
	if (record->event.pressed) {
            symbol_key_mac("d83dde99","d83ddea2");
	}
	return false;
    case E_BUS:
	if (record->event.pressed) {
            symbol_key_mac("d83dde8e","d83ddee9");
	}
	return false;
    case E_TRAIN:
	if (record->event.pressed) {
            symbol_key_mac("d83dde8a","d83ddeb2");
	}
	return false;
    case E_TAXI:
	if (record->event.pressed) {
            symbol_key_mac("d83dde95","d83ddef4");
	}
	return false;
    case E_FLAGUS:
	if (record->event.pressed) {
            symbol_key_mac("d83cddfad83cddf8","d83cddeed83cddf9");
	}
	return false;
    case E_FLAGPI:
	if (record->event.pressed) {
            symbol_key_mac("d83cddf5d83cdded","d83cdde8d83cddf3");
	}
	return false;
    case E_GLOBE:
	if (record->event.pressed) {
            symbol_key_mac("d83cdf0e","d83cdf10");
	}
	return false;
    case E_PIZZA:
	if (record->event.pressed) {
            symbol_key_mac("d83cdf55","d83cdf69");
	}
	return false;
    case E_BURGER:
	if (record->event.pressed) {
            symbol_key_mac("d83cdf54","d83cdf5f");
	}
	return false;
    case E_CHICKEN:
	if (record->event.pressed) {
            symbol_key_mac("d83cdf57","d83cdf2d");
	}
	return false;
    case E_TACO:
	if (record->event.pressed) {
            symbol_key_mac("d83cdf2e","d83cdf66");
	}
	return false;
    case E_SNAIL:
	if (record->event.pressed) {
            symbol_key_mac("d83ddc0c","26a1");
	}
	return false;
    case E_NINJA:
	if (record->event.pressed) {
            symbol_key_mac("d83edd77","d83ddc88");
	}
	return false;
    case E_STOP:
	if (record->event.pressed) {
            symbol_key_mac("d83dded1","270a");
	}
	return false;
    case E_HAND:
	if (record->event.pressed) {
            symbol_key_mac("d83ddd90","270c");
	}
	return false;
    case E_SHH:
	if (record->event.pressed) {
            symbol_key_mac("d83edd2b","d83dde34");
	}
	return false;
    case E_PACKAGE:
	if (record->event.pressed) {
            symbol_key_mac("d83ddce6","d83ddcec");
	}
	return false;
    case E_POINTU:
	if (record->event.pressed) {
            symbol_key_mac("d83ddc46","2b06fe0f");
	}
	return false;
    case E_POINTD:
	if (record->event.pressed) {
            symbol_key_mac("d83ddc47","2b07fe0f");
	}
	return false;
    case E_POINTL:
	if (record->event.pressed) {
            symbol_key_mac("d83ddc48","2b05fe0f");
	}
	return false;
    case E_POINTR:
	if (record->event.pressed) {
            symbol_key_mac("d83ddc49","27a1fe0f");
	}
	return false;
    case E_DRINK:
	if (record->event.pressed) {
            symbol_key_mac("2615","d83cdf7a");
	}
	return false;
    case E_CMARK:
	if (record->event.pressed) {
            symbol_key_mac("2705","2714");
	}
	return false;
    case E_EMARK:
	if (record->event.pressed) {
            symbol_key_mac("2757","2755");
	}
	return false;
    case E_QMARK:
	if (record->event.pressed) {
            symbol_key_mac("2753","2754");
	}
	return false;
    case E_BULB:
	if (record->event.pressed) {
            symbol_key_mac("d83ddca1","d83edeab");
	}
	return false;
    case E_SSHOT:
	if (record->event.pressed) {
            symbol_key_mac("d83dddbc","d83ddcf8");
	}
	return false;
    case E_MIC:
	if (record->event.pressed) {
            symbol_key_mac("d83cdf99","d83cdfa4");
	}
	return false;
    case E_TRASH:
	if (record->event.pressed) {
            symbol_key_mac("d83dddd1","267bfe0f");
	}
	return false;
    case E_I:
	if (record->event.pressed) {
            symbol_key_mac("2139fe0f","2139");
	}
	return false;
    case E_K0:
	if (record->event.pressed) {
            symbol_key_mac("0030fe0f20e3","D83DDD59");
	}
	return false;
    case E_K1:
	if (record->event.pressed) {
            symbol_key_mac("0031fe0f20e3","D83DDD50");
	}
	return false;
    case E_K2:
	if (record->event.pressed) {
            symbol_key_mac("0032FE0F20E3","D83DDD51");
	}
	return false;
    case E_K3:
	if (record->event.pressed) {
            symbol_key_mac("0033FE0F20E3","D83DDD52");
	}
	return false;
    case E_K4:
	if (record->event.pressed) {
            symbol_key_mac("0034FE0F20E3","D83DDD53");
	}
	return false;
    case E_K5:
	if (record->event.pressed) {
            symbol_key_mac("0035FE0F20E3","D83DDD54");
	}
	return false;
    case E_K6:
	if (record->event.pressed) {
            symbol_key_mac("0036FE0F20E3","D83DDD55");
	}
	return false;
    case E_K7:
	if (record->event.pressed) {
            symbol_key_mac("0037FE0F20E3","D83DDD56");
	}
	return false;
    case E_K8:
	if (record->event.pressed) {
            symbol_key_mac("0038FE0F20E3","D83DDD57");
	}
	return false;
    case E_K9:
	if (record->event.pressed) {
            symbol_key_mac("0039FE0F20E3","D83DDD58");
	}
	return false;
    case E_STAR:
	if (record->event.pressed) {
            symbol_key_mac("002AFE0F20E3","2731");
	}
	return false;
    case E_HASH:
	if (record->event.pressed) {
            symbol_key_mac("0023FE0F20E3","d83ddcf1");
	}
	return false;
    case E_MINS:
	if (record->event.pressed) {
            symbol_key_mac("2796","D83DDD5A");
	}
	return false;
    case E_PLUS:
	if (record->event.pressed) {
            symbol_key_mac("2795","D83DDD5B");
	}
	return false;
    case E_DIV:
	if (record->event.pressed) {
            symbol_key_mac("2797","2716FE0F");
	}
	return false;
    case E_GRIM:
	if (record->event.pressed) {
            symbol_key_mac("d83dde2c","d83dde16");
	}
	return false;
    case E_KB:
	if (record->event.pressed) {
            symbol_key_mac("2328FE0F","D83DDDA5FE0F");
	}
	return false;
    case E_OK:
	if (record->event.pressed) {
            symbol_key_mac("d83ddc4c","d83ddc4d");
	}
	return false;
    case E_SGLASS:
	if (record->event.pressed) {
            symbol_key_mac("d83dde0e","D83DDD76FE0F");
	}
	return false;
    case E_BOTTLE:
	if (record->event.pressed) {
            symbol_key_mac("d83cdf7c","d83cdf7e");
	}
	return false;
    case FLASH_KB:
        if (record->event.pressed) {
           // command to flash this keyboard
           send_string("qmk flash -j 0 -kb " QMK_KEYBOARD " -km " QMK_KEYMAP "\n");
        }
	return false;
    case BOOTLDR:
        if (record->event.pressed) {
            key_timer = timer_read32();
        } else if (timer_elapsed32(key_timer) >= 500) {
            reset_keyboard();
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
