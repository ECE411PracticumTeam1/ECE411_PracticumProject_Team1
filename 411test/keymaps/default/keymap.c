#include QMK_KEYBOARD_H

enum custom_keycodes {
    COPY = SAFE_RANGE,
    ALT_TAB,
    PASTE,
};

bool is_alt_tab_active = false; 
uint16_t alt_tab_timer = 0;     

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │ A │ B │ C │
     * ├───┼───┼───┤
     * │ D │ E │ F │
     * └───┴───┴───┘
     */
    [0] = LAYOUT_ortho_2x3(
        COPY,    PASTE,    ALT_TAB,
        KC_D,    KC_E,    KC_F
    )
};

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {

    render_logo();

    return false;
}

#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case COPY: 
            if(record->event.pressed) {
                SEND_STRING(SS_LCTL("c"));
            }
            break;
        case PASTE:
            if(record->event.pressed) {
                SEND_STRING(SS_LCTL("v"));
            }
            break;
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } 
            else {
                unregister_code(KC_TAB);
            }
            break;
    }
    return true;
}

void matrix_scan_user(void) { 
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
        }
    }
}