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

#include "SymUnI.h"
#include <Kaleidoscope-Unicode.h>
#include <Kaleidoscope-LED-AlphaSquare.h>

namespace algernon {
namespace SymUnI {

static const struct {
  const char *symbol;
  uint32_t code;
} symbol_map[] PROGMEM = {
  {"coffee", 0x2615},
  {"lambda", 0x03bb},
  {"poop", 0x1f4a9},
  {"rofl", 0x1f923},
  {"kiss", 0x1f619},
  {"snowman", 0x2603},
  {"heart", 0x2764},
  {"bolt", 0x26a1},
  {"pi", 0x03c0},
  {"mouse", 0x1f401},
  {"micro", 0x00b5},
  {"tm", 0x2122},
  {"family", 0x1f46a},
  {"child", 0x1f476},
  {"ok", 0x2713}
};

void input(const char *symbol) {
  uint32_t code = 0;
  bool lambda = false;

  for (uint8_t i = 0; i < sizeof(symbol_map) / sizeof(symbol_map[0]); i++) {
    const char *map_symbol = (const char *)pgm_read_word(&symbol_map[i].symbol);
    if (strcmp(symbol, map_symbol) == 0) {
      code = pgm_read_dword(&symbol_map[i].code);
      break;
    }
  }

  if (code)
    Unicode.type(code);
  else
    typeString(symbol);

  if (lambda) {
    AlphaSquare.display(kaleidoscope::alpha_square::symbols::Lambda);
    delay(500);
    AlphaSquare.clear(kaleidoscope::alpha_square::symbols::Lambda);
  }
}

void typeString(const char *str) {
  Unicode.start();

  for (uint8_t i = 0; str[i]; i++) {
    const char c = str[i];
    Key key = Key_NoKey;

    switch (c) {
    case 'a' ... 'z':
      key.keyCode = Key_A.keyCode + (c - 'a');
      break;
    case 'A' ... 'Z':
      key.keyCode = Key_A.keyCode + (c - 'A');
      break;
    case '1' ... '9':
      key.keyCode = Key_1.keyCode + (c - '1');
      break;
    case '0':
      key.keyCode = Key_0.keyCode;
      break;
    }

    Unicode.input();
    handleKeyswitchEvent(key, 255, 255, IS_PRESSED | INJECTED);
    Keyboard.sendReport();
    Unicode.input();
    handleKeyswitchEvent(key, 255, 255, WAS_PRESSED | INJECTED);
    Keyboard.sendReport();
  }
  Unicode.end();
}

}
}
