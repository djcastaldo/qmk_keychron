// @djcastaldo 08-01-2025
// setup to access layers from outside keymap
#pragma once

enum layers {
    MAC_BASE,
    WIN_BASE,
    FN_LAYR,
    SFT_LAYR,
    KCTL_LAYR,
    TMUX_LAYR,
    MSYM_LAYR,
    WSYM_LAYR,
    WIDE_LAYR,
    CIRC_LAYR,
    EMO_LAYR,
    LOCK_LAYR
};

bool dip_switch_update_keymap(uint8_t index, bool active);
