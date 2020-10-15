/* Copyright 2018-2019 eswai <@eswai>
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
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif
#include "keymap_jp.h"

// NICOLA親指シフト
#include "nicola.h"
NGKEYS nicola_keys;
// NICOLA親指シフト

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum keymap_layers {
  _QWERTY,
// NICOLA親指シフト
  _NICOLA, // NICOLA親指シフト入力レイヤー
// NICOLA親指シフト
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  KC_QWERTY = NG_SAFE_RANGE,
  KC_EISU,
  KC_LOWER,
  KC_RAISE,
  KC_ADJUST,
  KC_BACKLIT,
  KC_KANA2,
  RGBRST
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define _____ KC_TRNS
#define XXXXX KC_NO
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUITB GUI_T(KC_TAB)
#define KC_RESET RESET
#define KC_ABLS LALT(KC_BSLS)
#define KC_CMDENT  CMD_T(KC_ENT)
#define KC_SFTSPC  LSFT_T(KC_SPC)
#define KC_CTLSPC  CTL_T(KC_SPC)
#define KC_ALTSPC  ALT_T(KC_SPC)
#define KC_CTLBS   CTL_T(KC_BSPC)
#define KC_CTLENT  CTL_T(KC_ENT)
#define KC_CTLESC  CTL_T(KC_ESC)

#define KC_C(A) C(KC_##A)
#define KC_S(A) S(KC_##A)
#define KC_G(A) G(KC_##A)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     CTLESC,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  RALT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RCMD,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER,SFTSPC,CTLSPC,   CMDENT,SFTSPC, RAISE \
                              //`--------------------'  `--------------------'
  ),

// NICOLA親指シフト
  // デフォルトレイヤーに関係なくQWERTYで
  [_NICOLA] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,  NG_Q,  NG_W,  NG_E,  NG_R,  NG_T,                   NG_Y,  NG_U,  NG_I,  NG_O,  NG_P, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  NG_A,  NG_S,  NG_D,  NG_F,  NG_G,                   NG_H,  NG_J,  NG_K,  NG_L,NG_SCLN, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  NG_Z,  NG_X,  NG_C,  NG_V,  NG_B,                   NG_N,  NG_M,NG_COMM,NG_DOT,NG_SLSH, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____,NG_SHFTL, _____,   _____,NG_SHFTR, _____ \
                              //`--------------------'  `--------------------'
  ),
// NICOLA親指シフト


  [_LOWER] = LAYOUT( \
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //             !      @      #      $      %                       :     /                           -
     KC_ESC,JP_EXLM,JP_AT,JP_HASH,JP_DLR,JP_PERC,              JP_COLN,JP_SLSH,JP_LBRC,JP_RBRC,JP_PIPE,JP_MINS, \
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //                                                                                                   +
      KC_NO,  KC_1, KC_2,   KC_3,  KC_4,  KC_5,                   KC_6,  KC_7,  KC_8,  KC_9,  KC_0,JP_PLUS, \
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //             \      |      ~     _       ¥
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,JP_BSLS, \
  //+------+------+------+------+------+------+------+  +------+------+------+------+------+------+------+
                               KC_LOWER, KC_NO,KC_CTLBS,KC_CMDENT,KC_KANA2,KC_RAISE \
  //                            +------+------+------+  +------+------+------+
  ),
  [_RAISE] = LAYOUT_kc( \
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //                           <      >
      _____, XXXXX, XXXXX,    LT,    GT, XXXXX,                  XXXXX,  PGUP,    UP, XXXXX,  PGUP,   DEL,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //             (      )      {      }
      XXXXX,  LPRN,  RPRN,  LCBR,  RCBR, XXXXX,                  XXXXX,  LEFT,  DOWN,  RGHT,  PGDN,  EISU,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //             [      ]
      XXXXX,  LBRC,  RBRC, XXXXX,  COMM, XXXXX,                  XXXXX,  PGDN, XXXXX, XXXXX, XXXXX, KANA2,\
  //+------+------+------+------+------+------+------+  +------+------+------+------+------+------+------+
                                  LOWER, EISU, CTLBS,   CMDENT, XXXXX, RAISE \
  //                            +------+------+------+  +------+------+------+
  ),

  [_ADJUST] = LAYOUT_kc( \
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
       LHUI,  LHUD,  WAKE, XXXXX, RESET, XXXXX,                   LTOG, XXXXX,  VOLU, XXXXX,  BRIU, XXXXX,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
       LSAI,  LSAD, XXXXX, XXXXX, XXXXX, XXXXX,                   LMOD,  MRWD,  VOLD,  MFFD,  BRID, XXXXX,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
       LVAI,  LVAD,  SLEP, XXXXX, XXXXX, XXXXX,                   LRST, XXXXX,  MPLY, XXXXX, XXXXX, XXXXX,\
  //+------+------+------+------+------+------+------+  +------+------+------+------+------+------+------+
                                  LOWER, XXXXX, CTLBS,   CMDENT, XXXXX, RAISE \
  //                            +------+------+------+  +------+------+------+
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
  // NICOLA親指シフト
  set_nicola(_NICOLA);
  // NICOLA親指シフト

  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
      iota_gfx_init(!has_usb());   // turns on the display
  #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case KC_QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case KC_EISU:
      if (record->event.pressed) {
        // NICOLA親指シフト
        nicola_off();
        // NICOLA親指シフト
      }
      return false;
      break;
    case KC_KANA2:
      if (record->event.pressed) {
        // NICOLA親指シフト
        nicola_on();
        // NICOLA親指シフト
      }
      return false;
      break;
    case KC_ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case KC_LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
      return false;
      break;
    case KC_RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
      return false;
      break;
  }

  // NICOLA親指シフト
  bool a = true;
  if (nicola_state()) {
    nicola_mode(keycode, record);
    a = process_nicola(keycode, record);
  }
  if (a == false) return false;
  // NICOLA親指シフト

  return true;
}
