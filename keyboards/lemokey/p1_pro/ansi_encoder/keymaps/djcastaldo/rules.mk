CONSOLE_ENABLE = yes
KEYBOARD_SHARED_EP = yes
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
KEY_LOCK_ENABLE = yes
LEADER_ENABLE = yes
SRC += features/layer_lock.c
ifneq ("$(wildcard keyboards/lemokey/p1_pro/ansi_encoder/keymaps/djcastaldo/secrets.c)","")
  SRC += secrets.c
endif
ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif
