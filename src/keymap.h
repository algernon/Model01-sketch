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

#pragma once

#include "00-config.h"
#include "Macros.h"

namespace LP = kaleidoscope::language;

#define R(n) (Key){.raw = LP::n}
#define MW(d) Key_mouseWarp ## d
#define MM(d) Key_mouse ## d

enum {
  APPSEL_MUSIC,
  APPSEL_CHAT,
  APPSEL_EMACS,
  APPSEL_TERM,
  APPSEL_WEB,
};

#define Key_AT    LSHIFT(Key_2)
#define Key_STAR  LSHIFT(Key_8)
#define Key_DOLLR LSHIFT(Key_4)
#define Key_CARET LSHIFT(Key_6)
#define Key_PRCNT LSHIFT(Key_5)
#define Key_EXCLM LSHIFT(Key_1)
#define Key_HASH  LSHIFT(Key_3)
#define Key_AND   LSHIFT(Key_7)
#define Key_LCB   LSHIFT(Key_LeftBracket)
#define Key_RCB   LSHIFT(Key_RightBracket)

#define AS_MUS M(APPSEL_MUSIC)
#define AS_CHT M(APPSEL_CHAT)
#define AS_ECS M(APPSEL_EMACS)
#define AS_TRM M(APPSEL_TERM)
#define AS_WEB M(APPSEL_WEB)

#define MS_SUP MM(ScrollUp)
#define MS_SDN MM(ScrollDn)

#define Key_PlayPause Consumer_PlaySlashPause
#define Key_LArrow Key_LeftArrow
#define Key_RArrow Key_RightArrow
#define Key_DnArrow Key_DownArrow
#define Key_PageDn Key_PageDown

#if WITH_PROGMEM_KEYMAP
const Key keymaps[][ROWS][COLS] PROGMEM = {
  [_DVORAK] = KEYMAP_STACKED
  (
    TD(F11)       ,Key_LCB   ,Key_AT    ,Key_STAR   ,Key_DOLLR ,Key_CARET ,TD(TMUX)
   ,Key_Backtick  ,Key_Quote ,Key_Comma ,Key_Period ,Key_P     ,Key_Y     ,TD(LPB)
   ,Key_Tab       ,Key_A     ,Key_O     ,Key_E      ,Key_U     ,Key_I
   ,TD(GUI)       ,Key_Slash ,Key_Q     ,Key_J      ,Key_K     ,Key_X     ,OSM(LeftControl)

   ,TD(COLON)  ,Key_Backspace ,OSM(LeftShift) ,Key_Escape
   ,OSL(_NAV)

   ,TD(TMUXP)    ,Key_PRCNT ,Key_EXCLM ,Key_HASH ,Key_AND ,Key_RCB ,TD(MNP)
   ,TD(RPB)      ,Key_F     ,Key_G     ,Key_C    ,Key_R   ,Key_L   ,Key_Backslash
                 ,Key_D     ,Key_H     ,Key_T    ,Key_N   ,Key_S   ,Key_Equals
   ,OSM(LeftAlt) ,Key_B     ,Key_M     ,Key_W    ,Key_V   ,Key_Z   ,Key_PlayPause

   ,LEAD(MAIN) ,Key_Enter ,Key_Spacebar ,Key_Minus
   ,OSL(_AUX)
  ),

  [_ADORE] = KEYMAP_STACKED
  (
    TD(F11)       ,Key_LCB   ,Key_AT ,Key_STAR ,Key_DOLLR ,Key_CARET ,TD(TMUX)
   ,Key_Backslash ,Key_Quote ,Key_W  ,Key_C    ,Key_H     ,Key_F     ,TD(LPB)
   ,Key_Tab       ,Key_A     ,Key_O  ,Key_E    ,Key_I     ,Key_U
   ,TD(GUI)       ,Key_Z     ,Key_Q  ,Key_X    ,Key_B     ,Key_Comma ,OSM(LeftControl)

   ,TD(COLON)  ,Key_Backspace ,OSM(LeftShift) ,Key_Escape
   ,OSL(_NAV)

   ,TD(TMUXP)    ,Key_PRCNT  ,Key_EXCLM ,Key_HASH ,Key_AND ,Key_RCB   ,TD(MNP)
   ,TD(RPB)      ,Key_M      ,Key_G     ,Key_L    ,Key_P   ,Key_Slash ,Key_Backslash
                 ,Key_D      ,Key_R     ,Key_T    ,Key_N   ,Key_S     ,Key_Equals
   ,OSM(LeftAlt) ,Key_Period ,Key_K     ,Key_V    ,Key_Y   ,Key_J     ,Key_PlayPause

   ,LEAD(MAIN) ,Key_Enter ,Key_Spacebar ,Key_Minus
   ,OSL(_AUX)
  ),

  [_NAV] = KEYMAP_STACKED
  (
    ___ ,Key_F9 ,Key_F7 ,Key_F5 ,Key_F3 ,Key_F1 ,XXX
   ,XXX ,MS_SUP ,MM(Up) ,MS_SDN ,MW(NW) ,MW(NE) ,MW(End)
   ,XXX ,MM(L)  ,MM(Dn) ,MM(R)  ,MW(SW) ,MW(SE)
   ,___ ,XXX    ,XXX    ,XXX    ,XXX    ,XXX    ,XXX

   ,MM(BtnL) ,MM(BtnR) ,___ ,___
   ,___

   ,LGUI(Key_L) ,Key_F10 ,Key_F2     ,Key_F4      ,Key_F6     ,Key_F8 ,XXX
   ,XXX         ,XXX     ,Key_Home   ,Key_UpArrow ,Key_End    ,XXX    ,XXX
                ,XXX     ,Key_LArrow ,Key_DnArrow ,Key_RArrow ,XXX    ,XXX
   ,___         ,XXX     ,Key_PageUp ,XXX         ,Key_PageDn ,XXX    ,XXX

   ,TD(VOLD) ,___ ,___ ,Consumer_VolumeIncrement
   ,OSL(_EMPTY)
  ),

  [_AUX] = KEYMAP_STACKED
  (
    XXX ,XXX       ,XXX        ,XXX       ,XXX        ,XXX       ,XXX
   ,XXX ,XXX       ,R(HUN_ODA) ,XXX       ,R(HUN_UDA) ,XXX       ,XXX
   ,XXX ,R(HUN_AA) ,R(HUN_OA)  ,R(HUN_EA) ,R(HUN_UA)  ,R(HUN_IA)
   ,XXX ,XXX       ,R(HUN_OU)  ,XXX       ,R(HUN_UU)  ,XXX       ,XXX

   ,XXX ,___ ,___ ,___
   ,OSL(_EMPTY)

   ,XXX ,XXX   ,XXX   ,XXX   ,XXX   ,XXX ,XXX
   ,XXX ,XXX   ,Key_7 ,Key_8 ,Key_9 ,XXX ,XXX
        ,Key_0 ,Key_4 ,Key_5 ,Key_6 ,XXX ,XXX
   ,___ ,XXX   ,Key_1 ,Key_2 ,Key_3 ,XXX ,XXX

   ,XXX ,XXX ,XXX ,XXX
   ,___
  ),

  [_APPSEL] = KEYMAP_STACKED
  (
    XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX
   ,XXX

   ,XXX ,XXX ,XXX    ,XXX    ,XXX    ,XXX ,XXX
   ,XXX ,XXX ,XXX    ,XXX    ,XXX    ,XXX ,XXX
        ,XXX ,AS_TRM ,AS_ECS ,AS_WEB ,XXX ,XXX
   ,XXX ,XXX ,AS_MUS ,XXX    ,AS_CHT ,XXX ,XXX

   ,XXX ,XXX ,XXX ,XXX
   ,XXX
  ),

  [_PLOVER] = KEYMAP_STACKED
  (  XXX    ,XXX   ,XXX   ,XXX   ,XXX   ,XXX    ,S(N6)
    ,XXX    ,S(N1) ,S(N2) ,S(N3) ,S(N4) ,S(N5)  ,S(ST1)
    ,S(FN)  ,S(S1) ,S(TL) ,S(PL) ,S(HL) ,S(ST1)
    ,S(PWR) ,S(S2) ,S(KL) ,S(WL) ,S(RL) ,S(ST2) ,S(ST2)

    ,S(A)   ,S(O)  ,XXX   ,S(RE1)
    ,XXX

    ,S(N7)  ,XXX    ,XXX   ,XXX   ,XXX   ,XXX   ,XXX
    ,S(ST3) ,S(N8)  ,S(N9) ,S(NA) ,S(NB) ,S(NC) ,XXX
    ,S(ST3) ,S(FR)  ,S(PR) ,S(LR) ,S(TR) ,S(DR)
    ,S(ST4) ,S(ST4) ,S(RR) ,S(BR) ,S(GR) ,S(SR) ,S(ZR)

    ,S(RE2) ,XXX    ,S(E)  ,S(U)
    ,XXX),

#if 0
  // This is here for reference only, this layer is implemented in the getKey
  // function instead.
  [_EMPTY] = KEYMAP_STACKED
  (
    XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX
   ,___

   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
        ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX

   ,XXX ,XXX ,XXX ,XXX
   ,___
  ),
#endif
};
#else
const Key keymaps[][ROWS][COLS] PROGMEM = {
};
#endif
