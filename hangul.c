#include "hangul.h"

const ucschar syllable_base  = 0xac00;
const ucschar choseong_base  = 0x1100;
const ucschar jungseong_base = 0x1161;
const ucschar jongseong_base = 0x11a7;
const int njungseong = 21;
const int njongseong = 28;

int hangul_is_syllable(ucschar c) {
    return c >= 0xac00 && c <= 0xd7a3;
}

int hangul_is_choseong_conjoinable(ucschar c) {
    return c >= 0x1100 && c <= 0x1112;
}

int hangul_is_jungseong_conjoinable(ucschar c) {
    return c >= 0x1161 && c <= 0x1175;
}

int hangul_is_jongseong_conjoinable(ucschar c) {
    return c >= 0x11a7 && c <= 0x11c2;
}

void hangul_syllable_to_jamo(ucschar syllable, ucschar* choseong, ucschar* jungseong, ucschar* jongseong) {
	if (jongseong != 0)
		*jongseong = 0;
	if (jungseong != 0)
		*jungseong = 0;
	if (choseong != 0)
		*choseong = 0;

	if (!hangul_is_syllable(syllable))
		return;

	syllable -= syllable_base;

	if (jongseong != 0) {
		if (syllable % njongseong != 0)
			*jongseong = jongseong_base + syllable % njongseong;
	}
	syllable /= njongseong;

	if (jungseong != 0) {
		*jungseong = jungseong_base + syllable % njungseong;
	}
	syllable /= njungseong;

	if (choseong != 0) {
		*choseong = choseong_base + syllable;
	}
}

ucschar hangul_jamo_to_syllable(ucschar choseong, ucschar jungseong, ucschar jongseong) {
	ucschar c;

    /* we use 0x11a7 like a Jongseong filler */
    if (jongseong == 0)
	jongseong = 0x11a7;         /* Jongseong filler */

    if (!hangul_is_choseong_conjoinable(choseong))
	return 0;
    if (!hangul_is_jungseong_conjoinable(jungseong))
	return 0;
    if (!hangul_is_jongseong_conjoinable(jongseong))
	return 0;

    choseong  -= choseong_base;
    jungseong -= jungseong_base;
    jongseong -= jongseong_base;

    c = ((choseong * njungseong) + jungseong) * njongseong + jongseong
	+ syllable_base;
    return c;
}