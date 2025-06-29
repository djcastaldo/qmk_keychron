CONSOLE_ENBALE = no 
KEYBOARD_SHARED_EP = yes
EXTRAKEY_ENABLE = yes 
MOUSEKEY_ENBALE = yes 
DEFERRED_EXEC_ENABLE = yes 
TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes 
DYNAMIC_MACRO_ENABLE = yes 
KEY_LOCK_ENABLE = yes
LEADER_ENABLE = yes
SRC += features/layer_lock.c
ifneq ("$(wildcard keyboards/keychron/q6_max/ansi_encoder/keymaps/djcastaldo/secrets.c)","")
  SRC += secrets.c
endif
ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif
