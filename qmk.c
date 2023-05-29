int languageMode = 0; // 0 for en, 1 for ko
int isShift = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case LANG:
			if (record->event.pressed) {
				clear_hangul();
				languageMode = (languageMode + 1) % 2;
			}
			return false;
		case KC_A ... KC_Z: //ckeck key press Alpha
			char c = keycode - KC_A;
			if (isShift)
				c += 'A';
			else
				c += 'a';

			if (record->event.pressed) {
				if (languageMode) {
					SEND_STRING(hangul(c)); // put ko
					return false;
				} else  {
					return true; // put en
				}
			}
		case KC_LSFT:
		case KC_RSFT:
			if (record->event.pressed)
				isShift = 1;
			else
				isShift = 0;f
		default: // check every key press except Alpha
			if (record->event.pressed) {
				clear_hangul(); // clear buffer
			}
	}
	return true;
}