#ifndef HANGUL_H
#define HANGUL_H

#include <stdint.h>

typedef uint32_t ucschar;

int hangul_is_syllable(ucschar c);
int hangul_is_choseong_conjoinable(ucschar c);
int hangul_is_jungseong_conjoinable(ucschar c);
int hangul_is_jongseong_conjoinable(ucschar c);
void hangul_syllable_to_jamo(ucschar syllable, ucschar* choseong, ucschar* jungseong, ucschar* jongseong);
ucschar hangul_jamo_to_syllable(ucschar choseong, ucschar jungseong, ucschar jongseong);

#endif