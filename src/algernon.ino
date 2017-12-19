/* -*- mode: c++ -*-
 * Model01-Sketch -- algernon's Model01 Sketch
 * Copyright (C) 2016, 2017  Gergely Nagy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "00-config.h"

#include <Kaleidoscope.h>

#include "LED-Off.h"
#include <Kaleidoscope-CycleTimeReport.h>
#include <Kaleidoscope-EEPROM-Keymap.h>
#include <Kaleidoscope-EEPROM-Settings.h>
#include <Kaleidoscope-Escape-OneShot.h>
#include <Kaleidoscope-Focus.h>
#include <Kaleidoscope-HostOS.h>
#include <Kaleidoscope/HostOS-select.h>
#include <Kaleidoscope-LED-ActiveModColor.h>
#include <Kaleidoscope-LED-Stalker.h>
#if WITH_WAVEPOOL_EFFECT
# include <Kaleidoscope-LED-Wavepool.h>
#endif
#if WITH_MATRIX_EFFECT
# include <Kaleidoscope-LEDEffect-DigitalRain.h>
#endif
#include <Kaleidoscope-LEDControl.h>
#include <Kaleidoscope-LangPack-Hungarian.h>
#include <Kaleidoscope-Macros.h>
#include <Kaleidoscope-MouseKeys.h>
#include <Kaleidoscope-Steno.h>
#include "MouseWrapper.h"

#include "Layers.h"

#include "Colormap.h"
#include "Focus.h"
#include "Leader.h"
#include "MagicCombo.h"
#include "OneShot.h"
#include "Settings.h"
#include "Syster.h"
#include "TapDance.h"

#include "keymap.h"

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  if (macroIndex == F11) {
    if (!keyToggledOff(keyState))
      return MACRO_NONE;
    return MACRO(T(F11));
  }

  if (!keyToggledOn(keyState))
    return MACRO_NONE;

  switch (macroIndex) {
  case APPSEL_MUSIC ... APPSEL_PWMGR:
    Serial.print(F("appsel:"));
    break;
  }

  switch (macroIndex) {
  case APPSEL_MUSIC:
    Serial.println(F("music"));
    break;
  case APPSEL_CHAT:
    Serial.println(F("chat"));
    break;
  case APPSEL_EMACS:
    Serial.println(F("emacs"));
    break;
  case APPSEL_TERM:
    Serial.println(F("term"));
    break;
  case APPSEL_WEB:
    Serial.println(F("web"));
    break;
  case APPSEL_SOC:
    Serial.println(F("social"));
    break;
  case APPSEL_SOC2:
    Serial.println(F("social2"));
    break;
  case APPSEL_PWMGR:
    Serial.println(F("pwmgr"));
    break;
  }
  return MACRO_NONE;
}

static void emptyLayerForceOff(bool postClear) {
  if (postClear)
    return;

  if (!(KeyboardHardware.leftHandState.all & R3C6) &&
      !(KeyboardHardware.rightHandState.all & R3C9)) {
    Layer.off(_EMPTY);
  }
}

static Key getKey(uint8_t layer, byte row, byte col) {
  if (layer != _EMPTY)
    return EEPROMKeymap.getKey(layer, row, col);

  if (row == 3 && (col == 6 || col == 9))
    return Key_Transparent;

  return Key_NoKey;
}

void setup() {
  Serial.begin(9600);

  Kaleidoscope.setup();

#if WITH_STALKER_EFFECT
  StalkerEffect.variant = STALKER(BlazingTrail);
#endif

  Kaleidoscope.useLoopHook(emptyLayerForceOff);

  Kaleidoscope.use(&LEDOff,
#if WITH_STALKER_EFFECT
                   &StalkerEffect,
#endif
#if WITH_WAVEPOOL_EFFECT
                   &WavepoolEffect,
#endif
#if WITH_MATRIX_EFFECT
                   &LEDDigitalRainEffect,
#endif
                   &HostOS);

  algernon::Settings::configure();
  algernon::Colormap::configure();

  algernon::Leader::configure();
  algernon::TapDance::configure();
  algernon::OneShot::configure();
  algernon::Syster::configure();
  algernon::MagicCombo::configure();

  Kaleidoscope.use(&EscapeOneShot,
#if WITH_STENO
                   &GeminiPR,
#endif
                   &Macros,
                   &Hungarian,
                   &MouseKeys,
                   &ActiveModColorEffect);

  algernon::FocusSetup::configure();

  Layer.getKey = getKey;
  LEDControl.syncDelay = 64;
  MouseWrapper.speedLimit = 64;
  MouseKeys.wheelDelay = 35;

#if WITH_CYCLE_REPORT
  Kaleidoscope.use(&CycleTimeReport);
#endif

  algernon::Settings::seal();
}

#if WITH_CYCLE_REPORT
void cycleTimeReport(void) {
  if (!algernon::Settings::settings.cycleTimer)
    return;

  Serial.print(F("# average loop time: "));
  Serial.println(CycleTimeReport.average_loop_time);
}
#endif

void loop() {
  Kaleidoscope.loop();

  if (algernon::TapDance::cancelOneShot) {
    if (!Layer.isOn(_APPSEL))
      OneShot.cancel();
    algernon::TapDance::cancelOneShot = false;
  }

  if (Layer.isOn(_PLOVER)) {
    LEDControl.set_all_leds_to(CRGB(0x56, 0x80, 0x78));
  }
  if (Layer.isOn(_EMPTY)) {
    LEDControl.set_all_leds_to(CRGB(0x0, 0x0, 0x0));
  }
}
