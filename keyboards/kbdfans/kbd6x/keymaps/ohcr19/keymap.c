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
  LOWER = LT(_LOWER, KC_ESC),
  LOWER_APP = LT(_LOWER, KC_APP),
  RAISE = LT(_RAISE, KC_DEL),
  CTRL_R = MT(MOD_RCTL, KC_RGHT),
  RALT_L = MT(MOD_RALT, KC_LEFT),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL, KC_BSPC,
      KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,       KC_BSLS,
      LOWER,         KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,             KC_ENT,
      KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, RAISE,
      KC_LCTL,    KC_LGUI,    KC_LALT,                               KC_SPACE,                             RALT_L,    LOWER_APP,  CTRL_R
  ),

  [_LOWER] = LAYOUT(
      KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
      KC_CAPS,    KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_INS, _______, _______, KC_UP,   _______, _______, _______, _______,       _______,
      _______,       KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,            _______,
      _______,          KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, KC_DOWN,           KC_UP, _______,
      _______,    KC_NUBS,    _______,                               KC_LEAD,                              KC_LEFT,    _______,    KC_RGHT
  ),

  [_RAISE] = LAYOUT(
      KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_DEL,
      _______,    KC_BTN2, KC_MS_U, KC_BTN1, _______, KC_INS, _______, _______, KC_UP,   _______, _______, _______, _______,       KC_INS,
      _______,       KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_NUHS,             _______,
      _______,          _______, _______, _______,  _______, _______,  _______, _______, KC_WBAK, KC_WFWD, KC_WREF,        _______, _______,
      _______,    _______,    _______,                               _______,                               _______,    _______,    _______
  ),

  [_ADJUST] = LAYOUT(
      KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
      _______,    RESET,  DEBUG,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, KC_PSCR, KC_VOLD, KC_VOLU,       KC_MYCM,
      _______,       RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             KC_CALC,
      _______,          BL_DEC, BL_TOGG, BL_INC,  BL_STEP, RGB_VAI,  RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______, _______,
      _______,    _______,    _______,                               _______,                               _______,    _______,    _______
  ),

};

void matrix_init_user(void) {

}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_F) {
      // Anything you can do in a macro.
      SEND_STRING("QMK is awesome.");
    }
    SEQ_TWO_KEYS(KC_D, KC_D) {
      SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    }
    SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
      SEND_STRING("https://start.duckduckgo.com\n");
    }
    // SEQ_TWO_KEYS(KC_A, KC_S) {
    //   register_code(KC_LGUI);
    //   register_code(KC_S);
    //   unregister_code(KC_S);
    //   unregister_code(KC_LGUI);
    // }

    // ctrl bspc
    SEQ_TWO_KEYS(KC_X, KC_X) {
      // SEND_STRING(SS_TAP(C(KC_BSPC)));
      register_code(KC_LCTL);
      register_code(KC_BSPC);
      unregister_code(KC_BSPC);
      unregister_code(KC_LCTL);
    }
    // calculator
    SEQ_TWO_KEYS(KC_C, KC_A) {
      // SEND_STRING(SS_TAP(KC_CALC));
      register_code(KC_CALC);
      unregister_code(KC_CALC);
    }
    // ctrl alt del
    SEQ_THREE_KEYS(KC_C, KC_A, KC_D) {
      // SEND_STRING(SS_TAP(C(A(KC_DEL))));
      register_code(KC_LCTL);
      register_code(KC_LSFT);
      register_code(KC_DEL);
      unregister_code(KC_DEL);
      unregister_code(KC_LSFT);
      unregister_code(KC_LCTL);
    }

  }
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
    case LOWER_APP:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      // return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      // return false;
      break;
  }
  return true;
}

