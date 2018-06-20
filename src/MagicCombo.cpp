/* -*- mode: c++ -*-
 * Model01-Sketch -- algernon's Model01 Sketch
 * Copyright (C) 2016, 2017, 2018  Gergely Nagy
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

#include "MagicCombo.h"
#include "Layers.h"
#include "Macros.h"

#include <Kaleidoscope-MagicCombo.h>
#include <Kaleidoscope-LangPack-Hungarian.h>
#include <Kaleidoscope-Macros.h>

enum {
  ADORE,
  CsillaDvorak,
  CsillaADORE,
  Steno,
};

static void toggleADORE(uint8_t combo_index) {
  if (Layer.isOn(_ADORE)) {
    Layer.defaultLayer(_DVORAK);
  } else {
    Layer.defaultLayer(_ADORE);
  }
}

static void togglePlover(uint8_t combo_index) {
  if (Layer.isOn(_PLOVER)) {
    Layer.off(_PLOVER);
  } else {
    Layer.on(_PLOVER);
  }
}

USE_MAGIC_COMBOS(
    [ADORE] = {.action = toggleADORE,
               // palm keys + AD
               .keys = {R3C6, R2C1, R3C9, R2C10}},
    [CsillaDvorak] = {.action = (kaleidoscope::MagicCombo::ComboAction)algernon::Macros::Csilla,
                      .keys = {R3C6, R3C9, R1C12, R2C14}},
    [CsillaADORE] = {.action = (kaleidoscope::MagicCombo::ComboAction)algernon::Macros::Csilla,
                     .keys = {R3C6, R3C9, R1C3, R2C14}},
    [Steno] = {.action = togglePlover,
               .keys = {R0C7, R1C7, R2C7, R3C6, R3C9}});
