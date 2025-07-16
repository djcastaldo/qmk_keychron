CONSOLE_ENABLE = no
KEYBOARD_SHARED_EP = no
FACTORY_TEST_FNJZ_ENABLE = no
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
ifeq ($(strip $(FACTORY_TEST_FNJZ_ENABLE)), yes)
    OPT_DEFS += -DFACTORY_TEST_FNJZ_ENABLE
endif
