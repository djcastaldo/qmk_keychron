// process_record_userspace.h
// @djcastaldo 07/30/2025
#pragma once

#include "deferred_exec.h"    // required for deferred_token
#include "report.h"           // required for report_mouse_t

extern deferred_token jiggler_token;
extern report_mouse_t jiggler_report;
bool process_record_userspace(uint16_t keycode, keyrecord_t *record);
void jiggle_mouse(void);
