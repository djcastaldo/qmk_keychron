$(info >>> LOADING $(USER_PATH) rules.mk <<<)
SRC += users/djcastaldo/features/layer_lock.c
SECRETS_PATH := $(USER_PATH)/secrets.c
ifneq ("$(wildcard $(SECRETS_PATH))","")
  SRC += $(SECRETS_PATH)
endif
ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif
