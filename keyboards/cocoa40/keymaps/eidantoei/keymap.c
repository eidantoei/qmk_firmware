/* Copyright 2019 'Naoto Takai'
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

enum layer_names {
	_BASE,
	_NUMS,
	_SYMS,
	_FN,
};

#define KC_NUMS LT(_NUMS, KC_SPACE)
#define KC_SYMS LT(_SYMS, KC_SPACE)
#define KC_FN MO(_FN)
#define CMD_EISU MT(MOD_LGUI,KC_LANG2)
#define CMD_KANA MT(MOD_RGUI,KC_LANG1)
#define LCTL_ESC MT(MOD_LCTL,KC_ESC)

enum tap_dance {
  TD_SFT_FN,
};

void td_sft_fn_finished(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count == 1) {
    register_code(KC_LSHIFT);
  } else {
    layer_on(_FN);
  }
}

void td_sft_fn_reset(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count == 1) {
    unregister_code(KC_LSHIFT);
  } else {
    layer_off(_FN);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SFT_FN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_sft_fn_finished, td_sft_fn_reset),
};

enum combos {
  SS_WHOLE,
  SS_SELECT
};

const uint16_t PROGMEM ss_whole_combo[] = {KC_TAB, KC_E, COMBO_END};
const uint16_t PROGMEM ss_select_combo[] = {KC_TAB, KC_R, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [SS_WHOLE] = COMBO_ACTION(ss_whole_combo),
  [SS_SELECT] = COMBO_ACTION(ss_select_combo)
};

void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case SS_WHOLE:
      if (pressed) {
        tap_code16(SGUI(KC_3));
      }
      break;
    case SS_SELECT:
      if (pressed) {
        tap_code16(SGUI(KC_4));
      }
      break;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_RBRACKET, KC_BSPACE,
    LCTL_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE, KC_ENTER,
    TD(TD_SFT_FN),KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSHIFT, KC_FN,
    KC_LALT, CMD_EISU, KC_NUMS, KC_SYMS, CMD_KANA, KC_RALT
  ),
  [_NUMS] = LAYOUT(
    KC_TAB, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_BSLASH,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______
  ),
  [_SYMS] = LAYOUT(
    KC_GRAVE, KC_EXCLAIM, KC_AT, KC_HASH, KC_DOLLAR, KC_PERCENT, KC_CIRCUMFLEX, KC_AMPERSAND, KC_ASTERISK, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_MINUS, KC_PLUS, KC_PIPE,
    _______, _______, _______, _______, _______, _______, _______, KC_UP, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______
  ),
  [_FN] = LAYOUT(
    _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DELETE,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_END, KC_PGDN, _______, _______, _______,
    _______, _______, _______, _______, _______, RESET
  ),
};
