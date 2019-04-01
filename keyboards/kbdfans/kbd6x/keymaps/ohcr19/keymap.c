/* Copyright 2018 MechMerlin
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

// #define FN_CAPS LT(_FL, KC_CAPSLOCK)
// #define FN_DEL LT(_FL, KC_DEL)

enum ohcr_kbd6x_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum ohcr_kbd6x_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER = LT(_LOWER, KC_CAPS),
  RAISE = LT(_RAISE, KC_DEL),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,
      KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,       KC_BSLS,
      LOWER,         KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,             KC_ENT,
      KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, RAISE,
      KC_LCTL,    KC_LGUI,    KC_LALT,                               KC_SPACE,                             KC_RALT,    KC_RGUI,    KC_RCTL
  ),

  [_LOWER] = LAYOUT(
      KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_DEL,
      KC_CAPS,    KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, _______, _______, KC_UP,   _______, _______, _______, _______,       _______,
      _______,       KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,             _______,
      _______,          KC_NUBS, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______, _______,          _______, _______,
      _______,    _______,    _______,                               _______,                               _______,    _______,    _______
  ),

  [_RAISE] = LAYOUT(
      KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
      _______,    RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, _______, KC_UP,   _______, _______, _______, _______,       _______,
      _______,       _______, _______, _______, RGB_VAI, _______, RGB_VAD, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,             _______,
      _______,          _______, _______, BL_DEC,  BL_TOGG, BL_INC,  BL_STEP, _______, _______, _______, _______,          _______, _______,
      _______,    _______,    _______,                               _______,                               _______,    _______,    _______
  ),

  [_ADJUST] = LAYOUT(
      KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
      _______,    RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, _______, KC_UP,   _______, _______, _______, _______,       _______,
      _______,       KC_0,  _______, _______, RGB_VAI, _______, RGB_VAD, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,             _______,
      _______,          _______, _______, BL_DEC,  BL_TOGG, BL_INC,  BL_STEP, _______, _______, _______, _______,          _______, _______,
      _______,    _______,    _______,                               _______,                               _______,    _______,    _______
  ),

};

// TODO: iso keys

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
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
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}

