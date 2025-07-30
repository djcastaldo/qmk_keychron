$(info >>> LOADING $(USER_PATH) rules.mk <<<)
SECRETS_PATH := $(USER_PATH)/secrets.c
ifneq ("$(wildcard $(SECRETS_PATH))","")
  SRC += $(SECRETS_PATH)
endif
ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif
