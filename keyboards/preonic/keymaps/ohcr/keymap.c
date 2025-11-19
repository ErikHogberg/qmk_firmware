/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

#include QMK_KEYBOARD_H
#include "muse.h"

enum preonic_layers {
  _QWERTY,
  _RUNIC,
  _ARROWS,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  RUNIC,
  ARROWS,
  LOWER = LT(_LOWER, KC_TAB),
  RAISE = LT(_RAISE, KC_DEL), // IDEA: leader key
  BACKLIT
};

#define FEHU 0x16A0 // ᚠ, f, Frey/wealth
#define URUZ 0x16A2 // ᚢ, u, ox
#define THURISAZ 0x16A6 // ᚦ,th, Thor
#define ANSUZ 0x16A8 // ᚨ, a, Odin
#define RAIDO 0x16B1 // ᚱ, r, riding
#define KAUNAN 0x16B2 // ᚲ, k/c, torch
#define GEBO 0x16B7 // ᚷ, g, gift
#define WUNJO 0x16B9 // ᚹ, w, joy
#define HAGALAZ 0x16BA // ᚺ, h, hail rain
#define NAUDIZ 0x16BE // ᚾ, n, need
#define ISAZ 0x16C1 // ᛁ, i, ice
#define JERA 0x16C3 // ᛃ, j, year
#define EIWAZ 0x16C7 // ᛇ, y, yew-tree
#define PERTH 0x16C8 // ᛈ, p, pear-tree
#define ALGIZ 0x16C9 // ᛉ, z, protection
#define SOWILO 0x16CA // ᛊ, s, sun
#define TIWAZ 0x16CF // ᛏ, t, Tyr/sacrifice
#define BERKANAN 0x16D2 // ᛒ, b, birch-tree
#define EHWAZ 0x16D6 // ᛖ, e, horse
#define MANNAZ 0x16D7 // ᛗ, m, man
#define LAGUZ 0x16DA // ᛚ, l, lake
#define INGWAZ 0x16DC // ᛜ, ng, Yngvi
#define DAGAZ 0x16DE // ᛞ, d, day
#define OTHALA 0x16DF // ᛟ, ᛊo, heritage/estate

#define THINSPACE 0x2009

// wait DELAY ms before unregistering media keys
#define MEDIA_KEY_DELAY 10

// float my_song[][2] = SONG(MARIO_THEME);

// TODO: underglow, with layer indication
// TODO: unicode runes

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-------------------------------------------------------------------------------------.
 * |    `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  Bksp |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|
 * |Tab****|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   \   |
 * |-------+------+------+------+------+-------------+------+------+------+------+-------|
 * |  Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Enter |
 * |-------+------+------+------+------+------|------+------+------+------+------+-------|
 * | Shift |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |  "*** |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|
 * |  Ctrl |   \  |  GUI | Alt  |Lower |    Space    |Raise | Left*| Down |  Up  |Right**|
 * `-------------------------------------------------------------------------------------'
 * *MT(AltGr, Left)
 * **MT(Ctrl, Right)
 * ***MT(Shift, ")
 * ****Rotary encoder (left for shift tab, right for tab, press for tab)
 *
 */
[_QWERTY] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,  KC_5,   KC_6,   KC_7,  KC_8,                  KC_9,    KC_0,    KC_BSPC,               \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,                  KC_O,    KC_P,    KC_BSLS,               \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,                  KC_L,    KC_SCLN, KC_ENT,                \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM,               KC_DOT,  KC_SLSH, MT(MOD_RSFT, KC_QUOT), \
  KC_LCTL, KC_NUBS, KC_LGUI, KC_LALT, LOWER, KC_SPC, KC_SPC, RAISE, MT(MOD_RALT, KC_LEFT), KC_DOWN, KC_UP,   MT(MOD_RCTL, KC_RGHT)  \
),

/* Runic
 * ,-------------------------------------------------------------------------------------.
 * |    `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  Bksp |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|
 * |Tab****|   ᛜ  |   ᚹ  |   ᛖ  |   ᚱ  |   ᛏ  |   ᛇ  |   ᚢ  |   ᛁ  |   ᛟ  |   ᛈ  |   \   |
 * |-------+------+------+------+------+-------------+------+------+------+------+-------|
 * |  Esc  |   ᚨ  |   ᛊ  |   ᛞ  |   ᚠ  |   ᚷ  |   ᚺ  |   ᛃ  |   ᚲ  |   ᛚ  |   ;  | Enter |
 * |-------+------+------+------+------+------|------+------+------+------+------+-------|
 * | Shift |   ᛉ  |   ᚦ  |   ᚲ  |   ᚹ  |   ᛒ  |   ᚾ  |   ᛗ  |   ,  |   .  |   /  |  "*** |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|
 * |  Ctrl |   \  |  GUI | Alt  |Lower |    Space    |Raise | Left*| Down |  Up  |Right**|
 * `-------------------------------------------------------------------------------------'
 * *MT(AltGr, Left)
 * **MT(Ctrl, Right)
 * ***MT(Shift, ")
 * ****Rotary encoder (left for shift tab, right for tab, press for tab)
 *
 */
