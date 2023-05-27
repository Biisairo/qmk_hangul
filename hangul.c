#include "hangul.h"

const ucschar syllable_base  = 0xac00;
const ucschar choseong_base  = 0x1100;
const ucschar jungseong_base = 0x1161;
const ucschar jongseong_base = 0x11a7;
const int njungseong = 21;
const int njongseong = 28;

ucschar getChoseong(char c) {
	ucschar table_choseong[26] = {
		0x1106, // a
		0x1172, // b
		0x110E, // c
		0x110B, // d
		0x1103, // e
		0x1105, // f
		0x1112, // g
		0x1169, // h
		0x1163, // i
		0x1165, // j
		0x1161, // k
		0x1175, // l
		0x1173, // m
		0x116E, // n
		0x1162, // o
		0x1166, // p
		0x1107, // q
		0x1100, // r
		0x1102, // s
		0x1109, // t
		0x1167, // u
		0x1111, // v
		0x110C, // w
		0x1110, // x
		0x116D, // y
		0x110F, // z
	};

	ucschar table_choseong_ssang[26] = {
		0x1106, // a
		0x1172, // b
		0x110E, // c
		0x110B, // d
		0x1104, // e
		0x1105, // f
		0x1112, // g
		0x1169, // h
		0x1163, // i
		0x1165, // j
		0x1161, // k
		0x1175, // l
		0x1173, // m
		0x116E, // n
		0x1162, // o
		0x1166, // p
		0x1108, // q
		0x1101, // r
		0x1102, // s
		0x1109, // t
		0x1167, // u
		0x1111, // v
		0x110D, // w
		0x1110, // x
		0x116D, // y
		0x110F, // z
	};
	if ('a' <= c && c <= 'z')
		return table_choseong_ssang[c - 'a'];
	return table_choseong_ssang[c - 'A'];
}

ucschar getJongseong(char c) {
	ucschar table_jongseong[26] = {
		0x11B7, // a
		0x1172, // b
		0x11BE, // c
		0x11BC, // d
		0x11AE, // e
		0x11AF, // f
		0x11C2, // g
		0x1169, // h
		0x1163, // i
		0x1165, // j
		0x1161, // k
		0x1175, // l
		0x1173, // m
		0x116E, // n
		0x1162, // o
		0x1166, // p
		0x11B8, // q
		0x11A8, // r
		0x11AB, // s
		0x11BA, // t
		0x1167, // u
		0x11C1, // v
		0x11BD, // w
		0x11C0, // x
		0x116D, // y
		0x11BF, // z
	};

	ucschar table_jongseong_ssang[26] = {
		0x11B7, // a
		0x1172, // b
		0x11BE, // c
		0x11BC, // d
		0x11AE, // e
		0x11AF, // f
		0x11C2, // g
		0x1169, // h
		0x1163, // i
		0x1165, // j
		0x1161, // k
		0x1175, // l
		0x1173, // m
		0x116E, // n
		0x1162, // o
		0x1166, // p
		0x11B8, // q
		0x11A9, // r
		0x11AB, // s
		0x11BB, // t
		0x1167, // u
		0x11C1, // v
		0x11BD, // w
		0x11C0, // x
		0x116D, // y
		0x11BF, // z
	};
	if ('a' <= c && c <= 'z')
		return table_jongseong_ssang[c - 'a'];
	return table_jongseong_ssang[c - 'A'];
}

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