[_RUNIC] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,       KC_2,         KC_3,       KC_4,      KC_5,         KC_6,          KC_7,       KC_8,                  KC_9,       KC_0,      KC_BSPC,               \
  KC_TAB,  UC(INGWAZ), UC(WUNJO),    UC(EHWAZ),  UC(RAIDO), UC(TIWAZ),    UC(EIWAZ),     UC(URUZ),   UC(ISAZ),              UC(OTHALA), UC(PERTH), KC_BSLS,               \
  KC_ESC,  UC(ANSUZ),  UC(SOWILO),   UC(DAGAZ),  UC(FEHU),  UC(GEBO),     UC(HAGALAZ),   UC(JERA),   UC(KAUNAN),            UC(LAGUZ),  KC_SCLN,   KC_ENT,                \
  KC_LSFT, UC(ALGIZ),  UC(THURISAZ), UC(KAUNAN), UC(WUNJO), UC(BERKANAN), UC(NAUDIZ),    UC(MANNAZ), KC_COMM,               KC_DOT,     KC_SLSH,   MT(MOD_RSFT, KC_QUOT), \
  KC_LCTL, KC_NUBS,    KC_LGUI,      KC_LALT,    LOWER,     UC(THINSPACE),UC(THINSPACE), RAISE,      MT(MOD_RALT, KC_LEFT), KC_DOWN,    KC_UP,     MT(MOD_RCTL, KC_RGHT)  \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |  F1  |  F1  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  | Home |  Up  |  End | PGUP |  Ins | Pause|   _  |   +  |   [  |   ]  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  | Left | Down | Right| PGDN |      |      |   -  |   =  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Prev | Play | Next |      | Back |  Fwd |ISO ~ |ISO | |   -  |   +  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Menu |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 * IDEA: V as leader key
 */
[_LOWER] = LAYOUT_preonic_grid( \
  KC_TAB,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,  \
  KC_CAPS, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_INS,  KC_PAUS, KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_NUHS,  \
  KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, KC_MINS, KC_EQL,  KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_WBAK, KC_WFWD,S(KC_NUHS),S(KC_NUBS),KC_MINS,KC_PLUS,_______, \
  _______, KC_APP,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Mute |RClick|MouseU|LClick|      |      |      |   _  |   +  |  F11 |  F12 | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |MouseL|MouseD|MouseR|      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |ISO # |ISO / | Menu | Menu |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Home | PgDn | PgUp | End |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_DEL,  \
  KC_MUTE, KC_BTN2, KC_MS_U, KC_BTN1, RGB_MOD, RGB_TOG, RGB_M_P, KC_UNDS, KC_PLUS, KC_F11,  KC_F12,   KC_NUHS,  \
  KC_DEL,  KC_MS_L, KC_MS_D, KC_MS_R, RGB_RMOD, RGB_M_B, RGB_M_G, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,  KC_BSLS, \
  _______, _______, _______, _______, _______, _______, RGB_M_SW,KC_NUHS, KC_NUBS, KC_APP,  KC_APP,   _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      | Runic| Term | Term |      | Print|  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|Arrows|Qwerty|Runic | My PC| Calc |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Brite|Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|MusTog|      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |Vol Dn|Vol Up|      |
 * `-----------------------------------------------------------------------------------'
 // [_ADJUST] = LAYOUT_preonic_grid( \
 //   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
 //   _______, RESET,   _______,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, KC_PSCR, KC_DEL,  \
 //   _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, ARROWS, QWERTY,  RUNIC,   KC_MYCM, KC_CALC,  \
 //   BACKLIT, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  MU_TOG,  _______, _______, _______, _______, \
 //   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, _______  \
 // ),
 */

[_ADJUST] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, QK_BOOT, DB_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
  _______, _______, MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______, _______, _______,
  _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Qwerty|      |  Up  |      |      |      |      |      |  Up  |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Left | Down |Right |      |      |      | Left | Down |Right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ARROWS] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  QWERTY, _______,  KC_UP,   _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______, \
  _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
)

};

// void eeconfig_init_user(void) {
//   set_unicode_input_mode(UC_WINC);
// }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case RUNIC:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_RUNIC);
          }
          return false;
          break;
        case ARROWS:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_ARROWS);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          //return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          //return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef __AVR__
            PORTE &= ~(1<<6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            PORTE |= (1<<6);
            #endif
          }
          return false;
          break;
      }
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool clockwise_tab = false;

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (IS_LAYER_ON(_LOWER)) {
      if (clockwise) {
        register_code(KC_WH_D);
        unregister_code(KC_WH_D);
      } else {
        register_code(KC_WH_U);
        unregister_code(KC_WH_U);
      }

    } else if (IS_LAYER_ON(_RAISE)) {
      uint16_t held_keycode_timer = timer_read();
      if (clockwise) {
        register_code(KC_VOLU);
          // thanks to u/mindsound for volume knob fix fix: https://www.reddit.com/r/olkb/comments/9jzbg1/help_with_rotary_encoder_code/?utm_source=amp&utm_medium=comment_list
          while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY) {
            // no-op
          }
        unregister_code(KC_VOLU);
      } else {
        register_code(KC_VOLD);
        while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY) {
          // no-op
        }
        unregister_code(KC_VOLD);
      }

    } else if (IS_LAYER_ON(_ADJUST)) {
        // FIXME: encoder adjust not working, uses lower instead?
        // IDEA: alt+arrow up and down to move lines instead?
      if (clockwise) {
        register_code(KC_DEL);
        unregister_code(KC_DEL);
      } else {
        register_code(KC_BSPC);
        unregister_code(KC_BSPC);
      }

    } else {
      if ((clockwise && clockwise_tab)||(!clockwise && !clockwise_tab)) {
        register_code(KC_TAB);
        unregister_code(KC_TAB);
      } else {
        register_code(KC_LSFT);
        register_code(KC_TAB);
        unregister_code(KC_TAB);
        unregister_code(KC_LSFT);
      }

    }

  }

  return true;
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      break;
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
        #endif
      }
      break;
    case 2:
      break;
    case 3:
      if (active) {
        clockwise_tab = true;
      } else {
        clockwise_tab = false;
      }
      break;
   }
}

void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
